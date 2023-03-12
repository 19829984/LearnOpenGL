#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 uv;

struct Material{
    sampler2D texture_diffuse1;
};

uniform Material material;

void main(){
	FragColor = texture(material.texture_diffuse1, uv);
}
