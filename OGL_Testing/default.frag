#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;
in vec3 light;
in vec3 lightsource;
in vec3 shinecolor;

void main()
{
	vec3 lightcolor = {1,1,1};
	if(length(shinecolor)!=0)FragColor = vec4(color * dot(light,normalize(lightsource)) * lightcolor, 1.0f);
	else FragColor = vec4(lightcolor, 1.0f);
}