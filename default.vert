#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 tex;
layout (location = 3) in vec3 normals;

out vec3 color;
out vec2 texturePosition;

out vec3 currentPos;
out vec3 normal;

out vec4 fragPosLightSpace;

uniform mat4 camMatrix;

uniform float scale;
uniform vec3 translation;
uniform mat4 rotation;

uniform mat4 lightProjection;

void main()
{
    currentPos = vec3(vec4(position, 1.0f));

    vec4 pos = vec4(position + position * scale, 1.0);
    pos = rotation * pos;
    pos = pos + vec4(translation, 0.0);

    fragPosLightSpace = lightProjection * pos;

    gl_Position = camMatrix * pos;
    color = aColor;
    texturePosition = tex;

    normal = normals;
}
