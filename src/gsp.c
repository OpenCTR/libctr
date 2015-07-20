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

#include "ctr/base_private.h"
#include "ctr/sys_private.h"
#include "ctr/error_private.h"
#include "ctr/gsp_private.h"
#include "ctr/atomic.h"

static void ctrGspInit(void) CTR_INIT;
static void ctrGspExit(void) CTR_FINI;

CtrGspContextData* CTR_GSP_THIS = NULL;

static void ctrGspInit(void) {
    int ret;

    CTR_GSP_THIS = ctrGspContextDataNew();
    if(CTR_GSP_THIS == NULL) {
        sys_debug_printf("Error allocating GSP context: 0x%08x\n", cerror());
        sys_process_exit();
    }
}

static void ctrGspExit(void) {
    ctrGspContextDataFree(CTR_GSP_THIS);
}

void* ctrGspLocalAlign(const uint32_t alignment, const uint32_t size) {
    int ret;
    uint32_t addr;

    if(alignment % 2 != 0) {
        (*cerrorptr()) = EINVAL;
        return NULL;
    } else if(size <= 0) {
        (*cerrorptr()) = EINVAL;
        return NULL;
    }

    ret = sys_control_memory(&addr, 0x00, 0x00, size, 0x00010003, 0x03);
    if(ret != 0) {
        (*cerrorptr()) = ret;
        return NULL;
    }

    addr = (addr + (alignment - 1)) & (~(alignment - 1));

    return (void*)addr;
}

int ctrGspLocalFree(void* addr) {
    int ret;
    sys_memory_info meminfo;
    sys_page_info pageinfo;

    ret = sys_query_memory(&meminfo, &pageinfo, (uint32_t)addr);
    if(ret != 0) {
        (*cerrorptr()) = ret;
        return -1;
    }

    ret = sys_control_memory(&meminfo.base_addr,
                             meminfo.base_addr,
                             0x00,
                             meminfo.size,
                             0x0003,
                             0x00);
    if(ret != 0) {
        (*cerrorptr()) = ret;
        return -1;
    }

    return 0;
}

int ctrGspSetTarget(CtrGspContextData* context, const CtrGspTarget* tgt) {
    uint32_t* cmdbuf = NULL;
    int ret;

    if((context == NULL) || (tgt == NULL)) {
        (*cerrorptr()) = EINVAL;
        return -1;
    }

    if((tgt->screen != CTR_GSP_TOP_SCREEN) &&
       (tgt->screen != CTR_GSP_BOTTOM_SCREEN)) {
        // TODO: CTR_GSP_ERROR_INVALID_SCREEN
        (*cerrorptr()) = EINVAL;
        return -1;
    }

    cmdbuf = sys_get_commandbuffer();

    cmdbuf[0] = 0x00050200;

    switch(tgt->screen) {
        case CTR_GSP_TOP_SCREEN:
            /* Use the target as the latest-registered framebuffers (when
             * flushing) */
            if(tgt->address[0] != NULL) {
                context->top_framebuffer = tgt->address[0];
            }
            if(tgt->address[1] != NULL) {
                context->stereo_framebuffer = tgt->address[1];
            }
            context->top_format = tgt->format;
            context->stereo_format = tgt->format;

            cmdbuf[1] = 0x00;
            cmdbuf[5] = CTR_GSP_SCREEN0_WIDTH * ctrGspPixelSize(tgt->format);
            if(tgt->address[1] != NULL) {
                cmdbuf[6] = (1 << 8) | (1 << 6) | (1 << 5) | (tgt->format);
            } else {
                cmdbuf[6] = (1 << 8) | (1 << 6) | (0 << 5) | (tgt->format);
            }
            break;
        case CTR_GSP_BOTTOM_SCREEN:
            /* Use the target as the latest-registered framebuffers (when
             * flushing) */
            if(tgt->address[0] != NULL) {
                context->bottom_framebuffer = tgt->address[0];
            }
            context->bottom_format = tgt->format;

            cmdbuf[1] = 0x01;
            cmdbuf[5] = CTR_GSP_SCREEN1_WIDTH * ctrGspPixelSize(tgt->format);
            cmdbuf[6] = (tgt->format);
            break;
        default:
            break;
    }

    cmdbuf[2] = 0x01;
    cmdbuf[3] = ((uint32_t)tgt->address[0]);
    cmdbuf[4] = ((uint32_t)tgt->address[1]);
    cmdbuf[7] = 0x01;
    cmdbuf[8] = 0x00000000;

    ret = sys_send_sync_request(context->handle);
    if(ret != 0) {
        (*cerrorptr()) = ret;
        return -1;
    }

    ret = cmdbuf[1];
    if(ret != 0) {
        (*cerrorptr()) = ret;
        return -1;
    }

    return 0;
}

