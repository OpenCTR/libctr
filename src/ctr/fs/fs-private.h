/**
 * @file ctr/fs/fs-private.h
 * @brief Filesystem API (private).
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

#ifndef __LIBCTR_FILESYSTEM_PRIVATE_H__
#define __LIBCTR_FILESYSTEM_PRIVATE_H__

#include <stdint.h>

#include "ctr/fs/fs-types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the filesystem API.
 * @details Because this function is not thread-safe, and because some internal
 * libctr functions may need to use the filesystem, this function is not 
 * public. **Users should not call this function directly**. It is called
 * internally at startup. 
 * 
 * Also, because libctr uses the filesystem internally, calling ctrFsInit()
 * internally allows greater opportunity for potentially correcting errors.
 * Finally, if an unrecoverable error is encountered, libctr will terminate
 * the application. By doing so, we may assume (during runtime) that the 
 * filesystem system was successfully initialized, which means that fewer
 * error checks are required, compared to the rest of the libctr API.
 * 
 * @return On success, 0 is returned. On error, -1 is returned.
 */
//int ctrFsInit(void);


#ifdef __cplusplus
}
#endif

#endif
