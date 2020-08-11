#pragma once
#include <string>
#include "Math/Vector2.h"
#include "Resources/Resource.h"
#include <SDL.h>

namespace nc {
	class Texture : public Resource {
	public:
		bool Create(const std::string& name, void* renderer) override;
		void Destroy() override;

		void Draw(const Vector2& position, const Vector2& scale = { 1, 1 }, float angle = 0);
		void Draw(const SDL_Rect& source, const Vector2& position, const Vector2& scale = { 1, 1 }, float angle = 0);

		Vector2 GetSize() const;

	protected:
		SDL_Texture* m_texture;
		SDL_Renderer* m_renderer;
	};
}
