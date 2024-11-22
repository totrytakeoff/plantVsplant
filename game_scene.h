#pragma once

#include"scene_manager.h"
#include"scene.h"

extern SceneManager scene_manager;


class GameScene:public Scene{
public:
	GameScene() {

	}
	~GameScene() {
	}
	void on_enter() {///处理进入时的初始化逻辑
		std::cout << " 进入游戏内场景 " << std::endl;
	}

	void on_update(int delta) {//处理数据
		std::cout << "游戏正在运行" << std::endl;
	}

	void on_draw(const Camera& camera) {//绘制
		outtextxy(20, 20, _T("游戏局内正在绘制内容"));
	}

	void on_input(const ExMessage& msg) {///处理玩家输入
		if (msg.message == WM_KEYDOWN) {///按下任意键进入 GameScene
			scene_manager.switch_scene(SceneManager::SceneType::Menu);
		}
	}
	void on_exit(){
		///处理场景退出时的卸载逻辑
		std::cout << "游戏内退出" << std::endl;
	}



};

