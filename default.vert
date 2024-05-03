#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 tex;

out vec3 color;
out vec2 texturePosition;

uniform mat4 camMatrix;

uniform float scale;
uniform vec3 translation;
uniform mat4 rotation;

void main()
{
   vec4 pos = vec4(position + position * scale, 1.0);
   pos = rotation * pos; // Apply rotation
   pos = pos + vec4(translation, 0.0); // Apply translation

   gl_Position = camMatrix * pos;
   color = aColor;
   texturePosition = tex;
}