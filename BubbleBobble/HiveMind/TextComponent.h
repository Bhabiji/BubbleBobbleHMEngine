#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "RenderComponent.h"
namespace HiveMind
{
	class Font;
	class Texture2D;
	class TextComponent : public RenderComponent
	{
	public:
		void SetText(const std::string& text);
		void SetPosition(float x, float y);

		TextComponent(const std::string& text,  Font* font);
		TextComponent(const std::string& text, Font* font, const bool enableStaticPos, const FPoint2& staticPos);

		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	protected:
		virtual void Initialize() override;
		void Update(const float& deltaTime);
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		Font* m_Font;
	};
}
