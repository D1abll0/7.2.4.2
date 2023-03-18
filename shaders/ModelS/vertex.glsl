#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 tex;
layout (location = 3) in vec3 tang;
layout (location = 4) in vec3 bitang;
layout (location = 5) in ivec4 boneIds; 
layout (location = 6) in vec4 weights;
	
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float size;
uniform float uv;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
	
void main()
{
	gl_Position =  projection * view * model * vec4(pos*size, 1.0);
	TexCoords = tex * uv;
	FragPos = vec3(model * vec4(pos, 1.0));
	Normal = mat3(transpose(inverse(model))) * norm;  
}