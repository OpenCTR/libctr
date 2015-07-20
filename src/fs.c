/*
 * libctr - Library for Nintendo 3DS homebrew.
 *
 * Copyright (C) 2015 The OpenCTR Project.
 *
 * This file is part of libctr.
 *
 * libctr is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * libctr is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libctr. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ctr/base_private.h"
#include "ctr/sys_private.h"
#include "ctr/error_private.h"
#include "ctr/fs_private.h"

#define CTR_FS_SDMC (0x00000009)

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
}

static void ctrFsExit(void) {
    ctrFsContextDataFree(CTR_FS_THIS);
}

int ctrFsOpen(CtrFsContextData* context, int* fd, const char* path, int flags) {
    int ret;
    uint32_t* cmdbuf = NULL;

    if(context == NULL) {
        (*cerrorptr()) = EINVAL;
        return -1;
    } else if(fd == NULL) {
        (*cerrorptr()) = EFAULT;
        return -1;
    } else if(path == NULL) {
        (*cerrorptr()) = EFAULT;
        return -1;
    }

    const int len = strlen(path) + 1;
    if(len <= 1) {
        (*cerrorptr()) = EFAULT;
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
    cmdbuf[2] = CTR_FS_SDMC;
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
        (*cerrorptr()) = ret;
        return -1;
    }

    ret = cmdbuf[1];
    if(ret != 0) {
        (*cerrorptr()) = ret;
        return -1;
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

    if(context == NULL) {
        (*cerrorptr()) = EINVAL;
        return -1;
    }

    // TODO: Get offset.
    const uint64_t offset = 0;

    cmdbuf = sys_get_commandbuffer();

    cmdbuf[0] = 0x080200C2;
    cmdbuf[1] = (uint32_t)(offset);
    cmdbuf[2] = (uint32_t)(offset >> 32);
    cmdbuf[3] = (uint32_t)(size);
    cmdbuf[4] = ((size << 0x04) | 0x0C);
    cmdbuf[5] = ((uint32_t)buffer);

    ret = sys_send_sync_request(fd);
    if(ret != 0) {
        (*cerrorptr()) = ret;
        return -1;
    }

    ret = cmdbuf[1];
    if(ret != 0) {
        (*cerrorptr()) = ret;
        return -1;
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

    if(context == NULL) {
        (*cerrorptr()) = EINVAL;
        return -1;
    }

    const uint64_t offset = 0;

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
        (*cerrorptr()) = ret;
        return -1;
    }

    ret = cmdbuf[1];
    if(ret != 0) {
        (*cerrorptr()) = ret;
        return -1;
    }

    if(osize != NULL) {
        *osize = cmdbuf[2];
    }

    return 0;
}

int ctrFsClose(CtrFsContextData* context, int fd) {
    uint32_t* cmdbuf = NULL;
    int ret;

    if(context == NULL) {
        (*cerrorptr()) = EINVAL;
        return -1;
    }

    cmdbuf[0] = 0x08080000;

    ret = sys_send_sync_request(fd);
    if(ret != 0) {
        (*cerrorptr()) = ret;
        return -1;
    }

    ret = cmdbuf[1];
    if(ret != 0) {
        (*cerrorptr()) = ret;
        return -1;
    }

    sys_close_handle(fd);

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
        (*cerrorptr()) = ENOMEM;
        return NULL;
    }

    memset(context, 0x00, sizeof(struct CtrFsContextDataPrivate));

    ret = sys_service_get_handle(&context->handle, "fs:USER");
    if(ret != 0) {
        (*cerrorptr()) = ret;
        return NULL;
    }

    cmdbuf = sys_get_commandbuffer();

    cmdbuf[0] = 0x08010002;
    cmdbuf[1] = 0x00000020;

    ret = sys_send_sync_request(context->handle);
    if(ret != 0) {
        (*cerrorptr()) = ret;
        return NULL;
    }

    ret = cmdbuf[1];
    if(ret != 0) {
        (*cerrorptr()) = ret;
        return NULL;
    }

    return context;
}

void ctrFsContextDataFree(CtrFsContextData* context) {
    uint8_t i;

    if(context == NULL) {
        (*cerrorptr()) = EINVAL;
        return;
    }

    sys_close_handle(context->handle);

    free(context);
}
