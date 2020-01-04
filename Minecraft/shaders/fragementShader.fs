#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture0;

void main()
{
	vec4 lightColor = vec4(1.0f,1.0f,1.0f,1.f);
	float ambientStrength = 0.75f;
	vec4 ambient = ambientStrength * lightColor;
	FragColor = texture(texture0, TexCoord) * ambient;
}