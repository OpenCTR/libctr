/*
 * This file is part of libctr.
 * 
 * libctr is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * libctr is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with libctr. If not, see <http://www.gnu.org/licenses/>.
*/

#include <sys/iosupport.h>

#include "ctr/svc/svc.h"

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

	// Jump to the loader if it provided a callback
	if(__system_retAddr) {
		__system_retAddr();
	}

	// Since above did not jump, end this process
	svc_exit_process();
}


void __attribute__((weak)) ctr_init(void (*retAddr)(void)) {
	uint32_t tmp = 0;

	// Register newlib exit() syscall
	__syscalls.exit = ctr_exit;

	__system_retAddr = __service_ptr ? retAddr : NULL;

	/* Set the heap base to the address of the ARM9 main memory. */
	__heapBase = 0x08000000;

	/* Allocate the heap. */
	svc_control_memory(&tmp, __heapBase, 0x0, __heap_size, 3, 0x3);

	// Set up newlib heap
	fake_heap_start = (char*)__heapBase;
	fake_heap_end = fake_heap_start + __heap_size;
}

