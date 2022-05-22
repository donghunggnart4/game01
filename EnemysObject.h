#ifndef ENEMYS_OBJECT_H_
#define ENEMY_OBJECT_H_

#include "basefunction.h"
#include "baseoject.h"
#include "BulletOject.h"

#define THREAT_FRAME_NUM 8
#define GRAVITY 0.8
#define MAX_FALL 10
#define ENEMY_SPEED 3;

class EnemysObject : public BaseObject {
public:
	EnemysObject();
	~EnemysObject();

	enum TypeMove {
		STATIC_ENEMY = 0,
	    MOVE_IN_SPACE_ENEMY = 1,

	};
	void set_x_val(const float &xVal) { x_val_ = xVal; }
	void set_y_val(const float &yVal) { y_val_ = yVal; }
	void set_x_pos(const float& xP) { x_pos_ = xP; }
	void set_y_pos(const float& yP) { y_pos_ = yP; }
	float get_x_pos() { return x_pos_; }
	float get_y_pos() { return y_pos_; }
	void setMapXY(const int& mp_x, const int& mp_y) { map_x_ = mp_x; map_y_ = mp_y; }
	void set_clips();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	int get_width_frame() const { return width_frame_; }
	int get_height_frame() const { return height_frame_; }
	void DoEnemy(Map& gMap);
	void CheckToMap(Map& gMap);
	void InnitEnemy();
	void set_type_move(const int& typeMove) { type_move_ = typeMove; }
	void set_animation_pos(const int& pos_a, const int& pos_b) { animation_a = pos_a; animation_b = pos_b; }
	void set_input_left(const int& ipLeft) { input_type_.left_ = ipLeft; }
	void ImpMoveType(SDL_Renderer* screen);

	std::vector<BulletObject*> get_bullet_list() const { return bullet_list_; }
	void set_bullet_list(const std::vector<BulletObject*>& bl_list) { bullet_list_ = bl_list; }

	void InitBullet(BulletObject* p_bullet, SDL_Renderer* screen);
	void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
	void RemoveBullet(const int& idx);
	SDL_Rect get_rect_frame();

private:
	SDL_Rect frame_clip_[THREAT_FRAME_NUM];
	int width_frame_;
	int height_frame_;
	int frame_;
	bool on_ground_;
	int comeback_time_;
	float x_pos_;
	float y_pos_;
	float x_val_;
	float y_val_;
	int map_x_;
	int map_y_;

	int type_move_;
	int animation_a;
	int animation_b;
	Input input_type_;

	std::vector<BulletObject*>  bullet_list_;
};

#endif // !ENEMYS_OBJECT_H_
