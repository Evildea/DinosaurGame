#pragma once

// This turns on debug mode which visualises any hidden objects and their links to the viewer.
// It should only be used for fixing errors.
const bool g_DEBUGMODE = false;

// This determins the map width and height. 1 Unit is equal to 100 pixels.
const int g_MAPWIDTH = 30;			// A number above 30 isn't recommended.
const int g_MAPHEIGHT = 30;			// A number above 30 isn't recommended.

// This determines the automatically generated content of the map.
const int g_TREEDENSITY = 70;		// Must be between 0 - 1000.
const int g_ROCKDENSITY = 80;		// Must be between 0 - 1000.
const int g_WATERDENSITY = 30;		// Must be between 0 - 1000.
const int g_PREDATORCOUNT = 4;		// Real number of predators. Must be more than 1.
const int g_HERBICOUNT = 20;		// Real number of herbivores. Must be more than 1.

// This determines the speed at which the dinosaur can run.
const int m_DINOSAURSPEED = 100;			// A number above 150 will cause the dinosaurs to start jumping rocks etc.
const int m_DINOSAURSLOWINGRADIUS = 100;	// A number above 100 can cause the dinosaurs to move excessively slow.

// This determines how far specific types of dinosaurs can see.
const int m_HERBIVIEWDISTANCE = 300;		// A number above 1000 isn't recommended.
const int m_PREDATORVIEWDISTANCE = 450;		// A number above 1000 isn't recommended.

// This determines how fast dinosaurs starve and die of thirst.
const float g_SUFFER = 0.5;					// A number above 1 isn't recommended as the dinosaurs will die too quickly.

// This determines the length of the dinosaurs tails.
// A number less than 10 will break the game!
const int m_TAILLENGTH = 60;				// A number above 100 isn't recommended as it drives up resources and doesn't provide any real benefit.