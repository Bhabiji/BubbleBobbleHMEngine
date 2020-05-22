#pragma once
#include "BaseComponent.h"
#include <iostream>
#include "Texture2D.h"
#include "Math.h"
namespace HiveMind
{
	class RenderComponent : public BaseComponent
	{
	public:


		explicit RenderComponent();
		explicit RenderComponent(const bool enableStaticPos, const FPoint2& staticPos);


		virtual ~RenderComponent();
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
		void SetTexture(const std::string& fileName, const std::string& IDName);
		void SetTextTexture(Texture2D* spTexture);
		void SetStaticPos(const FPoint2& pos);
		void EnableStaticPos(const bool enable);

	/*	void SetTextTexture(const std::string& text, const std::string& font);*/
	protected:
		virtual void Initialize() override;
		void Update(const float& deltaTime);
		void Render() const;
		Texture2D* m_pTexture;
		FPoint2 m_Pos;
		bool m_IsStaticPos;
	private:
		bool m_NeedsUpdate;
	};

}

