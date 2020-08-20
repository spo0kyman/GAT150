#pragma once
#include "Object.h"

namespace nc {
	class Engine;
	class GameObject;

	class Scene : public Object {
	public:
		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual void Update() override;

		void Read(const rapidjson::Value& value) override;
		void ReadGameObjects(const rapidjson::Value& value);

		void Draw();

		GameObject* Find(const std::string& name);

		void AddGameObject(GameObject* gameObject);
		void RemoveGameObject(GameObject* gameObject);
		void RemoveAllGameObjects();

	protected:
		Engine* m_engine{ nullptr };
		std::list<GameObject*> m_gameObjects;
	};
}