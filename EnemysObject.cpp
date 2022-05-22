#include "EnemysObject.h"

EnemysObject::EnemysObject()
{
	width_frame_ = 0;
	height_frame_ = 0;
	x_val_ = 0.0;
	y_val_ = 0.0;
	x_pos_ = 0.0;
	y_pos_ = 0.0;
	on_ground_ = 0;
	comeback_time_ = 0;
	frame_ = 0;
	animation_a = 0;
	animation_b = 0;
	input_type_.left_ = 0;
	type_move_ = STATIC_ENEMY;
}

EnemysObject::~EnemysObject()
{

}

void EnemysObject::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0) {
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = height_frame_;

		frame_clip_[1].x = width_frame_;
		frame_clip_[1].y = 0;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;

		frame_clip_[2].x = 2 * width_frame_;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;

		frame_clip_[3].x = 3 * width_frame_;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = height_frame_;

		frame_clip_[4].x = 4 * width_frame_;
		frame_clip_[4].y = 0;
		frame_clip_[4].w = width_frame_;
		frame_clip_[4].h = height_frame_;

		frame_clip_[5].x = 5 * width_frame_;
		frame_clip_[5].y = 0;
		frame_clip_[5].w = width_frame_;
		frame_clip_[5].h = height_frame_;

		frame_clip_[6].x = 6 * width_frame_;
		frame_clip_[6].y = 0;
		frame_clip_[6].w = width_frame_;
		frame_clip_[6].h = height_frame_;

		frame_clip_[7].x = 7 * width_frame_;
		frame_clip_[7].y = 0;
		frame_clip_[7].w = width_frame_;
		frame_clip_[7].h = height_frame_;
	}
}

bool EnemysObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == true) {
		width_frame_ = rect_.w / THREAT_FRAME_NUM;
		height_frame_ = rect_.h;
	}
	return ret;
}

void EnemysObject::Show(SDL_Renderer* des)
{
	if (comeback_time_ == 0) {
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		frame_++;
		if (frame_ >= 8) {
			frame_ = 0;
		}
		SDL_Rect* currentClip = &frame_clip_[frame_];
		SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
		SDL_RenderCopy(des, p_object_, currentClip, &renderQuad);

	}
}

void EnemysObject::DoEnemy(Map& gMap)
{
	if (comeback_time_ == 0) {
		x_val_ = 0;
		y_val_ += GRAVITY;
		if (y_val_ >= MAX_FALL) {
			y_val_ = MAX_FALL;
		}

		if (input_type_.left_ == 1) {
			x_val_ -= ENEMY_SPEED;
		}
		else if (input_type_.right_ == 1) {
			x_val_ += ENEMY_SPEED;
		}

		CheckToMap(gMap);

	}
	else if (comeback_time_ > 0) {
		comeback_time_--;
		if (comeback_time_ == 0) {
			InnitEnemy();
		}
	}
}

void EnemysObject::CheckToMap(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	x1 = (x_pos_ + x_val_ - 1) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAP_MAX_X && y1 >= 0 && y2 < MAP_MAX_Y) {

		if (x_val_ > 0) {
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];
			if ((val1 != 0 && val1 != STATE_GEM) || (val2 != 0 && val2 != STATE_GEM)) {
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= width_frame_ + 1;
				x_val_ = 0;
			}
		}
		else if (x_val_ < 0) {
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];
			if ((val1 != 0 && val1 != STATE_GEM) || (val2 != 0 && val2 != STATE_GEM)) {
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;
		     }
		}
	}

	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;
	if (x1 >= 0 && x2 < MAP_MAX_X && y1 >= 0 && y2 < MAP_MAX_Y) {
		if (y_val_ > 0) {
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
			if ((val1 != 0 && val1 != STATE_GEM) || (val2 != 0 && val2 != STATE_GEM)) {
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= (height_frame_ + 1);
				y_val_ = 0;
				on_ground_ = true;
			}
		}
		else if (y_val_ < 0) {
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			if ((val1 != 0 && val1 != STATE_GEM) || (val2 != 0 && val2 != STATE_GEM)) {
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
			}
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0) {
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > map_data.max_x_) {
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}
	if (y_pos_ > map_data.max_y_) {
		comeback_time_ = 60;
	}
}

void EnemysObject::InnitEnemy()
{
	x_val_ = 0;
	y_val_ = 0;
	if (x_pos_ > 256) {
		x_pos_ -= 256;
		animation_a -= 256;
		animation_b -= 256;
	}
	else {
		x_pos_ = 0;
	}
	y_pos_ = 0;
	comeback_time_ = 0;
	input_type_.left_ = 1;
}

void EnemysObject::ImpMoveType(SDL_Renderer* screen)
{
	if (type_move_ == STATIC_ENEMY) {
		;
	}
	else {
		if (on_ground_ == true) {
			if (x_pos_ > animation_b) {
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				LoadImg("enemy_left.png", screen);
			}
			else if(x_pos_ < animation_a) {
				input_type_.left_ = 0;
				input_type_.right_ = 1;
				LoadImg("enemy_right.png", screen);
			}
		}
		else {
			if (input_type_.left_ == 1) {
				LoadImg("enemy_left.png", screen);
			}
		}
	}
}

void EnemysObject::InitBullet(BulletObject* p_bullet, SDL_Renderer* screen)
{
	if (p_bullet != NULL) {
		p_bullet->set_bullet_type(BulletObject::BASE);
		p_bullet->LoadImgBullet(screen);
		p_bullet->set_move(true);
		p_bullet->SetRect(x_pos_ , y_pos_ + 40);
		p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
		p_bullet->set_x_val(10);
		bullet_list_.push_back(p_bullet);
	}
}

void EnemysObject::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < bullet_list_.size(); i++) {
		BulletObject* p_bullet = bullet_list_[i];
		if (p_bullet != NULL) {
			if (p_bullet->get_move() == true) {
				int bullet_distance = rect_.x - p_bullet->GetRect().x;
				if (bullet_distance < 300) {
					p_bullet->HandleMove(x_limit, y_limit);
					p_bullet->Render(screen);
				}
				else {
					p_bullet->set_move(false);
				}
			}
			else {
				p_bullet->set_move(true);
				p_bullet->SetRect(this->rect_.x , this->rect_.y + 40);
			}
		}
	}
}

void EnemysObject::RemoveBullet(const int& idx)
{
	int size = bullet_list_.size();
	if (size > 0 && idx < size) {
		BulletObject* p_bullet = bullet_list_[idx];
		bullet_list_.erase(bullet_list_.begin() + idx);

		if (p_bullet) {
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}

SDL_Rect EnemysObject::get_rect_frame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame_;
	rect.h = height_frame_;

	return rect;
}

