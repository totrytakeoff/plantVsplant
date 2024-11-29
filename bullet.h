#pragma once
#include"vector2.h"
#include"player_id.h"
#include<functional>
#include"camera.h"
#include<easyx.h>

extern bool is_debug;

class Bullet {

public:
	Bullet(){}
	~Bullet(){}

	void set_damage(int val){
		damage = val;
	}

	int get_damage() {
		return damage;
	}

	void set_position(float x, float y) {
		position.x = x, position.y=y;
	}

	const Vector2& get_position()const {
		return position;
	}

	const Vector2& get_size()const {
		return size;
	}

	void set_velocity(float x, float y) {
		velocity.x = x, velocity.y = y;
	}

	void set_collide_target(PlayerID target) {
		target_id = target;
	}

	PlayerID get_collide_target()const {
		return target_id;
	}

	void set_callback(std::function<void()> callback) {
		this->callback = callback;
	}

	void set_valid(bool flag) {
		valid = flag;
	}

	bool get_valid()const {
		return valid;
	}

	bool check_can_remove() const{
		return can_remove;
	}
	
	virtual void on_collide() {
		if (callback) {
			callback();
		}
	 }

	virtual bool check_collision(const Vector2& pos, const Vector2& _size) {
		return this->position.x + this->size.x / 2 >= pos.x
			&& this->position.x + this->size.x / 2 <= pos.x + _size.x
			&& this->position.y + this->size.y / 2 >= pos.y
			&& this->position.y + this->size.y/2 <= pos.y + _size.y;
	}

	virtual void on_update(int delta){
		
		
	}

	virtual void on_draw(const Camera &camera) const {
		if(is_debug)
		{
			setfillcolor(RGB(255, 255, 255));
			setlinecolor(RGB(255, 255, 255));
			rectangle(position.x, position.y, position.x + size.x, position.y + size.y);
			solidcircle(position.x + size.x / 2, position.y + size.y / 2,5);

		}
		 
	}

	bool check_if_exceeds_screen() {
		return (position.x + size.x <= 0 || position.x >= getwidth() || position.y + size.y <= 0 || position.y >= getwidth());
	}

protected:
	Vector2 size;//子弹尺寸
	Vector2 position;//子弹位置
	Vector2 velocity;
	int damage = 10;
	bool valid = true;///是否有效
	bool can_remove = false;///是否能被移除

	std::function<void()> callback;
	PlayerID target_id = PlayerID::P1;

};






