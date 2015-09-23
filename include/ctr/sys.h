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

#ifndef __LIBCTR_SYS_H__
#define __LIBCTR_SYS_H__

/**
 * @file ctr/sys.h
 * @brief System API.
 */

#include "ctr/base.h"

/** Highest thread priority. */
#define SYS_THREAD_PRIORITY_MAX (0x00)
/** Lowest thread priority. */
#define SYS_THREAD_PRIORITY_MIN (0x1F)

CTR_API_BEGIN

/**
 * @enum SYSProcessorID
 * @brief Identify which core a thread should run on.
 * @note If you are unsure which value to use, use SYS_PROCESSOR_APPCORE.
 */
typedef enum {
    /** Enable syscore and appcore. */
    SYS_PROCESSOR_ALL = 0xFFFFFFFC,
    /** Enable syscore. */
    SYS_PROCESSOR_SYSCORE = 0xFFFFFFFD,
    /** Enable appcore. */
    SYS_PROCESSOR_APPCORE = 0xFFFFFFFE,
} SYSProcessorID;

/**
 * @enum sys_lock_t
 * @brief Mutex states.
 */
typedef enum {
    /** Mutex is locked. */
    SYS_MUTEX_LOCKED = 0x00000000,
    /** Mutex is unlocked. */
    SYS_MUTEX_UNLOCKED = 0x00000001,
} sys_lock_t;

/**
 * @brief Handle to a kernel thread.
 */
typedef uint32_t sys_thread_t;

/**
 * @brief Handle to a kernel mutex.
 */
typedef uint32_t sys_mutex_t;

/**
 * @typedef sys_thread_func
 * @brief Function to run inside a thread.
 * @details <code>void sys_thread_cb(void* arg)</code>
 * @param[in] arg Parameter passed to the thread function.
 */
typedef void (*sys_thread_func)(void *arg);

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
CAPI int sys_thread_create(sys_thread_t *id,
                           sys_thread_func entry,
                           void *arg,
                           uint32_t *stack_top,
                           int priority,
                           SYSProcessorID idnum);

/**
 * @brief Wait for a thread to finish.
 * @param[in] id Thread ID.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int sys_thread_join(sys_thread_t id);

/**
 * @brief Put the current thread to sleep.
 * @param[in] nsec Time to suspend execution, in nanoseconds.
 */
CAPI void sys_thread_sleep(uint64_t nsec);

/**
 * @brief Yield the current thread.
 */
CAPI void sys_thread_yield(void);

/**
 * @brief Exit the current thread.
 */
CAPI void sys_thread_exit(void) CTR_NORETURN;

/**
 * @brief Exit the current process.
 */
CAPI void sys_process_exit(void) CTR_NORETURN;

/**
 * @brief Create a new mutex.
 * @param[out] mutex_id Mutex ID.
 * @param[in] status Boolean indicating if mutex should be locked upon creation.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int sys_mutex_new(sys_mutex_t *mutex_id, sys_lock_t status);

/**
 * @brief Destroy a mutex variable.
 * @param[in] mutex_id Mutex ID.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int sys_mutex_free(sys_mutex_t mutex_id);

/**
 * @brief Lock a mutex variable.
 * @param[in] mutex_id Mutex ID.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int sys_mutex_lock(sys_mutex_t mutex_id);

/**
 * @ingroup systhread
 * @brief Unlock a mutex variable.
 * @param[in] mutex_id Mutex ID.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int sys_mutex_unlock(sys_mutex_t mutex_id);

/**
 * @brief Print a debug string.
 * @details String is printed to the debug console. On retail
 * consoles this function has no effect. On emulators it will
 * be printed as debug output.
 * @param[in] str String to print.
 */
CAPI void sys_debug_printf(const char *str, ...);

CTR_API_END

#endif
