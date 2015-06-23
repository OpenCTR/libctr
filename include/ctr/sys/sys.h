/**
 * @file ctr/sys/sys.h
 * @brief System interface.
 */

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

#ifndef __LIBCTR_SYS_H__
#define __LIBCTR_SYS_H__

#include "sys-types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Create a new thread.
 * @details Obtains a handle to a thread created by the kernel.
 * @param[out] id Thread ID.
 * @param[in] entry Function to execute inside the new thread.
 * @param[in] arg Argument given to the thread function. 
 * @param[in] stack_top Address to use for the thread-specific stack.
 * @param[in] priority Priority assigned to the new thread. 
 * @param[in] idnum Processor the thread should be created by.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int sys_thread_create(sys_thread_t* id, sys_thread_cb entry, void* arg, uint32_t stack_top, int priority, SYSProcessorID idnum);

/**
 * @brief Wait for a thread to finish.
 * @param[in] id Thread ID.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int sys_thread_join(sys_thread_t id);

/**
 * @brief Put the current thread to sleep.
 * @param[in] nsec Time to suspend execution, in nanoseconds.
 */
void sys_thread_sleep(uint64_t nsec);

/**
 * @brief Yield the current thread.
 */
void sys_thread_yield(void);

/**
 * @brief Exit the current thread.
 */
void sys_thread_exit(void) SYS_NORETURN;

/**
 * @brief Exit the current process.
 */
void sys_process_exit(void) SYS_NORETURN;

/**
 * @brief Create a new mutex.
 * @param[out] mutex_id Mutex ID.
 * @param[in] status Boolean indicating if mutex should be locked upon creation.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int sys_mutex_new(sys_mutex_t* mutex_id, sys_lock_t status);

/**
 * @brief Destroy a mutex variable.
 * @param[in] mutex_id Mutex ID.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int sys_mutex_free(sys_mutex_t mutex_id);

/**
 * @brief Lock a mutex variable.
 * @param[in] mutex_id Mutex ID.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int sys_mutex_lock(sys_mutex_t mutex_id);

/**
 * @ingroup systhread
 * @brief Unlock a mutex variable.
 * @param[in] mutex_id Mutex ID.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int sys_mutex_unlock(sys_mutex_t mutex_id);

/**
 * @brief Print a debug string.
 * @details String is printed to the debug console. On retail 
 * consoles this function has no effect. On emulators it will 
 * be printed as debug output.
 * @param[in] str String to print.
 */
void sys_debug_printf(const char* str, ...);

#ifdef __cplusplus
}
#endif

#endif
