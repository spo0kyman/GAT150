#include "pch.h"
#include "Graphics/Texture.h"
#include "Resources/ResourceManager.h"
#include "Graphics/Renderer.h"
#include "Input/InputSystem.h"
#include "Core/Timer.h"


nc::ResourceManager resourceManager;
nc::Renderer renderer;
nc::InputSystem inputSystem;

nc::FrameTimer timer;

int main(int, char**) {

	//nc::Timer timer;
	//for (size_t i = 0; i < 1000; i++) { std::sqrt(rand() % 100); }
	//
	//std::cout << timer.ElapsedTicks() << std::endl;
	//std::cout << timer.ElapsedSeconds() << std::endl;

	
	renderer.Startup();
	resourceManager.Startup();
	inputSystem.Startup();


	renderer.Create("GAT150", 800, 600);


	nc::Texture* background = resourceManager.Get<nc::Texture>("background.png", &renderer);
	nc::Texture* cars = resourceManager.Get<nc::Texture>("cars.png", &renderer);

	float angle{ 0 };
	nc::Vector2 position{ 400, 300 };

	SDL_Event event;
	bool quit = false;
	while (!quit) {

		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}

		timer.Tick();
		resourceManager.Update();
		inputSystem.Update();

		quit = (inputSystem.GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED);

		if (inputSystem.GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD) {
			position.x = position.x - 200.0f * timer.DeltaTime();
		}

		if (inputSystem.GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD) {
			position.x = position.x + 200.0f * timer.DeltaTime();
		}


		//SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255);
		renderer.BeginFrame();

		angle = angle + 90 * timer.DeltaTime();
		background->Draw({ 0, 0 }, { 1.0f, 1.0f }, 0);
		cars->Draw({ 0, 16, 64, 144 }, position, { 1.0f, 1.0f }, 0);

		renderer.EndFrame();
	}
	renderer.Shutdown();
	resourceManager.Shutdown();
	inputSystem.Shutdown();
	IMG_Quit();
	SDL_Quit();
	return 0;
}