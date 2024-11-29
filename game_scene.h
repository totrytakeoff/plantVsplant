#pragma once

#include"scene_manager.h"
#include"scene.h"
#include"camera.h"
#include"platform.h"
#include"player.h"
#include"status_bar.h"

//#include<algorithm>

extern SceneManager scene_manager;

extern IMAGE img_sky;
extern IMAGE img_hills;
extern IMAGE img_platform_large;
extern IMAGE img_platform_small;
extern Camera main_camera;

extern std::vector<Platform> platform_list;

extern Player* player_1;
extern Player* player_2;

extern IMAGE* img_player_1_avater;
extern IMAGE* img_player_2_avater;


class GameScene:public Scene{
public:
	GameScene() {

	}
	~GameScene() {
	}
	void on_enter() {///处理进入时的初始化逻辑
		
		std::cout << " 进入游戏内场景 " << std::endl;

		status_bar_1P.set_avater(img_player_1_avater);
		status_bar_2P.set_avater(img_player_2_avater);

		status_bar_1P.set_position(235, 625);
		status_bar_2P.set_position(675, 625);


		player_1->set_pos(200, 50);
		player_2->set_pos(975, 50);

		///为处理窗口抖动时出地图问题，故背景图大于窗口，需要居中显示 
		pos_img_sky.x = (getwidth() - img_sky.getwidth()) / 2;
		pos_img_hills.x = (getwidth() - img_hills.getwidth()) / 2;

		pos_img_sky.y = (getheight() - img_sky.getheight()) / 2;
		pos_img_hills.y = (getheight() - img_hills.getheight()) / 2;

		platform_list.resize(4);

		Platform& large_platform = platform_list[0];
		large_platform.img = &img_platform_large;
		large_platform.render_pos.x = 122;
		large_platform.render_pos.y = 455;
		large_platform.shape.left = (float)(large_platform.render_pos.x +30);
		large_platform.shape.right = (float)(large_platform.render_pos.x+img_platform_large.getwidth() - 30);
		large_platform.shape.y = (float)(large_platform.render_pos.y + 60);
		Platform& small_platform_1 = platform_list[1];
		small_platform_1.img = &img_platform_small;
		small_platform_1.render_pos.x = 177;
		small_platform_1.render_pos.y = 360;
		small_platform_1.shape.left = (float)(small_platform_1.render_pos.x +40);
		small_platform_1.shape.right = (float)(small_platform_1.render_pos.x+img_platform_small.getwidth() - 40);
		small_platform_1.shape.y = (float)(small_platform_1.render_pos.y + img_platform_small.getheight()/2);
		
		Platform& small_platform_2 = platform_list[2];
		small_platform_2.img = &img_platform_small;
		small_platform_2.render_pos.x = 855;
		small_platform_2.render_pos.y = 360;
		small_platform_2.shape.left = (float)(small_platform_2.render_pos.x +40);
		small_platform_2.shape.right = (float)(small_platform_2.render_pos.x+img_platform_small.getwidth() - 40);
		small_platform_2.shape.y = (float)(small_platform_2.render_pos.y + img_platform_small.getheight()/2);
		
		Platform& small_platform_3 = platform_list[3];
		small_platform_3.img = &img_platform_small;
		small_platform_3.render_pos.x = 515;
		small_platform_3.render_pos.y = 225;
		small_platform_3.shape.left = (float)(small_platform_3.render_pos.x +40);
		small_platform_3.shape.right = (float)(small_platform_3.render_pos.x+img_platform_small.getwidth() - 40);
		small_platform_3.shape.y = (float)(small_platform_3.render_pos.y + img_platform_small.getheight()/2);
	

	}
	
	void on_update(int delta) {//处理数据

		player_1->on_update(delta);
		player_2->on_update(delta);
		main_camera.on_update(delta);

		bullet_list.erase(
			std::remove_if(
				bullet_list.begin(), bullet_list.end(),
		[&](const Bullet* bullet) {
			bool deletable = bullet->check_can_remove();
			if (deletable)delete bullet;
			return deletable;
			}
			),
		bullet_list.end()

		);////逆天的简洁


		for (Bullet* bullet : bullet_list) {
			bullet->on_update(delta);

			//std::cout << bullet_list.size() << std::endl;
			//std::cout <<"valid: "<< bullet->get_valid() << std::endl;
			//std::cout <<"check_can_remove: "<< bullet->check_can_remove() << std::endl;
		}

		
		status_bar_1P.set_hp(player_1->get_hp());
		status_bar_1P.set_mp(player_1->get_mp());

		status_bar_2P.set_hp(player_2->get_hp());
		status_bar_2P.set_mp(player_2->get_mp());


	}
	 
	void on_draw(const Camera& camera) {//绘制
		putimage_Alpha(pos_img_sky.x, pos_img_sky.y, &img_sky);
		putimage_Alpha(pos_img_hills.x, pos_img_hills.y, &img_hills);
		for (const Platform platform : platform_list) {
			platform.on_draw(camera);
		}
		if (is_debug) {
			settextcolor(RED);
			settextstyle(24, 0, _T("楷体"));
			outtextxy(15, 15, _T("have enter debug mode, press /'Q' to exit debug"));
		}
		player_1->on_draw(camera);
		player_2->on_draw(camera);

		for (Bullet* bullet : bullet_list) {
			bullet->on_draw(camera);
		}

		status_bar_1P.on_draw();
		status_bar_2P.on_draw();


	}

	void on_input(const ExMessage& msg) {///处理玩家输入
		player_1->on_input(msg);
		player_2->on_input(msg);
		
		switch (msg.message) {
		case WM_KEYDOWN:
			break;
		case WM_KEYUP:
			switch (msg.vkcode) {
			case 0x51://Q
				if (!is_debug) {
					is_debug = true;
				}
				else is_debug = false;
				break;
			default:
				break; 
			}
			break;
		default:
			break;
		}
	}
	void on_exit(){
		///处理场景退出时的卸载逻辑
	}
	
private:
	POINT pos_img_sky = { 0 };
	POINT pos_img_hills = { 0 };
	
	StatusBar status_bar_1P;///玩家1的状态条
	StatusBar status_bar_2P;///玩家2的状态条


};

