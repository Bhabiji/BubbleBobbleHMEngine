#include "HiveMindPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Components.h"
#include "RenderComponent.h"

HiveMind::GameObject::GameObject()
	:m_pTransform{new TransformComponent()}
{
	AddComponent(m_pTransform);
}

HiveMind::GameObject::~GameObject()
{
	for (BaseComponent* pComponent: m_pComponents)
	{
		delete pComponent;
	}
	
}


void HiveMind::GameObject::Initialize()
{
	for (BaseComponent* pComponent : m_pComponents)
	{
		if(!pComponent->IsInitialized())
			pComponent->Initialize();
	}
}

void HiveMind::GameObject::Update(const float& deltaTime)
{
	for (BaseComponent* pComponent : m_pComponents)
		pComponent->Update(deltaTime);
}

void HiveMind::GameObject::Render() const
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Render();
	}
	//const auto pos = m_pTransform->GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

bool HiveMind::GameObject::IsOnGround() const
{
	return m_IsOnGround;
}

void HiveMind::GameObject::CreateLevelBlock(const int& blockData, FPoint3& pos)
{
		SpriteComponent* pSpriteComponent{ new SpriteComponent("../Data/Blocks.png","Blocks", SpriteConfig{ 10, 10 }, false)};
		BlockColliderComponent* pColliderComponent(new BlockColliderComponent());
		pos *= 2.f;
		pSpriteComponent->SetCroppingDimensions();
		FPoint3 dstPos{ pSpriteComponent->GetCroppedWidth() * pos.x, pSpriteComponent->GetCroppedHeight() * pos.y,0 };
		pSpriteComponent->SetLocalSpriteArea(FPoint2(blockData * pSpriteComponent->GetCroppedWidth(), blockData * pSpriteComponent->GetCroppedHeight()), dstPos);
		AddComponent(pSpriteComponent);
		AddComponent(pColliderComponent);
		pSpriteComponent->RescaleSprite(Float2(2.f, 2.f));
		GetTransform()->SetPosition(dstPos);
}

void HiveMind::GameObject::CreateLevelBlockNoCollision(const int& blockData, FPoint3& pos)
{
	SpriteComponent* pSpriteComponent{ new SpriteComponent("../Data/Blocks.png","Blocks", SpriteConfig{ 10, 10 }, false) };
	pos *= 2.f;
	pSpriteComponent->SetCroppingDimensions();
	FPoint3 dstPos{ pSpriteComponent->GetCroppedWidth() * pos.x, pSpriteComponent->GetCroppedHeight() * pos.y,0 };
	pSpriteComponent->SetLocalSpriteArea(FPoint2(blockData * pSpriteComponent->GetCroppedWidth(), blockData * pSpriteComponent->GetCroppedHeight()), dstPos);
	AddComponent(pSpriteComponent);
	pSpriteComponent->RescaleSprite(Float2(2.f, 2.f));
	GetTransform()->SetPosition(dstPos);
}


void HiveMind::GameObject::CreateBlob(const bool isLookingLeft, const FPoint3& pos, const FPoint2& velocity, const float lifeTime)
{
	SpriteComponent* pSpriteComponent{ new SpriteComponent("../Data/BulletSprite.png","Bullets", SpriteConfig{ 8, 1 }, true) };
	ProjectileComponent* pProjectileComp{ new ProjectileComponent(isLookingLeft,pos,velocity) };
	LifeTimeComponent* pMortalComp{ new LifeTimeComponent(lifeTime, true) };
	FPoint2 srcPos{0, 0};

	GetTransform()->SetPosition(pos);
	pSpriteComponent->SetCroppingDimensions();
	pSpriteComponent->SetLocalSpriteArea(srcPos, pos);

	AddComponent(pSpriteComponent);
	AddComponent(pProjectileComp);
	AddComponent(pMortalComp);
	GetTransform()->SetPosition(pos);

}

void HiveMind::GameObject::CreatePlayer(const SpriteConfig& spriteConfig)
{
	SpriteComponent* pSpriteComponent{ new SpriteComponent("../Data/CharacterSprites.png", "Characters", spriteConfig, false) };
	pSpriteComponent->SetCroppingDimensions();
	FPoint2 srcPos{ 0,0 };
	FPoint3 pos{ GetTransform()->GetPosition() };
	GetTransform()->SetPosition(pos);
	pSpriteComponent->SetLocalSpriteArea(srcPos, pos);
	ActorComponent* pActorComponent{ new PlayerControlComponent() };

	ScoreCounterComponent* pScoreCounterComp{ new ScoreCounterComponent(ResourceManager::GetInstance().LoadFont("pixelated.ttf",30),0,FPoint2{40,2}) };
	LifeCounterComponent* pLifeCounterComp{ new LifeCounterComponent(ResourceManager::GetInstance().LoadFont("pixelated.ttf",30),3,FPoint2{224,2}) };

	AddComponent(pScoreCounterComp);
	AddComponent(pLifeCounterComp);

	AddComponent(pActorComponent);

	AddComponent(pSpriteComponent);
	AddComponent(new CharacterColliderComponent());
	pSpriteComponent->RescaleSprite(Float2(2, 2));
	SetPosition(FPoint2(100, 170));
}

