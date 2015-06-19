/**
 * @file ctr/fs/fs.h
 * Interface to the filesystem service.
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

#ifndef __LIBCTR_FS_H__
#define __LIBCTR_FS_H__

#include "fs-types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup fs
 * @brief Create a new session with the FS service, and mount a filesystem.
 * @param[out] ctx New FS context.
 * @param[in] device Device to mount as the default filesystem.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int fs_session_new(FSContext* ctx, FSDevice device);

/**
 * @ingroup fs
 * @brief Close a session with the filesystem service.
 * @param[in] ctx FS context representing a session.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
int fs_session_close(FSContext* ctx);


int fs_open_file(FSContext* ctx, FSHandle* fd, const char* path, FSOpenFlag openflags, FSAttribute attributes);
int fs_close_file(FSContext* ctx, FSHandle fd);
int fs_read_file(FSContext* ctx, FSHandle fd, uint64_t offset, )


int fs_create_file(FSContext* ctx, const char* path);
int fs_delete_file(FSContext* ctx, const char* path);
int fs_rename_file(FSContext* ctx, const char* source, const char* destination);


#if 0

Result FSUSER_OpenArchive(Handle* handle, FS_archive* archive);
Result FSUSER_OpenDirectory(Handle* handle, Handle* out, FS_archive archive, FS_path dirLowPath);
Result FSUSER_CloseArchive(Handle* handle, FS_archive* archive);
Result FSUSER_CreateDirectory(Handle* handle, FS_archive archive, FS_path dirLowPath);
Result FSUSER_DeleteDirectory(Handle *handle, FS_archive archive, FS_path dirLowPath);
Result FSUSER_DeleteDirectoryRecursively(Handle *handle, FS_archive archive, FS_path dirLowPath);
Result FSUSER_RenameDirectory(Handle *handle, FS_archive srcArchive, FS_path srcDirLowPath, FS_archive destArchive, FS_path destDirLowPath);
Result FSUSER_IsSdmcDetected(Handle *handle, u8 *detected);
Result FSUSER_IsSdmcWritable(Handle *handle, u8 *writable);

Result FSFILE_Close(Handle handle);
Result FSFILE_Read(Handle handle, u32 *bytesRead, u64 offset, void *buffer, u32 size);
Result FSFILE_Write(Handle handle, u32 *bytesWritten, u64 offset, const void *buffer, u32 size, u32 flushFlags);
Result FSFILE_GetSize(Handle handle, u64 *size);
Result FSFILE_SetSize(Handle handle, u64 size);
Result FSFILE_GetAttributes(Handle handle, u32 *attributes);
Result FSFILE_SetAttributes(Handle handle, u32 attributes);
Result FSFILE_Flush(Handle handle);

Result FSDIR_Read(Handle handle, u32 *entriesRead, u32 entrycount, FS_dirent *buffer);
Result FSDIR_Close(Handle handle);
#endif


#ifdef __cplusplus
}
#endif

#endif
