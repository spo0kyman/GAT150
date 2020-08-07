#include "Graphics/Texture.h"
#include "Resources/ResourceManager.h"
#include "Graphics/Renderer.h"
#include <iostream>
#include <SDL_image.h>
#include <SDL.h>


nc::ResourceManager resourceManager;
nc::Renderer renderer;

int main(int, char**){
	
	renderer.Startup();
	resourceManager.Startup();
	

	renderer.Create("GAT150", 800, 600);


	nc::Texture* texture1 = resourceManager.Get<nc::Texture>("sf2.png", &renderer);
	nc::Texture* texture2 = resourceManager.Get<nc::Texture>("sf2.bmp", &renderer);

	float angle{ 0 };

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}

		//SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255);
		renderer.BeginFrame();

		
		texture1->Draw({ 300,150 }, { 2,2 }, angle);
		texture2->Draw({ 500,100 }, { 2,2 }, angle);

		renderer.EndFrame();
	}
	IMG_Quit();
	SDL_Quit();
	return 0;
}