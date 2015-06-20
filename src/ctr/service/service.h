/**
 * @file ctr/service/service.h
 * @brief Services API.
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

#ifndef __LIBCTR_SERVICE_H__
#define __LIBCTR_SERVICE_H__

#include "ctr/svc/svc-types.h"

#ifdef __cplusplus
extern "C" {
#endif

int ctrServiceGetHandle(SVCHandle* handle, const char* name);

#ifdef __cplusplus
}
#endif

#endif
