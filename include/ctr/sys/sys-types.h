/**
 * @file ctr/sys/sys-types.h
 * @brief System types.
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

#ifndef __LIBCTR_SYS_TYPES_H__
#define __LIBCTR_SYS_TYPES_H__

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

/** Function attribute that informs the compiler it will never return. */
#define SYS_NORETURN __attribute__((noreturn))

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @enum SYSProcessorID
 * @brief Identify which core a thread should run on.
 * @note If you are unsure which value to use, use SYS_PROCESSOR_APPCORE.
 */
typedef enum {
	SYS_PROCESSOR_ALL 		= 0xFFFFFFFC, /**< Enable syscore and appcore. */
	SYS_PROCESSOR_SYSCORE 	= 0xFFFFFFFD, /**< Enable syscore. */
	SYS_PROCESSOR_APPCORE 	= 0xFFFFFFFE, /**< Enable appcore. */
} SYSProcessorID;

/**
 * @enum sys_lock_t
 * @brief Mutex states.
 */
typedef enum {
	SYS_MUTEX_LOCKED 		= 0x00000000, /**< Mutex is locked. */
	SYS_MUTEX_UNLOCKED 		= 0x00000001, /**< Mutex is unlocked. */
} sys_lock_t;

/** 
 * @typedef uint32_t sys_thread_t
 * @brief Handle to a kernel thread.
 */
typedef uint32_t sys_thread_t;

/**
 * @typedef uint32_t sys_mutex_t
 * @brief Handle to a kernel mutex.
 */
typedef uint32_t sys_mutex_t;

/**
 * @typedef sys_thread_cb
 * @brief Function to run inside a thread.
 * @details <code>void sys_thread_cb(void* arg)</code>
 * @param[in] arg Parameter passed to the thread function.
 */
typedef void(*sys_thread_cb)(void* arg);

#ifdef __cplusplus
}
#endif

#endif
