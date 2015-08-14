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

#ifndef __LIBCTR_FONT_H__
#define __LIBCTR_FONT_H__

/**
 * @file ctr/font.h
 * @brief Font API.
 */

#include "ctr/base.h"

CTR_API_BEGIN

/**
 * @typedef CtrFont
 * @brief Font datatype.
 * @details <code>CtrFont</code> is an opaque type. <i>It
 * should NEVER be modified by users</i>.
 */
typedef struct CtrFontPrivate CtrFont;

/**
 * @brief Initialize the libctr built-in font.
 * @details This function initializes the TrueType
 * font built into libctr. The font is attached
 * to CTR_GSP_THIS, so be careful about calling
 * this function in a thread.
 * @return On success, 0 is returned. On error, -1 is returned.
 */
CAPI int ctrFontInitDefault(void);

/**
 * @brief Create a new font variable.
 * @return New CtrFont.
 */
CAPI CtrFont* ctrFontNew(void);

/**
 * @brief Free a CtrFont.
 * @param[in] font CtrFont.
 */
CAPI void ctrFontFree(CtrFont* font) CTR_ARG_NONNULL(1);

/**
 * @brief Open a font from a file.
 * @param font Address of CtrFont to hold the font.
 * @param path Path to a font file on the filesystem.
 * @retval 0 Success.
 * @retval -1 Error.
 */
CAPI int ctrFontOpenFont(CtrFont* font, const char* path) CTR_ARG_NONNULL(1);

/**
 * @brief Open a font from a file.
 * @param font Address of CtrFont to hold the font.
 * @param addr Address containing the font data.
 * @param size Size of the font data.
 * @retval 0 Success.
 * @retval -1 Error.
 */
CAPI int ctrFontOpenFontMemory(CtrFont* font, const void* addr, const uint32_t size) CTR_ARG_NONNULL(1,2);

CTR_API_END

#endif