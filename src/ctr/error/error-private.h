/**
 * @file ctr/error/error-private.h
 * @brief Private interface for libctr Errors.
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

#ifndef __LIBCTR_ERROR_PRIVATE_H__
#define __LIBCTR_ERROR_PRIVATE_H__

#include <stdint.h>

#include "ctr/error/error-types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Obtain a pointer to the libctr errno.
 * Returns a thread-safe pointer for libctr 
 * functions to set.
 */
int* cerrorptr(void);

#ifdef __cplusplus
}
#endif

#endif
