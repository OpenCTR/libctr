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

#ifndef __LIBCTR_GSP_PRIVATE_H__
#define __LIBCTR_GSP_PRIVATE_H__

/**
 * @file ctr/gsp/gsp_private.h
 * @brief Private GSP API.
 */

#include "ctr/base.h"

CTR_API_BEGIN

struct CtrGspContextDataPrivate {
	/**
	 * @brief Number of users.
	 * @details context->users is always incremented 
	 */
	uint32_t users;
};

CTR_API_END

#endif
