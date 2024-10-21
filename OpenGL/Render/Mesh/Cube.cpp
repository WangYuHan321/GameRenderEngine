#include "Cube.h"
#include<GLM/glm.hpp>
#include<vector>

Cube::Cube()
{
    m_vecPos = std::vector<Vector3>{
     Vector3(-0.5f, -0.5f, -0.5f),
     Vector3(0.5f,  0.5f, -0.5f),
     Vector3(0.5f, -0.5f, -0.5f),
     Vector3(0.5f,  0.5f, -0.5f),
     Vector3(-0.5f, -0.5f, -0.5f),
     Vector3(-0.5f,  0.5f, -0.5f),

     Vector3(-0.5f, -0.5f,  0.5f),
     Vector3(0.5f, -0.5f,  0.5f),
     Vector3(0.5f,  0.5f,  0.5f),
     Vector3(0.5f,  0.5f,  0.5f),
     Vector3(-0.5f,  0.5f,  0.5f),
     Vector3(-0.5f, -0.5f,  0.5f),

     Vector3(-0.5f,  0.5f,  0.5f),
     Vector3(-0.5f,  0.5f, -0.5f),
     Vector3(-0.5f, -0.5f, -0.5f),
     Vector3(-0.5f, -0.5f, -0.5f),
     Vector3(-0.5f, -0.5f,  0.5f),
     Vector3(-0.5f,  0.5f,  0.5f),

     Vector3(0.5f,  0.5f,  0.5f),
     Vector3(0.5f, -0.5f, -0.5f),
     Vector3(0.5f,  0.5f, -0.5f),
     Vector3(0.5f, -0.5f, -0.5f),
     Vector3(0.5f,  0.5f,  0.5f),
     Vector3(0.5f, -0.5f,  0.5f),

     Vector3(-0.5f, -0.5f, -0.5f),
     Vector3(0.5f, -0.5f, -0.5f),
     Vector3(0.5f, -0.5f,  0.5f),
     Vector3(0.5f, -0.5f,  0.5f),
     Vector3(-0.5f, -0.5f,  0.5f),
     Vector3(-0.5f, -0.5f, -0.5f),

     Vector3(-0.5f,  0.5f, -0.5f),
     Vector3(0.5f,  0.5f,  0.5f),
     Vector3(0.5f,  0.5f, -0.5f),
     Vector3(0.5f,  0.5f,  0.5f),
     Vector3(-0.5f,  0.5f, -0.5f),
     Vector3(-0.5f,  0.5f,  0.5f),
    };
    m_vecUV = std::vector<Vector2>{
        Vector2(0.0f, 0.0f),
        Vector2(1.0f, 1.0f),
        Vector2(1.0f, 0.0f),
        Vector2(1.0f, 1.0f),
        Vector2(0.0f, 0.0f),
        Vector2(0.0f, 1.0f),

        Vector2(0.0f, 0.0f),
        Vector2(1.0f, 0.0f),
        Vector2(1.0f, 1.0f),
        Vector2(1.0f, 1.0f),
        Vector2(0.0f, 1.0f),
        Vector2(0.0f, 0.0f),

        Vector2(1.0f, 0.0f),
        Vector2(1.0f, 1.0f),
        Vector2(0.0f, 1.0f),
        Vector2(0.0f, 1.0f),
        Vector2(0.0f, 0.0f),
        Vector2(1.0f, 0.0f),

        Vector2(1.0f, 0.0f),
        Vector2(0.0f, 1.0f),
        Vector2(1.0f, 1.0f),
        Vector2(0.0f, 1.0f),
        Vector2(1.0f, 0.0f),
        Vector2(0.0f, 0.0f),

        Vector2(0.0f, 1.0f),
        Vector2(1.0f, 1.0f),
        Vector2(1.0f, 0.0f),
        Vector2(1.0f, 0.0f),
        Vector2(0.0f, 0.0f),
        Vector2(0.0f, 1.0f),

        Vector2(0.0f, 1.0f),
        Vector2(1.0f, 0.0f),
        Vector2(1.0f, 1.0f),
        Vector2(1.0f, 0.0f),
        Vector2(0.0f, 1.0f),
        Vector2(0.0f, 0.0f),
    };
    m_vecNormal = std::vector<Vector3>{
        Vector3(0.0f,  0.0f, -1.0f),
        Vector3(0.0f,  0.0f, -1.0f),
        Vector3(0.0f,  0.0f, -1.0f),
        Vector3(0.0f,  0.0f, -1.0f),
        Vector3(0.0f,  0.0f, -1.0f),
        Vector3(0.0f,  0.0f, -1.0f),

        Vector3(0.0f,  0.0f,  1.0f),
        Vector3(0.0f,  0.0f,  1.0f),
        Vector3(0.0f,  0.0f,  1.0f),
        Vector3(0.0f,  0.0f,  1.0f),
        Vector3(0.0f,  0.0f,  1.0f),
        Vector3(0.0f,  0.0f,  1.0f),

        Vector3(-1.0f,  0.0f,  0.0f),
        Vector3(-1.0f,  0.0f,  0.0f),
        Vector3(-1.0f,  0.0f,  0.0f),
        Vector3(-1.0f,  0.0f,  0.0f),
        Vector3(-1.0f,  0.0f,  0.0f),
        Vector3(-1.0f,  0.0f,  0.0f),

        Vector3(1.0f,  0.0f,  0.0f),
        Vector3(1.0f,  0.0f,  0.0f),
        Vector3(1.0f,  0.0f,  0.0f),
        Vector3(1.0f,  0.0f,  0.0f),
        Vector3(1.0f,  0.0f,  0.0f),
        Vector3(1.0f,  0.0f,  0.0f),

        Vector3(0.0f, -1.0f,  0.0f),
        Vector3(0.0f, -1.0f,  0.0f),
        Vector3(0.0f, -1.0f,  0.0f),
        Vector3(0.0f, -1.0f,  0.0f),
        Vector3(0.0f, -1.0f,  0.0f),
        Vector3(0.0f, -1.0f,  0.0f),

        Vector3(0.0f,  1.0f,  0.0f),
        Vector3(0.0f,  1.0f,  0.0f),
        Vector3(0.0f,  1.0f,  0.0f),
        Vector3(0.0f,  1.0f,  0.0f),
        Vector3(0.0f,  1.0f,  0.0f),
        Vector3(0.0f,  1.0f,  0.0f),
    };

    m_topology = TRIANGLES;
    Finalize();
}