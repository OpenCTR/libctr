/**
 * @file ctr/svc/svc-types.h
 * @brief Private types for SVC.
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

#ifndef __LIBCTR_SVC_TYPES_H__
#define __LIBCTR_SVC_TYPES_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t SVCHandle;

typedef void(*SVCThreadFunc)(void* arg);

#ifdef __cplusplus
}
#endif

#endif
