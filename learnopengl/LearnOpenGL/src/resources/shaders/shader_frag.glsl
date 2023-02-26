#version 330 core
in vec3 Normal;
in vec3 FragPos;
in vec2 uv;
out vec4 FragColor;

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
    float distance = length(FragPos - light.position);
    float attenuation = 1.0/(light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = texture(material.diffuse, uv).rgb * light.ambient;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    //vec3 lightDir = normalize(-light.direction);

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = texture(material.diffuse, uv).rgb * diff * light.diffuse;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(reflectDir, viewDir), 0), material.shininess);
    vec3 specular = texture(material.specular, uv).rgb * spec * light.specular;

    vec3 result = attenuation * (ambient + intensity * (diffuse + specular));
    FragColor = vec4(result, 1.0);
}