#pragma once
#include "Texture.h"
#include <vector>
#include <assert.h>
#include "CRT.h"

struct resource;

class ResourceManager
{
private:
	std::vector<resource*> m_spriteList; // This represents a list of sprites.

public:
	ResourceManager();
	~ResourceManager();

	// These functions add or get a sprite based on the sprite's name.
	void addSprite(char a_spriteFilePath[], char a_spriteGameName[]);
	aie::Texture* getSprite(char a_spriteGameName[]);

};

// This represents an individual resource that holds a sprite and its name.
struct resource
{
	aie::Texture*	m_spritePath;
	char			m_spriteGameName[150];
};

