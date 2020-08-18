#include "pch.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Components/PlayerComponent.h"
#include "Core/Json.h"
#include "Core/Factory.h"
#include "Objects/ObjectFactory.h"

nc::Engine engine;

int main(int, char**) {

	engine.Startup();

	nc::ObjectFactory::Instance().Initialize();

	nc::ObjectFactory::Instance().Register("PlayerComponent", nc::Object::Instantiate<nc::PlayerComponent>);

	nc::GameObject* player = dynamic_cast<nc::GameObject*>(nc::ObjectFactory::Instance().Create("GameObject"));

	player->Create(&engine);

	rapidjson::Document document;
	nc::json::Load("player.txt", document);
	player->Read(document);

	nc::Component* component;
	component = nc::ObjectFactory::Instance().Create<nc::Component>("PhysicsComponent");
	component->Create(player);
	player->AddComponent(component);

	component = nc::ObjectFactory::Instance().Create<nc::Component>("SpriteComponent");
	nc::json::Load("sprite.txt", document);
	component->Create(player);
	component->Read(document);
	player->AddComponent(component);

	component = nc::ObjectFactory::Instance().Create<nc::Component>("PlayerComponent");
	component->Create(player);
	player->AddComponent(component);

	nc::Texture* background = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("background.png", engine.GetSystem<nc::Renderer>());
	
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

		engine.Update();
		player->Update();

		quit = (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED);

		//draw
		engine.GetSystem<nc::Renderer>()->BeginFrame();

		background->Draw({ 0, 0 }, { 1.0f, 1.0f }, 0);
		player->Draw();
		
		engine.GetSystem<nc::Renderer>()->EndFrame();
	}
	engine.Shutdown();
	return 0;
}