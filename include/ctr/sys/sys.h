/**
 * @file ctr/sys/sys.h
 * @brief System interface.
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

#ifndef __LIBCTR_SYS_H__
#define __LIBCTR_SYS_H__

#include "sys-types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Create a new thread.
 * @details Obtains a handle to a thread created by the kernel.
 * @param[out] thread Handle to the new thread.
 * @param[in] entrypoint Function to execute inside the new thread.
 * @param[in] arg Argument given to the thread function. May be <code>NULL</code>.
 * @param[in] stack_top Address to use for the thread-specific stack.
 * @param[in] priority Priority assigned to the new thread. Higher values mean a lower priority.
 * @param[in] idnum Processor the thread should be created by.
 * @return On success, 0 is returned. On error, -1 is returned, and cerror is updated appropriately.
 */
int sys_thread_new(SYSThread* thread, SYSThreadFunc entrypoint, void* arg, uint32_t stack_top, int priority, SYSProcessorID idnum);

/**
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
