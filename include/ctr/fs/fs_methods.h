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

#ifndef __LIBCTR_FS_METHODS_H__
#define __LIBCTR_FS_METHODS_H__

/**
 * @file ctr/fs/fs_methods.h
 * @brief Filesystem functions.
 */

#include "ctr/base.h"

CTR_API_BEGIN

/**
 * @brief Open a file.
 * @param[out] fd File descriptor.
 * @param[in] path Path to file.
 * @param[in] flags Flags. See ::CtrFsOpenFlags.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsOpen(int* fd, const char* path, int flags);

/**
 * @brief Read from a file.
 * @param[in] fd File descriptor.
 * @param[out] buffer Buffer to hold file contents.
 * @param[in] size Size to read.
 * @param[out] osize Actual size read from file.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsRead(int fd, void* buffer, uint64_t size, uint64_t* osize);

/**
 * @brief Write to a file.
 * @param[in] fd File descriptor.
 * @param[in] buffer Buffer to write to file.
 * @param[in] size Size to write.
 * @param[out] osize Actual size written to file.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsWrite(int fd, const void* buffer, uint64_t size, uint64_t* osize);

/**
 * @brief Close a file.
 * @param[in] fd File descriptor.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsClose(int fd);

/**
 * @brief Open a directory.
 * @param[out] fd File descriptor.
 * @param[in] path Path to directory.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsOpendir(int* fd, const char* path);

/**
 * @brief Read a directory entry.
 * @param[in] fd File descriptor.
 * @param[out] dir Directory information.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsReaddir(int fd, CtrFsDirent* dir);

/**
 * @brief Close a directory.
 * @param[in] fd File descriptor.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsClosedir(int fd);

/**
 * @brief Get file status/information (using a filename path).
 * @param[in] path Path to a file or directory.
 * @param[out] st File information.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsStat(const char* path, CtrFsStat* st);

/**
 * @brief Get file status/information (using a file descriptor).
 * @param[in] fd File descriptor.
 * @param[out] st File information.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsFstat(int fd, CtrFsStat* st);

/**
 * @brief Create a new directory.
 * @param[in] path Path to directory to be created.
 * @param[in] mode Mode for the new directory.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsMkdir(const char* path, CtrFsMode mode);

/**
 * @brief Change the name of a file.
 * @param[in] source Path of an existing filename.
 * @param[in] dest Path to the new filename.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsRename(const char* source, const char* dest);

/**
 * @brief Delete a directory.
 * @param[in] path Path to a directory.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsRmdir(const char* path);

/**
 * @brief Delete a file.
 * @param[in] path Path to a file.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsUnlink(const char* path);

/**
 * @brief Change the current position of a file.
 * @param[in] fd File descriptor.
 * @param[in] offset Offset from the origin.
 * @param[in] origin Seek mode.
 * @param[out] pos Current position of file (after seeking).
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsLseek(int fd, int64_t offset, ctrFsOrigin origin, uint64_t* pos);

/**
 * @brief Synchronize a file's data with the filesystem.
 * @param[in] fd File descriptor.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsFsync(int fd);

/**
 * @brief Get the SD card status.
 * @param[out] status Current status.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsSdmcStatus(CtrFsStatus* status);

/**
 * @brief Change file size (using a filename path).
 * @param[in] path Path to a file.
 * @param[in] size New file size.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsTruncate(const char* path, uint64_t size);

/**
 * @brief Change file size (using a file descriptor).
 * @param[in] fd File descriptor.
 * @param[in] size New file size.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsFtruncate(int fd, uint64_t size);

/**
 * @brief Get free space on the SD card and NAND filesystem.
 * @param[out] sdmc_size Available space on the SD card.
 * @param[out] nand_size Available space on the NAND filesystem.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsGetAvailableSize(uint64_t* sdmc_size, uint64_t* nand_size);

CTR_API_END

#endif
