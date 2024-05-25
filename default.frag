#version 330 core

out vec4 fragColor;

in vec3 color;
in vec2 texturePosition;

in vec3 currentPos;
in vec3 normal;

uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	float ambient = 0.2f;

	vec3 normals = normalize(normal);
	vec3 lightDirection = normalize(lightPos - currentPos);

	float diffuse = max(dot(normals, lightDirection), 0.0f);
	float specular = 0.0f;

	if(diffuse != 0.0f)
	{
		float specularLight = 0.5f;
		vec3 viewDirection = normalize(camPos - currentPos);
		vec3 reflectionDirection = reflect(-lightDirection, normals);

		vec3 halfLightVector = normalize(viewDirection + lightDirection);

		float specAmount = pow(max(dot(normals, halfLightVector), 0.0f), 8);
		float specular = specAmount * specularLight;
	}

	fragColor = texture(tex0, texturePosition) * lightColor *  (diffuse + ambient + specular);
}