#include "pch.h"
#include "GameObject.h"
#include "Components/Component.h"
#include "Components/RenderComponent.h"

namespace nc {

	void GameObject::Create(void* data)
	{
		m_engine = static_cast<Engine*>(data);
	}

	void GameObject::Destroy()
	{
		RemoveAllComponenets();
	}

	void GameObject::Read(const rapidjson::Value& value)
	{
		json::Get(value, "name", m_name);
		json::Get(value, "position", m_transform.position);
		json::Get(value, "scale", m_transform.scale);
		json::Get(value, "angle", m_transform.angle);
	}

	void GameObject::Update()
	{
		for (auto component : m_components) {
			component->Update();
		}
	}

	void GameObject::Draw()
	{
		RenderComponent* component = GetComponent<RenderComponent>();
		if (component) {
			component->Draw();
		}
	}

	void GameObject::AddComponent(Component* component)
	{
		m_components.push_back(component);
	}

	void GameObject::RemoveComponent(Component* component)
	{
		auto iter = std::find(m_components.begin(), m_components.end(), component);
		if (iter != m_components.end()) {
			(*iter)->Destroy();
			delete(*iter);
		}
	}

	void GameObject::RemoveAllComponenets()
	{
		for (auto component : m_components) {
			component->Destroy();
			delete component;
		}
	}
}
