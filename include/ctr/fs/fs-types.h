/**
 * @file ctr/fs/fs-types.h
 * @brief FileSystem types.
 * 
 * @defgroup fs File System.
 * @brief Filesystem API.
 * @note sdmcInit() will be the only function most users will need to call
 * directly.
 * @note Don't worry, I will add an equivalent to <code>sdmcInit()</code>, 
 * AFTER I get thread-local variables in GCC working.
 * 
 */

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

#ifndef __LIBCTR_FS_TYPES_H__
#define __LIBCTR_FS_TYPES_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * @ingroup fs
 * @typedef struct FSContext FSContext
 * @brief Handle to a filesystem session.
 * @details Each filesystem is represented by a context. Having each 
 * filesystem represented by a context makes it much more thread-safe, although
 * caution should still be used. Also, each individual session with the 
 * filesystem service may only have up to 32 handles open at one time. By 
 * giving each context its own session (whenever possible) this means that 
 * resource limits may not need to be shared across different individual 
 * filesystem, e.g. thread 1 may have 32 files from the SDMC filesystem open, 
 * and thread 2 can still have 32 files from the gamecart filesystem open.
 */
typedef struct struct FSContext;

/**
 * @ingroup fs
 * @typedef uint32_t FSHandle
 * @brief Handle to a file on a filesystem.
 */
typedef uint32_t FSHandle;

/**
 * @ingroup fs
 * @enum FSDevice
 * @brief Individual filesystem devices.
 */
typedef enum {
	FS_DEVICE_GAMEDATA 			= 0x00000000, /**< Game data filesystem. */
	FS_DEVICE_SAVEDATA 			= 0x00000001, /**< Save data filesystem. */
	FS_DEVICE_SDMC 				= 0x00000002, /**< SDMC filesystem. */
	FS_DEVICE_NAND 				= 0x00000003, /**< NAND filesystem. */
} FSDevice;

/**
 * @ingroup fs
 * @enum FSOpenFlag
 * @brief Flags for controlling how files should be opened.
 */
typedef enum {
	FS_OPEN_READ 				= (1 << 0), /**< Open file for reading. */
	FS_OPEN_WRITE 				= (1 << 1), /**< Open file for writing. */
	FS_OPEN_CREATE 				= (1 << 2), /**< Create file if it does not already exist. */
} FSOpenFlag;

/**
 * @ingroup fs
 * @enum FSAttribute
 * @brief Flags for controlling the individual attributes of files.
 */
typedef enum {
	FS_ATTRIBUTE_NONE 			= 0x00000000, /**< No attributes. */
	FS_ATTRIBUTE_READONLY 		= 0x00000001, /**< Create with read-only attribute. */
	FS_ATTRIBUTE_ARCHIVE 		= 0x00000100, /**< Create with archive attribute. */
	FS_ATTRIBUTE_HIDDEN 		= 0x00010000, /**< Create with hidden attribute. */
	FS_ATTRIBUTE_DIRECTORY 		= 0x01000000, /**< Create with directory attribute. */
} FSAttribute;

/**
 * @ingroup fs
 * @enum FSWriteFlag
 * @brief Flags for controlling how files should be written.
 */
typedef enum {
	FS_WRITE_NOFLUSH 			= 0x00000000, /**< Do not flush the contents of the file. */
	FS_WRITE_FLUSH 				= 0x00010001, /**< Flush the contents of the file. */
} FSWriteFlag;

#ifdef __cplusplus
}
#endif

#endif
