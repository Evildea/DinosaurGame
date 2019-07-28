#pragma once

// This turns on debug mode which visualises any hidden objects and their links to the viewer.
// It is only used for fixing errors.
const bool g_DEBUGMODE = false;

// This determins the map width and height. 1 Unit is equal to 100 pixels.
const int g_MAPWIDTH = 25; 
const int g_MAPHEIGHT = 25;
const int g_TREEDENSITY = 70;		// Must be between 0 - 1000.
const int g_ROCKDENSITY = 80;		// Must be between 0 - 1000.
const int g_WATERDENSITY = 30;		// Must be between 0 - 1000.

const int g_PREDATORCOUNT = 4;		// Real number of predators. Must be more than 1.
const int g_HERBICOUNT = 10;		// Real number of herbivores. Must be more than 1.

// This determines the speed at which the dinosaur can run.
const int m_DINOSAURSPEED = 200;
const int m_DINOSAURSLOWINGRADIUS = 250;

const int m_HERBIVIEWDISTANCE = 300;

// This determines the length of the dinosaurs tails.
// A number less than 10 will break the game!
const int m_TAILLENGTH = 60;