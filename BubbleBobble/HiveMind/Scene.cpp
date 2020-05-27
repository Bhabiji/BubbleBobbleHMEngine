#include "HiveMindPCH.h"
#include "Scene.h"
#include <algorithm>
#include "Components.h"
using namespace HiveMind;

unsigned int Scene::m_IdCounter = 0;

std::string HiveMind::Scene::GetName() const
{
	return m_Name;
}

bool HiveMind::Scene::IsActive() const
{
	return m_IsActive;
}

void HiveMind::Scene::SetActive(const bool toggle)
{
	m_IsActive = toggle;
}

void HiveMind::Scene::Remove(GameObject* gameObject)
{
	int index{ 0 };
	bool deleteObject{ false };
	for (GameObject* object : m_Objects)
	{
		if (gameObject == object)
		{
			deleteObject = true;
			break;
		}
		index++;
	}
	if(deleteObject)
		m_Objects.erase(m_Objects.cbegin() + index);

}

void HiveMind::Scene::DeleteInactives()
{
	std::vector<GameObject*>::iterator it = m_Objects.begin();
	//delete all inactive objects
	while (it != m_Objects.end()) 
	{
		if (!(*it)->IsActive())
		{
			it = m_Objects.erase(it);
		}
		else
			++it;
	}
}

std::vector<GameObject*> HiveMind::Scene::GetObjects() const
{
	return m_Objects;
}

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(GameObject* object)
{
	object->Initialize();
	m_Objects.push_back(object);
}

void HiveMind::Scene::Initialize()
{
	for (auto& object : m_Objects)
	{
		object->Initialize();
	}
}

void HiveMind::Scene::BindEnemiesAndTarget()
{
	//SET THE TARGET TO PLAYER FOR ALL ENEMIES
	std::vector<GameObject*>::iterator it = m_Objects.begin();
	while (it != m_Objects.end())
	{
		if ((*it)->HasComponent<ActorComponent>() && !(*it)->GetComponent<ActorComponent>()->IsNPC())
			break;
		else
			it++;
	}
	if (it != m_Objects.end())
	{
		for (auto& object : m_Objects)
		{
			if (object->HasComponent<ActorComponent>() && object->GetComponent<ActorComponent>()->IsNPC())
				object->GetComponent<ActorComponent>()->SetTarget(*it);
		}
	}

}

void Scene::Update(const float& deltaTime)
{
	for(auto& object : m_Objects)
	{
		if(object)
			object->Update(deltaTime);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		if(object->HasComponent<ProjectileComponent>())
			object->Render();
		else
			object->Render();


	}
}

