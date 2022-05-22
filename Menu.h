#ifndef MENU_H_
#define MENU_H_

#include "basefunction.h"
#include "baseoject.h"

class Button : public BaseObject {
public:

	Button();

	Button(int x, int y);

	void SetPosition(int x, int y);

	bool IsInside(SDL_Event* e);

private:
	SDL_Point position;
};

void HandlePlayButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play);

void HandleExitButton(SDL_Event* e, Button& ExitButton, bool& do_game, bool& QuitMenu);


#endif // !MENU_H_

