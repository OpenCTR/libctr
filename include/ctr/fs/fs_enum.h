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

#ifndef __LIBCTR_FS_ENUM_H__
#define __LIBCTR_FS_ENUM_H__

/**
 * @file ctr/fs/fs_enum.h
 * @brief Filesystem enums.
 */

#include "ctr/base.h"

CTR_API_BEGIN

/**
 * @brief Mode values.
 * @sa ctrFsMkdir()
 */
typedef enum {
	CTR_FS_MODE_NONE 	= 0x00, /**< Default mode. */
} CtrFsMode;

/**
 * @brief File position values.
 */
typedef enum {
	CTR_FS_SEEK_SET 	= 0x00, /**< Seek from the beginning. */
	CTR_FS_SEEK_CUR 	= 0x01, /**< Seek from the current position. */
	CTR_FS_SEEK_END 	= 0x02, /**< Seek from the end. */
} ctrFsOrigin;

/**
 * @brief File types.
 */
typedef enum {
	CTR_FS_TYPE_UNKNOWN 	= 0x00, /**< Unknown. */
	CTR_FS_TYPE_DIRECTORY 	= 0x01, /**< Directory. */
	CTR_FS_TYPE_REGULAR 	= 0x02, /**< Regular. */
} CtrFsType;

/**
 * @brief ctrFsOpen() flags.
 */
typedef enum {
	/** Open in read-only mode. */
	CTR_FS_O_RDONLY 	= 0x00000001,
	/** Open in write-only mode. */
	CTR_FS_O_WRONLY 	= 0x00000002,
	/** Open in read/write mode. */
	CTR_FS_O_RDWR 		= 0x00000003,
	/** Create file if it doesn't exist. */
	CTR_FS_O_CREAT 		= 0x00000004,
} CtrFsOpenFlags;

CTR_API_END

#endif
