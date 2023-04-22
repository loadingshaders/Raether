#pragma once

#include <iostream>
#include <string.h>
#include <vector>

#include <SDL\SDL.h>
#include <glm\glm.hpp>

namespace glm {
	typedef tvec4<uint8_t> ui8_tvec4;
}

enum struct RaeState { ACTIVE, EXIT };
enum struct Keystate { STANDBY, W, A, S, D, Q, E};
enum struct Mousestate { STATIC, INMOTION };

class Raether {
public:
	Raether();
	~Raether();

	void raeCreateWindow(const char* w_t, int w_width, int w_height);
	void raeRun();
	void raeDrawPix(int u, int v, std::vector<glm::ui8_tvec4>& PixData);
	void raeRenderBegin();
	void raeRenderEnd();
	bool raeIP();
	void raeQuit();

	RaeState windowState;
	Keystate keyState;
	Mousestate mouseState;
	glm::vec2 delta;
private:
	SDL_Window* window;
	const char* title;
	int windowwidth;
	int windowheight;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect screensize;
	

	void raeErrorList(std::string errorList);
	void raeInit();

};