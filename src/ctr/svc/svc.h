/**
 * @file ctr/svc/svc.h
 * @brief Private interface to SVC.
 */

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

#ifndef __LIBCTR_SVC_H__
#define __LIBCTR_SVC_H__

#include <stdbool.h>

#include "svc-types.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32_t* svc_get_tls(void);

uint32_t* svc_get_commandbuffer(void);

int svc_control_memory(uint32_t* outaddr, uint32_t addr0, uint32_t addr1, uint32_t size, uint32_t operation, uint32_t permissions);

void __attribute__((noreturn)) svc_exit_process(void);

int svc_thread_create(SVCHandle* handle, SVCThreadFunc entrypoint, uint32_t arg, uint32_t stacktop, int32_t priority, int32_t processorid);

void __attribute__((noreturn)) svc_exit_thread(void);

void svc_thread_sleep(int64_t ns);

int svc_create_mutex(SVCHandle* mutex, bool initially_locked);

int svc_release_mutex(SVCHandle mutex);

int svc_close_handle(SVCHandle handle);

int svc_wait_synchronization(SVCHandle handle, int64_t nanoseconds);

int svc_connect_to_port(SVCHandle* handle, const char* port);

int svc_send_sync_request(SVCHandle handle);

int svc_output_debug_string(const char* str, const int len);

#ifdef __cplusplus
}
#endif

#endif
