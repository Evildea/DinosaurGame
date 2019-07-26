#include "Bones.h"

Bones::Bones()
{
	m_depth = 0.5f;

	// Randomly rotate the bones so all bones don't face in the same direction.
	float random = (rand() % 31415926) / 10;
	m_transform.rotate(random);
}
