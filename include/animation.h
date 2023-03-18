#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include "bone.h"
#include <functional>
#include "animdata.h"
#include "model_animation.h"

using namespace std;
using namespace glm;

struct AssimpNodeData
{
	mat4 transformation;
	string name;
	int childrenCount;
	vector<AssimpNodeData> children;
};

class Animation
{
public:
	Animation() = default;

	Animation(const string& animationPath, class Model* model);

	~Animation(){}

	Bone* FindBone(const string& name);
	
	inline float GetTicksPerSecond() { return m_TicksPerSecond; }
	inline float GetDuration() { return m_Duration;}
	inline const AssimpNodeData& GetRootNode() { return m_RootNode; }
	inline const map<string,BoneInfo>& GetBoneIDMap() { return m_BoneInfoMap; }

private:
	void ReadMissingBones(const aiAnimation* animation, Model& model);

	void ReadHierarchyData(AssimpNodeData& dest, const aiNode* src);
	float m_Duration;
	int m_TicksPerSecond;
	vector<Bone> m_Bones;
	AssimpNodeData m_RootNode;
	map<string, BoneInfo> m_BoneInfoMap;
};

#endif