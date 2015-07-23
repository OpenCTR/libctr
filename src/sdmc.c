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

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dirent.h>
#include <sys/iosupport.h>
#include <sys/param.h>
#include <unistd.h>

#if 0
static char __cwd[PATH_MAX+1] = "/";
static char __fixedpath[PATH_MAX+1];
static uint16_t __utf16path[PATH_MAX+1];

/*
 * Originally from ctrulib.
 */
static ssize_t decode_utf8(uint32_t* out, const uint8_t* in) {
    uint8_t code1;
    uint8_t code2;
    uint8_t code3;
    uint8_t code4;

    code1 = *in++;
    if(code1 < 0x80) {
        /* 1-byte sequence */
        *out = code1;
        return 1;
    } else if(code1 < 0xC2) {
        return -1;
    } else if(code1 < 0xE0) {
        /* 2-byte sequence */
        code2 = *in++;
        if((code2 & 0xC0) != 0x80) {
            return -1;
        }
        *out = (code1 << 6) + code2 - 0x3080;
        return 2;
    } else if(code1 < 0xF0) {
        /* 3-byte sequence */
        code2 = *in++;
        if((code2 & 0xC0) != 0x80) {
            return -1;
        } else if(code1 == 0xE0 && code2 < 0xA0) {
            return -1;
        }
        code3 = *in++;
        if((code3 & 0xC0) != 0x80) {
            return -1;
        }
        *out = (code1 << 12) + (code2 << 6) + code3 - 0xE2080;
        return 3;
    } else if(code1 < 0xF5) {
        /* 4-byte sequence */
        code2 = *in++;
        if((code2 & 0xC0) != 0x80) {
            return -1;
        } else if(code1 == 0xF0 && code2 < 0x90) {
            return -1;
        } else if(code1 == 0xF4 && code2 >= 0x90) {
            return -1;
        }

        code3 = *in++;
        if((code3 & 0xC0) != 0x80) {
            return -1;
        }

        code4 = *in++;
        if((code4 & 0xC0) != 0x80) {
            return -1;
        }

        *out = (code1 << 18) + (code2 << 12) + (code3 << 6) + code4 - 0x3C82080;
        return 4;
    }

    return -1;
}

static const char* sdmc_fixpath(struct _reent* r, const char* path) {
    size_t units;
    uint32_t code;
    const uint8_t* p = NULL;

    p = (const uint8_t*)path;

    /* Move the path pointer to the start of the actual path. */
    do {
        units = decode_utf8(&code, p);
        if(units == (size_t)-1) {
            r->_errno = EILSEQ;
            return NULL;
        }
        p += units;
    } while(code != ':' && code != 0);

    /* We found a colon -- p points to the actual path. */
    if(code == ':') {
        path = (const char*)p;
    }

    /*
     * Make sure there are no more colons and that the
     * remainder of the filename is valid UTF-8.
     */
    p = (const uint8_t*)path;
    do {
        units = decode_utf8(&code, p);
        if(units == (size_t)-1) {
            r->_errno = EILSEQ;
            return NULL;
        } else if(code == ':') {
            r->_errno = EINVAL;
            return NULL;
        }
        p += units;
    } while(code != 0);

    if(path[0] == '/') {
        strncpy(__fixedpath, path, PATH_MAX+1);
    } else {
        strncpy(__fixedpath, __cwd, PATH_MAX+1);
        strncat(__fixedpath, path, PATH_MAX+1);
    }

    if(__fixedpath[PATH_MAX] != 0) {
        __fixedpath[PATH_MAX] = 0;
        r->_errno = ENAMETOOLONG;
        return NULL;
    }

    return __fixedpath;
}

#endif


/**
 * @brief Open a file.
 * @param[in,out] r Newlib reentrancy struct.
 * @param[out] fileStruct Pointer to file struct to fill in.
 * @param[in] path Path to open.
 * @param[in] flags Open flags from open(2)
 * @param[in] mode Permissions to set on create.
 * @return 0 for success, -1 for error.
 */
static int sdmc_open(struct _reent* r,
                     int* fd,
                     const char* path,
                     int flags,
                     int mode) {
    int ret;
    uint32_t sdmc_flags = 0;
    CtrFsContextData* context = NULL;

    context = (CtrFsContextData*)(GetDeviceOpTab("sdmc")->deviceData);
    if(context == NULL) {
        r->_errno = EIO;
        return -1;
    }

    /* Check access mode. */
    switch(flags & O_ACCMODE) {
        case O_RDONLY:
            sdmc_flags = CTR_FS_O_RDONLY;
            if(flags & O_APPEND) {
                r->_errno = EINVAL;
                return -1;
            }
            break;
        case O_WRONLY:
            sdmc_flags = CTR_FS_O_WRONLY;
            break;
        case O_RDWR:
            sdmc_flags = CTR_FS_O_RDWR;
            break;
        default:
            r->_errno = EINVAL;
            return -1;
    }

    /* Create file */
    if(flags & O_CREAT) {
        sdmc_flags |= CTR_FS_O_CREAT;
#if 0
        if(flags & O_EXCL) {
            ret = FSUSER_CreateFile(NULL, sdmcArchive, fs_path, 0);
            if(ret != 0) {
                r->_errno = sdmc_translate_error(rc);
                return -1;
            }
        }
#endif
    }

    /* Open the file */
    ret = ctrFsOpen(context, fd, path, sdmc_flags);
    if(ret != 0) {
#if 0
        r->_errno = sdmc_translate_error(cerrno());
#endif
        return -1;
    }

#if 0
    if((flags & O_ACCMODE) != O_RDONLY && (flags & O_TRUNC)) {
        ret = FSFILE_SetSize(fd, 0);
        if(ret != 0) {
            FSFILE_Close(fd);
            r->_errno = sdmc_translate_error(rc);
            return -1;
        }
    }
#endif


    return 0;
}
