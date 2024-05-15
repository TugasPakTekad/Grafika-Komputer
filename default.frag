#version 330 core

out vec4 fragColor;

in vec3 color;
in vec2 texturePosition;

in vec3 currentPos;
in vec3 normal;

in vec4 fragPosLight;

uniform sampler2D tex0;
uniform sampler2D shadowMap;

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

	// Shadow value
	float shadow = 0.0f;
	// Sets lightCoords to cull space
	vec3 lightCoords = fragPosLight.xyz / fragPosLight.w;
	if(lightCoords.z <= 1.0f)
	{
		// Get from [-1, 1] range to [0, 1] range just like the shadow map
		lightCoords = (lightCoords + 1.0f) / 2.0f;
		float currentDepth = lightCoords.z;
		// Prevents shadow acne
		float bias = max(0.025f * (1.0f - dot(normal, lightDirection)), 0.0005f);

		// Smoothens out the shadows
		int sampleRadius = 2;
		vec2 pixelSize = 1.0 / textureSize(shadowMap, 0);
		for(int y = -sampleRadius; y <= sampleRadius; y++)
		{
		    for(int x = -sampleRadius; x <= sampleRadius; x++)
		    {
		        float closestDepth = texture(shadowMap, lightCoords.xy + vec2(x, y) * pixelSize).r;
				if (currentDepth > closestDepth + bias)
					shadow += 1.0f;     
		    }    
		}
		// Get average shadow
		shadow /= pow((sampleRadius * 2 + 1), 2);
	}

	fragColor = texture(tex0, texturePosition) * lightColor * (diffuse * (1.0f - shadow) + ambient + specular);
}