#pragma once
#include<GL/glew.h>
#include<GLM/glm.hpp>
#include<GLFW/glfw3.h>
#include <glm/gtx/quaternion.hpp>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<intrin.h>
#include<map>
#include <functional>
#include "../Math/Math.h"
#include"string_id.hpp"
#include"../Log/Logger.h"
#include"../ThirdLib/ImGui/imgui.h"
#include"../ThirdLib/ImGui/imgui_internal.h"

#define USE_NO_EDITOR //使用不是编辑器下面

//#define USE_EDITOR //使用不是编辑器下面

#define MSAA_NUM 4

#define DUMP_FILE L"C://dump.dmp" 

typedef unsigned int uint32;
typedef int int32;
typedef unsigned __int64 uint64;
typedef __int64 int64;  
typedef std::string string;

using Vector3 = glm::vec3;
using Vector2 = glm::vec2;
using Vector4 = glm::vec4;
using Matrix2 = glm::mat2;
using Matrix3 = glm::mat3;
using Matrix4 = glm::mat4;

struct Quaternion {
	glm::quat m_quat;

	Quaternion()
	{
		m_quat = glm::quat(0.0f,0.0f,0.0f,0.0f);
	}
	
	Quaternion(glm::quat _quat)
	{
		m_quat = _quat;
	}

	Quaternion(Matrix3 p_rotationMatrix)
	{
		float trace = p_rotationMatrix[0][0] + p_rotationMatrix[1][1] + p_rotationMatrix[2][2];
		if (trace > 0.0f)
		{
			// I changed M_EPSILON to 0
			float s = 0.5f / sqrt(trace + 1.0f);
			m_quat.w = 0.25f / s;
			m_quat.x = (p_rotationMatrix[2][1] - p_rotationMatrix[1][2]) * s;
			m_quat.y = (p_rotationMatrix[0][2] - p_rotationMatrix[2][0]) * s;
			m_quat.z = (p_rotationMatrix[1][0] - p_rotationMatrix[0][1]) * s;
		}
		else
		{
			if (p_rotationMatrix[0][0] > p_rotationMatrix[1][1] && p_rotationMatrix[0][0] > p_rotationMatrix[2][2])
			{
				float s = 2.0f * sqrt(1.0f + p_rotationMatrix[0][0] - p_rotationMatrix[1][1] - p_rotationMatrix[2][2]);
				m_quat.w = (p_rotationMatrix[2][1] - p_rotationMatrix[1][2]) / s;
				m_quat.x = 0.25f * s;
				m_quat.y = (p_rotationMatrix[0][1] + p_rotationMatrix[1][0]) / s;
				m_quat.z = (p_rotationMatrix[0][2] + p_rotationMatrix[2][0]) / s;
			}
			else if (p_rotationMatrix[1][1] > p_rotationMatrix[2][2])
			{
				float s = 2.0f * sqrt(1.0f + p_rotationMatrix[1][1] - p_rotationMatrix[0][0] - p_rotationMatrix[2][2]);
				m_quat.w = (p_rotationMatrix[0][2] - p_rotationMatrix[2][0]) / s;
				m_quat.x = (p_rotationMatrix[0][1] + p_rotationMatrix[1][0]) / s;
				m_quat.y = 0.25f * s;
				m_quat.z = (p_rotationMatrix[1][2] + p_rotationMatrix[2][1]) / s;
			}
			else
			{
				float s = 2.0f * sqrt(1.0f + p_rotationMatrix[2][2] - p_rotationMatrix[0][0] - p_rotationMatrix[1][1]);
				m_quat.w = (p_rotationMatrix[1][0] - p_rotationMatrix[0][1]) / s;
				m_quat.x = (p_rotationMatrix[0][2] + p_rotationMatrix[2][0]) / s;
				m_quat.y = (p_rotationMatrix[1][2] + p_rotationMatrix[2][1]) / s;
				m_quat.z = 0.25f * s;
			}
		}
	}

	Quaternion(Matrix4 mat4)
	{
		m_quat = glm::quat(mat4);
	}

