#include "Menu.h"

Button::Button()
{
	position.x = 0;
	position.y = 0;

}

Button::Button(int x, int y)
{
	position.x = x;
	position.y = y;

}

void Button::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

bool Button::IsInside(SDL_Event* e)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		int button_width, button_height;

		button_width = BUTTON_WIDTH;
		button_height = BUTTON_HEIGHT;

		SDL_GetMouseState(&x, &y);

		bool inside = true;
		if (x < position.x)
		{
			inside = false;
		}
		else if (x > position.x + button_width)
		{
			inside = false;
		}
		else if (y < position.y)
		{
			inside = false;
		}
		else if (y > position.y + button_height)
		{
			inside = false;
		}
		return inside;
	}
	return false;
}

void HandlePlayButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play)
{
	if (e->type == SDL_QUIT)
	{
		QuitMenu = true;
	}

	if (PlayButton.IsInside(e))
	{
		switch (e->type)
		{
		case SDL_MOUSEBUTTONDOWN:
			Play = true;
			QuitMenu = true;
			break;
		}
	}
}

void HandleExitButton(SDL_Event* e, Button& ExitButton, bool& do_game, bool& QuitMenu)
{
	if (e->type == SDL_QUIT)
	{
		do_game = false;
	}

	if (ExitButton.IsInside(e))
	{
		switch (e->type)
		{
		case SDL_MOUSEBUTTONDOWN:
			do_game = false;
			QuitMenu = true;
			break;
		}
	}
}
