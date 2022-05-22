#pragma once
#ifndef BASE_FUNCTION_H_
#define BASE_FUNCTION_H_

#include <Windows.h>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int FPS = 60;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int RENDER_DRAW_COLOR = 0xff;

const int PLAY_BUTON_POSX = 540;
const int PLAY_BUTTON_POSY = 302;

const int EXIT_BUTTON_POSX = 540;
const int EXIT_BUTTON_POSY = 402;

const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 95;

#define TILE_SIZE 64

#define MAP_MAX_X 400
#define MAP_MAX_Y 10

#define STATE_GEM 4
#define WIN_CUP 10

typedef struct Input {
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
};

typedef struct Map {
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAP_MAX_Y][MAP_MAX_X];
	char* file_name_;
};

namespace SDLbasefunc{
	bool CheckCollision(const SDL_Rect& object1,const SDL_Rect& object2);
}
#endif
