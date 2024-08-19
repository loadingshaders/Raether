#include "Raether.h"

Raether::Raether() : windowTitle("Raether"),
					 windowWidth(1000),
					 windowHeight(500),
					 window(nullptr),
					 renderer(nullptr),
					 texture(nullptr),
					 screensize(SDL_Rect{ 0, 0, windowWidth, windowHeight }),
					 windowState(RaeState::ACTIVE),
					 keyState(Keystate::STANDBY),
					 mouseDelta(glm::si32_tvec2(0.f, 0.f)),
					 scrollAmount(0)
{
}
Raether::~Raether() { }

void Raether::raeInit() {
	// Setting the render scale quality as nearest pixel sampling
	if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0) != SDL_TRUE) {
		Utils::PrintError("SDL Hint could not be set: " + std::string(SDL_GetError()));
	}
	// Initialize the required subsystems
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
		Utils::PrintError("SDL subsystems could not be initialized: " + std::string(SDL_GetError()));
	}
	// Create window pointer
	window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		Utils::PrintError("SDL window could not be created: " + std::string(SDL_GetError()));
	}
	// Create renderer pointer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		Utils::PrintError("SDL renderer could not be created: " + std::string(SDL_GetError()));
	}
	// Set render blendmode as alpha blending
	// dstRGB = (srcRGB * srcA) + (dstRGB * (1 - srcA))
	// dstA = srcA + (dstA * (1 - srcA))
	if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND)) {
		Utils::PrintError("SDL blendmode could not be set: " + std::string(SDL_GetError()));
	}
	// Create the texture with texture acess streaming
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
	if (texture == nullptr) {
		Utils::PrintError("SDL texture could not be created: " + std::string(SDL_GetError()));
	}

	// Setting up the destination rect
	screensize.x = 0;
	screensize.y = 0;
	screensize.w = windowWidth;
	screensize.h = windowHeight;
}

void Raether::raeCreateWindow(const char* w_t, int w_width, int w_height) {
	windowTitle = w_t;
	windowWidth = w_width;
	windowHeight = w_height;

	raeInit();
}

void Raether::raeDrawImage(std::vector<glm::ui8_tvec4>& PixData) {

	uint32_t* pixels;
	int pitch;

	// Lock the texture pixels for direct write access
	if (SDL_LockTexture(texture, &screensize, (void**)&pixels, &pitch)) {
		Utils::PrintError("SDL texture could not be locked: " + std::string(SDL_GetError()));
	}

	// Copy the pixel data to the locked texture
	memcpy(pixels, PixData.data(), PixData.size() * sizeof(glm::ui8_tvec4));

	// Unlock the texture to allow rendering
	SDL_UnlockTexture(texture);
}

bool Raether::raeInputEvents() {

	bool Moved = false;
	keyState = Keystate::STANDBY;
	mouseState = Mousestate::STATIC;

	SDL_Event event;

	while (SDL_PollEvent(&event)) {

		// Exit event
		if (event.type == SDL_QUIT) {
			windowState = RaeState::EXIT;
			break;
		}
		// Mouse wheel event
		else if (event.type == SDL_MOUSEWHEEL) {
			// Hide the mouse cursor
			SDL_ShowCursor(SDL_DISABLE);
			// Lock the mouse to the window
			SDL_SetWindowGrab(window, SDL_TRUE);

			scrollAmount = event.wheel.y;

			mouseState = Mousestate::SCROLLING;
			Moved = true;
			
			break;
		}
		// Mouse left button event
		else if (event.button.button == SDL_BUTTON_LEFT) {

			if (event.type == SDL_MOUSEMOTION) {
				// Hide the mouse cursor
				SDL_ShowCursor(SDL_DISABLE);
				// Lock the mouse to the window
				SDL_SetWindowGrab(window, SDL_TRUE);

				mouseDelta.x = event.motion.xrel;
				mouseDelta.y = event.motion.yrel;

				mouseState = Mousestate::INMOTION;
				Moved = true;
				
				break;
			}
		}
		// Keyboard event
		else if (event.type == SDL_KEYDOWN) {

			if (event.key.keysym.sym == SDLK_w) {
				keyState = Keystate::W;
				Moved = true;
			}
			else if (event.key.keysym.sym == SDLK_a) {
				keyState = Keystate::A;
				Moved = true;
			}
			else if (event.key.keysym.sym == SDLK_s) {
				keyState = Keystate::S;
				Moved = true;
			}
			else if (event.key.keysym.sym == SDLK_d) {
				keyState = Keystate::D;
				Moved = true;
			}
			else if (event.key.keysym.sym == SDLK_q) {
				keyState = Keystate::Q;
				Moved = true;
			}
			else if (event.key.keysym.sym == SDLK_e) {
				keyState = Keystate::E;
				Moved = true;
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
	// Clear the render target
	SDL_RenderClear(renderer);
}

void Raether::raeRenderEnd() {
	// Copy the texture to the render to the render target
	SDL_RenderCopy(renderer, texture, NULL, &screensize);
	// Swap the buffers
	SDL_RenderPresent(renderer);
}

void Raether::raeQuit() {
	if (windowState == RaeState::EXIT) {
		// Destroy all the pointers
		SDL_DestroyTexture(texture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		// Clean up all the initialized subsystems
		SDL_Quit();
	}
}
