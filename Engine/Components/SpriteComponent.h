#pragma once
#include "RenderComponent.h"

namespace nc {

	class SpriteComponent : public RenderComponent {
	public:
		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() const override { return new SpriteComponent{ *this }; }

		virtual void Update() override;
		virtual void Draw() override;
		void Read(const rapidjson::Value& value) override;
		

	protected:
		std::string m_textureName;
		Vector2 m_origin;
		SDL_Rect m_rect{ 0,0,0,0 };
	};

}