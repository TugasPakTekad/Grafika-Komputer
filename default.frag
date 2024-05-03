#version 330 core

out vec4 fragColor;

in vec3 color;
in vec2 texturePosition;

uniform sampler2D tex0;

void main()
{
	//fragColor = vec4(color, 1.0f);
	fragColor = texture(tex0, texturePosition);
}