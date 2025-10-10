#include <stdio.h>

#include "vipx.h"

static void save_frame(void *p, int xs, int ys, int ps)
{
	char s[BUFSIZ];
	FILE *fp;

	sprintf(s, "frame.raw");
	fp = fopen(s, "wb");
	if (fp != NULL) {
		fwrite(p, ps, xs*ys, fp);
		fclose(fp);
	}

	return;
}

int main(int argc, char *argv[])
{
	int xs, ys, ps;
	void *p;

	if (argc < 2) {
		printf("Usage: vipx-simple imager\n");
		return -1;
	}

	vipx_open(argv[1]);

	vipx_set_mode(0);

	xs = vipx_get_width();
	ys = vipx_get_height();
	ps = vipx_get_pixel_size();
	p = malloc(xs*ys*ps);

	vipx_set_acquisition_type(VIPX_RAW_FRAME);

	vipx_acquisition_start_s();
	vipx_acquisition_wait_s(1000, p, xs*ys*ps);
	save_frame(p, xs, ys, ps);
	vipx_acquisition_stop_s();

	free(p);

	vipx_close();

	return 0;
}
