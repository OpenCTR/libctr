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

/**
 * @file ctr/fs.h
 * @brief Filesystem API.
 */

#include "ctr/base.h"

/** Maximum length of a filename.  */
#define CTR_FS_MAX_FILENAME_LENGTH (0x00000100)

/**
 * @def CTR_FS_THIS
 * @brief Global Filesystem Context Data.
 * @details A thread-safe reference to the global Filesystem context
 * data. This is created automatically during libctr
 * startup, and should <em>NEVER<em> be allocated or freed by the user.
 * @note If the filesystem is mounted with ctrFsMount(), then users will
 * not need to use this. By default, libctr uses CTR_FS_THIS when mounting
 * the filesystem.
 */
#define CTR_FS_THIS gFS

CTR_API_BEGIN

/**
 * @enum CtrFsMode
 * @brief Mode values.
 * @sa ctrFsMkdir()
 */
typedef enum {
    /** Default mode. */
    CTR_FS_MODE_NONE = 0x00,
} CtrFsMode;

/**
 * @enum CtrFsOrigin
 * @brief File position values.
 */
typedef enum {
    /** Seek from the beginning. */
    CTR_FS_SEEK_SET = 0x00,
    /** Seek from the current position. */
    CTR_FS_SEEK_CUR = 0x01,
    /** Seek from the end. */
    CTR_FS_SEEK_END = 0x02,
} CtrFsOrigin;

/**
 * @enum CtrFsType
 * @brief File types.
 */
typedef enum {
    /** Unrecognized entry. */
    CTR_FS_TYPE_UNKNOWN = 0x00,
    /** Directory entry. */
    CTR_FS_TYPE_DIRECTORY = 0x01,
    /** Regular file entry. */
    CTR_FS_TYPE_REGULAR = 0x02,
} CtrFsType;

/**
 * @enum CtrFsOpenFlags
 * @brief Flags for ctrFsOpen().
 */
typedef enum {
    /** Open in read-only mode. */
    CTR_FS_O_RDONLY = 0x00000001,
    /** Open in write-only mode. */
    CTR_FS_O_WRONLY = 0x00000002,
    /** Open in read/write mode. */
    CTR_FS_O_RDWR = 0x00000003,
    /** Create file if it doesn't exist. */
    CTR_FS_O_CREAT = 0x00000004,
} CtrFsOpenFlags;

/**
 * @struct CtrFsStat
 * @brief File status and information.
 */
typedef struct {
    /** File size. */
    uint64_t st_size;
} CtrFsStat;

/**
 * @struct CtrFsStatus
 * @brief Filesystem status and availability.
 */
typedef struct {
    /** Is the filesystem usable? */
    uint8_t available;
    /** Is the filesystem writable? */
    uint8_t writable;
} CtrFsStatus;

/**
 * @struct CtrFsDirent
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

/**
 * @struct CtrFsContextData
 * @brief Filesystem Context Data.
 * @details <code>CtrFsContextData</code> is an opaque type. <i>It
 * should NEVER be modified by users</i>.
 */
CTR_CONTEXT_DECLARE(FS, CtrFsContextData);

/**
 * @brief Create a new filesystem context.
 * @warning <em>NEVER</em> use this function to initialize CTR_FS_THIS.
 * @return A newly created Filesystem Context.
 */
CAPI CtrFsContextData *ctrFsContextDataNew(void);

/**
 * @brief Release a Filesystem context.
 * @warning <em>NEVER</em> call this function for CTR_FS_THIS.
 * @param[in] context Filesystem context to release.
 */
CAPI void ctrFsContextDataFree(CtrFsContextData *context) CTR_ARG_NONNULL(1);

