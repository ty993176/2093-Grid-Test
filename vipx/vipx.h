#ifndef VIPX_H
#define VIPX_H

#include "stdint.h"

#include <windows.h>

#include "FluoroStructs.h"
#include "HcpErrors.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
	VIPX_RAW_FRAME,
	VIPX_CORRECTED_FRAME,
	VIPX_OFFSET_CORRECTED_FRAME,
	VIPX_GAIN_CORRECTED_FRAME,
	VIPX_PREVIEW_FRAME_FLAG = 0x0100,
};

enum {
	VIPX_TRIGGER_SOFT,
	VIPX_TRIGGER_INTERNAL,
	VIPX_TRIGGER_EXTERNAL,
	VIPX_TRIGGER_AUTO,
};

typedef enum {
	VIPX_MESSAGE,
	VIPX_IMAGE,
} VIPXCondition;

typedef enum {
	VIPX_IMAGE_UNKNOWN,
	VIPX_IMAGE_PREVIEW,
	VIPX_IMAGE_FINAL,
	VIPX_IMAGE_FLUORO,
} VIPXImageType;

typedef struct {
	uint32_t xs, ys, ps;
	uint32_t type;
	void *pixel;
} VIPXImage;

typedef int (*VIPXCallback)(VIPXCondition condition,
			    const void *detail,
			    void *data);

int vipx_open(const char *imager);
int vipx_close(void);

int vipx_set_mode(int mode);
int vipx_set_trigger_source(int source);
int vipx_set_frame_rate(int fps1000);

int vipx_set_analog_gain_level(int gain0_level, int gain1_level);
int vipx_set_binning(int x, int y);
int vipx_set_region(int x0, int r0, int xs, int ys);

int vipx_get_width(void);
int vipx_get_height(void);
int vipx_get_pixel_size(void);

int vipx_set_acquisition_type(int type);

int vipx_acquisition(VIPXCallback callback, void *data);
int vipx_offset_calibration(VIPXCallback callback, void *data);
int vipx_gain_calibration(VIPXCallback callback, void *data,
					int integration_time);

int vipx_acquisition_start(int n,
					HANDLE *pevent, SLivePrms **plive);
int vipx_acquisition_wait(HANDLE event, int timeout);
int vipx_acquisition_stop(HANDLE event);

int vipx_acquisition_start_s(void);
int vipx_acquisition_wait_s(int timeout, void *p, int size);
int vipx_acquisition_stop_s(void);

#ifdef __cplusplus
}
#endif

#endif /* VIPX_H */
