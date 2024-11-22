#pragma once


#include<graphics.h>

#pragma comment(lib,"MSIMG32.LIB")///注意大小写

inline void flip_image(IMAGE* src ,IMAGE*dst) {///图片翻转

	int w = src->getwidth();
	int h = src->getheight();

	Resize(dst, w, h);
	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int idx_src = y * w + x;
			int idx_dst = y * w + (w - x - 1);
			dst_buffer[idx_dst] = src_buffer[idx_src];

		}

	}
}

inline void putimage_Alpha(int x, int y, IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });

}///利用Windows api重新封装putimage使之能透明显示
