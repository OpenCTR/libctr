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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with libctr.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>

#include "ctr/sys/sys.h"
#include "ctr/svc/svc.h"
#include "ctr/error/error-private.h"

int sys_thread_new(sys_thread_t* id, sys_thread_cb entry, void* arg, uint32_t stack_top, int priority, SYSProcessorID idnum) {
	int ret;

	if(id == NULL) {
		(*cerrorptr()) = EINVAL;
		return -1;
	}

	if(entry == NULL) {
		(*cerrorptr()) = EINVAL;
		return -1;
	}

	ret = svc_thread_create(id, entry, (uint32_t)arg, stack_top, priority, idnum);
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	return 0;
}

void sys_print_debug(const char* str) {
	const int len = strlen(str);

	svc_output_debug_string(str, len);
}

void sys_debug_printf(const char* str, ...) {
	char* buffer = NULL;
	va_list args;
	int ret;

	va_start(args, str);
	ret = vasprintf(&buffer, str, args);
	if(ret == -1) {
		return;
	}
	va_end(args);

	svc_output_debug_string(buffer, ret);

	free(buffer);
}

void sys_process_exit(void) {
	svc_exit_process();
}

void sys_thread_sleep(uint64_t nsecs) {
	svc_thread_sleep((int64_t)nsecs);
}

