#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;
in vec3 light;

void main()
{
	FragColor = vec4(color * light, 1.0f) ;
}