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

#include "ctr/base_private.h"
#include "ctr/sys_private.h"
#include "ctr/error_private.h"

static uint32_t ctr_service_handle = 0;

static void service_init(void) __attribute__((constructor(105)));
static void service_exit(void) __attribute__((destructor(105)));

static void service_init(void) {
    char buffer[200];
    uint32_t* cmdbuf = NULL;
    int ret;

    if(ctr_service_handle != 0) {
        return;
    }

    ret = sys_connect_to_port(&ctr_service_handle, "srv:");
    if(ret != 0) {
        sys_debug_printf("sys_connect_to_port() error: 0x%08x\n", ret);
        sys_process_exit();
    }

    cmdbuf = sys_get_commandbuffer();
    assert(cmdbuf != NULL);

    cmdbuf[0] = 0x00010002;
    cmdbuf[1] = 0x00000020;

    ret = sys_send_sync_request(ctr_service_handle);
    if(ret != 0) {
        sys_debug_printf("sys_send_sync_request() error: 0x%08x\n", ret);
        sys_process_exit();
    }

    if(cmdbuf[1] != 0) {
        sys_debug_printf("service_init() error: 0x%08x\n", ret);
        sys_process_exit();
    }
}

static void service_exit(void) {
    int ret;

    ret = sys_close_handle(ctr_service_handle);
    if(ret != 0) {
        sys_debug_printf("Error closing service handle: 0x%08x\n", ret);
        sys_process_exit();
    }
}

int sys_service_get_handle(uint32_t* handle, const char* name) {
    uint32_t* cmdbuf = NULL;
    int ret;

#if 0
    Handle h = __get_handle_from_list(name);
    if(h != 0) {
        return svcDuplicateHandle(out, h);
    }
#endif

    const int len = strlen(name);

    cmdbuf = sys_get_commandbuffer();
    assert(cmdbuf != NULL);

    cmdbuf[0] = 0x00050100;

    // cmdbuf[1] = name;
    strcpy((char*)&cmdbuf[1], name);

    cmdbuf[3] = len;
    cmdbuf[4] = 0x00;

    ret = sys_send_sync_request(ctr_service_handle);
    if(ret != 0) {
        return ret;
    }

    ret = cmdbuf[1];
    if(ret != 0) {
        return ret;
    }

    if(handle != NULL) {
        *handle = cmdbuf[3];
    }

    return 0;
}
