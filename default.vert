#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 translation;

void main()
{
   gl_Position = projection * view * model * vec4(position + translation, 1.0);
   color = aColor;
}