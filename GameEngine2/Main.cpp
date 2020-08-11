#include "pch.h"
#include "Graphics/Texture.h"
#include "Resources/ResourceManager.h"
#include "Graphics/Renderer.h"
#include "Input/InputSystem.h"
#include "Core/Timer.h"
#include "Math/Math.h"

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
	nc::Vector2 velocity{ 0,0 };

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
			angle = angle - 200.0f * timer.DeltaTime();
		}

		if (inputSystem.GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD) {
			angle = angle + 200.0f * timer.DeltaTime();
		}

		//physics
		nc::Vector2 force{ 0,0 };
		if (inputSystem.GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD) {
			force = nc::Vector2::forward * 1000.0f;
		}
		force = nc::Vector2::Rotate(force, nc::DegreesToRadians(angle));
		velocity = velocity + force * timer.DeltaTime();
		velocity = velocity * 0.95f;
		position = position + velocity * timer.DeltaTime();


		//draw
		renderer.BeginFrame();

		
		background->Draw({ 0, 0 }, { 1.0f, 1.0f }, 0);
		cars->Draw({ 64, 110, 60, 112 }, position, { 1.0f, 1.0f }, angle);

		renderer.EndFrame();
	}
	renderer.Shutdown();
	resourceManager.Shutdown();
	inputSystem.Shutdown();
	IMG_Quit();
	SDL_Quit();
	return 0;
}