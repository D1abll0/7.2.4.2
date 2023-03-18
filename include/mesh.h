#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <string>
#include <vector>
using namespace std;
using namespace glm;

#define NUM_BONES_PER_VERTEX 4
#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define INVALID_MATERIAL 0xFFFFFFFF
#define MAX_BONE_INFLUENCE 4

struct Vertex
{
    vec3 Position;
    vec3 Normal;
    vec2 TexCoords;
    vec3 Tangent;
    vec3 Bitangent;
    
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	float m_Weights[MAX_BONE_INFLUENCE];    
};

struct Texture
{
    unsigned int id;
    string type;
    string path;
};

/*struct BoneInfo
{
	int id;
	mat4 offset;	
};*/

class Mesh
{
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    unsigned int VAO;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

    void Draw(Shader& shader);

private:
    unsigned int VBO, EBO;

    void setupMesh();
};
#endif