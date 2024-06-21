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
    // pembagian perspektif
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Transform ke [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    
    // cek jika projCoords > 1.0 range
    if(projCoords.z > 1.0)
        return 0.0;

    float currentDepth = projCoords.z;

    // Bias untuk menghindari shadow acne
    float bias = max(0.005 * (1.0 - dot(normal, lightDirection)), 0.005);

    // PCF kernel size
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0; // Averaging the 3x3 kernel results

    // Clamp shadow ke [0,1]
    shadow = clamp(shadow, 0.0, 1.0);

    return shadow;
}


void main()
{
    float ambient = 0.4f;

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
