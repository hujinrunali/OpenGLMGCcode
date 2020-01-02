#version 330 core
layout(location = 0) in vec3 aFragPos;
layout(location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection*view*model*vec4(aFragPos,1.0f);
	TexCoords = aTexCoords;
}
