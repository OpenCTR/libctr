/*
 *******************************************************************************
 * libctr - Library for Nintendo 3DS homebrew.
 *
 * Copyright (C) 2015, OpenCTR Contributors.
 *
 * This file is part of libctr.
 *
 * libctr is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3 as published by
 * the Free Software Foundation.
 *
 * libctr is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libctr. If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************
*/

#include <fcntl.h>

#include "ctr/atomic.h"

#include "ctr/base_private.h"
#include "ctr/sys_private.h"
#include "ctr/error_private.h"
#include "ctr/fs_private.h"

extern int ctrFsSdmcMount(CtrFsContextData* context);

static void ctrFsInit(void) CTR_INIT;
static void ctrFsExit(void) CTR_FINI;

CtrFsContextData* CTR_FS_THIS = NULL;

static void ctrFsInit(void) {
    int ret;

    CTR_FS_THIS = ctrFsContextDataNew();
    if(CTR_FS_THIS == NULL) {
        sys_debug_printf("Error allocating FS context: 0x%08x\n", cerror());
        sys_process_exit();
    }

    ret = ctrFsContextMount(CTR_FS_THIS, CTR_FS_ARCHIVE_SDMC);
    if(ret != 0) {
        sys_debug_printf("Error mounting SDMC: 0x%08x\n", cerror());
        sys_process_exit();
    }
}

static void ctrFsExit(void) {
    ctrFsContextDataFree(CTR_FS_THIS);
}

int ctrFsOpen(CtrFsContextData* context, int* fd, const char* path, int flags) {
    int ret;
    uint32_t* cmdbuf = NULL;
    uint32_t i;

    if(context == NULL) {
        cerror_set(EINVAL);
        return -1;
    } else if(fd == NULL) {
        cerror_set(EFAULT);
        return -1;
    } else if(path == NULL) {
        cerror_set(EFAULT);
        return -1;
    }

    if(context->archive == 0) {
        /* TODO: CTR_FS_NOT_MOUNTED. */
        cerror_set(EFAULT);
        return -1;
    }

    const int len = strlen(path) + 1;
    if(len <= 1) {
        cerror_set(EFAULT);
        return -1;
    }

    /**
     * @todo Check if NAND mode. If true, replace cmdbuf[2].
     * Current behavior: Use SDMC for all files.
     * Future: Use SDMC by default, allow switching between SDMC/NAND.
     */

    cmdbuf = sys_get_commandbuffer();

    cmdbuf[0] = 0x08030204;
    cmdbuf[1] = 0x00000000;
    cmdbuf[2] = context->archive;
    cmdbuf[3] = 0x00000001;
    cmdbuf[4] = 0x00000000;
    cmdbuf[5] = 0x00000003;
    cmdbuf[6] = len;
    cmdbuf[7] = flags;
    cmdbuf[8] = 0x00000000;  // attributes
    cmdbuf[9] = ((0x00000000 << 0x0E) | 0x00000802);
    cmdbuf[10] = (uint32_t)((uint8_t*)"");
    cmdbuf[11] = ((len << 0x0E) | 0x02);
    cmdbuf[12] = (uint32_t)path;

    ret = sys_send_sync_request(context->handle);
    if(ret != 0) {
        cerror_set(ret);
        return -1;
    }

    ret = cmdbuf[1];
    if(ret != 0) {
        cerror_set(ret);
        return -1;
    }

    /* Add the new file to the list of files. */
    for(i = 0; i < CTR_FS_HANDLES_MAX; i++) {
        if(context->files[i].handle != 0) {
            context->files[i].handle = cmdbuf[3];
            context->files[i].flags = (flags & (O_ACCMODE | O_APPEND | O_SYNC));
            context->files[i].offset = 0x00;
            break;
        }
    }

    if(fd != NULL) {
        *fd = cmdbuf[3];
    }

    return 0;
}

