#pragma once
#include"atlas.h"
#include"tools.h"
#include<functional>


class Animation {


public:
	Animation() {
	}
	~Animation(){}

	void reset() {
		timer = 0;
		idx_frame = 0;
	}

	void set_atlas(Atlas* new_atlas) {
		reset();
		atlas = new_atlas;
	}

	void set_loop(bool flag) {
		is_loop = flag;
	}

	void set_interval(int ms) {
		interval = ms;
	};

	int get_idx_frame() {
		return idx_frame;
	}

	bool get_is_loop() {
		return is_loop;
	}

	IMAGE* get_frame() {
		return atlas->get_image(idx_frame);
	}

	bool check_finished() {
		if (is_loop)return false;

		return (idx_frame == atlas->get_size() - 1);
	 }

	void on_update(int delta ) {
		timer +=delta ;
		if (timer >= interval) {
			timer = 0;
			idx_frame++;
			if (idx_frame >= atlas->get_size()) {
				idx_frame = is_loop ? 0 : atlas->get_size() - 1;
				if (!is_loop && callback) {
					callback();
				}
			}
		}
	}

	void on_draw(int x,int y) {
		putimage_Alpha(x, y, atlas->get_image(idx_frame));
	}

	void set_callback(std::function<void()> callback) {
		
		this->callback = callback;

	}


private:

	int timer = 0;///计时器--->后续可用通用计时器类替换
	int interval = 0;///帧间隔
	int idx_frame = 0;//帧索引
	bool is_loop = true;//是否循环播放
	Atlas* atlas = nullptr;

	std::function<void()> callback;///std::function回调函数实现延迟对象生命周期


};