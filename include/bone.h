#ifndef BONE_H
#define BONE_H

#include <vector>
#include <assimp/scene.h>
#include <list>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "assimp_glm_helpers.h"

using namespace std;
using namespace glm;

struct KeyPosition
{
	vec3 position;
	float timeStamp;
};

struct KeyRotation
{
	quat orientation;
	float timeStamp;
};

struct KeyScale
{
	vec3 scale;
	float timeStamp;
};

class Bone
{
public:
	Bone(const string& name, int ID, const aiNodeAnim* channel);
	
	void Update(float animationTime);
	
	mat4 GetLocalTransform() { return Bone::m_LocalTransform; }
	string GetBoneName() const { return m_Name; }
	int GetBoneID() { return m_ID; }
	
	int GetPositionIndex(float animationTime);

	int GetRotationIndex(float animationTime);

	int GetScaleIndex(float animationTime);

private:

	float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);

	mat4 InterpolatePosition(float animationTime);

	mat4 InterpolateRotation(float animationTime);

	mat4 InterpolateScaling(float animationTime);

	vector<KeyPosition> m_Positions;
	vector<KeyRotation> m_Rotations;
	vector<KeyScale> m_Scales;
	int m_NumPositions;
	int m_NumRotations;
	int m_NumScalings;

	mat4 m_LocalTransform;
	string m_Name;
	int m_ID;
};

#endif