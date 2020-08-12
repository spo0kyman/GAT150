#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

void nc::SpriteComponent::Create(void* data)
{
	m_texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>("cars.png", m_owner->m_engine->GetSystem<nc::Renderer>());
}

void nc::SpriteComponent::Destroy()
{
}

void nc::SpriteComponent::Update()
{
}

void nc::SpriteComponent::Draw()
{
	m_texture->Draw({ 64, 110, 60, 112 }, m_owner->m_transform.position, { 1.0f, 1.0f }, m_owner->m_transform.angle);
}
