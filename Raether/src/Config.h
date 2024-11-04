#pragma once

// For Enabling Camera Specs
#define camDetails 0

// Utility Macros
#define black glm::vec3(0.0f, 0.0f, 0.0f)
#define white glm::vec3(1.0f)
#define blue glm::vec3(0.5294f, 0.8078f, 0.9215f) // glm::vec3(0.5f, 0.7f, 1.0f)

#define camNearDist 0.001
#define camFarDist 1000.0

#define rayNearDist 0.00001
#define rayFarDist 10000.0

// Camera Related Macros
#define minFov 5.f
#define maxFov 180.f
#define camMotionSensitivity 0.01f
#define camMovementSpeed 0.3f

// Multithreading Related Macros
#define MT 0 // Enables Multithreading

// Bvh Build Related Macros
#define RBVH 0 // Enable Random Axis BVH Split (The Default is Longest Axis Split)

// Scene Related Macros
#define SCENE10 // Enable a Particular Scene
#define NumofProcSpheres 40 // Represents Total Number of Procedural Spheres

// Logging Related Macros
#define PrintPerFrameTime false // Enable Per Frame Info Logging
#define PrintFinalRenderTime true // Enable Final Frame Info Logging (Prints Avg of all collected data points)