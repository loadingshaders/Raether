#include "Raether.h"

Raether::Raether() {
	raeState = RaeState::ACTIVE;
	window = nullptr;
	title = "Raether";
	windowwidth = 1280;
	windowheight = 720;
	renderer = nullptr;
	texture = nullptr;
	screensize = SDL_Rect{ 0, 0, windowwidth, windowheight };
}
Raether::~Raether() {
	std::cout << "\nAbout to call raeQuit" << std::endl;
	raeQuit();
	std::cout << "raeQuit call done!" << std::endl;
}

void Raether::raeErrorList(std::string errorlist) {
	std::cout << errorlist << std::endl;
	std::cin.get();
	SDL_Quit();
}

void Raether::raeInit() {
	SDL_bool hintError = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);

	int sdlError = SDL_Init(SDL_INIT_EVERYTHING);
	if (sdlError != 0) {
		raeErrorList(SDL_GetError());
	}

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowwidth, windowheight, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		raeErrorList("SDL window could not be created...");
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		raeErrorList(SDL_GetError());
		raeErrorList("SDL renderer could not be created...");
	}

	int sdlblendmode = SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	if (sdlblendmode != 0) {
		raeErrorList(SDL_GetError());
		raeErrorList("SDL blendmode could not be created...");
	}

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, windowwidth, windowheight);
	if (texture == nullptr) {
		raeErrorList(SDL_GetError());
		raeErrorList("SDL texture could not be created...");
	}

	// destination rect
	screensize.x = 0;
	screensize.y = 0;
	screensize.w = windowwidth;
	screensize.h = windowheight;
}

void Raether::raeCreateWindow(const char* w_t, int w_width, int w_height) {
	title = w_t;
	windowwidth = w_width;
	windowheight = w_height;

	raeInit();
}

void Raether::raeDrawPix(int u, int v) {
	int sdlError = SDL_RenderDrawPoint(renderer, u, v);
	if (sdlError != 0) {
		raeErrorList("SDL pixel could not be drawn...");
		raeErrorList(SDL_GetError());
	}
}

void Raether::raeDrawCol(SDL_Color color) {
	int sdlError = SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	if (sdlError != 0) {
		raeErrorList(SDL_GetError());
		raeErrorList("SDL color could not be created...");
	}
}

SDL_Color Raether::raeCreateCol(glm::ui8_tvec4 color) {
	SDL_Color c{ color.r, color.g, color.b, color.a };
	return c;
}

void Raether::raeIP() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			raeState = RaeState::EXIT;
		break;
		}
	}
}

void Raether::raeLoop() {
	while (raeState == RaeState::ACTIVE) {
		raeRender();
	}
}

void Raether::raeRenderBegin() {
	SDL_SetRenderTarget(renderer, texture);
}
void Raether::raeRenderEnd() {
	SDL_SetRenderTarget(renderer, texture);
	SDL_RenderCopy(renderer, texture, NULL, &screensize);
	SDL_RenderPresent(renderer);
}

void Raether::raeRender() {
	raeRenderEnd();
	raeIP();
	raeRenderBegin();
}

void Raether::raeQuit() {
	if (raeState == RaeState::EXIT) {
		SDL_DestroyTexture(texture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
}

void Raether::raeRun() {
	raeLoop();
}