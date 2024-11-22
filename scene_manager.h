#pragma once

#include"scene.h"



extern Scene* menu_scene;
extern Scene* game_scene;
extern Scene* select_scene;

class SceneManager {
public:
 	SceneManager(){}
	~SceneManager() {}

	///枚举，切换场景 --不用指针/引用-->不同场景跳转时频繁使用指针容易引起内存问题
	enum class SceneType {
		Menu,
		Game,
		Select
	};
	void set_current_scene(Scene* scene) {
		current_scene = scene;
		current_scene->on_enter();//进入初始化场景

	}

	void switch_scene(SceneType type) {
		current_scene->on_exit();
		switch (type) {
		case SceneType::Menu:
			current_scene = menu_scene;
			break;
		case SceneType::Game:
			current_scene = game_scene;
			break;
		case SceneType::Select:
			current_scene = select_scene;
			break;
		default:
			break;
		}
		current_scene->on_enter();
	}

	void on_update(int delta) {//处理数据
		current_scene->on_update(delta);
	}

	void on_draw(const Camera& camera) {//绘制

		current_scene->on_draw(camera);

	}

	void on_input(const ExMessage& msg) {///处理玩家输入
		current_scene->on_input(msg);
	}

private:
	Scene* current_scene=nullptr;

};
