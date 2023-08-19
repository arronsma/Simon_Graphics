#version 330 core
layout (location = 0) in vec3 aPos;

layout (location = 2) in vec2 inTexCoord;

out vec2 texCoord;

uniform mat2 transform;

void main () {
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1);
	texCoord = transform * inTexCoord;

}
