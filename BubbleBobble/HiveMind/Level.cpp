#include "HiveMindPCH.h"
#include "Level.h"
#include "Components.h"
#include "TransformComponent.h"

HiveMind::Level::Level(const std::vector< std::pair<std::pair<SHORT, Float2>, GameObject*>>& levelData)
	:m_LevelData{levelData}
{
	for (size_t i = 0; i < m_LevelData.size(); i++)
	{
		FPoint3 pos = m_LevelData[i].second->GetTransform()->GetPosition();
		pos *= 2;
		m_LevelData[i].second->GetTransform()->SetPosition(pos);

	}
}

HiveMind::Level::Level()
	:m_LevelData{}
{
}

void HiveMind::Level::SetLevelData(const std::vector< std::pair<std::pair<SHORT, Float2>, GameObject*>>& pLevelData)
{
	m_LevelData = pLevelData;
	
}

std::vector<std::pair<std::pair<SHORT, Float2>, HiveMind::GameObject*>> HiveMind::Level::GetLevelData() const
{
	return m_LevelData;
}

HiveMind::Level::~Level()
{
}

void HiveMind::Level::Initialize()
{
	for (size_t i = 0; i < m_LevelData.size(); i++)
	{

		m_LevelData[i].second->Initialize();
		SpriteComponent* sprite = m_LevelData[i].second->GetComponent<SpriteComponent>();
		FPoint3 dstPos{ sprite->GetCroppedWidth() * m_LevelData[i].first.second.x, sprite->GetCroppedHeight() * m_LevelData[i].first.second.y,0 }; //The height or width of each row or column times the row or column it's at
		dstPos *= 2;
		m_LevelData[i].second->GetTransform()->SetPosition(dstPos);
	}

}

void HiveMind::Level::Update(const float& deltaTime)
{
	for (size_t i = 0; i < m_LevelData.size(); i++)
	{
		if (m_LevelData[i].first.first != 0)
		{
			SpriteComponent* sprite = m_LevelData[i].second->GetComponent<SpriteComponent>();
			if (sprite != nullptr)
			{
				
				FPoint2 dstPos{ m_LevelData[i].second->GetTransform()->GetPosition() }; //The height or width of each row or column times the row or column it's at
				FPoint2 srcPos{ sprite->GetCroppedWidth() * m_LevelData[i].first.first, sprite->GetCroppedHeight() * m_LevelData[i].first.first };
				sprite->SetLocalSpriteArea(srcPos, dstPos); //
				sprite->RescaleSprite(Float2(2, 2));
				//m_LevelData[i].second->Update(deltaTime);
			}
		}
	}
	//GameObject::Update(deltaTime);
}

void HiveMind::Level::Render() const
{
	for (size_t i = 0; i < m_LevelData.size(); i++)
	{
		m_LevelData[i].second->Render();
	}
}

bool HiveMind::Level::IsOnGround() const
{
	return false;
}


