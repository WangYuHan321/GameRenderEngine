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
#include"string_id.hpp"
#include"../Log/Logger.h"
#include"../ThirdLib/ImGui/imgui.h"
#include"../ThirdLib/ImGui/imgui_internal.h"

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
using Quaternion = glm::quat;
using Matrix2 = glm::mat2;
using Matrix3 = glm::mat3;
using Matrix4 = glm::mat4;


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
		m_localMatrix = glm::mat4(1, 0, 0, p_position.x,
								  0, 1, 0, p_position.y,
			                      0, 0, 1, p_position.z,
			                      0, 0, 0, 1) * 
		glm::mat4(glm::normalize(p_rotation)) * glm::mat4(p_scale.x, 0, 0, 0,
														  0, p_scale.y, 0, 0,
														  0, 0, p_scale.z, 0,
														  0, 0, 0, 1);
		m_localPosition = p_position;
		m_localRot = p_rotation;
		m_localScale = p_scale;

		UpdateWorldMatrix();
	}

	void UpdateWorldMatrix()
	{
		m_worldMatrix = HasParent() ? m_parent->m_worldMatrix * m_localMatrix : m_localMatrix;
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
