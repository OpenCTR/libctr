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

#ifndef __LIBCTR_SYS_PRIVATE_H__
#define __LIBCTR_SYS_PRIVATE_H__

/**
 * @file ctr/sys/sys_private.h
 * @brief Private System API.
 */

#include "ctr/base.h"

CTR_API_BEGIN

/**
 * @brief Memory info.
 */
typedef struct {
	/** Base address. */
	uint32_t base_addr;
	/** Size. */
	uint32_t size;
	/** Memory permissions. */
	uint32_t permission;
	/** Memory status. */
	uint32_t state;
} sys_memory_info;

/**
 * @brief Page info.
 */
typedef struct {
	/** Page flags. */
	uint32_t flags;
} sys_page_info;

uint32_t* sys_get_tls(void);
uint32_t* sys_get_commandbuffer(void);
int sys_control_memory(uint32_t* outaddr, uint32_t addr0, uint32_t addr1, uint32_t size, uint32_t operation, uint32_t permissions);
extern int sys_control_memory_ex(uint32_t* outaddr, uint32_t addr0, uint32_t addr1, uint32_t size, uint32_t operation, uint32_t permissions);
int sys_query_memory(sys_memory_info* meminfo, sys_page_info* pageinfo, uint32_t addr);
extern int sys_query_memory_ex(sys_memory_info* meminfo, sys_page_info* pageinfo, uint32_t addr);
extern int sys_thread_create_ex(uint32_t* handle, sys_thread_func entrypoint, uint32_t arg, uint32_t stacktop, int32_t priority, int32_t processorid);
extern void sys_thread_sleep_ex(int64_t ns);
extern int sys_close_handle(uint32_t handle);
extern int sys_wait_synchronization(uint32_t handle, int64_t nanoseconds);
extern int sys_mutex_unlock_ex(uint32_t mutex);
extern int sys_mutex_new_ex(sys_mutex_t* mutex, sys_lock_t status);
extern int sys_connect_to_port(uint32_t* handle, const char* port);
extern int sys_send_sync_request(uint32_t handle);
extern int sys_debug_printf_ex(const char* str, const int len);

int sys_service_get_handle(uint32_t* handle, const char* name);


CTR_API_END

#endif
