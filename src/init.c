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

int __system_argc;
char** __system_argv;
void (*__system_retAddr)(void);

extern void* __service_ptr;
extern char* fake_heap_start;
extern char* fake_heap_end;
extern uint32_t __heap_size;
uint32_t __heapBase;

void __attribute__((weak)) __attribute__((noreturn)) ctr_exit(int rc) {
    uint32_t tmp = 0;

    /* Jump to the loader, if a callback was provided. */
    if(__system_retAddr) {
        __system_retAddr();
    }

    /* Since above did not jump, end this process. */
    sys_process_exit();
}

void __attribute__((weak)) ctr_init(void (*retAddr)(void)) {
    uint32_t tmp = 0;

    /* Register newlib exit() syscall. */
    __syscalls.exit = ctr_exit;

    __system_retAddr = __service_ptr ? retAddr : NULL;

    /* Set the heap base to the address of the ARM9 main memory. */
    __heapBase = 0x08000000;

    /* Allocate the heap. */
    sys_control_memory(&tmp, __heapBase, 0x0, __heap_size, 3, 0x3);

    /* Setup the newlib heap. */
    fake_heap_start = (char*)__heapBase;
    fake_heap_end = fake_heap_start + __heap_size;
}
