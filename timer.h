#pragma once
///通用计时器

#include<functional>

class Timer {
public:
	Timer(){}
	~Timer() {}

	void on_update(int delta) {
		if (paused)return;
		
		pass_time += delta;
		if (pass_time >= wait_time) {

			if ((!one_shot || (one_shot && !shotted)) && callback) {///不是单次触发 或者 是单次触发但还没有触发 && callback有效
				callback();
			}
			shotted = true;
			pass_time = 0;
		}

		
	}
	
	void restart() {
		pass_time = 0;
		shotted = false;
	}

	void set_wait_time(int time) {
		wait_time = time;
	}

	void set_one_shot(bool flag){
		one_shot = flag;
	}

	void pause() {
		paused = true;
	}
	void resume() {
		paused = false;
	}


	void set_callback(std::function<void()> callback) {
		this->callback = callback;
	}


protected:
	int pass_time = 0;
	int wait_time = 0;
	bool paused = false;//是否暂停
	bool shotted = false;//是否触发
	bool one_shot = false;//单次触发
	std::function<void()> callback;

};


