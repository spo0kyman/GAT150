#include "pch.h"
#include "Renderer.h"

bool nc::Renderer::Startup()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	return true;
}

void nc::Renderer::Shutdown()
{
}

void nc::Renderer::Update()
{
}

bool nc::Renderer::Create(const std::string& name, int width, int height)
{
	m_window = SDL_CreateWindow(name.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN);
	if (m_window == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl; SDL_Quit();
		return false;
	}


	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr) {
		std::cout << "Error: " << SDL_GetError() << std::endl; SDL_Quit();
		return false;
	}

	return true;
}

void nc::Renderer::BeginFrame()
{
	SDL_RenderClear(m_renderer);
}

void nc::Renderer::EndFrame()
{
	SDL_RenderPresent(m_renderer);
}
