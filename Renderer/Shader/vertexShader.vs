#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec2 TexCoord;

void main () {
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1);
	TexCoord = aTexCoord;
	gl_Position = projection * view * model * gl_Position;
}
