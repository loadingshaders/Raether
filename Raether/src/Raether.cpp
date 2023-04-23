#include "Raether.h"

Raether::Raether() {
	windowState = RaeState::ACTIVE;
	keyState = Keystate::STANDBY;
	window = nullptr;
	title = "Raether";
	windowwidth = 900;
	windowheight = 500;
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

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, windowwidth, windowheight);
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

void Raether::raeDrawPix(int u, int v, std::vector<glm::ui8_tvec4>& PixData) {

	uint32_t* pixels;
	int pitch;
	
	const int numofPixels = u * v;

	// Lock the texture pixels for direct write access
	int sdlError = SDL_LockTexture(texture, &screensize, (void **)&pixels, &pitch);
	
	if (sdlError != 0) {
		raeErrorList(SDL_GetError());
		raeErrorList("SDL texture could not be locked...");
	}

	memcpy(pixels, PixData.data(), numofPixels * sizeof(uint32_t));

	// Unlock the texture to allow rendering
	SDL_UnlockTexture(texture);
}

bool Raether::raeIP() {
	bool Moved = false;

	SDL_Event event;

	while (SDL_PollEvent(&event)) {

		keyState = Keystate::STANDBY;
		mouseState = Mousestate::STATIC;

		if (event.type == SDL_QUIT) {
			windowState = RaeState::EXIT;
			break;
		}
		else if (event.button.button == SDL_BUTTON_LEFT) {

			if (event.type == SDL_MOUSEMOTION) {

				// Hide the mouse cursor
				SDL_ShowCursor(SDL_DISABLE);

				// Lock the mouse to the window
				SDL_SetWindowGrab(window, SDL_TRUE);

				delta.x = event.motion.xrel;
				delta.y = event.motion.yrel;

				Moved = true;

				mouseState = Mousestate::INMOTION;
				
				break;
			}
		}
		else if (event.type == SDL_KEYDOWN) {

			if (event.key.keysym.sym == SDLK_w) {
				keyState = Keystate::W;
				Moved = true;
				break;
			}
			else if (event.key.keysym.sym == SDLK_a) {
				keyState = Keystate::A;
				Moved = true;
				break;
			}
			else if (event.key.keysym.sym == SDLK_s) {
				keyState = Keystate::S;
				Moved = true;
				break;
			}
			else if (event.key.keysym.sym == SDLK_d) {
				keyState = Keystate::D;
				Moved = true;
				break;
			}
			else if (event.key.keysym.sym == SDLK_q) {
				keyState = Keystate::Q;
				Moved = true;
				break;
			}
			else if (event.key.keysym.sym == SDLK_e) {
				keyState = Keystate::E;
				Moved = true;
				break;
			}
		}
		else {
			// Show the mouse cursor
			SDL_ShowCursor(SDL_ENABLE);

			// Unlock the mouse to the window
			SDL_SetWindowGrab(window, SDL_FALSE);
		}

	}
	return Moved;
}

void Raether::raeRenderBegin() {
	SDL_SetRenderTarget(renderer, texture);
	SDL_RenderCopy(renderer, texture, NULL, &screensize);
	SDL_RenderPresent(renderer);
}

void Raether::raeRenderEnd() {
	SDL_SetRenderTarget(renderer, texture);
}

void Raether::raeQuit() {
	if (windowState == RaeState::EXIT) {
		SDL_DestroyTexture(texture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
}