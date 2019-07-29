#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (resource* i : m_spriteList)
	{
		delete i->m_spritePath;
		delete i;
	}
}

void ResourceManager::addSprite(char a_spriteFilePath[], char a_spriteGameName[])
{
	if (strlen(a_spriteGameName) < 150) {
		if (strlen(a_spriteFilePath) != 0 && strlen(a_spriteGameName) != 0)
		{
			m_spriteList.push_back(DBG_NEW resource);
			for (int i = 0; i < strlen(a_spriteGameName)+1; i++)
				m_spriteList.back()->m_spriteGameName[i] = a_spriteGameName[i];
			m_spriteList.back()->m_spritePath = DBG_NEW aie::Texture(a_spriteFilePath);
		}
		else
			assert(false && "Either the m_spriteFilePath or m_spriteGameName is empty.");
	}
	else
		assert(false && "The m_spriteGameName is too long. It must be less than 150 characters");
	
}

aie::Texture * ResourceManager::getSprite(char a_spriteGameName[])
{
	aie::Texture* t = nullptr;
	bool found = false;

	if (strlen(a_spriteGameName) < 150) {
		for (resource* i : m_spriteList)
		{
			for (int j = 0; j < strlen(i->m_spriteGameName) + 1; j++)
			{
				found = false;
				if (i->m_spriteGameName[j] == a_spriteGameName[j])
					found = true;
				else
					break;
			}
			if (found == true)
			{
				t = i->m_spritePath;
				break;
			}
		}
		return t;
	}
	else
		assert(false && "The m_spriteGameName is too long. It must be less than 150 characters");
}
