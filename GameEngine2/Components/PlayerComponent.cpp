#include "PlayerComponent.h"
#include "pch.h"
#include "Components/PhysicsComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SpriteComponent.h"

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
		auto contacts = m_owner->GetContactsWithTag("Floor");
		bool onGround = !contacts.empty();

		nc::Vector2 force{ 0,0 };

		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD) {
			force.x = -100;
		}

		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD) {
			force.x = 100;
		}

		if (onGround && m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED) {
			force.y = -1500;
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>(); 
			if (audioComponent) {
				audioComponent->Play();
			}
		}
		PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
		if (component) {
			component->ApplyForce(force);

			SpriteComponent* spriteComponent = m_owner->GetComponent<SpriteComponent>();
			Vector2 velocity = component->GetVelocity();
			if (velocity.x >= 0.5f) spriteComponent->Flip(false);
			if (velocity.x <= -0.5f) spriteComponent->Flip(true);
				
		}

		//check collision
		auto coinContacts = m_owner->GetContactsWithTag("Coin");
		for (auto contact : coinContacts) {
			contact->m_flags[GameObject::eFlags::DESTROY] = true;
		}

		auto enemyContacts = m_owner->GetContactsWithTag("Enemy");
		if (!enemyContacts.empty()) std::cout << "enemy hit\n";
	}
}
