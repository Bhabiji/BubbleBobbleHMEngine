#include "HiveMindPCH.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Math.h"

HiveMind::RenderComponent::RenderComponent()
	: m_NeedsUpdate{ true }
	, m_pTexture{ nullptr }
	, m_IsStaticPos{false}
{
}

HiveMind::RenderComponent::RenderComponent(const bool enableStaticPos, const FPoint2& staticPos)
	:m_NeedsUpdate{true}
	,m_pTexture{nullptr}
	,m_IsStaticPos{enableStaticPos}
	,m_Pos{staticPos}
{
}

HiveMind::RenderComponent::~RenderComponent()
{
}

void HiveMind::RenderComponent::SetTexture(const std::string& fileName, const std::string& IDName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName,IDName);

}

void HiveMind::RenderComponent::SetTextTexture(Texture2D* spTexture)
{
	m_pTexture = spTexture;
}

void HiveMind::RenderComponent::SetStaticPos(const FPoint2& pos)
{
	m_Pos = pos;
}

void HiveMind::RenderComponent::EnableStaticPos(const bool enable)
{
	m_IsStaticPos = enable;
}

void HiveMind::RenderComponent::Initialize()
{
	m_IsInitialized = true;
}

void HiveMind::RenderComponent::Update(const float& elapsedSec)
{
	if (!m_IsStaticPos)
		m_Pos = GetTransform()->GetPosition();
	(elapsedSec);
}

void HiveMind::RenderComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_pTexture, m_Pos.x, m_Pos.y);
}
