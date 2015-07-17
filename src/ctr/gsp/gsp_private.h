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

/** Default thread stack size. */
#define CTR_GSP_STACK_SIZE (0x00001000)

CTR_API_BEGIN

enum {
	CTR_GSP_EVENT_PSC0 = 0x00,
	CTR_GSP_EVENT_PSC1 = 0x01,
	CTR_GSP_EVENT_VBLANK0 = 0x02,
	CTR_GSP_EVENT_VBLANK1 = 0x03,
	CTR_GSP_EVENT_PPF = 0x04,
	CTR_GSP_EVENT_P3D = 0x05,
	CTR_GSP_EVENT_DMA = 0x06,

	CTR_GSP_EVENT_MAX,
};

enum {
	CTR_GSP_EXIT = 0x00,
	CTR_GSP_RUNNING = 0x01,
};

struct CtrGspContextDataPrivate {
	/**
	 * @brief GSP::GPU Service Handle.
	 */
	uint32_t handle;
	/**
	 * @brief Event handle.
	 */
	uint32_t event_handle;
	/**
	 * @brief Thread handle.
	 */
	uint32_t thread_handle;
	/**
	 * @brief Shared memory handle.
	 */
	uint32_t shmem_handle;
	/**
	 * @brief Shared memory address.
	 */
	uint8_t* shmem;
	/**
	 * @brief Handles to GSP events.
	 */
	uint32_t events[CTR_GSP_EVENT_MAX];
	/**
	 * @brief Event data.
	 */
	volatile uint8_t* event_data;
	/**
	 * @brief Stack for the event thread.
	 */
	uint8_t event_stack[CTR_GSP_STACK_SIZE] __attribute__((aligned(8)));
	/**
	 * @brief Atomic status integer. Set to CTR_GSP_RUNNING when
	 * running, CTR_GSP_EXIT when time to exit.
	*/
	uint32_t status;

	uint8_t* top_framebuffer;
	uint8_t* stereo_framebuffer;
	uint8_t* bottom_framebuffer;
	CtrGspColorFormat top_format;
	CtrGspColorFormat stereo_format;
	CtrGspColorFormat bottom_format;

};

static int ctrGspAcquireRight(CtrGspContextData* context);

static int ctrGspCreateEventHandler(CtrGspContextData* context);

static void ctrGspEventThreadMain(void* arg);

static int ctrGspReleaseRight(CtrGspContextData* context);

static int ctrGspSetLcdForceBlack(CtrGspContextData* context);

static int ctrGspFlushDataCache(CtrGspContextData* context, uint8_t* addr, uint32_t size);


CTR_API_END

#endif
