#pragma once

#include"scene.h"
#include"scene_manager.h"
#include"atlas.h"
#include"animation.h"

extern IMAGE img_VS;// VS艺术字图片
extern IMAGE img_1P;// 1P文本图片
extern IMAGE img_2P;//2P文本图片
extern IMAGE img_1P_desc;//1P键位描述图片
extern IMAGE img_2P_desc;//2P键位描述图片
extern IMAGE img_gravestone_left;// 朝向左的墓碑图片
extern IMAGE img_gravestone_right;//朝向右的墓碑图片
extern IMAGE img_selector_tip;//选角界面提示信息文本图片
extern IMAGE img_selector_background;//选角界面背景图
extern IMAGE img_1P_selector_btn_idle_left;//1P向左选择按钮默认状态图片
extern IMAGE img_1P_selector_btn_idle_right;// 1P向右选择按钮默认状态图片
extern IMAGE img_1P_selector_btn_down_left;//1P向左选择按钮按下状态图片
extern IMAGE img_1P_selector_btn_down_right;//1P向右选择按钮按下状态图片
extern IMAGE img_2P_selector_btn_idle_left;//2P向左选择按钮默认状态图片
extern IMAGE img_2P_selector_btn_idle_right;//2P向右选择按钮默认状态图片
extern IMAGE img_2P_selector_btn_down_left;//2P向左选择按钮按下状态图片
extern IMAGE img_2P_selector_btn_down_right;// 2P向右选择按钮按下状态图片
extern IMAGE img_peashooter_selector_background_left;//选角界面朝向左的婉逗射手背景图片
extern IMAGE img_peashooter_selector_background_right;//选角界面朝向右的婉逗射手背景图片
extern IMAGE img_sunflower_selector_background_left;//选角界面朝向左的龙日葵背景图片
extern IMAGE img_sunflower_selector_background_right;//选角界面朝向右的龙日葵背景图片

extern Atlas atlas_peashooter_idle_right;//婉逗射手朝向右的默认动画图集
extern Atlas atlas_sunflower_idle_right;

extern IMAGE img_avatar_peashooter;//婉逗射手头像图片
extern IMAGE img_avatar_sunflower;//龙日葵头像图片

extern SceneManager scene_manager;

class SelectScene :public Scene {
public:
	SelectScene(){}
	~SelectScene(){}
	 

	void on_enter() {///处理进入时的初始化逻辑


	}

	void on_update(int delta) {//处理数据

	}

	void on_draw(const Camera& camera) {//绘制

	}

	void on_input(const ExMessage& msg) {///处理玩家输入


	}

	void on_exit() {///处理场景退出时的卸载逻辑

	}


private:
	POINT pos_img_VS = { 0 };
	POINT pos_img_tip = { 0 };
	POINT pos_img_1P = { 0 };
	POINT pos_img_2P = { 0 };
	POINT pos_img_1P_desc = { 0 };
	POINT pos_img_2P_desc = { 0 };
	POINT pos_img_1P_name = { 0 };
	POINT pos_img_2P_name = { 0 };
	POINT pos_animation_1P = { 0 };
	POINT pos_animation_2P = { 0 };
	POINT pos_img_1P_gravestone = { 0 };
	POINT pos_img_2P_gravestone = { 0 };
	POINT pos_1P_selector_btn_left = { 0 };
	POINT pos_1P_selector_btn_right = { 0 };
	POINT pos_2P_selector_btn_left = { 0 };
	POINT pos_2P_selector_btn_right = { 0 };
	
	
};