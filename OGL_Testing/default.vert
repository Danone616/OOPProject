#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;

layout (location = 2) in vec3 aLight;

// Outputs the color for the Fragment Shader
out vec3 color;
out vec3 light;
out vec3 lightsource;
out vec3 shinecolor;

uniform mat4 camMatrix;
uniform mat4 objectMatrix;
uniform vec3 LightSource;
uniform mat4 orientation;
uniform vec3 Shinecolor;

void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix*objectMatrix*vec4(aPos,1.0);
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	shinecolor=Shinecolor;
	light = vec3(orientation*vec4(aLight,1.0));
	lightsource = vec3(LightSource[0]-objectMatrix[3][0],LightSource[1]-objectMatrix[3][1],LightSource[2]-objectMatrix[3][2]);
}