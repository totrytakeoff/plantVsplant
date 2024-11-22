#pragma once

#include<graphics.h>
#include<iostream>
#include"camera.h"


class Scene {
public:
	Scene(){}
	~Scene(){}


	///  不用构造/析构--->>避免不断构建和删除新的对象从而浪费性能 // 处理场景内对象生命周期长于场景生命周期-->使场景对象的生命周期与游戏的生命周期相同
	///简单理解 ---》 将new操作改为refresh initiate
	
	virtual void on_enter() {///处理进入时的初始化逻辑
	}

	virtual void on_update(int delta) {//处理数据

		//SceneManager::switch_scene(arg);
	}

	virtual void on_draw(const Camera& camera){//绘制
	}

	virtual void on_input(const ExMessage& msg) {///处理玩家输入

	}

	virtual void on_exit() {///处理场景退出时的卸载逻辑

	}


};



