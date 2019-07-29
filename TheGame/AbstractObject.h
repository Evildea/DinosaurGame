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

	// These are custom update and draw functions.
	virtual void customUpdate(float deltatime) = 0;
	virtual void customDraw(aie::Renderer2D* a_renderer) = 0;

	// This function manages the objects rotation and calls upon its behaviour manager.
	void update(float deltaTime, V2<int> a_cameraPosition);

	// This function draws the object's body and bounding box if required.
	void draw(aie::Renderer2D* a_renderer);

	// These functions apply sprites to the object's body.
	void addSprite(ResourceManager* a_resourceManager, char a_spriteGameName[]);
	void addScarSprite(ResourceManager* a_resourceManager, char a_spriteGameName[]);

	// These functions set the position and velocity.
	void setPosition(float x, float y);
	void setVelocity(float x, float y);

	// This function sets the target of its eyeline.
	void setTarget(V2<float> a_target);

	// These functions return the object's position, transform and velocity.
	V2<float> getPosition();
	M3<float> getTransform();
	V2<float> getVelocity();
	float getX();
	float getY();
	float getT();

	// These functions return the object's vitals.
	virtual int getThirst() { return 0; };
	virtual int getHealth() { return 0; };
	virtual int getHunger() { return 0; };

	// These functions set the object's vitals.
	virtual void setHealth(int a_health) {};
	virtual void setThirst(int a_thirst) {};
	virtual void setHunger(int a_hunger) {};

	// This function returns the AI associated with the object.
	virtual BehaviourType getBehaviourType() { return HerbiControlledAI; };

	// These functions enable the object to access the objectManager and share it.
	void setObjectManager(ObjectManager* a_objectManager);
	ObjectManager* getObjectManager();

};
