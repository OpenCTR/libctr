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
 * @ingroup systhread
 * @brief Create a new thread.
 * @details Obtains a handle to a thread created by the kernel.
 * @param[out] thread Handle to the new thread.
 * @param[in] entrypoint Function to execute inside the new thread.
 * @param[in] arg Argument given to the thread function. 
 * @param[in] stack_top Address to use for the thread-specific stack.
 * @param[in] priority Priority assigned to the new thread. 
 * @param[in] idnum Processor the thread should be created by.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int sys_thread_new(SYSThread* thread, SYSThreadFunc entrypoint, void* arg, uint32_t stack_top, int priority, SYSProcessorID idnum);

/**
 * @ingroup systhread
 * @brief Wait for a thread to finish.
 * @param[in] thread Handle to a kernel thread.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int sys_thread_join(SYSThread* thread);

/**
 * @ingroup systhread
 * @brief Set the priority of a thread.
 * @param[in] thread Handle to a thread.
 * @param[in] priority New thread priority level.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int sys_thread_set_priority(SYSThread* thread, int32_t priority);

/**
 * @ingroup systhread
 * @brief Put the current thread to sleep.
 * @param[in] nanoseconds Time to suspend execution, in nanoseconds.
 */
void sys_thread_sleep(uint64_t nanoseconds);

/**
 * @ingroup systhread
 * @brief Exit the current thread.
 */
SYS_NORETURN void sys_exit_thread(void);

/**
 * @ingroup systhread
 * @brief Create a new mutex.
 * @param[out] mutex New mutex variable.
 * @param[in] status Boolean indicating if mutex should be locked upon creation.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int sys_mutex_new(SYSMutex* mutex, SYSMutexLocked status);

/**
 * @ingroup systhread
 * @brief Lock a mutex variable.
 * @param[in] mutex Mutex variable to lock.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int sys_mutex_lock(SYSMutex* mutex);

/**
 * @ingroup systhread
 * @brief Unlock a mutex variable.
 * @param[in] mutex Mutex variable to unlock.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int sys_mutex_unlock(SYSMutex* mutex);

/**
 * @ingroup systhread
 * @brief Release a mutex variable.
 * @param[in] mutex Mutex variable to release.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int sys_mutex_free(SYSMutex* mutex);

/**
 * @ingroup sysdebug
 * @brief Print a debug string.
 * @details String is printed to the debug console. On retail 
 * consoles this function has no effect. On emulators it will 
 * be printed as debug output.
 * @param[in] str String to print.
 */
void sys_print_debug(const char* str);

#ifdef __cplusplus
}
#endif

#endif