CtrGspContextData* ctrGspContextDataNew(void) {
    int ret;
    CtrGspContextData* context = NULL;
    const uint32_t size = sizeof(struct CtrGspContextDataPrivate);

    context = (CtrGspContextData*)malloc(size);
    if(context == NULL) {
        (*cerrorptr()) = ENOMEM;
        return NULL;
    }

    memset(context, 0x00, size);

    ret = sys_service_get_handle(&context->handle, "gsp::Gpu");
    if(ret != 0) {
        (*cerrorptr()) = ret;
        return NULL;
    }

#if 0
    /* Removed because Citra-emu doesn't implement AcquireRight. */
    ret = ctrGspAcquireRight(context);
    if(ret != 0) {
        (*cerrorptr()) = ret;
        return NULL;
    }
#endif

    ret = ctrGspCreateEventHandler(context);
    if(ret != 0) {
        (*cerrorptr()) = ret;
        return NULL;
    }

    ret = ctrGspSetLcdForceBlack(context);
    if(ret != 0) {
        (*cerrorptr()) = ret;
        return NULL;
    }

    return context;
}

uint8_t ctrGspPixelSize(CtrGspColorFormat format) {
    if(format == CTR_GSP_COLOR_FORMAT_RGBA8) {
        return 4;
    } else if(format == CTR_GSP_COLOR_FORMAT_BGR8) {
        return 3;
    } else if(format == CTR_GSP_COLOR_FORMAT_RGB5A1) {
        return 2;
    } else if(format == CTR_GSP_COLOR_FORMAT_RGB565) {
        return 2;
    } else if(format == CTR_GSP_COLOR_FORMAT_RGBA4) {
        return 2;
    }
    return 0;
}

static int ctrGspAcquireRight(CtrGspContextData* context) {
    int ret;
    uint32_t* cmdbuf = NULL;

    cmdbuf = sys_get_commandbuffer();
    cmdbuf[0] = 0x00160042;
    cmdbuf[1] = 0x00000000;
    cmdbuf[2] = 0x00000000;
    cmdbuf[3] = 0xFFFF8001;

    ret = sys_send_sync_request(context->handle);
    if(ret != 0) {
        return ret;
    }

    ret = cmdbuf[1];
    if(ret != 0) {
        return ret;
    }

    return 0;
}

static int ctrGspCreateEventHandler(CtrGspContextData* context) {
    int ret;
    uint8_t i;
    uint8_t j;
    uint32_t* cmdbuf = NULL;
    uint32_t thread_id = 0;

    ret = sys_event_create(&context->event_handle, 0x00);
    if(ret != 0) {
        return ret;
    }

    cmdbuf = sys_get_commandbuffer();
    cmdbuf[0] = 0x00130042;
    cmdbuf[1] = 0x00000001;
    cmdbuf[2] = 0x00000000;
    cmdbuf[3] = ((uint32_t)context->event_handle);

    ret = sys_send_sync_request(context->handle);
    if(ret != 0) {
        return ret;
    }

#if 0
    /* Caused errors in Citra */
    ret = cmdbuf[1];
    if(ret != 0) {
        return ret;
    }
#endif

    thread_id = cmdbuf[2];

    context->shmem_handle = cmdbuf[4];
    context->shmem = ((uint8_t*)0x10002000);

    ret = sys_map_memoryblock(context->shmem_handle,
                              (uint32_t)context->shmem,
                              0x00000003,
                              0x10000000);
    if(ret != 0) {
        return ret;
    }

    for(i = 0; i < CTR_GSP_EVENT_MAX; i++) {
        ret = sys_event_create(&context->events[i], 0x00);
        if(ret != 0) {
            for(j = 0; j < i; j++) {
                sys_close_handle(context->events[i]);
            }
            return ret;
        }
    }

    context->event_data =
        ((volatile uint8_t*)context->shmem) + (thread_id * 0x00000040);

    uint32_t* stack = (uint32_t*)(context->event_stack + 0x00004000);

    /* Set status to running. */
    ctrAtomicStore(&context->status, CTR_GSP_RUNNING);

    ret = sys_thread_create_ex(&context->thread_handle,
                               ctrGspEventThreadMain,
                               (uint32_t)context,
                               stack,
                               0x31,
                               0xFFFFFFFE);
    if(ret != 0) {
        return ret;
    }

    return 0;
}

static void ctrGspEventThreadMain(void* arg) {
    uint32_t i;
    CtrGspContextData* context = (CtrGspContextData*)arg;

    while(ctrAtomicRead(&context->status) == CTR_GSP_RUNNING) {
        sys_wait_sync(context->event_handle, UINT64_MAX);
        sys_event_clear(context->event_handle);

        int count = context->event_data[1];
        int cur = context->event_data[0];
        int last = cur + count;
        while(last >= 0x34) {
            last -= 0x34;
        }
        for(i = 0; i < count; i++) {
            int curEvent = context->event_data[0x0C + cur];
            cur++;
            if(cur >= 0x34) {
                cur -= 0x34;
            }
            if(curEvent >= CTR_GSP_EVENT_MAX) {
                continue;
            }
            sys_event_signal(context->events[curEvent]);
        }
        context->event_data[0] = last;
        context->event_data[1] -= count;
        context->event_data[2] = 0;
    }

    sys_thread_exit();
}

