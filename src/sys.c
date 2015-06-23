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

int sys_thread_create(sys_thread_t* id, sys_thread_cb entry, void* arg, uint32_t stack_top, int priority, SYSProcessorID idnum) {
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

int sys_thread_join(sys_thread_t id) {
	int ret;

	ret = svc_wait_synchronization((SVCHandle)id, UINT64_MAX);
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	svc_close_handle((SVCHandle)id);

	return 0;
}

void sys_thread_sleep(uint64_t nsecs) {
	svc_thread_sleep((int64_t)nsecs);
}

void sys_thread_yield(void) {
	svc_thread_sleep(0);
}

void sys_thread_exit(void) {
	svc_exit_thread();
}

void sys_process_exit(void) {
	svc_exit_process();
}

int sys_mutex_new(sys_mutex_t* mutex_id, sys_lock_t status) {
	int ret;

	switch(status) {
		case SYS_MUTEX_LOCKED:
			ret = svc_create_mutex((SVCHandle*)mutex_id, true);
			break;
		case SYS_MUTEX_UNLOCKED:
			ret = svc_create_mutex((SVCHandle*)mutex_id, false);
			break;
		default:
			break;
	}

	return ret;
}

int sys_mutex_free(sys_mutex_t mutex_id) {
	int ret;

	ret = svc_close_handle(mutex_id);
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	return 0;
}

int sys_mutex_lock(sys_mutex_t mutex_id) {
	int ret;

	ret = svc_wait_synchronization(mutex_id, UINT64_MAX);
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	return 0;
}

int sys_mutex_unlock(sys_mutex_t mutex_id) {
	int ret;

	ret = svc_release_mutex(mutex_id);
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	return 0;
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
