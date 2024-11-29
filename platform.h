#pragma once

#include"camera.h"

#include<easyx.h>
#include"tools.h"

extern bool is_debug;

class Platform {
public:
	Platform(){}
	~Platform(){}
	
	void on_draw(const Camera& camera)const {
		putimage_Alpha(camera, render_pos.x, render_pos.y,img);
		if (is_debug) {
			setlinecolor(RED);
			debug_line(camera,(int)shape.left,shape.y, (int)shape.right, (int)shape.y);

		}

	}

public:
	//平台碰撞外形
	struct CollisionShape {
		float y;
		float left, right;
	};

	CollisionShape shape;
	IMAGE* img = nullptr;
	POINT render_pos = { 0 };
};