void ctrGspContextDataFree(CtrGspContextData* context) {
    uint8_t i;

    if(context == NULL) {
        (*cerrorptr()) = EINVAL;
        return;
    }

    ctrAtomicStore(&context->status, CTR_GSP_EXIT);

    sys_wait_sync(context->thread_handle, 1000000000);
    sys_close_handle(context->thread_handle);
    sys_close_handle(context->event_handle);

    /* TODO: Free SHMEM/SHMEM handle? */

    for(i = 0; i < CTR_GSP_EVENT_MAX; i++) {
        sys_close_handle(context->events[i]);
    }

    ctrGspReleaseRight(context);

    sys_close_handle(context->handle);

    free(context);
}

static int ctrGspReleaseRight(CtrGspContextData* context) {
    int ret;
    uint32_t* cmdbuf = NULL;

    cmdbuf = sys_get_commandbuffer();
    cmdbuf[0] = 0x00170000;

    ret = sys_send_sync_request(context->handle);
    if(ret != 0) {
        return ret;
    }

    ret = cmdbuf[1];
    if(ret != 0) {
        return ret;
    }

    return 0;
}

static int ctrGspSetLcdForceBlack(CtrGspContextData* context) {
    int ret;
    uint32_t* cmdbuf = NULL;

    cmdbuf = sys_get_commandbuffer();
    cmdbuf[0] = 0x000B0040;
    cmdbuf[1] = 0x00000000;

    ret = sys_send_sync_request(context->handle);
    if(ret != 0) {
        return ret;
    }

    ret = cmdbuf[1];
    if(ret != 0) {
        return ret;
    }

    return 0;
}

int ctrGspWaitForVBlank(CtrGspContextData* context, CtrGspScreen screen) {
    int ret;

    switch(screen) {
        case CTR_GSP_SCREEN0: {
            sys_event_clear(context->events[CTR_GSP_EVENT_VBLANK0]);
            sys_wait_sync(context->events[CTR_GSP_EVENT_VBLANK0], UINT64_MAX);
            break;
        }
        case CTR_GSP_SCREEN1: {
            sys_event_clear(context->events[CTR_GSP_EVENT_VBLANK1]);
            sys_wait_sync(context->events[CTR_GSP_EVENT_VBLANK1], UINT64_MAX);
            break;
        }
        case CTR_GSP_SCREEN_ALL: {
            int32_t count;
            uint32_t events[2] = { context->events[CTR_GSP_EVENT_VBLANK0],
                                   context->events[CTR_GSP_EVENT_VBLANK1] };
            sys_event_clear(context->events[CTR_GSP_EVENT_VBLANK0]);
            sys_event_clear(context->events[CTR_GSP_EVENT_VBLANK1]);
            ret = sys_wait_sync2(&count, events, 2, 1, UINT64_MAX);
            if(ret != 0) {
                (*cerrorptr()) = ret;
                return -1;
            }
            break;
        }
        default: {
            (*cerrorptr()) = EINVAL;
            return -1;
        }
    }

    return 0;
}

int ctrGspFlush(CtrGspContextData* context) {
    int ret;

    if(context == NULL) {
        (*cerrorptr()) = EINVAL;
        return -1;
    }

    const uint32_t top_size = CTR_GSP_SCREEN0_WIDTH * CTR_GSP_SCREEN0_HEIGHT *
                              ctrGspPixelSize(context->top_format);
    const uint32_t bottom_size = CTR_GSP_SCREEN1_WIDTH *
                                 CTR_GSP_SCREEN1_HEIGHT *
                                 ctrGspPixelSize(context->bottom_format);

    if(context->top_framebuffer != NULL) {
        ret = ctrGspFlushDataCache(context, context->top_framebuffer, top_size);
        if(ret != 0) {
            (*cerrorptr()) = ret;
            return ret;
        }
    }

    if(context->stereo_framebuffer != NULL) {
        ret = ctrGspFlushDataCache(
            context, context->stereo_framebuffer, top_size);
        if(ret != 0) {
            (*cerrorptr()) = ret;
            return ret;
        }
    }

    if(context->bottom_framebuffer != NULL) {
        ret = ctrGspFlushDataCache(
            context, context->bottom_framebuffer, bottom_size);
        if(ret != 0) {
            (*cerrorptr()) = ret;
            return ret;
        }
    }

    return 0;
}

static int ctrGspFlushDataCache(CtrGspContextData* context,
                                uint8_t* addr,
                                uint32_t size) {
    int ret;
    uint32_t* cmdbuf = NULL;

    cmdbuf = sys_get_commandbuffer();
    cmdbuf[0] = 0x00080082;
    cmdbuf[1] = ((uint32_t)addr);
    cmdbuf[2] = ((uint32_t)size);
    cmdbuf[3] = 0x00000000;
    cmdbuf[4] = 0xFFFF8001;

    ret = sys_send_sync_request(context->handle);
    if(ret != 0) {
        return ret;
    }

    ret = cmdbuf[1];
    if(ret != 0) {
        return ret;
    }

    return 0;
}
