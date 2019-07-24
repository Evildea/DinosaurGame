#pragma once
#include <vector>
#include "Component.h"

class GameObject
{
protected:
	std::vector<ComponentPtr> m_components;

public:
	GameObject();
	~GameObject();

	void addComponent(const ComponentPtr& component)
	{
		m_components.push_back(component);
	};

	virtual void update(float deltaTime) {
		for (auto& component : m_components)
			component->update(this, deltaTime);
	}

	virtual void draw() {
		for (auto& component : m_components)
			component->draw(this);
	}
};

