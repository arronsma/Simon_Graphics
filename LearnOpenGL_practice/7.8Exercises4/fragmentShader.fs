#version 330 core
out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D texture2D_0;
uniform sampler2D texture2D_1;
uniform float mixFactor;
void main () {
	FragColor = mix(texture(texture2D_0, texCoord), texture(texture2D_1, texCoord), mixFactor);
}