void HiveMind::GameObject::CreateMaita()
{
	SpriteComponent* pSpriteComponent{ new SpriteComponent("../Data/Maita.png", "Maita", SpriteConfig{8,5}, false) };
	pSpriteComponent->SetCroppingDimensions();
	FPoint2 srcPos{ 0,0 };
	FPoint3 pos{ GetTransform()->GetPosition() };
	pSpriteComponent->SetLocalSpriteArea(srcPos, pos);
	NPCComponent* pActorComponent{ new NPCComponent() };
	LifeTimeComponent* pMortalComp{ new LifeTimeComponent(0.f, false) };
	AddComponent(pActorComponent);
	AddComponent(pSpriteComponent);
	AddComponent(pMortalComp);
	AddComponent(new CharacterColliderComponent());
	pSpriteComponent->RescaleSprite(Float2(2, 2));
	SetPosition(FPoint2(120, 170));
}

void HiveMind::GameObject::CreateMaita(FPoint3& pos)
{
	SpriteComponent* pSpriteComponent{ new SpriteComponent("../Data/Maita.png", "Maita", SpriteConfig{8,5}, false) };
	FPoint2 srcPos{ 0,0 };
	pos.y *= 2;
	pSpriteComponent->SetCroppingDimensions();
	FPoint3 dstPos{ pSpriteComponent->GetCroppedWidth() * pos.x, pSpriteComponent->GetCroppedHeight() * pos.y,0 };
	GetTransform()->SetPosition(pos);
	pSpriteComponent->SetLocalSpriteArea(srcPos, pos);
	NPCComponent* pActorComponent{ new NPCComponent() };
	LifeTimeComponent* pMortalComp{ new LifeTimeComponent(0.f, false) };
	AddComponent(pActorComponent);
	AddComponent(pSpriteComponent);
	AddComponent(pMortalComp);
	AddComponent(new CharacterColliderComponent());
	pSpriteComponent->RescaleSprite(Float2(2, 2));
	SetPosition(dstPos);

}



void HiveMind::GameObject::CreateScorePickup(const int& whichPickup, const FPoint3& pos, std::vector<GameObject*> pPlayerVec)
{
	SpriteComponent* pSpriteComponent{ new SpriteComponent("../Data/ScorePickups.png", "ScorePickups", SpriteConfig{3,1}, false) };
	pSpriteComponent->SetCroppingDimensions();
	FPoint2 srcPos{ pSpriteComponent->GetCroppedWidth() * whichPickup,0 };
	PickupComponent* pPickupComponent{new PickupComponent(1000*whichPickup+1,pPlayerVec)};
	LifeTimeComponent* pMortalComp{ new LifeTimeComponent(0.f, false) };

	GetTransform()->SetPosition(pos);
	pSpriteComponent->SetLocalSpriteArea(srcPos, GetTransform()->GetPosition());
	pSpriteComponent->RescaleSprite(Float2{ 2,2 });
	AddComponent(pSpriteComponent);
	AddComponent(pMortalComp);
	AddComponent(pPickupComponent);

}

void HiveMind::GameObject::CreateScorePickup(const int& whichPickup, const FPoint3& pos, GameObject* pPlayer)
{
	SpriteComponent* pSpriteComponent{ new SpriteComponent("../Data/ScorePickups.png", "ScorePickups", SpriteConfig{3,1}, false) };
	pSpriteComponent->SetCroppingDimensions();
	FPoint2 srcPos{ pSpriteComponent->GetCroppedWidth() * whichPickup,0 };
	PickupComponent* pPickupComponent{ new PickupComponent(1000 * (whichPickup + 1) , pPlayer) };
	LifeTimeComponent* pMortalComp{ new LifeTimeComponent(0.f, false) };

	GetTransform()->SetPosition(pos);
	pSpriteComponent->SetLocalSpriteArea(srcPos, GetTransform()->GetPosition());
	pSpriteComponent->RescaleSprite(Float2{ 2,2 });

	AddComponent(pSpriteComponent);
	AddComponent(pMortalComp);
	AddComponent(pPickupComponent);
}

void HiveMind::GameObject::SetTexture(const std::string& fileName, const std::string& texName)
{

	/*if (!temp)
	{
		AddComponent(temp);
	}*/
	GetComponent<RenderComponent>()->SetTexture(fileName,texName);

}

void HiveMind::GameObject::SetPosition(const FPoint2& pos)
{
	m_pTransform->SetPosition(pos.x, pos.y, 0.0f);
}

void HiveMind::GameObject::AddComponent(BaseComponent* pComponent)
{
	if (typeid(pComponent) == typeid(TransformComponent) && HasComponent<TransformComponent>())
	{
		throw("Only one TransformComponent is allowed per GameObject");
	}
	//if(!pComponent->IsInitialized())
	//	pComponent->Initialize();
	m_pComponents.push_back(pComponent);
	pComponent->m_pGameObject = this;
}

HiveMind::TransformComponent* HiveMind::GameObject::GetTransform() const
{
	return m_pTransform;
}





