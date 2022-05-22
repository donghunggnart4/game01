#include "basefunction.h"
#include "baseoject.h"
#include "game_map.h"
#include "PlayerObject.h"
#include "ImpTimer.h"
#include "EnemysObject.h"
#include "Menu.h"


BaseObject g_background;
BaseObject g_menu;
Button PlayButton;
Button ExitButton;

bool InitData() {
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	g_window = SDL_CreateWindow("GAME1",
		                         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == NULL) {
		success = false;
	}
	else {
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL) {
			success = false;
		}
		else {
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags)) success = false;
		}
	}
	return success;
}

bool LoadBackgruond() {
	bool ret = g_background.LoadImg("background.jpg", g_screen);
	if (ret == false) {
		return false;
	}
	else {
		return true;
	}
}

bool LoadMenu() {
	g_menu.LoadImg("menu_bg.png", g_screen);
	PlayButton.LoadImg("PlayButton.png", g_screen);
	ExitButton.LoadImg("ExitButton.png", g_screen);
	PlayButton.SetRect(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
	ExitButton.SetRect(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
	PlayButton.SetPosition(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
	ExitButton.SetPosition(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
	return true;
}


void Close() {
	g_background.Free();
	g_menu.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();

}

std::vector<EnemysObject*> MakeEnemysList() {
	std::vector<EnemysObject*> list_enemys;

	EnemysObject* enemys = new EnemysObject[10];
	for (int i = 0; i < 10; i++) {
		EnemysObject* p_enemy = (enemys + i);
		if (p_enemy != NULL) {
			p_enemy->LoadImg("enemy_level.png", g_screen);
			p_enemy->set_clips();
			p_enemy->set_x_pos(1000 + i* 1200);
			p_enemy->set_y_pos(250);
			p_enemy->set_type_move(EnemysObject::STATIC_ENEMY);
			p_enemy->set_input_left(0);

			BulletObject* p_bullet = new BulletObject();
			p_enemy->InitBullet(p_bullet, g_screen);

			list_enemys.push_back(p_enemy); 
		}
	}

	EnemysObject* move_enemys = new EnemysObject[30];
	for (int i = 0; i < 30; i++) {
		EnemysObject* p_enemy = (move_enemys + i);
		if (p_enemy != NULL) {
			p_enemy->LoadImg("enemy_left.png", g_screen);
			p_enemy->set_clips();
			p_enemy->set_type_move(EnemysObject::MOVE_IN_SPACE_ENEMY);
			p_enemy->set_x_pos(600 + i * 1000);
			p_enemy->set_y_pos(250);
			int pos1 = p_enemy->get_x_pos() - 60;
			int pos2 = p_enemy->get_x_pos() + 60;
			p_enemy->set_animation_pos(pos1, pos2);
			p_enemy->set_input_left(1);

			list_enemys.push_back(p_enemy);
		}
	}

	return list_enemys;
}

int main(int argc, char* args[])
{
	ImpTimer fps_timer;

	if (InitData() == false) {
		return -1;
	}
	
	if (LoadBackgruond() == false) {
		return -1;
	}

	if (LoadMenu() == false) {
		return -1;
	}

	GameMap game_map;
	std::string mapdat = "map01.dat";
	char* name = new char[mapdat.size() + 1];
	std::copy(mapdat.begin(), mapdat.end(), name);
	name[mapdat.size()] = '\0';
	game_map.LoadMap(name);
	game_map.LoadTiles(g_screen);

	PlayerObject p_player;
	p_player.LoadImg("player_right.png", g_screen);
	p_player.set_clips();

	std::vector<EnemysObject*> enemys_list = MakeEnemysList();

	bool GAME = true;
	bool Quit_Menu = false;
	bool Play_Game = false;
	int num_die = 0;

	while(GAME == true) {
		while (!Quit_Menu) {
			SDL_Event e_mouse;
			while (SDL_PollEvent(&e_mouse) != 0)
			{
				if (e_mouse.type == SDL_QUIT)
				{
					GAME = false;
					Quit_Menu = true;
				}

				bool Quit_Game = false;
				HandlePlayButton(&e_mouse, PlayButton, Quit_Menu, Play_Game);
				HandleExitButton(&e_mouse, ExitButton, GAME, Quit_Menu);


			}
			g_menu.Render(g_screen, NULL);
			PlayButton.Render(g_screen, NULL);
			ExitButton.Render(g_screen, NULL);
			SDL_RenderPresent(g_screen);

		}

		while (Play_Game) {
			fps_timer.start();
			while (SDL_PollEvent(&g_event) != 0) {
				if (g_event.type == SDL_QUIT) {
					GAME = false;
					Play_Game = false;
				}
				p_player.HandelInputAction(g_event, g_screen);
				if (g_event.type == SDL_KEYDOWN) {
					if (g_event.key.keysym.sym == SDLK_ESCAPE) {
						Play_Game = false;
						Quit_Menu = false;
					}
				}
			}

			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			SDL_RenderClear(g_screen);
			g_background.Render(g_screen, NULL);

			Map map_data = game_map.getMap();

			p_player.HandleBullet(g_screen);
			p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
			p_player.DoPlayer(map_data);
			p_player.Show(g_screen);

			game_map.setMap(map_data);
			game_map.DrawMap(g_screen);

			std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();

			for (int t = 0; t < bullet_arr.size(); t++) {
				BulletObject* p_bullet = bullet_arr.at(t);
				if (p_bullet != NULL) {
					for (int r = 0; r < enemys_list.size(); r++) {
						EnemysObject* enemy_obj = enemys_list.at(r);
						if (enemy_obj != NULL) {
							SDL_Rect eRect;
							eRect.x = enemy_obj->GetRect().x;
							eRect.y = enemy_obj->GetRect().y;
							eRect.w = enemy_obj->get_width_frame();
							eRect.h = enemy_obj->get_height_frame();

							SDL_Rect bRect = p_bullet->GetRect();

							bool bCol = false;
							bCol = SDLbasefunc::CheckCollision(eRect, bRect);

							if (bCol == true) {
								p_player.RemoveBullet(t);
								enemy_obj->Free();
								enemys_list.erase(enemys_list.begin() + r);
							}
						}
					}
				}
			}

			for (int i = 0; i < enemys_list.size(); i++) {
				EnemysObject* p_enemy = enemys_list.at(i);
				if (p_enemy != NULL) {
					p_enemy->setMapXY(map_data.start_x_, map_data.start_y_);
					p_enemy->ImpMoveType(g_screen);
					p_enemy->DoEnemy(map_data);
					p_enemy->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
					p_enemy->Show(g_screen);

					SDL_Rect rect_player = p_player.get_rect_frame();
					bool bCol1 = false;
					std::vector<BulletObject*> tBullet_list = p_enemy->get_bullet_list();
					for (int ii = 0; ii < tBullet_list.size(); ii++) {
						BulletObject* pt_bullet = tBullet_list[ii];
						if (pt_bullet != NULL) {
							bCol1 = SDLbasefunc::CheckCollision(pt_bullet->GetRect(), rect_player);
							if (bCol1 == true) {
								p_enemy->RemoveBullet(ii);
								break;
							}
						}
					}

					SDL_Rect rect_enemy = p_enemy->get_rect_frame();
					bool bCol2 = false;
					bCol2 = SDLbasefunc::CheckCollision(rect_player, rect_enemy);
					if (bCol1 == true || bCol2 == true) {
						num_die++;
						if (num_die <= 3) {
							p_player.SetRect(0, 0);
							p_player.SetComeBackTime(60);
							p_enemy->Free();
							enemys_list.erase(enemys_list.begin() + i);
							continue;
						}
						else {
							if (MessageBox(NULL, L"GAME_OVER", L"Infor", MB_OK | MB_ICONSTOP) == IDOK) {
								p_enemy->Free();
								Close();
								SDL_Quit();
								return 0;
							}
						}
					}
				}

			}

			if (p_player.GetWCD() == true)
			{
				BaseObject winscreen;
				winscreen.LoadImg("winner.png", g_screen);
				winscreen.Render(g_screen, NULL);
			}

			SDL_RenderPresent(g_screen);

			int real_imp_time = fps_timer.get_ticks();
			int time_one_frame = 1000 / FPS;

			if (real_imp_time < time_one_frame) {
				int delay = time_one_frame - real_imp_time;
				SDL_Delay(delay);
			}
		}
	}

	for (int i = 0; i < enemys_list.size(); i++) {
		enemys_list[i]->Free();
		enemys_list[i] = NULL;
	}

	enemys_list.clear();

	Close();
	return 0;
}