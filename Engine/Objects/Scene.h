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
		void ReadPrototypes(const rapidjson::Value& value);

		void Draw();

		GameObject* Find(const std::string& name);
		std::vector<GameObject*> FindGameObjectsWithTag(const std::string& tag);

		void AddGameObject(GameObject* gameObject);
		void RemoveGameObject(GameObject* gameObject);
		void RemoveAllGameObjects();

	public:
		Engine* m_engine{ nullptr };

	protected:
		std::list<GameObject*> m_gameObjects;
	};
}