int ctrFsRead(CtrFsContextData* context,
              int fd,
              void* buffer,
              uint64_t size,
              uint64_t* osize) {
    uint32_t* cmdbuf = NULL;
    int ret;
    uint32_t i;
    uint64_t offset = 0;

    if(context == NULL) {
        cerror_set(EINVAL);
        return -1;
    }

    /* Find the files' current offset. */
    for(i = 0; i < CTR_FS_HANDLES_MAX; i++) {
        if(context->files[i].handle == fd) {
            offset = context->files[i].offset;
            break;
        }
    }

    cmdbuf = sys_get_commandbuffer();

    cmdbuf[0] = 0x080200C2;
    cmdbuf[1] = (uint32_t)(offset);
    cmdbuf[2] = (uint32_t)(offset >> 32);
    cmdbuf[3] = (uint32_t)(size);
    cmdbuf[4] = ((size << 0x04) | 0x0C);
    cmdbuf[5] = ((uint32_t)buffer);

    ret = sys_send_sync_request(fd);
    if(ret != 0) {
        cerror_set(ret);
        return -1;
    }

    ret = cmdbuf[1];
    if(ret != 0) {
        cerror_set(ret);
        return -1;
    }

    /* Change the file offset. */
    for(i = 0; i < CTR_FS_HANDLES_MAX; i++) {
        if(context->files[i].handle == fd) {
            context->files[i].offset += cmdbuf[2];
            break;
        }
    }

    if(osize != NULL) {
        *osize = cmdbuf[2];
    }

    return 0;
}

int ctrFsWrite(CtrFsContextData* context,
               int fd,
               const void* buffer,
               uint64_t size,
               uint64_t* osize) {
    uint32_t* cmdbuf = NULL;
    int ret;
    uint32_t i;
    uint64_t offset = 0;

    if(context == NULL) {
        cerror_set(EINVAL);
        return -1;
    }

    /* Find the files' current offset. */
    for(i = 0; i < CTR_FS_HANDLES_MAX; i++) {
        if(context->files[i].handle == fd) {
            offset = context->files[i].offset;
            break;
        }
    }

    cmdbuf = sys_get_commandbuffer();

    cmdbuf[0] = 0x08030102;
    cmdbuf[1] = (uint32_t)(offset);
    cmdbuf[2] = (uint32_t)(offset >> 32);
    cmdbuf[3] = (uint32_t)(size);
    cmdbuf[4] = (0x00000000);
    cmdbuf[5] = ((size << 0x04) | 0x0A);
    cmdbuf[6] = (uint32_t)buffer;

    ret = sys_send_sync_request(fd);
    if(ret != 0) {
        cerror_set(ret);
        return -1;
    }

    ret = cmdbuf[1];
    if(ret != 0) {
        cerror_set(ret);
        return -1;
    }

    /* Change the file offset. */
    for(i = 0; i < CTR_FS_HANDLES_MAX; i++) {
        if(context->files[i].handle == fd) {
            context->files[i].offset += cmdbuf[2];
            break;
        }
    }

    if(osize != NULL) {
        *osize = cmdbuf[2];
    }

    return 0;
}

int ctrFsClose(CtrFsContextData* context, int fd) {
    uint32_t* cmdbuf = NULL;
    int ret;
    uint32_t i;

    if(context == NULL) {
        cerror_set(EINVAL);
        return -1;
    }

    cmdbuf[0] = 0x08080000;

    ret = sys_send_sync_request(fd);
    if(ret != 0) {
        cerror_set(ret);
        return -1;
    }

    ret = cmdbuf[1];
    if(ret != 0) {
        cerror_set(ret);
        return -1;
    }

    ret = sys_close_handle(fd);
    if(ret != 0) {
        cerror_set(ret);
        return -1;
    }

    /* Remove the file from the list. */
    for(i = 0; i < CTR_FS_HANDLES_MAX; i++) {
        if(context->files[i].handle == fd) {
            memset(&context->files[i], 0x00, sizeof(CtrFsFile));
            break;
        }
    }

    return 0;
}

/* Stubs */
int ctrFsOpendir(CtrFsContextData* context, int* fd, const char* path) {
    return -1;
}

int ctrFsReaddir(CtrFsContextData* context, int fd, CtrFsDirent* dir) {
    return -1;
}

int ctrFsClosedir(CtrFsContextData* context, int fd) {
    return -1;
}

int ctrFsStat(CtrFsContextData* context, const char* path, CtrFsStat* st) {
    return -1;
}

