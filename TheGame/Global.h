#pragma once

// This turns on debug mode which visualises any hidden objects and their links to the viewer.
// It is only used for fixing errors.
const bool g_DEBUGMODE = false;

// This determins the map width and height. 1 Unit is equal to 100 pixels.
const int g_MAPWIDTH = 20; 
const int g_MAPHEIGHT = 20;
const int g_TREEDENSITY = 50;		// Must be less than 100.
const int g_ROCKDENSITY = 15;		// Must be less than 30.
const int g_WATERDENSITY = 2;		// Must be less than 30.
const int g_PREDATORDENSITY = 1;	// Must be more than 1.
const int g_HERBIDENSITY = 2;		// Must be more than 1.

// This determines the speed at which the dinosaur can run.
const int m_DINOSAURSPEED = 200;
const int m_DINOSAURSLOWINGRADIUS = 250;

// This determines the length of the dinosaurs tails.
// A number less than 10 will break the game!
const int m_TAILLENGTH = 60;