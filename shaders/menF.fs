#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture0;


void main()
{
  vec4 texel = texture(texture0, TexCoord);
  if(texel.a < 0.5)
    discard;
	FragColor = texel;
}
	