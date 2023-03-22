#pragma once

#include <iostream>
#include <string.h>

#include <SDL\SDL.h>
#include <glm\glm.hpp>

namespace glm {
	typedef tvec4<uint8_t> ui8_tvec4;
}

enum class RaeState { ACTIVE, EXIT };
class Raether {
public:
	Raether();
	~Raether();

	void raeCreateWindow(const char* w_t, int w_width, int w_height);
	void raeRun();
	void raeDrawPix(int u, int v);
	void raeDrawCol(SDL_Color color);
	SDL_Color raeCreateCol(glm::ui8_tvec4 color);

private:
	SDL_Window* window;
	const char* title;
	int windowwidth;
	int windowheight;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect screensize;
	RaeState raeState;

	void raeErrorList(std::string errorList);
	void raeInit();
	void raeIP();
	void raeRenderBegin();
	void raeRenderEnd();
	void raeRender();
	void raeLoop();
	void raeQuit();
};