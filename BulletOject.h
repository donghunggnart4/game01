#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "basefunction.h"
#include "baseoject.h"

class BulletObject : public BaseObject {

public:
	BulletObject() ;
	~BulletObject() ;

	enum BulletDir {
		DIR_RIGHT = 20,
	    DIR_LEFT = 21,
	};

	enum BulletType {
		LAZE = 50,
		BASE = 51,
	};

	void set_x_val(const int& xVal) {
		x_val_ = xVal;
	}
	void set_y_val(const int& yVal) {
		y_val_ = yVal;
	}
	int get_x_val() { return x_val_; }
	int get_y_val() { return y_val_; }

	void set_move(const bool& isMove) { is_move_ = isMove; }
	bool get_move() const { return is_move_; }
	void set_bullet_dir(const int& bulletDir) {
		bullet_dir_ = bulletDir;
	}
	int get_bullet_dir() const { return bullet_dir_; }
	void HandleMove(const int& x_boder, const int& y_boder);
	int get_bullet_type() const { return bullet_type_; }
	void set_bullet_type(const int& bulletType) { bullet_type_ = bulletType; }
	void LoadImgBullet(SDL_Renderer* screen);
private:
	int y_val_;
	int x_val_;
	bool is_move_;
	int bullet_dir_;
	int bullet_type_;
};

#endif
