#include "Bone.h"

template <class T>
const T& get_start(typename std::map<float, T>& mp, float animation_time, const T& default_value)
{
	typename std::map<float, T>::iterator lower = mp.lower_bound(animation_time);

	if (mp.size() != 0 && lower != mp.end() && animation_time == lower->first)
	{
		return lower->second;
	}
	if (lower == mp.begin() || mp.size() == 0)
	{
		return default_value;
	}
	return std::next(lower, -1)->second;
}

template <class T>
const T& get_end(typename std::map<float, T>& mp, float animation_time, const T& default_value)
{
	if (mp.size() == 0)
	{
		return default_value;
	}
	typename std::map<float, T>::iterator upper = mp.upper_bound(animation_time);
	if (upper == mp.begin())
	{
		return upper->second;
	}
	if (std::next(upper, -1)->first == animation_time || upper == mp.end())
	{
		return std::next(upper, -1)->second;
	}
	return upper->second;
}

template <class T>
const std::pair<const T&, const T&> get_start_end(typename std::map<float, T>& mp, float animation_time, const T& default_value)
{
	if (mp.size() == 0)
	{
		auto tmp_val = default_value;
		tmp_val.time = animation_time;
		return std::make_pair(default_value, tmp_val);
	}
	typename std::map<float, T>::iterator lower = mp.lower_bound(animation_time);

	if (lower != mp.end() && animation_time == lower->first)
	{
		return { lower->second, lower->second };
	}
	if (lower == mp.begin())
	{
		return { default_value, lower->second };
	}
	if (lower != mp.end())
	{
		return { std::next(lower, -1)->second, lower->second };
	}
	lower--;
	return { lower->second, lower->second };
}

float get_scale_factor(float last_time_stamp, float next_time_stamp, float animation_time)
{
	float scaleFactor = 0.0f;
	float midWayLength = animation_time - last_time_stamp;
	float framesDiff = next_time_stamp - last_time_stamp;
	if (last_time_stamp == next_time_stamp || framesDiff < 0.0f)
	{
		return 1.0;
	}
	scaleFactor = midWayLength / framesDiff;
	return scaleFactor;
}

Bone::Bone(const std::string& name, const aiNodeAnim* channel, const glm::mat4& inverseBindingPose):
	name(name),
	localTransform(inverseBindingPose)
{
	int num_pos = channel->mNumPositionKeys;
	int num_rotat = channel->mNumRotationKeys;
	int num_scale = channel->mNumScalingKeys;

	for (int pos_idx = 0; pos_idx < num_pos; ++pos_idx)
	{
		aiVector3D aiPos = channel->mPositionKeys[pos_idx].mValue;
		float time = channel->mPositionKeys[pos_idx].mTime;
		positions[time] = KeyPosition{ Vector3(aiPos.x, aiPos.y, aiPos.z), time };
		times.insert(time);
	}

	for (int rot_idx = 0; rot_idx < num_rotat; ++rot_idx)
	{
		aiQuaterniont aiRotat = channel->mRotationKeys[rot_idx].mValue;
		float time = channel->mPositionKeys[rot_idx].mTime;
		rotations[time] = KeyRotation { Quaternion(aiRotat.x, aiRotat.y, aiRotat.z, aiRotat.w), time };
		times.insert(time);
	}

	for (int sca_idx = 0; sca_idx < num_scale; ++sca_idx)
	{
		aiVector3D aiScale = channel->mScalingKeys[sca_idx].mValue;
		float time = channel->mPositionKeys[sca_idx].mTime;
		scales[time] = KeyScale{ Vector3(aiScale.x, aiScale.y, aiScale.z), time };
		times.insert(time);
	}

	for (auto time : times)
	{
		auto t = positions.find(time);
		auto r = rotations.find(time);
		auto s = scales.find(time);

		Vector3 tt = (t != positions.end()) ? t->second.position : Vector3(0.0f);
		Quaternion rr = (r != rotations.end()) ? r->second.quat : Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
		Vector3 ss = (s != scales.end()) ? s->second.scale : Vector3(1.0f);

		Matrix4 transform = Translate(tt) * rr.ToMatrix4() * Scale(ss);
		transform = inverseBindingPose * transform;

		auto [translation, rotation, scale] = DecomposeTransform(transform);
		if (t != positions.end())
		{
			t->second.position = translation;
		}
		if (r != rotations.end())
		{
			r->second.quat = rotation;
		}
		if (s != scales.end())
		{
			s->second.scale = scale;
		}
	}
}

