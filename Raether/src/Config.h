#pragma once

// For Enabling Camera Specs
#define camDetails 0

// Utility Macros
#define PI 3.14159265358979323

#define ColorBlack glm::dvec3(0.0, 0.0, 0.0)
#define ColorWhite glm::dvec3(1.0)
#define ColorBlue glm::dvec3(0.5294, 0.8078, 0.9215) // glm::dvec3(0.5, 0.7, 1.0)

#define camNearDist 0.001
#define camFarDist 1000.0

#define rayNearDist 0.001
#define rayFarDist Infinity

#define Infinity std::numeric_limits<double>::infinity()

// Camera Related Macros
#define minFov 5.0
#define maxFov 180.0
#define camMotionSensitivity 0.01
#define camMovementSpeed 0.3
#define JitterStrength 0.0035

// Multithreading Related Macros
#define MT 0 // Enables Multithreading

// Bvh Build Related Macros
#define RBVH 0 // Enable Random Axis BVH Split (The Default is Longest Axis Split)

// Scene Related Macros
#define SCENE18 // Enable a Particular Scene
#define NumofProcSpheres 40 // Represents Total Number of Procedural Spheres

// Logging Related Macros
#define PrintPerFrameTime false // Enable Per Frame Info Logging
#define PrintFinalRenderTime true // Enable Final Frame Info Logging (Prints Avg of all collected data points)