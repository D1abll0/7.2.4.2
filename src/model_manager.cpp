#include "../include/model_manager.h"
#include "../include/model_animation.h"

MDLManager::MDLManager(int type, const Shader& shader, const string& pathMDL, const string& pathANIM)
{
	MDL = new Model(pathMDL, 0);
	if(type == DYNAMIC)
	{
		animation = new Animation(pathANIM, MDL);
		animator = new Animator(animation);
	}
	
	this->type = (Type)type;
	this->shader = shader;
	
	
	T[0].x = -1; T[0].y = 0; T[0].z = 0; T[0].w = 0;
	T[1].x = 0; T[1].y = 0; T[1].z = 1; T[1].w = 0;
	T[2].x = 0; T[2].y = 1; T[2].z = 0; T[2].w = 0;
	T[3].x = 0; T[3].y = 0; T[3].z = 0; T[3].w = 1;	
}

void MDLManager::SetModelMat(mat4 mat)
{
	model = mat;
}

void MDLManager::SetViewMat(mat4 mat)
{
	view = mat;
}

void MDLManager::SetProjMat(mat4 mat)
{
	projection = mat;
}

mat4 MDLManager::GetModelMat()
{
	return model;
}

mat4 MDLManager::GetViewMat()
{
	return view;
}

mat4 MDLManager::GetProjMat()
{
	return projection;
}

void MDLManager::SetTexSize(float size, float uv)
{
	this->size = size;
	this->uv = uv;
}

void MDLManager::Scale(vec3 scale_)
{
	model = scale(model/*mat4(1.0)*/, scale_);
}

void MDLManager::Scale(float scale_)
{
	model = scale(model/*mat4(1.0)*/, vec3(scale_, scale_, scale_));
}

void MDLManager::Translate(vec3 pos)
{
	model = translate(model/*mat4(1.0)*/, pos);
}

void MDLManager::Translate(float pos)
{
	model = translate(model/*mat4(1.0)*/, vec3(pos, pos, pos));	
}

void MDLManager::Rotate(float angle, vec3 axes)
{
	model = rotate(model/*mat4(1.0)*/, radians(angle), axes);
}

void MDLManager::Rotate(float angle, float axes)
{
	model = rotate(model/*mat4(1.0)*/, radians(angle), vec3(axes, axes, axes));	
}

void MDLManager::Draw()
{
	shader.use();
	
	if(type == DYNAMIC)
	{
		auto bones = animator->GetFinalBoneMatrices();
		for(int i = 0; i < bones.size(); i++)
			shader.setMat4("finalBonesMatrices[" + to_string(i) + "]", bones[i]);		
	}

//model =  T * model * inverse(T);
//view = T * view;

	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	shader.setMat4("model", model);
	shader.setFloat("size", size);
	shader.setFloat("uv", uv);
	
	MDL->Draw(shader);
}

void MDLManager::Animate(float dt)
{
	animator->UpdateAnimation(dt);
}