#pragma once
#include<GL/glew.h>
#include<GLM/glm.hpp>
#include<GLFW/glfw3.h>
#include <glm/gtx/quaternion.hpp>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<map>
#include <functional>
#include "../Math/Math.h"
#include"string_id.hpp"
#include"../Log/Logger.h"
#include"../ThirdLib/ImGui/imgui.h"
#include"../ThirdLib/ImGui/imgui_internal.h"

#define EngineNew new
#define EngineDelete delete

#ifdef _WIN32
#define WINDOWS_PLATFORM
#endif

#ifdef RENDER_API
#define VULKAN_API
#endif

//#define USE_NO_EDITOR

#define USE_EDITOR //使用不是编辑器下面

#define MSAA_NUM 4

#define DUMP_FILE L"C://dump.dmp" 

typedef unsigned int uint32;
typedef int int32;
typedef unsigned long DWORD;
//typedef unsigned __int64 uint64;
//typedef __int64 int64;  
typedef std::string string;
typedef unsigned long long ullong;

#define THREAD_CALLBACK __stdcall

using Vector3 = glm::vec3;
using Vector2 = glm::vec2;
using Vector4 = glm::vec4;
using Matrix2 = glm::mat2;
using Matrix3 = glm::mat3;
using Matrix4 = glm::mat4;

struct Ray {
	Vector3 p0;
	Vector3 dir;
};

struct Quaternion {
	glm::quat m_quat;

	Quaternion()
	{
		m_quat = glm::quat(0.0f,0.0f,0.0f,0.0f);
	}

	Quaternion(Vector3 p_euler)
	{
		m_quat = glm::quat( Vector3(glm::radians(p_euler.x), glm::radians(p_euler.y), glm::radians(p_euler.z)) );
		//float yaw = TO_RADIANS(p_euler.z) * 0.5f;
		//float pitch = TO_RADIANS(p_euler.y) * 0.5f;
		//float roll = TO_RADIANS(p_euler.x) * 0.5f;

		//float cy = cos(yaw);
		//float sy = sin(yaw);
		//float cp = cos(pitch);
		//float sp = sin(pitch);
		//float cr = cos(roll);
		//float sr = sin(roll);

		//m_quat.x = sr * cp * cy - cr * sp * sy;
		//m_quat.y = cr * sp * cy + sr * cp * sy;
		//m_quat.z = cr * cp * sy - sr * sp * cy;
		//m_quat.w = cr * cp * cy + sr * sp * sy;
	}
	
	Quaternion(glm::quat _quat)
	{
		m_quat = _quat;
	}

	Quaternion(Matrix3 p_rotationMatrix)
	{
		m_quat = glm::toQuat(p_rotationMatrix);
	}

	Quaternion(Matrix4 mat4)
	{
		m_quat = glm::toQuat(mat4);
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
		return glm::toMat4(m_quat);
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
		//OpenGL T * R * S  i'm using OpenGL
		//DirectX  S * R * T

		m_localMatrix = Translate(p_position) * p_rotation.ToMatrix4() * Scale(p_scale);

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
		//Directx and OpenGL GLM in different

		auto [t, r, s] = DecomposeTransform(m_worldMatrix);

		m_worldPosition = t;


		m_worldScale = s;


		m_worldRot = r;
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

	Vector3 GetLocalForward()
	{
		return m_localRot * Vector3(0, 0, 1);
	}

	Vector3 GetLocalUp()
	{
		return m_localRot * Vector3(0, 1, 0);
	}

	Vector3 GetLocalRight()
	{
		return m_localRot * Vector3(1, 0, 0);
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

	Vector3 GetWorldForward()
	{
		return m_worldRot * Vector3(0, 0, 1);
	}

	Vector3 GetWorldUp() 
	{
		return m_worldRot * Vector3(0, 1, 0);
	}

	Vector3 GetWorldRight() 
	{
		return m_worldRot * Vector3(1, 0, 0);
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

#define POLYNOMIAL 0x04c11db7L
static unsigned int CRCTable[256] = { 0 };
static bool bInit = false;
static void InitCRCTable()
{
	register int i, j;
	register unsigned long crc_accum;
	for (i = 0; i < 256; i++)
	{
		crc_accum = ((unsigned long)i << 24);
		for (j = 0; j < 8; j++)
		{
			if (crc_accum & 0x80000000L) crc_accum = (crc_accum << 1) ^ POLYNOMIAL;
			else crc_accum = (crc_accum << 1);
		}
		CRCTable[i] = crc_accum;
	}
}
static unsigned int CRC32Compute(const void* pData, unsigned int uiDateSize)
{
	if (!bInit) { InitCRCTable(); bInit = true; }

	unsigned int uiResult;

	if (uiDateSize == 0) return 0;

	const unsigned char* pDateTemp = (const unsigned char*)pData;
	uiResult = *pDateTemp++ << 24;
	if (uiDateSize > 1)
	{
		uiResult |= *pDateTemp++ << 16;
		if (uiDateSize > 2)
		{
			uiResult |= *pDateTemp++ << 8;
			if (uiDateSize > 3) uiResult |= *pDateTemp++;
		}
	}
	uiResult = ~uiResult;

	for (size_t i = 4; i < uiDateSize; i++)
	{
		uiResult = (uiResult << 8 | *pDateTemp++) ^ CRCTable[uiResult >> 24];
	}

	return ~uiResult;
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

inline int valCount = 0;

inline void* operator new(std::size_t size) {
	void* ptr = std::malloc(size);
	if (ptr == nullptr) {
		throw std::bad_alloc();
	}
	valCount++;
	return ptr;
}

inline void operator delete(void* ptr) noexcept {
	std::free(ptr);
	valCount--;
}

inline void checkForMemoryLeaks() {
	LOG_ERROR(std::to_string( valCount ));
}

