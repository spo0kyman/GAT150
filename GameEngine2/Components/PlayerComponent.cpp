#include "PlayerComponent.h"
#include "pch.h"
#include "Components/PhysicsComponent.h"

namespace nc {

	void PlayerComponent::Create(void* data)
	{
		m_owner = static_cast<GameObject*>(data);
	}

	void PlayerComponent::Destroy()
	{

	}

	void PlayerComponent::Update()
	{
		nc::Vector2 force{ 0,0 };

		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD) {
			force.x = -20000;
		}

		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD) {
			force.x = 20000;
		}

		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED) {
			force.y = -400000;
		}
		PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
		if (component) {
			component->SetForce(force);
		}
	}
}
