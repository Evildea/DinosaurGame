#include "Entity.h"

Entity::Entity()
{
	m_health = 100;
	m_thirst = 100;
	m_hunger = 100;
	m_tiredness = 100;

	m_depth = 0.35;
	m_tail = new Tail;
	m_head = new Head;
	m_legs = new Legs;
	m_target = { 0,0 };
	m_behaviourManager->setAI(PredatorControlledAI, this);
	m_legs->addEntity(this);
}

Entity::~Entity()
{
	delete m_tail;
	delete m_head;
	delete m_legs;
}

void Entity::customUpdate(float deltaTime)
{
	// Sets the Previous Position to the current position.
	m_previousPosition = m_position;

	// Automatically increase the dinosaur's hunger and thirst overtime.
	m_hunger -= ((1 + (rand() % 1)) * deltaTime);
	m_thirst -= ((.5 + (rand() % 2)) * deltaTime);

	// If the dinosaur's hunger or thirst is too low start inflicting damage to the dinosaur.
	if (m_hunger <= 1 || m_thirst <= 1)
	{
		m_hunger = 1;
		m_health -= (2 * deltaTime);
	}

	// Update the dinosaur's position with it's velocity.
	m_position = m_position + m_velocity * deltaTime;

	// Update the dinosaur's rotation based on it's previous position.
	V2<float> dif = m_position - m_previousPosition;
	if (dif.getMagnitude() > 0.05)
		m_transform.rotate(m_previousPosition, m_position, false);
	m_previousDif = dif;

	// Update the head and tail.
	m_tail->update(m_position);
	m_head->update(m_transform + m_position, m_transform.getRadians(), m_target, deltaTime);

	// Update the legs.
	m_legs->update(m_transform + m_position, m_transform.getRadians());

}

void Entity::customDraw(aie::Renderer2D * a_renderer)
{
	// Draw the behavioural target (if in debug mode)
	m_behaviourManager->draw(a_renderer);

	// Draw the head, tail and legs.
	m_legs->draw(a_renderer, m_transform.yAxis);
	m_tail->draw(a_renderer, m_transform.yAxis);
	m_head->draw(a_renderer, m_transform.yAxis);

	// Draw the progress bars if selected.
	if (m_selectedStatus)
	{
		// Draw the health bar.
		DrawBar(a_renderer, 50, m_health, 0, 1, 0);

		// Draw the thirst bar.
		DrawBar(a_renderer, 65, m_thirst, 0, 0, 1);

		// Draw the hunger bar.
		DrawBar(a_renderer, 80, m_hunger, 1, 0, 0);

		// Draw the tiredness bar.
		DrawBar(a_renderer, 95, m_tiredness, .5, .5, .5);
	}

}

void Entity::setSelectedStatus(bool a_selectedStatus)
{
	m_selectedStatus = a_selectedStatus;

	// If the object is selected change it's behaviour type to user controlled.
	if (m_selectedStatus == true)
		m_behaviourManager->setAI(UserControlledAI, this);
	else
		m_behaviourManager->setAI(PredatorControlledAI, this);
}

void Entity::setTailColour(float r, float g, float b)
{
	m_tail->setColour(r, g, b);
}

void Entity::setTailSpotColour(float r, float g, float b)
{
	m_tail->setTailSpotColour(r, g, b);
}

bool Entity::getSelectedStatus()
{
	return m_selectedStatus;
}

Head * Entity::getHead()
{
	return m_head;
}

Legs * Entity::getLegs()
{
	return m_legs;
}

float Entity::getVelocityLength()
{
	return m_velocity.getMagnitude();
}

void Entity::DrawBar(aie::Renderer2D* a_renderer, int a_yOffset, int a_valueToDraw, float r, float g, float b)
{
	int xPos = m_position.x;
	int yPos = m_position.y;
	int value = a_valueToDraw < 5 ? 5 : a_valueToDraw;

	// Draw the black background of the bar.
	a_renderer->setRenderColour(0, 0, 0);
	a_renderer->drawBox(xPos, yPos - a_yOffset, 100, 10, 0, 0);

	// Draw the health on the bar.
	a_renderer->setRenderColour(r, g, b);
	a_renderer->drawBox(xPos - ((100 - value) * .5f), yPos - a_yOffset, value, 6, 0, 0);
}