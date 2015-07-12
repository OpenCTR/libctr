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

#ifndef __LIBCTR_SYS_ENUM_H__
#define __LIBCTR_SYS_ENUM_H__

/**
 * @file ctr/sys/sys_enum.h
 * @brief System enums.
 */

#include <ctr/base.h>
#include <ctr/base/base_headers.h>
#include <ctr/base/base_macros.h>

CTR_API_BEGIN

/**
 * @brief Identify which core a thread should run on.
 * @note If you are unsure which value to use, use SYS_PROCESSOR_APPCORE.
 */
typedef enum {
	SYS_PROCESSOR_ALL 		= 0xFFFFFFFC, /**< Enable syscore and appcore. */
	SYS_PROCESSOR_SYSCORE 	= 0xFFFFFFFD, /**< Enable syscore. */
	SYS_PROCESSOR_APPCORE 	= 0xFFFFFFFE, /**< Enable appcore. */
} SYSProcessorID;

/**
 * @brief Mutex states.
 */
typedef enum {
	SYS_MUTEX_LOCKED 		= 0x00000000, /**< Mutex is locked. */
	SYS_MUTEX_UNLOCKED 		= 0x00000001, /**< Mutex is unlocked. */
} sys_lock_t;

CTR_API_END

#endif
