#pragma once
#include "BaseComponent.h"
#include <string>
#include "Math.h"
namespace HiveMind {

	class ButtonComponent :
		public BaseComponent
	{
	public:
		enum class Action
		{
			NONE, LOADSINGLEPLAYERSCENE, LOADMULTIPLAYERSCENE, DESTROYSINGLEPLAYERSCENE, DESTROYMULTIPLAYERSCENE
		};
		ButtonComponent(const Int2& size, const std::string& linkedScene);
		ButtonComponent(const Int2& size, const Action action);
		ButtonComponent(const Int2& size, const Action action, const std::string& linkedScene);

		virtual ~ButtonComponent();

	protected:
		virtual void Initialize() override;
		virtual void Render() const override;
		virtual void Update(const float& elapsedSec);
	private:
		void Execute(Action action);
		const Int2 m_Size;
		const std::string m_LinkedSceneName;
		const Action m_Action;
		float m_Alpha;
	};
}


