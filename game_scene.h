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
extern IMAGE img_1P_winner;
extern IMAGE img_2P_winner;
extern IMAGE img_winner_bar;

extern IMAGE* img_player_1_avater;
extern IMAGE* img_player_2_avater;

extern Camera main_camera;

extern std::vector<Platform> platform_list;

extern Player* player_1;
extern Player* player_2;

extern IMAGE img_1P_winnner;
//1P获胜文本图片
extern IMAGE img_2P_winner;
// 2P获胜文本图片
extern IMAGE img_winner_bar;
//获胜玩家文本背景图片


class GameScene:public Scene{
public:
	GameScene() {

	}
	~GameScene() {
	}
	void on_enter() {///处理进入时的初始化逻辑
		
		is_game_over = false;
		is_slide_out_started = false;

		pos_img_winner_bar.x = (- img_winner_bar.getwidth());
		pos_img_winner_bar.y = (getheight() - img_winner_bar.getheight()) / 2;
		pos_x_img_winner_bar_dst = (getwidth() - img_winner_bar.getwidth()) / 2;

		pos_img_winner_text.x = pos_img_winner_bar.x;
		pos_img_winner_text.y = (getheight()  - img_1P_winner.getheight()) / 2;
		pos_x_img_winner_text_dst = (getwidth() - img_1P_winner.getwidth()) / 2;


		timer_winner_slide_in.restart();
		timer_winner_slide_in.set_wait_time(2500);
		timer_winner_slide_in.set_one_shot(true);
		timer_winner_slide_in.set_callback([&]()
		{
		    is_slide_out_started = true;
		});
		
		timer_winner_slide_out.restart();
		timer_winner_slide_out.set_wait_time(1000);
		timer_winner_slide_out.set_one_shot(true);
		timer_winner_slide_out.set_callback([&]()
		{
		    scene_manager.switch_scene(SceneManager::SceneType::Menu);
		});




		mciSendString(_T("play bgm_game repeat 0"),NULL,0,NULL);


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



		const Vector2& pos_player_1 = player_1->get_pos();
		const Vector2& pos_player_2 = player_2->get_pos();
		if (pos_player_1.y >= getheight()) {
			player_1->set_hp(0);
		}
		if (pos_player_2.y >= getheight()) {
			player_2->set_hp(0);
		}

		if (player_1->get_hp() <= 0 || player_2->get_hp() <= 0) {
			

			if (!is_game_over) {
				mciSendString(_T("stop bgm_game"), NULL, 0, NULL);
				mciSendString(_T("play ui_win from 0"), NULL, 0, NULL);
			}

			is_game_over = true;

		}


		
		status_bar_1P.set_hp(player_1->get_hp());
		status_bar_1P.set_mp(player_1->get_mp());

		status_bar_2P.set_hp(player_2->get_hp());
		status_bar_2P.set_mp(player_2->get_mp());
		
		if (is_game_over) {
			 pos_img_winner_bar.x+=speed_winner_bar*delta;
			 pos_img_winner_text.x+=speed_winner_text*delta;
			
			 if (!is_slide_out_started) {
				timer_winner_slide_in.on_update(delta);
				if (pos_img_winner_bar.x >= pos_x_img_winner_bar_dst) {
					pos_img_winner_bar.x = pos_x_img_winner_bar_dst;
				}
				if (pos_img_winner_text.x >= pos_x_img_winner_text_dst) {
					pos_img_winner_text.x = pos_x_img_winner_text_dst;
				}
			 
			 }
			 else {
				timer_winner_slide_out.on_update(delta);
			 }


		}

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

		if (is_game_over) {
			putimage_Alpha(pos_img_winner_bar.x, pos_img_winner_bar.y, &img_winner_bar);
			putimage_Alpha(pos_img_winner_text.x, pos_img_winner_text.y, player_1->get_hp() >0 ? &img_1P_winner:&img_2P_winner);
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
		delete player_1;player_1 = nullptr;
		delete player_2;player_2 = nullptr;

		is_debug = false;

		bullet_list.clear();
		main_camera.reset();
	}
	
private:
	POINT pos_img_sky = { 0 };
	POINT pos_img_hills = { 0 };
	
	StatusBar status_bar_1P;///玩家1的状态条
	StatusBar status_bar_2P;///玩家2的状态条

	bool is_game_over=false;

	POINT pos_img_winner_bar = { 0 };
	POINT pos_img_winner_text = { 0 };
	int pos_x_img_winner_bar_dst = 0;
	int pos_x_img_winner_text_dst = 0;
	Timer timer_winner_slide_in;//滑入
	Timer timer_winner_slide_out;//滑出
	bool is_slide_out_started = false;//是否开始滑出结算动效

	const float speed_winner_bar = 3.0f;
	const float speed_winner_text = 1.5f;


};

