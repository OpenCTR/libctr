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

#include "ctr/base.h"
#include "ctr/sys.h"
#include "ctr/error.h"
#include "ctr/atomic.h"
#include "ctr/gsp.h"

static uint32_t ctr_gsp_handle = 0;

static void ctrGspInit(void) CTR_INIT;
static void ctrGspExit(void) CTR_FINI;

CtrGspContextData* gCtrGspCurrentContext = NULL;

static void ctrGspInit(void) {
	int ret;

	ret = sys_service_get_handle(&ctr_gsp_handle, "gsp::Gpu");
	if(ret != 0) {
		sys_debug_printf("Error obtaining GSP::GPU handle: 0x%08x\n", ret);
		sys_process_exit();
	}

	ret = ctrGspContextDataInitialize(gCtrGspCurrentContext);
	if(ret != 0) {
		sys_debug_printf("Error allocating GSP context: 0x%08x\n", cerror());
		sys_process_exit();
	}

}

static void ctrGspExit(void) {
	sys_close_handle(ctr_gsp_handle);
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

	ret = sys_control_memory(&meminfo.base_addr, meminfo.base_addr, 0x00, meminfo.size, 0x0003, 0x00);
	if(ret != 0) {
		(*cerrorptr()) = ret;
		return -1;
	}

	return 0;
}

int ctrGspFlush(CtrGspContextData* context) {
	if(context == NULL) {
		(*cerrorptr()) = EINVAL;
		return -1;
	}

	return -1;
}

int ctrGspWaitForVSync(CtrGspContextData* context, CtrGspScreen screen) {
	if(context == NULL) {
		(*cerrorptr()) = EINVAL;
		return -1;
	}

	return -1;
}

int ctrGspSetTarget(CtrGspContextData* context, const CtrGspTarget* tgt) {
	if((context == NULL) || (tgt == NULL)) {
		(*cerrorptr()) = EINVAL;
		return -1;
	}

	return -1;
}

int ctrGspContextDataInitialize(CtrGspContextData* context) {
	context = (CtrGspContextData*)malloc(sizeof(struct CtrGspContextDataPrivate));
	if(context == NULL) {
		(*cerrorptr()) = ENOMEM;
		return -1;
	}

	memset(context, 0x00, sizeof(struct CtrGspContextDataPrivate));

	return 0;
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

