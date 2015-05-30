/**
 * @file ctr/sys/sys-types.h
 * @brief System types.
 * 
 * @defgroup systhread System Threads
 * @brief Module for creating and using system threads.
 * @details The Nintendo 3DS kernel provides support for 
 * running multiple threads on each ARM11 core. The thread scheduler is 
 * cooperative, meaning that control will not pass to the next thread until 
 * the current thread yields control. Often, threads yield by using an 
 * address arbiter.
 * 
 * Besides support for threads themselves, libctr also provides various 
 * synchronization methods.
 * 
 * 
 * @defgroup sysdebug System Debugging Features
 * @brief Module used for debugging application software.
 * @details Several functions are available to help with debugging 
 * a program during runtime. Although they are very useful during 
 * development, few if any of these should be used in production 
 * software.
 * 
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

#include <stdint.h>

/** Function attribute that informs the compiler it will never return. */
#define SYS_NORETURN (__attribute__((noreturn)))

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @enum SYSProcessorID
 * @brief Identify which core a thread should run on.
 * @note If you are unsure which value you should use, 
 * use SYS_PROCESSOR_APPCORE.
 */
typedef enum {
	SYS_PROCESSOR_ALL 		= 0xFFFFFFFC, /**< Enable syscore and appcore. */
	SYS_PROCESSOR_SYSCORE 	= 0xFFFFFFFD, /**< Enable syscore. */
	SYS_PROCESSOR_APPCORE 	= 0xFFFFFFFE, /**< Enable appcore. */
} SYSProcessorID;

/**
 * @enum SYSMutexLocked
 * @ingroup systhread
 * @brief Mutex states
 */
typedef enum {
	SYS_MUTEX_LOCKED 		= 0x00000000, /**< Mutex is locked. */
	SYS_MUTEX_UNLOCKED 		= 0x00000001, /**< Mutex is unlocked. */
} SYSMutexLocked;

/** 
 * @typedef struct SYSThread SYSThread
 * @ingroup systhread
 * @brief Handle to a kernel thread.
 */
typedef struct SYSThread SYSThread;

/**
 * @typedef struct SYSMutex SYSMutex
 * @ingroup systhread
 * @brief Handle to a kernel mutex.
 */
typedef struct SYSMutex SYSMutex;

/**
 * @typedef void(*SYSThreadFunc)(void* arg)
 * @ingroup systhread
 * @brief Function to run inside a thread.
 * @param[in] arg Parameter passed to the thread function.
 */
typedef void(*SYSThreadFunc)(void* arg);

#ifdef __cplusplus
}
#endif

#endif
