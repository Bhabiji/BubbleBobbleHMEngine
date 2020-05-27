#pragma once
#include "TextComponent.h"
#include "Math.h"
class Font;
namespace HiveMind
{
	class CounterComponent: public TextComponent
	{
	public:
		CounterComponent(Font* pFont, const int& initScore, const FPoint2& pos);
		CounterComponent(Font* pFont, const int& initScore,const bool enableStaticPos, const FPoint2& staticPos);

		virtual ~CounterComponent();
		void AddToCounter(const int& toAddCount);
		void SetCounter(const int& toSetCount);

		virtual void Initialize() override;
		virtual void Update(const float& elapsedSec) override;
	protected:
		int m_InitCount;
		Font* m_pFont;
	private:
	};
}

