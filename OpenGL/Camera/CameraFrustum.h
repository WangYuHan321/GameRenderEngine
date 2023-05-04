#pragma once
#include <GLM/glm.hpp>
#if 0 
class Camera;

//A*x+B*y+C*z+D=0
struct FrwustumPlane {
	glm::vec3 Normal;
	float D;

	void SetNormalD(glm::vec3 normal, glm::vec3 point)
	{
		Normal = normal;
		D = -glm::dot(Normal, point);
	}

};

#endif



class Camera;

struct FrustumPlane
{
    glm::vec3 Normal;
    float      D;

    void SetNormalD(glm::vec3 normal, glm::vec3 point)
    {
        Normal = glm::normalize(normal);
        D = -glm::dot(Normal, point);
    }

    float Distance(glm::vec3 point)
    {
        return glm::dot(Normal, point) + D;
    }
};


class CameraFrustum
{
public:
    union
    {
        FrustumPlane Planes[6];
        struct
        {
            FrustumPlane Left;
            FrustumPlane Right;
            FrustumPlane Top;
            FrustumPlane Bottom;
            FrustumPlane Near;
            FrustumPlane Far;
        };
    };

public:
    CameraFrustum() { } // NOTE(Joey): why do I need to define a constructor here? (otherwise I get deleted constructor error) LOOK IT UP!

    void Update(Camera* camera);

    bool Intersect(glm::vec3 point);
    bool Intersect(glm::vec3 point, float radius);
    bool Intersect(glm::vec3 boxMin, glm::vec3 boxMax);
};
