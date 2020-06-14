#include "HiveMindPCH.h"
#include "Components.h"
#include "Physics.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Primitives.h"
#include "LevelManager.h"

HiveMind::CharacterColliderComponent::CharacterColliderComponent()
	:ColliderComponent()
{
}

HiveMind::CharacterColliderComponent::CharacterColliderComponent(const FPoint2& pos, const Float2& size)
	:ColliderComponent(pos,size)
{
}

HiveMind::CharacterColliderComponent::~CharacterColliderComponent()
{
}

void HiveMind::CharacterColliderComponent::RayHitObstacle(const GameObject* other, const FPoint2& objPos)
{
	//CHECK LEFT
	m_Size = { m_pGameObject->GetComponent<SpriteComponent>()->GetDest().w,  m_pGameObject->GetComponent<SpriteComponent>()->GetDest().h };
	m_Pos = { m_pGameObject->GetComponent<SpriteComponent>()->GetDest().x,  m_pGameObject->GetComponent<SpriteComponent>()->GetDest().y };

	FPoint2 rayOrigin{ m_Pos.x + m_Size.x / 2.f,m_Pos.y + m_Size.y/ 2.f };
	FVector2 rayDir{ -(m_Size.x / 2.f + 1),0 };
	FPoint2 rayEnd{ rayOrigin + rayDir };
	if (!other->HasComponent<BlockColliderComponent>())
		return;
	BlockColliderComponent* temp{ other->GetComponent<BlockColliderComponent>() };
	if (temp->IsCollidingHorizontally(rayEnd))
		m_ColliderBox.left = true;

	///////////////////////
	g_Left = Line{ int(rayOrigin.x), int(rayOrigin.y), int(rayEnd.x), int(rayEnd.y) };

	//CHECK RIGHT

	rayDir= FVector2((m_Size.x / 2.f + 1),0 );
	rayEnd = rayOrigin + rayDir;
	if (temp->IsCollidingHorizontally(rayEnd))
		m_ColliderBox.right = true;
	///////////////////
	g_Right = Line{ int(rayOrigin.x), int(rayOrigin.y), int(rayEnd.x), int(rayEnd.y) };



	////CHECK UP NOT NECESSARY (CAN JUMP THROUGH) But necessary tro fix jump
	rayOrigin = FPoint2{ m_Pos.x + m_Size.x / 2.f,m_Pos.y + m_Size.y-1 }; // need to cover move collision area
	rayDir = FVector2( 0, -(4));
	rayEnd = rayOrigin + rayDir;
	if (temp->IsCollidingVertically(rayEnd))
		m_ColliderBox.top = true;
	g_Up = Line{ int(rayOrigin.x), int(rayOrigin.y), int(rayEnd.x), int(rayEnd.y) };

	//CHECK BOTTOM
	rayOrigin = FPoint2{ m_Pos.x + m_Size.x / 2.f,m_Pos.y + m_Size.y / 2.f };
	rayDir= FVector2( 0,+(m_Size.y / 2.f + 1) );
	rayEnd = rayOrigin + rayDir;


	//REVISE THIS SPAGHETTI
	if (temp->IsCollidingVertically(rayEnd))
	{
		m_ColliderBox.bottom = true;
		if (!m_ColliderBox.top) //if theres no block colliding above then that means char wont be bugged in block
		{

			if (GetGameObject()->HasComponent<ActorComponent>())
			{
				
				m_pGameObject->GetTransform()->SetPosition(objPos.x, temp->GetTransform()->GetPosition().y - 32, 0);
				
			}
		}
	}

	//////////////////
	g_Down = Line{ int(rayOrigin.x), int(rayOrigin.y), int(rayEnd.x), int(rayEnd.y) };



	//CHECK LEFTFOOT
	 rayOrigin = FPoint2{ m_Pos.x  ,m_Pos.y + m_Size.y / 2.f };
	 rayDir = FVector2{ 0,(m_Size.y / 2.f + 1) };
	 rayEnd = FPoint2{ rayOrigin + rayDir };
	if (!other->HasComponent<BlockColliderComponent>())
		return;
	if (temp->IsCollidingHorizontally(rayEnd))
		m_ColliderBox.leftFoot = true;
	///////////////////////
	g_LeftFoot = Line{ int(rayOrigin.x), int(rayOrigin.y), int(rayEnd.x), int(rayEnd.y) };

	//CHECK RIGHTFOOT
	 rayOrigin = FPoint2{ m_Pos.x + m_Size.x ,m_Pos.y + m_Size.x / 2.f };
	 rayDir = FVector2{ 0,(m_Size.x / 2.f + 1) };
	 rayEnd = FPoint2{ rayOrigin + rayDir };
	if (!other->HasComponent<BlockColliderComponent>())
		return;
	if (temp->IsCollidingHorizontally(rayEnd))
		m_ColliderBox.rightFoot = true;
	///////////////////////
	g_RightFoot = Line{ int(rayOrigin.x), int(rayOrigin.y), int(rayEnd.x), int(rayEnd.y) };

}

bool HiveMind::CharacterColliderComponent::IsCollidingVertically(const FPoint2& Point)
{
	return false;
}

bool HiveMind::CharacterColliderComponent::IsCollidingHorizontally(const FPoint2& Point)
{
	return false;
}


ColliderBox HiveMind::CharacterColliderComponent::GetCollisionResults() const
{
	return m_ColliderBox;
}

void HiveMind::CharacterColliderComponent::ResetCollision()
{
	m_ColliderBox = ColliderBox{};
}



void HiveMind::CharacterColliderComponent::Update(const float& deltaTime)
{
	std::vector<GameObject*> pTemp = SceneManager::GetInstance().GetActiveScene()->GetObjects();
	for (size_t i{ 0 }; i < pTemp.size(); i++)
	{
		if(pTemp[i]->HasComponent<BlockColliderComponent>())
			RayHitObstacle(pTemp[i], GetTransform()->GetPosition());
	}
}

void HiveMind::CharacterColliderComponent::Render() const
{
	SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &m_pGameObject->GetComponent<SpriteComponent>()->GetDest());
	SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), g_Left.x1, g_Left.y1, g_Left.x2, g_Left.y2);
	SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), g_Right.x1, g_Right.y1, g_Right.x2, g_Right.y2);
	SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), g_Down.x1, g_Down.y1, g_Down.x2, g_Down.y2);
	SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), g_Up.x1, g_Up.y1, g_Up.x2, g_Up.y2);

	SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), g_LeftFoot.x1, g_LeftFoot.y1, g_LeftFoot.x2, g_LeftFoot.y2);
	SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), g_RightFoot.x1, g_RightFoot.y1, g_RightFoot.x2, g_RightFoot.y2);

}