	Quaternion(float x, float y, float z, float w) 
	{ m_quat.x = x; m_quat.y = y; m_quat.z = z; m_quat.w = w; }

	Vector3 operator* (Vector3 vec3)
	{
		return (m_quat * vec3);
	}

	Vector4 operator* (Vector4 vec4)
	{
		return (m_quat * vec4);
	}

	bool operator==(Quaternion quat)
	{
		return m_quat == quat.m_quat;
	}

	Quaternion& Normalize()
	{
		Quaternion temp = m_quat;
		const float reciprocate = 1.0f / sqrtf(m_quat.x * m_quat.x + m_quat.y * m_quat.y + m_quat.z * m_quat.z + m_quat.w * m_quat.w);
		temp.m_quat.x *= reciprocate;
		temp.m_quat.y *= reciprocate;
		temp.m_quat.z *= reciprocate;
		temp.m_quat.w *= reciprocate;

		m_quat = temp.m_quat;
		return *this;
	}

	Matrix4 ToMatrix4()
	{

		float y2 = m_quat.y * m_quat.y;	float wz = m_quat.w * m_quat.z;	float x2 = m_quat.x * m_quat.x;
		float z2 = m_quat.z * m_quat.z;	float xz = m_quat.x * m_quat.z;	float yz = m_quat.y * m_quat.z;
		float xy = m_quat.x * m_quat.y;	float wy = m_quat.w * m_quat.y;	float wx = m_quat.w * m_quat.x;

		Matrix4 converted;
		converted[0][0] = 1.0f - (2 * y2) - (2 * z2);		converted[0][1] = (2 * xy) - (2 * wz);				converted[0][2] = (2 * xz) + (2 * wy);			 converted[0][3] = 0;
		converted[1][0] = (2 * xy) + (2 * wz);				converted[1][1] = 1.0f - (2 * x2) - (2 * z2);		converted[1][2] = (2 * yz) - (2 * wx);			 converted[1][3] = 0;
		converted[2][0] = (2 * xz) - (2 * wy);				converted[2][1] = (2 * yz) + (2 * wx);			    converted[2][2] = 1.0f - (2 * x2) - (2 * y2);    converted[2][3] = 0;
		converted[3][0] = 0;								converted[3][1] = 0;								converted[3][2] = 0;							 converted[3][3] = 1;
		return converted;
	}

};


struct TransformNotifer
{
public:
	enum class ENotification
	{
		TRANSFORM_CHANGED,
		TRANSFORM_DESTROYED
	};

	using NotificationHandler = std::function<void(ENotification)>;

	using NotificationHandlerID = uint64_t;

	NotificationHandlerID AddNotificationHandler(NotificationHandler p_notificationHandler)
	{
		NotificationHandlerID handlerID = m_availableHandlerID++;
		m_notificationHandlers.emplace(handlerID, p_notificationHandler);
		return handlerID;
	}

	void NotifyChildren(ENotification p_notification)
	{
		if (!m_notificationHandlers.empty())
			for (auto const& [id, handler] : m_notificationHandlers)
				handler(p_notification);
	}

	bool RemoveNotificationHandler(const NotificationHandlerID& p_notificationHandlerID)
	{
		return m_notificationHandlers.erase(p_notificationHandlerID) != 0;
	}
private:
	std::unordered_map<NotificationHandlerID, NotificationHandler> m_notificationHandlers;
	NotificationHandlerID m_availableHandlerID = 0;
};


struct FTransform
{
	FTransform(Vector3 p_localPostion = Vector3(0.0f, 0.0f, 0.0f), Quaternion p_localRot = Quaternion(0.0f, 0.0f, 0.0f, 1.0f), Vector3 p_localScale = Vector3(1.0f, 1.0f, 1.0f)):
		m_notificationHandlerID(-1),
		m_parent(nullptr)
	{
		GenerateMatrices(p_localPostion, p_localRot, p_localScale);
	}

	~FTransform()
	{
		Notifier.NotifyChildren(TransformNotifer::ENotification::TRANSFORM_DESTROYED);
	}

