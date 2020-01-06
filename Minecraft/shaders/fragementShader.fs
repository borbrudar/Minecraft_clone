#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

// texture samplers
uniform sampler2D texture0;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	//ambient lighting
	vec3 lightColor = vec3(1.f,1.f,1.f);
	float ambientStrength = 0.15f;
	vec4 ambient = ambientStrength * vec4(lightColor,1.f);

	//diffuse lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);  

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	//specular lighting
	float specularStrength = 0.5;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

	FragColor = texture(texture0, TexCoord) * (ambient + diffuse + specular);
}