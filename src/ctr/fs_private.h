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

#ifndef __LIBCTR_FS_PRIVATE_H__
#define __LIBCTR_FS_PRIVATE_H__

/**
 * @file ctr/fs_private.h
 * @brief Filesystem API (Private).
 */

#include "ctr/base_private.h"
#include "ctr/fs.h"

CTR_API_BEGIN

struct CtrFsContextDataPrivate {
    /**
     * @brief FS::USER Service Handle.
     */
    uint32_t handle;
};

CTR_API_END

#endif