	void GenerateMatrices(Vector3 p_position, Quaternion p_rotation, Vector3 p_scale)
	{
#if 0
		Matrix4 mat1 = Translate(p_position);

		Quaternion q = p_rotation.Normalize();

		Matrix4 mat2 = q.ToMatrix4();
		Matrix4 mat3 = Scale(p_scale);
		Matrix4 mat4 = Matrix4(0.0f);

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				printf("[%f]", mat1[i][j]);
			}
			printf("\n");
		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				printf("[%f]", mat2[i][j]);
			}
			printf("\n");
		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				printf("[%f]", mat3[i][j]);
			}
			printf("\n\n");
		}

		mat4 = Translate(p_position) * p_rotation.Normalize().ToMatrix4() * Scale(p_scale);

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				printf("[%f]", mat4[i][j]);
			}
			printf("\n");
		}
#endif
		m_localMatrix = Scale(p_scale) * p_rotation.Normalize().ToMatrix4() * Translate(p_position);

		m_localPosition = p_position;
		m_localRot = p_rotation;
		m_localScale = p_scale;

		UpdateWorldMatrix();
	}

	void UpdateWorldMatrix()
	{
		m_worldMatrix = HasParent() ?  m_localMatrix * m_parent->m_worldMatrix : m_localMatrix;
		PreDecomposeWorldMatrix();

		Notifier.NotifyChildren(TransformNotifer::ENotification::TRANSFORM_CHANGED);
	}

	void PreDecomposeWorldMatrix()
	{
		m_worldPosition.x = m_worldMatrix[0][3];
		m_worldPosition.y = m_worldMatrix[1][3];
		m_worldPosition.z = m_worldMatrix[2][3];

		Vector3 columns[3] =
		{
			{ m_worldMatrix[0][0], m_worldMatrix[1][0], m_worldMatrix[2][0]},
			{ m_worldMatrix[0][1], m_worldMatrix[1][1], m_worldMatrix[2][1]},
			{ m_worldMatrix[0][2], m_worldMatrix[1][2], m_worldMatrix[2][2]},
		};

		m_worldScale.x = glm::length(columns[0]);
		m_worldScale.y = glm::length(columns[1]);
		m_worldScale.z = glm::length(columns[2]);

		if (m_worldScale.x)
		{
			columns[0] /= m_worldScale.x;
		}
		if (m_worldScale.y)
		{
			columns[1] /= m_worldScale.y;
		}
		if (m_worldScale.z)
		{
			columns[2] /= m_worldScale.z;
		}

		Matrix3 rotationMatrix
		(
			columns[0].x, columns[1].x, columns[2].x,
			columns[0].y, columns[1].y, columns[2].y,
			columns[0].z, columns[1].z, columns[2].z
		);

		m_worldRot = Quaternion(rotationMatrix);
	}

	void NotificationHandler(TransformNotifer::ENotification p_notification)
	{
		switch (p_notification)
		{
		case TransformNotifer::ENotification::TRANSFORM_CHANGED:
			UpdateWorldMatrix();
			break;

		case TransformNotifer::ENotification::TRANSFORM_DESTROYED:
			GenerateMatrices(m_worldPosition, m_worldRot, m_worldScale);
			m_parent = nullptr;
			UpdateWorldMatrix();
			break;
		}
	}


	bool HasParent() const
	{
		return m_parent != nullptr;
	}

	const Vector3& GetLocalPosition() const
	{
		return m_localPosition;
	}

	const Quaternion& GetLocalRotation() const
	{
		return m_localRot;
	}

	const Vector3& GetWorldPosition() const
	{
		return m_worldPosition;
	}

	const Vector3& GetWorldScale() const
	{
		return m_worldScale;
	}

	const Quaternion& GetWorldRotation() const
	{
		return m_worldRot;
	}

	const Matrix4& GetLocalMatrix() const
	{
		return m_localMatrix;
	}

	const Matrix4& GetWorldMatrix() const
	{
		return m_worldMatrix;
	}

	const Vector3& GetLocalScale() const
	{
		return m_localScale;
	}

	void SetLocalPosition(Vector3 p_newPosition)
	{
		GenerateMatrices(p_newPosition, m_localRot, m_localScale);
	}

	void SetLocalRotation(Quaternion p_newRotation)
	{
		GenerateMatrices(m_localPosition, p_newRotation, m_localScale);
	}

	void SetLocalScale(Vector3 p_newScale)
	{
		GenerateMatrices(m_localPosition, m_localRot, p_newScale);
	}

	void SetParent(FTransform& p_parent)
	{
		m_parent = &p_parent;

		m_notificationHandlerID = m_parent->Notifier.AddNotificationHandler(std::bind(&FTransform::NotificationHandler, this, std::placeholders::_1));

		UpdateWorldMatrix();
	}

	bool RemoveParent()
	{
		if (m_parent != nullptr)
		{
			m_parent->Notifier.RemoveNotificationHandler(m_notificationHandlerID);
			m_parent = nullptr;
			UpdateWorldMatrix();

			return true;
		}

		return false;
	}

