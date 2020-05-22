#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include <iostream>
#include <string>
#include <chrono>
namespace HiveMind
{
	class UIComponent : public BaseComponent
	{
	public:


		explicit UIComponent();

		virtual ~UIComponent() = default;
		UIComponent(const UIComponent& other) = delete;
		UIComponent(UIComponent&& other) = delete;
		UIComponent& operator=(const UIComponent& other) = delete;
		UIComponent& operator=(UIComponent&& other) = delete;
		void SetPreviousTime(const std::chrono::high_resolution_clock::time_point& now);
		void SetCurrentTime(const std::chrono::high_resolution_clock::time_point& now);


	protected:
		virtual void Initialize() override;
		virtual void Update(const float& deltaTime) override;
		virtual void Render() const override;
	private:
		bool m_NeedsUpdate;
		std::chrono::high_resolution_clock::time_point m_PrevTime;
		std::chrono::high_resolution_clock::time_point m_CurrTime;
		int m_FPS;

	};

}

