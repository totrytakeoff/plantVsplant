#include<iostream>
#include<easyx.h>
#include<graphics.h>

#include"atlas.h"///图集

#include"tools.h"///工具集

#include"scene.h"
#include"menu_scene.h"
#include"game_scene.h"
#include"select_scene.h"

#include"scene_manager.h"
#include"animation.h"

#include"Init_res.h"///载入图像音乐等资源
#include"platform.h"

#include"player.h"
#include"bullet.h"



bool is_debug = false;
 
Scene* menu_scene = nullptr;//继承了Scene，故可以直接给Scene*的变量类型
Scene* game_scene = nullptr;//继承了Scene，故可以直接给Scene*的变量类型
Scene* select_scene = nullptr;//继承了Scene，故可以直接给Scene*的变量类型

Camera main_camera;
SceneManager scene_manager;
std::vector<Platform> platform_list;
std::vector<Bullet*>bullet_list;

Player* player_1 = nullptr;
Player* player_2 = nullptr;

IMAGE* img_player_1_avater = nullptr;
IMAGE* img_player_2_avater = nullptr;



int main() {
	load_image_res();


	ExMessage msg;
	const int FPS = 60;
	initgraph(1280,720);
	settextstyle(28, 0, _T("IPix"));
	setbkmode(TRANSPARENT);

	BeginBatchDraw();

	menu_scene = new Menuscene();
	game_scene = new GameScene();
	select_scene = new SelectScene();

	scene_manager.set_current_scene(menu_scene);
	
	
	while (1) {
		DWORD frame_start_time = GetTickCount();

		while (peekmessage(&msg)) {
			scene_manager.on_input(msg);
		}


		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick_time = current_tick_time - last_tick_time;
		scene_manager.on_update(delta_tick_time);
		last_tick_time = current_tick_time;


		cleardevice();
		
		scene_manager.on_draw(main_camera);



		FlushBatchDraw();

		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time = frame_end_time - frame_start_time;
		if (frame_delta_time < 1000 / FPS) {
			Sleep(1000 /FPS - frame_delta_time);
		}

	}

	EndBatchDraw();


	return 0;
}