#include "pch.h"
#include "PhysicsSystem.h"

namespace nc {

	bool PhysicsSystem::Startup()
	{
		//Declare a b2Vec2 variable call gravity set it to{ 0, -10 }
		b2Vec2 gravity(0.0f, 150.0f);
		//Create an instance of b2World using new and use gravity for the constructor, assign the m_world
		m_world = new b2World(gravity);

		return m_world;
	}

	void PhysicsSystem::Shutdown()
	{
		//Call delete on m_world
		delete m_world;
		//Set m_world to nullptr;
		m_world = nullptr;
	}

	void PhysicsSystem::Update()
	{
		//Declare a float timeStep and set it to a 60th of a second(1.0f / 60.0f)
		float timeStep = (1.0f / 60.0f);
		//Call Step on m_world passing in the timestep and 8 and 3 for the velocity and position iteration
		m_world->Step(timeStep, 8, 3);
	}

	b2Body* PhysicsSystem::CreateBody(const Vector2& position, const Vector2& size, float density, bool isDynamic)
	{
		b2BodyDef bodyDef;

		bodyDef.type = (isDynamic) ? b2_dynamicBody : b2_staticBody; 
		bodyDef.position.Set(position.x, position.y); 
		b2Body* body = m_world->CreateBody(&bodyDef); 

		b2PolygonShape shape;
		shape.SetAsBox(size.x, size.y);

		body->CreateFixture(&shape, density);

		return body;
	}

	b2Body* PhysicsSystem::CreateBody(const Vector2& position, RigidBodyData data, GameObject* gameObject)
	{
		b2BodyDef bodyDef;
		bodyDef.type = (data.isDynamic) ? b2_dynamicBody : b2_staticBody;
		bodyDef.position.Set(position.x, position.y);
		bodyDef.fixedRotation = data.lockAngle;
		b2Body* body = m_world->CreateBody(&bodyDef);

		b2PolygonShape shape;
		shape.SetAsBox(data.size.x, data.size.y);

		b2FixtureDef fixtureDef;
		fixtureDef.density = data.density;
		fixtureDef.friction = data.friction;
		fixtureDef.restitution = data.restitution;
		fixtureDef.shape = &shape;
		body->CreateFixture(&fixtureDef);

		return body;
	}
}
