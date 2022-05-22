#include"BulletOject.h"

BulletObject::BulletObject(){
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
	bullet_type_ = LAZE;
}

BulletObject :: ~BulletObject() {

}

void BulletObject :: HandleMove(const int& x_boder, const int& y_boder) {
	if (bullet_dir_ == DIR_RIGHT) {
		rect_.x += x_val_;
		if (rect_.x > x_boder) {
			is_move_ = false;
		}
	}
	if (bullet_dir_ == DIR_LEFT) {
		rect_.x -= x_val_;
		if (rect_.x < 0) {
			is_move_ = false;
		}
	}
}

void BulletObject::LoadImgBullet(SDL_Renderer* des)
{
	if (bullet_type_ == LAZE) {
		LoadImg("bullet_laze.png", des);
	}
	else if (bullet_type_ == BASE) {
		LoadImg("bullet_arrow.png", des);
	}
}
