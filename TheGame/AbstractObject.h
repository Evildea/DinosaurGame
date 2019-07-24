#pragma once
#include "BehaviourManager.h"
#include "ResourceManager.h"
#include "Renderer2D.h"
#include "Texture.h"
#include "M3.h"
#include "V2.h"

class ObjectManager;

class AbstractObject
{
protected:
	ObjectManager*				m_objectManager;
	BehaviourManager*			m_behaviourManager;
	aie::Texture*				m_sprite;
	M3<float>					m_transform;
	V2<float>					m_position;
	V2<float>					m_velocity;
	V2<float>					m_target;
	bool						m_selectedStatus;
	float						m_depth;

public:
	AbstractObject();
	~AbstractObject();

	virtual void customUpdate(float deltatime) = 0;
	virtual void customDraw(aie::Renderer2D* a_renderer) = 0;

	void update(float deltaTime, V2<int> a_cameraPosition);
	void draw(aie::Renderer2D* a_renderer);

	void addSprite(ResourceManager* a_resourceManager, char a_textureGameName[]);

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
	virtual void setHealth(int a_health) {};
	virtual void setThirst(int a_thirst) {};
	virtual void setHunger(int a_hunger) {};

	void setObjectManager(ObjectManager* a_objectManager);
	ObjectManager* getObjectManager();

};
