#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform mat4 camMatrix;

uniform float scale;
uniform vec3 translation;

void main()
{
   gl_Position = camMatrix * vec4(position + position * scale + translation, 1.0);
   color = aColor;
}