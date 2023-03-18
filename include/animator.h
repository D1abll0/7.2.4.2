#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include "animation.h"
#include "bone.h"

using namespace std;
using namespace glm;

class Animator
{
public:
	Animator() = default;
	Animator(Animation* animation);

	void UpdateAnimation(float dt);

	void PlayAnimation(Animation* pAnimation);

	void CalculateBoneTransform(const AssimpNodeData* node, mat4 parentTransform);

	vector<mat4> GetFinalBoneMatrices();

private:
	vector<mat4> m_FinalBoneMatrices;
	Animation* m_CurrentAnimation;
	float m_CurrentTime;
	float m_DeltaTime;

};
#endif