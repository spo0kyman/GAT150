#include "PlayerComponent.h"
#include "pch.h"
#include "Components/PhysicsComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SpriteComponent.h"

namespace nc {

	void PlayerComponent::Create(void* data)
	{
		m_owner = static_cast<GameObject*>(data);
		EventManager::Instance().Subscribe("CollisionEnter", std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1), m_owner);
		EventManager::Instance().Subscribe("CollisionEnter", std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1), m_owner);
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
				audioComponent->SetSoundName("jump.wav");
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

	}
	void PlayerComponent::OnCollisionEnter(const Event& event)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);

		if (gameObject->m_tag == "Enemy") {
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			audioComponent->SetSoundName("grunt.wav");
			audioComponent->Play();

			m_owner->m_flags[GameObject::eFlags::DESTROY] = true;

			Event event;
			event.type = "PlayerDead";
			int score = 300;
			event.data = &score;
			EventManager::Instance().Notify(event);
		}

		if (gameObject->m_tag == "Coin") {
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			audioComponent->SetSoundName("coin.wav");
			audioComponent->Play();

			gameObject->m_flags[GameObject::eFlags::DESTROY] = true;
		}

		
	}
	
	void PlayerComponent::OnCollisionExit(const Event& event)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);
		std::cout << "collision exit " << gameObject->m_name << std::endl;
	}
}
