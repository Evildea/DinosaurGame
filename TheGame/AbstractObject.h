#pragma once
#include "BehaviourManager.h"
#include "ResourceManager.h"
#include "Renderer2D.h"
#include "Texture.h"
#include "CRT.h"
#include "M3.h"
#include "V2.h"

class ObjectManager;

class AbstractObject
{
protected:
	ObjectManager*		m_objectManager;					// This represents the ObjectManager and allows the object to access it.
	BehaviourManager*	m_behaviourManager;					// This represents the BehaviourManager and allows the object to access it.
	aie::Texture*		m_sprite;							// This represents the sprite of the object.
	aie::Texture*		m_scarSprite;						// This represents the sprite of the object when damaged.
	M3<float>			m_transform;						// This represents the rotation of the object.
	V2<float>			m_position, m_velocity, m_target;	// This represents the position, velocity and eyesight target of the object.
	bool				m_selectedStatus;					// This represents whether the object has been selected by the mouse.
	float				m_depth;							// This represents the depth to draw the object at.
	float				m_health;							// This represents the health of the object.

public:
	AbstractObject();
	~AbstractObject();

	virtual void customUpdate(float deltatime) = 0;
	virtual void customDraw(aie::Renderer2D* a_renderer) = 0;

	void update(float deltaTime, V2<int> a_cameraPosition);
	void draw(aie::Renderer2D* a_renderer);

	void addSprite(ResourceManager* a_resourceManager, char a_textureGameName[]);
	void addScarSprite(ResourceManager* a_resourceManager, char a_textureGameName[]);

	void setPosition(float x, float y);
	void setVelocity(float x, float y);
	void setTarget(V2<float> a_target);

	V2<float> getPosition();
	M3<float> getTransform();
	V2<float> getVelocity();
	float getX();
	float getY();
	float getT();

	virtual int getThirst() { return 0; };
	virtual int getHealth() { return 0; };
	virtual int getHunger() { return 0; };
	virtual BehaviourType getBehaviourType() { return HerbiControlledAI; };
	virtual void setHealth(int a_health) {};
	virtual void setThirst(int a_thirst) {};
	virtual void setHunger(int a_hunger) {};

	void setObjectManager(ObjectManager* a_objectManager);
	ObjectManager* getObjectManager();

};
