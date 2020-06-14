#include "HiveMindPCH.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
HiveMind::SpriteComponent::SpriteComponent(const std::string& resourcePath, const std::string& resourceName, const SpriteConfig& spriteConfig, const bool isAnimation)
	:m_SrcRect{}
	, m_DestRect{}
	, m_Path{ resourceName }
	, m_Config{ spriteConfig }
	, m_AnimTimer{}
	, m_IsAnimation{isAnimation}
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(resourcePath, resourceName);
}

HiveMind::SpriteComponent::~SpriteComponent()
{
}

void HiveMind::SpriteComponent::SetCroppingDimensions()
{
	int texWidth{};
	int texHeight{};
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &texWidth, &texHeight); //Get measurements of texture to crop
	m_CropWidth = texWidth / m_Config.columns;
	m_CropHeight = texHeight / m_Config.rows;
	m_DestRect.w = m_CropWidth;
	m_DestRect.h = m_CropHeight;

}
//source is the sprite location within image, dest is the location it has to project to
void HiveMind::SpriteComponent::SetLocalSpriteArea(const FPoint2& srcPos, const FPoint2& dstPos)
{
	m_DestRect = RectI{ int(dstPos.x), int(dstPos.y), int(m_DestRect.w), int(m_DestRect.h) };
	m_SrcRect = RectI{ int(srcPos.x), int(srcPos.y), int(m_CropWidth), int(m_CropHeight) };
}

int HiveMind::SpriteComponent::GetCroppedWidth() const
{
	return m_CropWidth;
}

int HiveMind::SpriteComponent::GetCroppedHeight() const
{
	return m_CropHeight;
}

SpriteConfig HiveMind::SpriteComponent::GetSpriteConfig() const
{
	return m_Config;
}

HiveMind::RectI HiveMind::SpriteComponent::GetDest() const
{
	return m_DestRect;
}

void HiveMind::SpriteComponent::SetRow(const int rowVal)
{
	m_CurrFrameY = rowVal;
}



void HiveMind::SpriteComponent::RescaleSprite(const Float2& scaleMultiplier)
{
	//m_CropWidth *= int(scaleMultiplier.x);
	//m_CropHeight *= int(scaleMultiplier.y);
	if (GetGameObject())
	{
		auto pos = GetGameObject()->GetTransform()->GetPosition();
		pos.x *= scaleMultiplier.x;
		pos.y *= scaleMultiplier.y;
		GetTransform()->SetPosition(pos);
	}

	m_DestRect.w *= int(scaleMultiplier.x);
	m_DestRect.h *= int(scaleMultiplier.y);
}

void HiveMind::SpriteComponent::Initialize()
{
	m_IsInitialized = true;
	SetTexture("",m_Path);
}

void HiveMind::SpriteComponent::Update(const float& elapsedSec)
{
	auto pos = GetGameObject()->GetTransform()->GetPosition();
	m_DestRect.x = int(pos.x);
	m_DestRect.y = int(pos.y);

	if (m_IsAnimation)
	{
		const float animCooldown{ 0.05f };
		m_AnimTimer += elapsedSec;
		if (m_AnimTimer >= animCooldown)
		{
			if (m_CurrFrameY > m_Config.rows)
				m_CurrFrameY = m_Config.rows;

			m_SrcRect.x += m_CropWidth;
			m_SrcRect.y = m_CropHeight * m_CurrFrameY;
			m_CurrFrameX++;
			if (m_CurrFrameX >= m_Config.columns)
			{
				//reset to startframe
				m_SrcRect.x = 0;
				m_CurrFrameX = 0;
			}
			m_AnimTimer = 0;
		}
	}

}

void HiveMind::SpriteComponent::Render() const
{
	HiveMind::Renderer::GetInstance().RenderTexture(*m_pTexture, m_SrcRect, m_DestRect);
}


