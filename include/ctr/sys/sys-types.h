/**
 * @file ctr/sys/sys-types.h
 * @brief System types.
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

#ifndef __LIBCTR_SYS_TYPES_H__
#define __LIBCTR_SYS_TYPES_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @enum SYSProcessorID
 * @brief Identify which core a thread should run on.
 * @details If you are unsure which value you should use, 
 * use SYS_PROCESSOR_APPCORE.
 */
typedef enum {
	SYS_PROCESSOR_ALL 		= 0xFFFFFFFC, /**< Enable syscore and appcore. */
	SYS_PROCESSOR_SYSCORE 	= 0xFFFFFFFD, /**< Enable syscore. */
	SYS_PROCESSOR_APPCORE 	= 0xFFFFFFFE, /**< Enable appcore. */
} SYSProcessorID;

/** 
 * @brief Handle to a kernel thread.
 * @details SYSThread is a handle, and not an object, 
 * because kernel objects are owned by the kernel.
 */
typedef struct SYSThread SYSThread;

/**
 * @brief Function to run inside a thread.
 * @param[in] arg Parameter passed to the thread function.
 */
typedef void(*SYSThreadFunc)(void* arg);

#ifdef __cplusplus
}
#endif

#endif
