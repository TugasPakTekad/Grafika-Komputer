#version 330 core

out vec4 fragColor;

in vec3 color;
in vec2 texturePosition;

in vec3 currentPos;
in vec3 normal;

in vec4 fragPosLightSpace;

uniform sampler2D tex0;
uniform sampler2D shadowMap;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDirection)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

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

	float shadow = ShadowCalculation(fragPosLightSpace, normals, lightDirection);

	fragColor = texture(tex0, texturePosition) * lightColor *  (diffuse * (1.0f - shadow) + ambient + specular);
}
