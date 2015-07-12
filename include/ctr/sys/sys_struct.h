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

#ifndef __LIBCTR_SYS_STRUCT_H__
#define __LIBCTR_SYS_STRUCT_H__

/**
 * @file ctr/sys/sys_struct.h
 * @brief System data structures.
 */

CTR_API_BEGIN

/**
 * @brief Handle to a kernel thread.
 */
typedef uint32_t sys_thread_t;

/**
 * @brief Handle to a kernel mutex.
 */
typedef uint32_t sys_mutex_t;

/**
 * @typedef sys_thread_cb
 * @brief Function to run inside a thread.
 * @details <code>void sys_thread_cb(void* arg)</code>
 * @param[in] arg Parameter passed to the thread function.
 */
typedef void(*sys_thread_func)(void* arg);

CTR_API_END

#endif
