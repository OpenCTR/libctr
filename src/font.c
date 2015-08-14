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

#include "ctr/font_private.h"
#include "ctr/error_private.h"

////////////////////////////////////////////////////////////////////////////////

#define tt_tag4(p,c0,c1,c2,c3) ((p)[0] == (c0) && (p)[1] == (c1) && (p)[2] == (c2) && (p)[3] == (c3))
#define tt_tag(p,str) tt_tag4(p, str[0], str[1], str[2], str[3])

static uint16_t ttUSHORT(const uint8_t* p) {
    return p[0] * 256 + p[1];
}

static uint32_t ttULONG(const uint8_t* p)  {
    return ((p[0] << 24) + (p[1] << 16) + (p[2] << 8) + (p[3] << 0));
}

static uint32_t font_find_table(const uint8_t* data, uint32_t fontstart, const char *tag) {
    int32_t num_tables = ttUSHORT(data + fontstart + 4);
    uint32_t tabledir = fontstart + 12;
    int32_t i;
    for(i=0; i<num_tables; i++) {
        uint32_t loc = tabledir + 16 * i;
        if(tt_tag(data + loc + 0, tag)) {
            return ttULONG(data + loc + 8);
        }
   }
   return 0;
}


////////////////////////////////////////////////////////////////////////////////

CtrFont* ctrFontNew(void) {
    CtrFont* font = NULL;

    const uint32_t size = sizeof(struct CtrFontPrivate);

    font = (CtrFont*)malloc(size);
    if(font == NULL) {
        cerror_set(ENOMEM);
        return NULL;
    }

    memset(font, 0x00, size);

    return font;
}

int ctrFontOpenFontMemory(CtrFont* font, const void* addr, const uint32_t size) {
    int cmap;
    int t;
    int tables;
    int i;
    uint16_t id;
    uint16_t eid;
    uint32_t encoding_record;

    if(font == NULL) {
        cerror_set(EINVAL);
        return -1;
    } else if(addr == NULL) {
        cerror_set(EINVAL);
        return -1;
    } else if(size <= 0) {
        cerror_set(EINVAL);
        return -1;
    }

    font->buffer_size = size;
    font->buffer = (void*)addr;

    cmap = font_find_table((uint8_t*)addr, 0, "cmap");
    font->loca = font_find_table(addr, 0, "loca");
    font->head = font_find_table(addr, 0, "head");
    font->glyf = font_find_table(addr, 0, "glyf");
    font->hhea = font_find_table(addr, 0, "hhea");
    font->hmtx = font_find_table(addr, 0, "hmtx");
    font->kern = font_find_table(addr, 0, "kern");

    if(!cmap || !font->loca || !font->head || !font->glyf || !font->hhea || !font->hmtx) {
        // TODO: CTR_FONT_UNRECOGNIZED (?)
        return -1;
    }

    t = font_find_table(addr, 0, "maxp");
    if(t) {
        font->glyphs = ttUSHORT(addr + t + 4);
    } else {
        font->glyphs = 0x0000FFFF;
    }

    tables = ttUSHORT(addr + cmap + 2);
    font->cmap = 0;
    for(i=0; i<tables; i++) {
        encoding_record = cmap + 4 + 8 * i;
        id = ttUSHORT(addr + encoding_record);
        switch(id) {
            case 3:
                /* Microsoft. */
                eid = ttUSHORT(addr + encoding_record + 2);
                switch(eid) {
                    case 1:
                    case 10:
                        font->cmap = cmap + ttULONG(addr + encoding_record + 4);
                        break;
                    default:
                        break;
                }
            case 0:
                /* Unicode. */
                font->cmap = cmap + ttULONG(addr + encoding_record + 4);
                break;
            default:
                break;
        }
    }

    if(font->cmap == 0) {
        // TODO: CTR_FONT_INVALID
        return -1;
    }

    font->format = ttUSHORT(addr + font->head + 50);

    return 0;
}
