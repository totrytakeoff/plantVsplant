#pragma once

#include<iostream>
#include<graphics.h>
#include"camera.h"
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
inline void putimage_Alpha(int x, int y,int width,int height, IMAGE* img,int src_x,int src_y) {
	int w =width>0?width: img->getwidth();
	int h =height>0?height: img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), x, y, w, h, GetImageHDC(img), src_x, src_y, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });

}///利用Windows api重新封装putimage使之能透明显示

inline void putimage_Alpha(const Camera& camera,int x, int y, IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();
	const Vector2& pos_camera = camera.Get_pos();
	AlphaBlend(GetImageHDC(GetWorkingImage()), (int)(x-pos_camera.x), (int)(y-pos_camera.y), w, h, GetImageHDC(img), 0, 0, w, h, {AC_SRC_OVER,0,255,AC_SRC_ALPHA});

}///利用Windows api重新封装putimage使之能透明显示

inline void debug_line(const Camera& camera,int x1,int y1,int x2,int y2) {
	const Vector2 pos_camera = camera.Get_pos();
	line((int)(x1 - pos_camera.x), (int)(y1 - pos_camera.y), (int)(x2 - pos_camera.x), (int)(y2 - pos_camera.y));

}

inline void sketch_image(IMAGE* src, IMAGE* dst) {///受击变白

	int w = src->getwidth();
	int h = src->getheight();

	Resize(dst, w, h);

	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int idx = y * w + x;
			dst_buffer[idx] = BGR(RGB(255, 255, 255)) | (src_buffer[idx] & 0xFF000000);
		}

	}

}