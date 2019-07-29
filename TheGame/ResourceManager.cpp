#include "ResourceManager.h"



ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	for (resource* i : m_textureList)
		delete i;
}

void ResourceManager::addTexture(char m_textureFilePath[], char m_textureGameName[])
{
	if (strlen(m_textureGameName) < 150) {
		if (strlen(m_textureFilePath) != 0 && strlen(m_textureGameName) != 0)
		{
			m_textureList.push_back(DBG_NEW resource);
			for (int i = 0; i < strlen(m_textureGameName)+1; i++)
				m_textureList.back()->m_textureGameName[i] = m_textureGameName[i];
			m_textureList.back()->m_texturePath = DBG_NEW aie::Texture(m_textureFilePath);
		}
		else
			assert(false && "Either the m_textureFilePath or m_textureGameName is empty.");
	}
	else
		assert(false && "The m_textureGameName is too long. It must be less than 150 characters");
	
}

aie::Texture * ResourceManager::getTexture(char m_textureGameName[])
{
	aie::Texture* t = nullptr;
	bool found = false;

	if (strlen(m_textureGameName) < 150) {
		for (resource* i : m_textureList)
		{
			for (int j = 0; j < strlen(i->m_textureGameName) + 1; j++)
			{
				found = false;
				if (i->m_textureGameName[j] == m_textureGameName[j])
					found = true;
				else
					break;
			}
			if (found == true)
			{
				t = i->m_texturePath;
				break;
			}
		}
		return t;
	}
	else
		assert(false && "The m_textureGameName is too long. It must be less than 150 characters");
}