Matrix4 Bone::InterplatePosition(float animation_time)
{
	const auto& [p0Index, p1Index] = get_start_end<KeyPosition>(positions, animation_time, KeyPosition{ glm::vec3(0.0f, 0.0f, 0.0f), 0.0f });
	float scaleFactor = get_scale_factor(p0Index.time,
		p1Index.time, animation_time);
	return glm::translate(glm::mat4(1.0f), glm::mix(p0Index.position, p1Index.position, scaleFactor));
}

Matrix4 Bone::InterplateRotation(float animation_time)
{
	const auto& [p0Index, p1Index] = get_start_end<KeyRotation>(rotations, animation_time, KeyRotation{ glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 0.0f });
	float scaleFactor = get_scale_factor(p0Index.time,
		p1Index.time, animation_time);
	glm::quat finalRotation = glm::slerp(p0Index.quat.m_quat, p1Index.quat.m_quat, (float)scaleFactor);
	return glm::toMat4(glm::normalize(finalRotation));
}

Matrix4 Bone::InterplateScale(float animation_time)
{
	const auto& [p0Index, p1Index] = get_start_end<KeyScale>(scales, animation_time, KeyScale{ glm::vec3(1.0f, 1.0f, 1.0f), 0.0f });

	float scaleFactor = get_scale_factor(p0Index.time,
		p1Index.time, animation_time);
	return glm::scale(glm::mat4(1.0f), glm::mix(p0Index.scale, p1Index.scale, scaleFactor));
}

void Bone::Update(float animTime, float _factor)
{
	factor = _factor;
	animTime /= factor;

	glm::mat4 translation = InterplatePosition(animTime);
	glm::mat4 rotation = InterplateRotation(animTime);
	glm::mat4 scale = InterplateScale(animTime);
	localTransform = translation * rotation * scale;
}

Matrix4 Bone::GetLocalTransform(float animTime, float factor)
{
	Update(animTime, factor);
	return localTransform;
}

void Bone::Copy(aiNodeAnim& channel, const aiMatrix4x4& binding_pose_transform, float factor, bool is_interpolated)
{
	channel.mNodeName = aiString(name);

	std::vector<aiVectorKey> posKeys;
	std::vector<aiQuatKey> rotKeys;
	std::vector<aiVectorKey> sclKeys;

	std::map<float, Matrix4> transformMap;
	transformMap[0.0f] = Matrix4(1.0f);//默认 时间戳 0.0 transform不变化
	for (auto item : times)
	{
		float timeStamp = float(int(item * factor));
		transformMap[timeStamp] = GetLocalTransform(timeStamp, factor);
	}

	if (is_interpolated)
	{
		float duration = *times.rbegin();
		float anim_time = 0.0f;
		std::map<float, glm::mat4> new_transform_map;
		auto before_transform = glm::mat4(1.0f);
		for (auto& t_mp : transformMap)
		{
			for (; anim_time < t_mp.first; anim_time += 1.0f)
			{
				new_transform_map[anim_time] = GetLocalTransform(anim_time, factor);
			}
			before_transform = new_transform_map[t_mp.first] = t_mp.second;
			anim_time = t_mp.first + 1.0f;
		}
		transformMap = new_transform_map;
	}

	for (auto& transform : transformMap)
	{
		auto transformation = AiMatToGlmMat(binding_pose_transform) * transform.second;
		auto [t, r, s] = DecomposeTransform(transformation);

		posKeys.push_back(aiVectorKey(transform.first, GlmVecToAiVec(t)));
		rotKeys.push_back(aiQuatKey(transform.first, GlmQuatToAiQuat(r)));
		sclKeys.push_back(aiVectorKey(transform.first, GlmVecToAiVec(s)));
	}
	channel.mNumPositionKeys = posKeys.size(); // positions_.size();
	channel.mNumRotationKeys = rotKeys.size(); // rotations_.size();
	channel.mNumScalingKeys = sclKeys.size();  // scales_.size();

	channel.mPositionKeys = new aiVectorKey[channel.mNumPositionKeys];
	channel.mRotationKeys = new aiQuatKey[channel.mNumRotationKeys];
	channel.mScalingKeys = new aiVectorKey[channel.mNumScalingKeys];

	for (int i = 0; i < posKeys.size(); i++)
	{
		channel.mPositionKeys[i].mValue = posKeys[i].mValue;
		channel.mPositionKeys[i].mTime = posKeys[i].mTime;
		channel.mRotationKeys[i].mValue = rotKeys[i].mValue;
		channel.mRotationKeys[i].mTime = rotKeys[i].mTime;
		channel.mScalingKeys[i].mValue = sclKeys[i].mValue;
		channel.mScalingKeys[i].mTime = sclKeys[i].mTime;
	}

}