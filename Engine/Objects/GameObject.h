#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Engine.h"
#include <list>

namespace nc {

	class Component;

	class GameObject : public Object {
	public:
		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;

		void Read(const rapidjson::Value& value) override;

		void Update();
		void Draw();

		template<typename T>
		T* GetComponent();

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);
		void RemoveAllComponenets();
		void ReadComponents(const rapidjson::Value& value);

	public:
		std::string m_name;
		Transform m_transform;
		Engine* m_engine;

	protected:
		std::list<Component*> m_components;
		
	};
	
	template<typename T>
	T* GameObject::GetComponent() {
		T* result{ nullptr };

		for (auto component : m_components) {
			result = dynamic_cast<T*>(component);
			if (result) break;
		}

		return result;
	}
}