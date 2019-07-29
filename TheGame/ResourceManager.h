#pragma once
#include "Texture.h"
#include <vector>
#include <assert.h>
#include "CRT.h"

struct resource;

class ResourceManager
{
private:
	std::vector<resource*> m_textureList;

public:
	ResourceManager();
	~ResourceManager();

	void addTexture(char m_textureFilePath[], char m_textureGameName[]);
	aie::Texture* getTexture(char m_textureGameName[]);

};

struct resource
{
	aie::Texture*	m_texturePath;
	char			m_textureGameName[150];
};

