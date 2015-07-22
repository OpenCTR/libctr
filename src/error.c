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

#include "ctr/atomic.h"

#include "ctr/base_private.h"
#include "ctr/sys_private.h"
#include "ctr/error_private.h"


/**
 * @var cerrorno
 * @brief This is thread-safe, because we only allow reading
 * or writing <code>cerrorno</code> using atomic operations,
 * which are <em>always</em> thread-safe.
 */
static int cerrorno = 0;

int cerror(void) {
    return (int)ctrAtomicRead((uint32_t*)&cerrorno);
}

void cerror_set(int error) {
    ctrAtomicStore((uint32_t*)&cerrorno, error);
}
