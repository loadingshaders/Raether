#pragma once

#include <iostream>
#include <string.h>
#include <vector>

#include <SDL\SDL.h>
#include <glm\glm.hpp>

#include "Utils.h"

enum struct RaeState { ACTIVE, EXIT };
enum struct Keystate { STANDBY, W, A, S, D, Q, E};
enum struct Mousestate { STATIC, INMOTION , SCROLLING};

class Raether {

public:
	Raether();
	~Raether();

	void raeCreateWindow(const char* w_t, int w_width, int w_height);
	void raeRenderBegin();
	void raeDrawImage(std::vector<glm::ui8_tvec4>& PixData);
	void raeRenderEnd();
	bool raeInputEvents();
	void raeQuit();

private:
	void raeInit();

public:
	RaeState windowState;
	Keystate keyState;
	Mousestate mouseState;

	glm::si32_tvec2 mouseDelta;
	Sint32 scrollAmount;

private:
	const char* windowTitle;
	int windowWidth;
	int windowHeight;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;

	SDL_Rect screensize;
};