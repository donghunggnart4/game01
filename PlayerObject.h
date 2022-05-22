#ifndef PLAYER_OBJECT_H_
#define PLAYER_OBJECT_H_


#include <vector>
#include "basefunction.h"
#include "baseoject.h"
#include "BulletOject.h"

constexpr auto GRAVITY_FALL = 0.8;
constexpr auto MAX_FALL_SPEED = 10;
constexpr auto PLAYER_SPEED = 8;
constexpr auto PLAYER_JUMP_VAL = 20;

class PlayerObject : public BaseObject {
public:
	PlayerObject();
	~PlayerObject();

	enum WalkType {
		Walk_Right = 0,
		Walk_Left = 1,
	};

	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandelInputAction(SDL_Event event, SDL_Renderer* screen);
	void set_clips();
	SDL_Rect get_rect_frame();
	void DoPlayer(Map& map_data);
	void CheckToMap(Map& map_data);
	void SetMapXY(const int map_x, const int map_y) {
		this->map_x = map_x;
		this->map_y = map_y;
	}
	void CenterMap(Map& map_data);

	void set_bullet_list(std::vector <BulletObject*> bullet_list) {
		p_bullet_list = bullet_list;
	};

	std::vector<BulletObject*> get_bullet_list() const { return p_bullet_list; };
	void HandleBullet(SDL_Renderer* des);
	void IncreaseMoney();
	void RemoveBullet(const int& idx);
	void SetComeBackTime(const int& cb_t) { come_back_time = cb_t; }

	void SetWCD(const bool& w_cdt) { win_condition_ = w_cdt; }
	bool GetWCD() { return win_condition_; }

private:

	std::vector<BulletObject*> p_bullet_list;

	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[8];
	Input input_type_;
	int frame_;
	int status_;

	bool on_ground_;

	int map_x;
	int map_y;

	int come_back_time;

	int gem_count_;

	bool win_condition_;
};


#endif // !PLAYER_OBJECT_H_