int ctrFsFstat(CtrFsContextData* context, int fd, CtrFsStat* st) {
    return -1;
}

int ctrFsMkdir(CtrFsContextData* context, const char* path, CtrFsMode mode) {
    return -1;
}

int ctrFsRename(CtrFsContextData* context,
                const char* source,
                const char* dest) {
    return -1;
}

int ctrFsRmdir(CtrFsContextData* context, const char* path) {
    return -1;
}

int ctrFsUnlink(CtrFsContextData* context, const char* path) {
    return -1;
}

int ctrFsLseek(CtrFsContextData* context,
               int fd,
               int64_t offset,
               CtrFsOrigin origin,
               uint64_t* pos) {
    return -1;
}

int ctrFsFsync(CtrFsContextData* context, int fd) {
    return -1;
}

int ctrFsSdmcStatus(CtrFsContextData* context, CtrFsStatus* status) {
    return -1;
}

int ctrFsTruncate(CtrFsContextData* context, const char* path, uint64_t size) {
    return -1;
}

int ctrFsFtruncate(CtrFsContextData* context, int fd, uint64_t size) {
    return -1;
}

int ctrFsGetAvailableSize(CtrFsContextData* context,
                          uint64_t* sdmc_size,
                          uint64_t* nand_size) {
    return -1;
}

CtrFsContextData* ctrFsContextDataNew(void) {
    int ret;
    CtrFsContextData* context = NULL;
    uint32_t* cmdbuf = NULL;

    context = (CtrFsContextData*)malloc(sizeof(struct CtrFsContextDataPrivate));
    if(context == NULL) {
        cerror_set(ENOMEM);
        return NULL;
    }

    memset(context, 0x00, sizeof(struct CtrFsContextDataPrivate));

    ret = sys_service_get_handle(&context->handle, "fs:USER");
    if(ret != 0) {
        cerror_set(ret);
        return NULL;
    }

    cmdbuf = sys_get_commandbuffer();

    cmdbuf[0] = 0x08010002;
    cmdbuf[1] = 0x00000020;

    ret = sys_send_sync_request(context->handle);
    if(ret != 0) {
        cerror_set(ret);
        return NULL;
    }

    ret = cmdbuf[1];
    if(ret != 0) {
        cerror_set(ret);
        return NULL;
    }

    memset(context->files, 0x00, sizeof(CtrFsFile) * CTR_FS_HANDLES_MAX);

    return context;
}

void ctrFsContextDataFree(CtrFsContextData* context) {
    uint8_t i;

    if(context == NULL) {
        cerror_set(EINVAL);
        return;
    }

    sys_close_handle(context->handle);

    free(context);
}

int ctrFsContextMount(CtrFsContextData* context, CtrFsArchiveType type) {
    int ret;

    if(context == NULL) {
        cerror_set(EINVAL);
        return -1;
    }

    switch(type) {
        case CTR_FS_ARCHIVE_SDMC:
            context->archive = CTR_FS_ARCHIVE_SDMC;
            ret = 0;
            break;
        default:
            /* TODO: CTR_ERROR_UNSUPPORTED_ARCHIVE */
            ret = EINVAL;
            break;
    }

    if(ret != 0) {
        cerror_set(ret);
        return -1;
    }

    return 0;
}

int ctrFsMount(CtrFsContextData* context) {
    int ret;

    if(context == NULL) {
        cerror_set(EINVAL);
        return -1;
    }

    /* Check if the context is already mounted. */
    if(ctrAtomicRead(&context->mounted) == 1) {
        /* TODO: CTR_ERROR_ALREADY_MOUNTED. */
        return 0;
    }

    /* Mark as mounted. */
    ctrAtomicStore(&context->mounted, 1);

    switch(context->archive) {
        case CTR_FS_ARCHIVE_SDMC:
            ret = ctrFsSdmcMount(context);
            break;
        default:
            /* TODO: CTR_ERROR_UNSUPPORTED_ARCHIVE */
            ret = EINVAL;
            break;
    }

    if(ret != 0) {
        ctrAtomicStore(&context->mounted, 0);
        cerror_set(ret);
        return -1;
    }

    return 0;
}