/**
 * @brief Open a file.
 * @param[in] context Filesystem Context Data.
 * @param[out] fd File descriptor.
 * @param[in] path Path to file.
 * @param[in] flags Flags. See ::CtrFsOpenFlags.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsOpen(CtrFsContextData *context,
                   int *fd,
                   const char *path,
                   int flags) CTR_ARG_NONNULL(1);

/**
 * @brief Read from a file.
 * @param[in] context Filesystem Context Data.
 * @param[in] fd File descriptor.
 * @param[out] buffer Buffer to hold file contents.
 * @param[in] size Size to read.
 * @param[out] osize Actual size read from file.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsRead(CtrFsContextData *context,
                   int fd,
                   void *buffer,
                   uint64_t size,
                   uint64_t *osize) CTR_ARG_NONNULL(1);

/**
 * @brief Write to a file.
 * @param[in] context Filesystem Context Data.
 * @param[in] fd File descriptor.
 * @param[in] buffer Buffer to write to file.
 * @param[in] size Size to write.
 * @param[out] osize Actual size written to file.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsWrite(CtrFsContextData *context,
                    int fd,
                    const void *buffer,
                    uint64_t size,
                    uint64_t *osize) CTR_ARG_NONNULL(1);

/**
 * @brief Close a file.
 * @param[in] context Filesystem Context Data.
 * @param[in] fd File descriptor.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsClose(CtrFsContextData *context, int fd) CTR_ARG_NONNULL(1);

/**
 * @brief Open a directory.
 * @param[in] context Filesystem Context Data.
 * @param[out] fd File descriptor.
 * @param[in] path Path to directory.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsOpendir(CtrFsContextData *context, int *fd, const char *path)
    CTR_ARG_NONNULL(1);

/**
 * @brief Read a directory entry.
 * @param[in] context Filesystem Context Data.
 * @param[in] fd File descriptor.
 * @param[out] dir Directory information.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsReaddir(CtrFsContextData *context, int fd, CtrFsDirent *dir)
    CTR_ARG_NONNULL(1);

/**
 * @brief Close a directory.
 * @param[in] context Filesystem Context Data.
 * @param[in] fd File descriptor.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsClosedir(CtrFsContextData *context, int fd) CTR_ARG_NONNULL(1);

/**
 * @brief Get file status/information (using a filename path).
 * @param[in] context Filesystem Context Data.
 * @param[in] path Path to a file or directory.
 * @param[out] st File information.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsStat(CtrFsContextData *context, const char *path, CtrFsStat *st)
    CTR_ARG_NONNULL(1);

/**
 * @brief Get file status/information (using a file descriptor).
 * @param[in] context Filesystem Context Data.
 * @param[in] fd File descriptor.
 * @param[out] st File information.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsFstat(CtrFsContextData *context, int fd, CtrFsStat *st)
    CTR_ARG_NONNULL(1);

/**
 * @brief Create a new directory.
 * @param[in] context Filesystem Context Data.
 * @param[in] path Path to directory to be created.
 * @param[in] mode Mode for the new directory.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsMkdir(CtrFsContextData *context, const char *path, CtrFsMode mode)
    CTR_ARG_NONNULL(1);

/**
 * @brief Change the name of a file.
 * @param[in] context Filesystem Context Data.
 * @param[in] source Path of an existing filename.
 * @param[in] dest Path to the new filename.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsRename(CtrFsContextData *context,
                     const char *source,
                     const char *dest) CTR_ARG_NONNULL(1);

/**
 * @brief Delete a directory.
 * @param[in] context Filesystem Context Data.
 * @param[in] path Path to a directory.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsRmdir(CtrFsContextData *context, const char *path)
    CTR_ARG_NONNULL(1);

/**
 * @brief Delete a file.
 * @param[in] context Filesystem Context Data.
 * @param[in] path Path to a file.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsUnlink(CtrFsContextData *context, const char *path)
    CTR_ARG_NONNULL(1);

/**
 * @brief Change the current position of a file.
 * @param[in] context Filesystem Context Data.
 * @param[in] fd File descriptor.
 * @param[in] offset Offset from the origin.
 * @param[in] origin Seek mode.
 * @param[out] pos Current position of file (after seeking).
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsLseek(CtrFsContextData *context,
                    int fd,
                    int64_t offset,
                    CtrFsOrigin origin,
                    uint64_t *pos) CTR_ARG_NONNULL(1);

/**
 * @brief Synchronize a file's data with the filesystem.
 * @param[in] context Filesystem Context Data.
 * @param[in] fd File descriptor.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsFsync(CtrFsContextData *context, int fd) CTR_ARG_NONNULL(1);

/**
 * @brief Get the SD card status.
 * @param[in] context Filesystem Context Data.
 * @param[out] status Current status.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsSdmcStatus(CtrFsContextData *context, CtrFsStatus *status)
    CTR_ARG_NONNULL(1);

/**
 * @brief Change file size (using a filename path).
 * @param[in] context Filesystem Context Data.
 * @param[in] path Path to a file.
 * @param[in] size New file size.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsTruncate(CtrFsContextData *context,
                       const char *path,
                       uint64_t size) CTR_ARG_NONNULL(1);

/**
 * @brief Change file size (using a file descriptor).
 * @param[in] context Filesystem Context Data.
 * @param[in] fd File descriptor.
 * @param[in] size New file size.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsFtruncate(CtrFsContextData *context, int fd, uint64_t size)
    CTR_ARG_NONNULL(1);

/**
 * @brief Get free space on the SD card and NAND filesystem.
 * @param[in] context Filesystem Context Data.
 * @param[out] sdmc_size Available space on the SD card.
 * @param[out] nand_size Available space on the NAND filesystem.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFsGetAvailableSize(CtrFsContextData *context,
                               uint64_t *sdmc_size,
                               uint64_t *nand_size) CTR_ARG_NONNULL(1);

CTR_API_END

#endif
