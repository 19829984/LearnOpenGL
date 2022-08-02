#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec3 v_pos;
in vec2 uv;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, uv), texture(texture2, vec2(uv.x, uv.y)), 0.2);
}