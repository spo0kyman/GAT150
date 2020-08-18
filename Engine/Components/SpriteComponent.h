#pragma once
#include "RenderComponent.h"

namespace nc {

	class SpriteComponent : public RenderComponent {

		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual void Update() override;
		virtual void Draw() override;
		void Read(const rapidjson::Value& value) override;
		

	protected:
		std::string m_textureName;
		SDL_Rect m_rect{ 0,0,0,0 };
	};

}