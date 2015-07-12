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

#ifndef __LIBCTR_FS_STRUCT_H__
#define __LIBCTR_FS_STRUCT_H__

/**
 * @file ctr/fs/fs_struct.h
 * @brief Filesystem data structures.
 */

#include "ctr/base.h"

CTR_API_BEGIN

/**
 * @brief File status.
 */
typedef struct {
	/** File size. */
	uint64_t st_size;
} CtrFsStat;

/**
 * @brief Filesystem status.
 */
typedef struct {
	/** Is the filesystem usable? */
	uint8_t available;
	/** Is the filesystem writable? */
	uint8_t writable;
} CtrFsStatus;

/**
 * @brief Directory entry.
 */
typedef struct {
	/** File type. */
	uint8_t d_type;
	/** Length of string in d_name. */
	uint8_t d_namelen;
	/** Filename. */
	char d_name[CTR_FS_MAX_FILENAME_LENGTH + 1];
} CtrFsDirent;

CTR_API_END

#endif
