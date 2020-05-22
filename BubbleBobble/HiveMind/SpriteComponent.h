#pragma once
#include "RenderComponent.h"
#include "Primitives.h"
#include "Animations.h"
#include "Math.h"
namespace HiveMind
{
	class SpriteComponent final : public RenderComponent
	{
	public:
		SpriteComponent(const std::string& resourcePath, const std::string& resourceName, const SpriteConfig& spriteConfig, const bool isAnimation);
		virtual ~SpriteComponent();
		SpriteComponent(const  SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const  SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;
		void SetCroppingDimensions();
		void SetLocalSpriteArea(const FPoint2& srcPos, const FPoint2& dstPos);
		int GetCroppedWidth() const;
		int GetCroppedHeight() const;
		SpriteConfig GetSpriteConfig() const;
		RectI GetDest() const;
		void SetRow(const int rowVal);

		void RescaleSprite(const Float2& scaleMultiplier);
	protected:
		virtual void Initialize() override;
		virtual void Update(const float& deltaTime) override;
		void Render() const;
	private:

		bool m_IsAnimation;

		//RememberNote: Prog1/2 for Reference
		int m_CropWidth;
		int m_CropHeight;

		int m_CurrFrameX;
		int m_CurrFrameY;

		float m_AnimTimer;

		RectI m_SrcRect;
		RectI m_DestRect;
		std::string m_Path;
		SpriteConfig m_Config;
	};
}

