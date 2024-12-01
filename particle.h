#pragma once

#include"atlas.h"
#include"vector2.h"
#include"camera.h"
#include"tools.h"


class Particle {
public:
	Particle(){}
	Particle(const Vector2&pos,Atlas*atlas,int life_span):position(pos),atlas(atlas),life_span(life_span)
	{}

	~Particle(){}
	
	void set_atlas(Atlas* new_altas) {
		atlas = new_altas;
	}

	void set_pos(Vector2 pos) {
		position = pos;
	}

	void set_lifespan(int val) {
		life_span = val;
	}

	bool check_valid()const {
		return valid;
	}

	void on_update(int delta) {
		timer += delta;
		if (timer >= life_span) {
			timer = 0;
			idx_frame++;
			if(idx_frame >= atlas->get_size()) {
				idx_frame = atlas->get_size() - 1;//防止越界？ 
				valid = false;

			}
		}
	}

	void on_draw(const Camera& camera)const
	{
		putimage_Alpha(camera,position.x, position.y, atlas->get_image(idx_frame));
		///
	}
private:

	int timer = 0;
	int life_span = 0;///单帧粒子动画持续时长
	int idx_frame = 0;
	Vector2 position;
	bool valid = true;///粒子对象是否有效
	Atlas* atlas = nullptr;


};