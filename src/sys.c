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

#include "ctr/base.h"
#include "ctr/sys.h"
#include "ctr/error.h"

int sys_control_memory(uint32_t* outaddr, uint32_t addr0, uint32_t addr1, uint32_t size, uint32_t operation, uint32_t permissions) {
	int ret;

	ret = sys_control_memory_ex(outaddr, addr0, addr1, size, operation, permissions);
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	return 0;
}

int sys_query_memory(sys_memory_info* meminfo, sys_page_info* pageinfo, uint32_t addr) {
	int ret;

	ret = sys_query_memory_ex(meminfo, pageinfo, addr);
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	return 0;
}

int sys_thread_create(sys_thread_t* id, sys_thread_func entry, void* arg, uint32_t* stack_top, int priority, SYSProcessorID idnum) {
	int ret;

	if(id == NULL) {
		(*cerrorptr()) = EINVAL;
		return -1;
	}

	if(entry == NULL) {
		(*cerrorptr()) = EINVAL;
		return -1;
	}

	ret = sys_thread_create_ex(id, entry, (uint32_t)arg, stack_top, priority, idnum);
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	return 0;
}

int sys_thread_join(sys_thread_t id) {
	int ret;

	ret = sys_wait_synchronization(id, UINT64_MAX);
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	sys_close_handle(id);

	return 0;
}

void sys_thread_sleep(uint64_t nsecs) {
	sys_thread_sleep_ex((int64_t)nsecs);
}

void sys_thread_yield(void) {
	sys_thread_sleep_ex(0);
}

int sys_mutex_new(sys_mutex_t* mutex, sys_lock_t status) {
	int ret;

	ret = sys_mutex_new_ex(mutex, status);
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	return 0;
}

int sys_mutex_free(sys_mutex_t mutex_id) {
	int ret;

	ret = sys_close_handle(mutex_id);
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	return 0;
}

int sys_mutex_lock(sys_mutex_t mutex_id) {
	int ret;

	ret = sys_wait_synchronization(mutex_id, UINT64_MAX);
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	return 0;
}

int sys_mutex_unlock(sys_mutex_t mutex_id) {
	int ret;

	ret = sys_mutex_unlock_ex(mutex_id);
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

	sys_debug_printf_ex(buffer, ret);

	free(buffer);
}