public:
	TransformNotifer Notifier;
	TransformNotifer::NotificationHandlerID m_notificationHandlerID;

private:
	Vector3 m_localPosition;
	Quaternion m_localRot;
	Vector3 m_localScale;

	Vector3 m_worldPosition;
	Quaternion m_worldRot;
	Vector3 m_worldScale;

	Matrix4 m_localMatrix;
	Matrix4 m_worldMatrix;

	FTransform* m_parent;
};

namespace EasyGraphics {

#ifdef _DEBUG
	#include"new_on.h"
	#include"MemoryManager.h"
#else

#endif // DEBUG
	struct EWINDOWINFO
	{
		uint32 WINDOW_WIDTH;
		uint32 WINDOW_HEIGHT;
		string WINDOW_TITLE;

		EWINDOWINFO(uint32 width, uint32 height, string title) :
			WINDOW_WIDTH(width), WINDOW_HEIGHT(height), WINDOW_TITLE(title)
		{}
	};

	struct EINPUTMODEL
	{
		bool INPUT_CURSOUR_DISABLE;
		bool INPUT_KEYWORD_DISABLE;

		EINPUTMODEL(bool isMouseDsiable, bool isKeyboardDisable) : INPUT_CURSOUR_DISABLE(isMouseDsiable), INPUT_KEYWORD_DISABLE(isKeyboardDisable) {}
	};

	struct ETexture 
	{
		enum TextureType
		{
			Texture2D = GL_TEXTURE_2D,
			Texture3D = GL_TEXTURE_3D,
			Texture2DArray = GL_TEXTURE_2D_ARRAY,
			TextureCubeMap = GL_TEXTURE_CUBE_MAP,
			TextureCUbeArray = GL_TEXTURE_CUBE_MAP_ARRAY,
		};
		TextureType type;
		GLuint ID;
		GLint width;
		GLint height;
		GLint nrComponents;
	};
}

#if 0

#define Assert(exp, desc)\
if(!___assert(exp, desc, __FILE__, __LINE__))\
{ __debugbreak(); }\

static bool ___assert(bool exp, const char* desc,const char* filename, int line)
{
	if (!exp) {
		//ELOG_ERROR(desc);
		//ELOG_ERROR(filename);
		//ELOG_ERROR("" + line);
	}
	return exp;
}

#endif

struct Color3   
{
	float r, g, b;

	Color3& operator=(ImVec4& right)
	{
		r = right.x;
		g = right.y;
		b = right.z;
		return *this;
	}

	Color3(float _r, float _g, float _b)
	{
		r = _r;
		g = _g;
		b = _b;
	}
};

struct Color4
{
	float r, g, b, a;
	Color4() :r(0.0), g(0.0), b(0.0), a(0.0) {}
	Color4(float x, float y, float z, float w)
		:r(x), g(y), b(z), a(w) {}

	Color4& operator=(ImVec4& right)
	{
		r = right.x;
		g = right.y;
		b = right.z;
		a = right.w;
		return *this;
	}

	ImVec4 toImVec4()
	{
		ImVec4 imv;
		imv.x = r;
		imv.y = g;
		imv.z = b;
		imv.w = a;
		return imv;
	}
};
