#pragma once
#include "Core/System.h"
#include "box2d/box2d.h"

namespace nc {

	class PhysicsSystem : public System {
	public:
		struct RigidBodyData {
			Vector2 size;
			float density{ 0 };
			float friction{ 1 };
			float restitution{ 0.3f };
			bool lockAngle{ false };
			bool isDynamic{ false };
			bool isSensor{ false };
		};
	public:
		virtual bool Startup() override;
		virtual void Shutdown() override;
		virtual void Update() override;

		b2Body* CreateBody(const Vector2& position, float angle, RigidBodyData data, class GameObject* gameObject = nullptr);
		void DestroyBody(b2Body* body);

		static Vector2 WorldToScreen(const Vector2& world) { return world * 32.0f; }
		static Vector2 ScreenToWorld(const Vector2& screen) { return screen * (1.0f / 32.0f); }

	protected:
		b2World* m_world{ nullptr };
		class ContactListener* m_contactListener{ nullptr };
	};
}