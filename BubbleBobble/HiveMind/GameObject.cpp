#include "HiveMindPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Components.h"
#include "RenderComponent.h"
#include "SoundManager.h"
HiveMind::GameObject::GameObject()
	:m_pTransform{new TransformComponent()}
	, m_IsActive{ true }
{
	AddComponent(m_pTransform);
}

HiveMind::GameObject::~GameObject()
{
	for (BaseComponent* pComponent: m_pComponents)
	{
		if (pComponent)
		{
		delete pComponent;
		pComponent = nullptr;
		}
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

void HiveMind::GameObject::CreateCollision(FPoint2& pos, Float2& size)
{
	BlockColliderComponent* pColliderComp{ new BlockColliderComponent(pos,size) };
	GetTransform()->SetPosition(FPoint3{ pos,0 });
	AddComponent(pColliderComp);
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

void HiveMind::GameObject::CreateButton(const FPoint3& pos, const Int2& size, const std::string& text, const std::string& linkedScene, HiveMind::Font* pFont)
{
	GetTransform()->SetPosition(pos);
	TextComponent* pTextComponent{new TextComponent(text,pFont)};
	ButtonComponent* pButtonComponent{ new ButtonComponent(size, linkedScene) };
	AddComponent(pTextComponent);
	AddComponent(pButtonComponent);


}

void HiveMind::GameObject::CreateButton(const FPoint3& pos, const Int2& size, const std::string& text, const ButtonComponent::Action action, HiveMind::Font* pFont)
{
	GetTransform()->SetPosition(pos);
	TextComponent* pTextComponent{ new TextComponent(text,pFont) };
	ButtonComponent* pButtonComponent{ new ButtonComponent(size, action) };
	AddComponent(pTextComponent);
	AddComponent(pButtonComponent);


}

void HiveMind::GameObject::CreateButton(const FPoint3& pos, const Int2& size, const std::string& text, const ButtonComponent::Action action, const std::string& linkedScene, HiveMind::Font* pFont)
{
	GetTransform()->SetPosition(pos);
	TextComponent* pTextComponent{ new TextComponent(text,pFont) };
	ButtonComponent* pButtonComponent{ new ButtonComponent(size, action,linkedScene) };
	AddComponent(pTextComponent);
	AddComponent(pButtonComponent);
}

//------------PROJECTILES-----------
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

void HiveMind::GameObject::CreateFireBall(const bool isLookingLeft, const FPoint3& pos, const FPoint2& velocity, const float lifeTime)
{
	SpriteComponent* pSpriteComponent{ new SpriteComponent("../Data/FireBallSprite.png","FireBall", SpriteConfig{ 4, 2 }, true) };
	ProjectileComponent* pProjectileComp{ new ProjectileComponent(isLookingLeft,pos,velocity, ProjectileComponent::ProjectileState::FIREBALL) };
	LifeTimeComponent* pMortalComp{ new LifeTimeComponent(lifeTime, true) };
	GetTransform()->SetPosition(pos);
	pSpriteComponent->SetCroppingDimensions();
	FPoint2 srcPos{ 0, 0 };
	if (isLookingLeft)
	{
		pSpriteComponent->SetRow(1);
	}

	pSpriteComponent->SetLocalSpriteArea(srcPos, pos);
	AddComponent(pSpriteComponent);
	AddComponent(pProjectileComp);
	AddComponent(pMortalComp);
	GetTransform()->SetPosition(pos);
}
//END
bool HiveMind::GameObject::IsActive() const
{
	return m_IsActive;
}

bool HiveMind::GameObject::SetActive(const bool active)
{
	return m_IsActive = active;
}

void HiveMind::GameObject::CreatePlayer(const SpriteConfig& spriteConfig)
{
	SpriteComponent* pSpriteComponent{ new SpriteComponent("../Data/CharacterSprites.png", "Characters", spriteConfig, false) };
	pSpriteComponent->SetCroppingDimensions();
	FPoint2 srcPos{ 0,0 };
	FPoint3 pos{ 50,200,0 };
	GetTransform()->SetPosition(pos);
	pSpriteComponent->SetLocalSpriteArea(srcPos, pos);
	ActorComponent* pActorComponent{ new ActorComponent(true,false,false, 100) };
	HealthComponent* pHealthComponent{ new HealthComponent(3) };
	ScoreCounterComponent* pScoreCounterComp{ new ScoreCounterComponent(ResourceManager::GetInstance().LoadFont("pixelated.ttf",30),0,FPoint2{40,2}) };
	HealthCounterComponent* pHealthCounterComp{ new HealthCounterComponent(ResourceManager::GetInstance().LoadFont("pixelated.ttf",30),pHealthComponent->GetHealth(),FPoint2{250,2}) };
	ControllerComponent* pControllerComp{ new ControllerComponent(true) };
	SoundComponent* pSoundComp{ new SoundComponent() };

	pActorComponent->AddObserver(new HealthObserver());
	pActorComponent->AddObserver(new DeathObserver());

	pSoundComp->AddSound("Shoot", "../Data/Shoot.wav", false);

	AddComponent(pSoundComp);
	AddComponent(pScoreCounterComp);
	AddComponent(pHealthCounterComp);
	AddComponent(pHealthComponent);
	AddComponent(pControllerComp);


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
	ActorComponent* pActorComponent{ new ActorComponent(false,true,false,50) }; // ask why not NPC component
	HealthComponent* pHealthComponent{ new HealthComponent() };

	AddComponent(pHealthComponent);
	AddComponent(pActorComponent);
	AddComponent(pSpriteComponent);
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
	ActorComponent* pActorComponent{ new ActorComponent(false,true,false,50) };
	HealthComponent* pHealthComponent{ new HealthComponent() };

	AddComponent(pHealthComponent);
	AddComponent(pActorComponent);
	AddComponent(pSpriteComponent);
	AddComponent(new CharacterColliderComponent());
	pSpriteComponent->RescaleSprite(Float2(2, 2));
	SetPosition(dstPos);

}

void HiveMind::GameObject::CreateZenChan(FPoint3& pos)
{
	SpriteComponent* pSpriteComponent{ new SpriteComponent("../Data/ZenChan.png", "ZenChan", SpriteConfig{8,5}, false) };
	FPoint2 srcPos{ 0,0 };
	pos.y *= 2;
	pSpriteComponent->SetCroppingDimensions();
	FPoint3 dstPos{ pSpriteComponent->GetCroppedWidth() * pos.x, pSpriteComponent->GetCroppedHeight() * pos.y,0 };
	GetTransform()->SetPosition(pos);
	pSpriteComponent->SetLocalSpriteArea(srcPos, pos);
	ActorComponent* pActorComponent{ new ActorComponent(false,false,true,50) };
	HealthComponent* pHealthComponent{ new HealthComponent() };

	AddComponent(pHealthComponent);
	AddComponent(pActorComponent);
	AddComponent(pSpriteComponent);
	AddComponent(new CharacterColliderComponent());
	pSpriteComponent->RescaleSprite(Float2(2, 2));
	SetPosition(dstPos);
}

void HiveMind::GameObject::CreateMaitaPlayer(FPoint3& pos)
{
	SpriteComponent* pSpriteComponent{ new SpriteComponent("../Data/Maita.png", "Maita", SpriteConfig{8,5}, false) };
	FPoint2 srcPos{ 0,0 };
	pos.y *= 2;
	pSpriteComponent->SetCroppingDimensions();
	FPoint3 dstPos{ pSpriteComponent->GetCroppedWidth() * pos.x, pSpriteComponent->GetCroppedHeight() * pos.y,0 };
	GetTransform()->SetPosition(pos);
	pSpriteComponent->SetLocalSpriteArea(srcPos, pos);
	ActorComponent* pActorComponent{ new ActorComponent(true,true,false,100) };
	HealthComponent* pHealthComponent{ new HealthComponent() };
	ControllerComponent* pControllerComp{ new ControllerComponent(false) };

	AddComponent(pHealthComponent);
	AddComponent(pControllerComp);

	AddComponent(pActorComponent);
	AddComponent(pSpriteComponent);
	AddComponent(new CharacterColliderComponent());
	pSpriteComponent->RescaleSprite(Float2(2, 2));
	SetPosition(dstPos);
}



void HiveMind::GameObject::CreateScorePickup(const int& whichPickup, const FPoint3& pos, std::vector<GameObject*> pPlayerVec)
{
	SpriteComponent* pSpriteComponent{ new SpriteComponent("../Data/ScorePickups.png", "ScorePickups", SpriteConfig{2,1}, false) };
	pSpriteComponent->SetCroppingDimensions();
	FPoint2 srcPos{ pSpriteComponent->GetCroppedWidth() * whichPickup,0 };
	PickupComponent* pPickupComponent{new PickupComponent(100*(whichPickup+1),pPlayerVec)};
	LifeTimeComponent* pMortalComp{ new LifeTimeComponent(0.f, false) };
	SoundComponent* pSoundComp{ new SoundComponent() };
	pSoundComp->AddSound("Pickup", "../Data/Pickup.wav", false);

	GetTransform()->SetPosition(pos);
	pSpriteComponent->SetLocalSpriteArea(srcPos, GetTransform()->GetPosition());
	pSpriteComponent->RescaleSprite(Float2{ 2,2 });
	AddComponent(pSoundComp);
	AddComponent(pSpriteComponent);
	AddComponent(pMortalComp);
	AddComponent(pPickupComponent);

}

void HiveMind::GameObject::CreateScorePickup(const int& whichPickup, const FPoint3& pos, GameObject* pPlayer)
{
	SpriteComponent* pSpriteComponent{ new SpriteComponent("../Data/ScorePickups.png", "ScorePickups", SpriteConfig{2,1}, false) };
	pSpriteComponent->SetCroppingDimensions();
	FPoint2 srcPos{ pSpriteComponent->GetCroppedWidth() * whichPickup,0 };
	PickupComponent* pPickupComponent{ new PickupComponent(100 * (whichPickup + 1) , pPlayer) };
	LifeTimeComponent* pMortalComp{ new LifeTimeComponent(0.f, false) };
	SoundComponent* pSoundComp{ new SoundComponent() };
	pSoundComp->AddSound("Pickup", "../Data/Pickup.wav", false);

	GetTransform()->SetPosition(pos);
	pSpriteComponent->SetLocalSpriteArea(srcPos, GetTransform()->GetPosition());
	pSpriteComponent->RescaleSprite(Float2{ 2,2 });

	AddComponent(pSoundComp);
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





