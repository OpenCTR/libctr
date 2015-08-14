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

#ifndef __LIBCTR_FONT_PRIVATE_H__
#define __LIBCTR_FONT_PRIVATE_H__

/**
 * @file ctr/font_private.h
 * @brief Font API (Private).
 */

#include "ctr/base_private.h"
#include "ctr/gsp_private.h"
#include "ctr/font.h"

CTR_API_BEGIN

/**
 * @brief CTR Font.
 * @todo Make this less TTF specific.
 */
struct CtrFontPrivate {
    /** Font data. */
    void* buffer;
    /** Font size. */
    uint32_t buffer_size;
    /** Offset of the start of the font. */
    uint32_t start;
    /** Number of glyphs. */
    uint32_t glyphs;
    /** Glyph locations offset. */
    int loca;
    /** Font header offset. */
    int head;
    /** Glyph outline offset. */
    int glyf;
    /** Horizontal header offset. */
    int hhea;
    /** Horizontal metrics offset. */
    int hmtx;
    /** Kerning offset. */
    int kern;
    /** Character map. */
    int cmap;
    /** Format, needed to map from glyph index to glyph. */
    int format;
};

CTR_API_END

#endif