#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include "model_animation.h"
#include "animator.h"
#include "shader.h"
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm\gtx\dual_quaternion.hpp>

using namespace std;
using namespace glm;


enum Type {STATIC, DYNAMIC};

class MDLManager
{
	Model* MDL;
	Animation* animation;
	Animator* animator;
	Shader shader;
	
	mat4 model = mat4(1.0f);
	mat4 view = mat4(1.0f);
	mat4 projection = mat4(1.0f);
	
	Type type = STATIC;
	
	float size = 1.0;
	float uv = 1.0;
		
	mat4 T;

public:
	MDLManager(int type, const Shader& shader, const string& pathMDL, const string& pathANIM = "");
	
	void SetModelMat(mat4 mat);
	void SetViewMat(mat4 mat);
	void SetProjMat(mat4 mat);
	
	void SetTexSize(float size, float uv);
	
	mat4 GetModelMat();
	mat4 GetViewMat();
	mat4 GetProjMat();
	
	void Scale(vec3 scale_);
	void Scale(float scale_);
	void Translate(vec3 pos);
	void Translate(float pos);
	void Rotate(float angle, vec3 axes);
	void Rotate(float angle, float axes);
	
	void Animate(float dt);
	
	void Draw();
};
#endif