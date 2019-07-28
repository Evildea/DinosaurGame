#pragma once
#include "AbstractObject.h"
#include "Tail.h"
#include "Head.h"
#include "Legs.h"

class Entity : public AbstractObject
{
private:
	Tail*			m_tail;
	Head*			m_head;
	Legs*			m_legs;
	float			m_thirst, m_hunger, m_tiredness;
	V2<float>		m_previousPosition;
	V2<float>		m_previousDif;
	BehaviourType	m_dinosaurRole;

public:
	Entity();
	~Entity();

	virtual void customUpdate(float deltaTime);
	virtual void customDraw(aie::Renderer2D* a_renderer);

	void setSelectedStatus(bool a_selectedStatus);
	void setTailColour(float r, float g, float b);
	void setTailSpotColour(float r, float g, float b);
	void setSpeciesType(BehaviourType a_dinosaurRole);

	bool getSelectedStatus();
	Head* getHead();
	Legs* getLegs();

	virtual int getThirst() override { return m_thirst; };
	virtual int getHealth() override { return m_health; };
	virtual int getHunger() override { return m_hunger; };
	virtual BehaviourType getBehaviourType() override { return m_dinosaurRole; };
	virtual void setHealth(int a_health) override { m_health = (a_health < 100) ? a_health : 100; }
	virtual void setThirst(int a_thirst) override { m_thirst = a_thirst; }
	virtual void setHunger(int a_hunger) override { m_hunger = a_hunger; }
	float getVelocityLength();

	// This draws a health, thirst, hunger or tiredness bar to the screen.
	void DrawBar(aie::Renderer2D* a_renderer, int a_yOffset, int a_valueToDraw, float r, float g, float b);

};
