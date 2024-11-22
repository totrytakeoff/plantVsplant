#pragma once

#include<iostream>
#include"scene_manager.h"
#include"scene.h"
#include"atlas.h"
#include"animation.h"
#include"camera.h"
#include"timer.h"


extern SceneManager scene_manager;
extern IMAGE img_menu_background;



class Menuscene :public Scene {
public:
	Menuscene() {

	}
	~Menuscene() {

	}

	void on_enter() {///处理进入时的初始化逻辑
		mciSendString(_T("play bgm_menu repeat from 0"), NULL, 0, NULL);

	
	}
	 
	void on_update(int delta) {//处理数据

	}

	void on_draw(const Camera& camera) {//绘制
		putimage(0, 0, &img_menu_background);

	}

	void on_input(const ExMessage& msg) {///处理玩家输入
		if (msg.message == WM_KEYUP) {
			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			scene_manager.switch_scene(SceneManager::SceneType::Select);
		}

	}

	void on_exit() {///处理场景退出时的卸载逻辑

	}


private:
	Animation animation_peashooter_run_right;
	Camera camera;
	Timer timer;
};