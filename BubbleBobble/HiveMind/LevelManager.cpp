#include "HiveMindPCH.h"
#include "LevelManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include <fstream>
#include <regex>

HiveMind::LevelManager::~LevelManager()
{
}

void HiveMind::LevelManager::AddLevel(const std::wstring& pathName, Scene* scene)
{
	//Don't want to parse the next level, always want the next level to be ready for whatever reason
	Scene* currScene = SceneManager::GetInstance().GetActiveScene();
	int maxLevelsLoaded{ 2 };
	if (m_pLevelBlocks.size() == maxLevelsLoaded)
	{
		m_pLevelBlocks.erase(m_pLevelBlocks.begin());
		ParseLevel(pathName);
	}
	else
	{
		ParseLevel(pathName);
	}
	for(size_t i = 0; m_pLevelBlocks.at(m_LatestLevel).size() > i; i++)
		currScene->Add(m_pLevelBlocks.at(m_LatestLevel)[i]);
	//ADD EVERY BLOCVK OF THE LEVELID IN MAP
}


std::vector<HiveMind::GameObject*> HiveMind::LevelManager::GetCurrentLevel() const
{
	int maxLevelsLoaded{ 2 };
	if(maxLevelsLoaded == m_pLevelBlocks.size())
		return m_pLevelBlocks.at(m_LatestLevel - 1); //only return this if there are atleast 2 levels, out of bounds otherwise
	return m_pLevelBlocks.at(m_LatestLevel);
}


void HiveMind::LevelManager::ParseLevel(const std::wstring& pathName)
{
	int blockCounter{ 0 };
	std::ifstream inputFile{};
	inputFile.open(pathName, std::ios::in);
	if (!inputFile)
		throw std::runtime_error("File not found, possible fix: check pathName");
	int currRow{ 0 };
	int currCol{ 0 };


	std::string currLine;

	while (std::getline(inputFile, currLine))
	{
		std::regex levelNameReg{ "Level:\\d*" };
		std::regex levelEndReg{ "END" };
		if(std::regex_search(currLine, levelNameReg))
		{
			//FIND WHAT LEVEL WERE AT
			char toFind{ ':' };
			m_LatestLevel = std::stoi(currLine.substr(currLine.find(toFind)+1));
		}

		else if (std::regex_search(currLine, levelEndReg))
		{
			return;
		}

		else {

			for (const char& block : currLine)
			{
				if (block == '0')
					currCol++;
				else if (!std::isspace(block)&&!std::isalpha(block))
				{
					Float3 pos{ currCol, currRow,0 };
					int blockID{ block - '0' }; //to convert the number from ascii to actual numeral value
					m_pLevelBlocks[m_LatestLevel].push_back(new GameObject()); //Add id, pos to leveldata, each block is a gameobject with spriterendercomponent 
					//REWRITTEN IN MAP AFTER PREFABS WERE FORBIDDEN
					pos.y += 2;
					if(blockCounter < 32) //first 32 blocks of each level have no collision
						m_pLevelBlocks[m_LatestLevel].back()->CreateLevelBlockNoCollision(blockID, pos);
					else
						m_pLevelBlocks[m_LatestLevel].back()->CreateLevelBlock(blockID, pos);
					currCol++;
				}
				else if (block == 'M')
				{
					Float3 pos{ currCol, currRow,0 };
					m_pLevelBlocks[m_LatestLevel].push_back(new GameObject());
					m_pLevelBlocks[m_LatestLevel].back()->CreateMaita(pos);
					currCol++;
				}
				else if (block == '\r' || block == '\n')
				{
					currRow++;
					currCol = 0;
				}
				blockCounter++;
			}
			currRow++;
			currCol = 0;
		}
	}
}