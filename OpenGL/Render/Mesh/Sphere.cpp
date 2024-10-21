#include "Sphere.h"
#include <math.h>
#include "../../Math/Math.h"
Sphere::Sphere(unsigned int xSegments, unsigned int ySegments)
{
    for (unsigned int y = 0; y <= ySegments; ++y)
    {
        for (unsigned int x = 0; x <= xSegments; ++x)
        {
            float xSegment = (float)x / (float)xSegments;
            float ySegment = (float)y / (float)ySegments;
            float xPos = std::cos(xSegment * TAU) * std::sin(ySegment * PI); // TAU is 2PI
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * TAU) * std::sin(ySegment * PI);

            m_vecPos.push_back(glm::vec3(xPos, yPos, zPos));
            m_vecUV.push_back(glm::vec2(xSegment, ySegment));
            m_vecNormal.push_back(glm::vec3(xPos, yPos, zPos));
        }
    }

    bool oddRow = false;
    for (int y = 0; y < ySegments; ++y)
    {
        for (int x = 0; x < xSegments; ++x)
        {
            m_vecIndices.push_back((y + 1) * (xSegments + 1) + x);
            m_vecIndices.push_back(y * (xSegments + 1) + x);
            m_vecIndices.push_back(y * (xSegments + 1) + x + 1);

            m_vecIndices.push_back((y + 1) * (xSegments + 1) + x);
            m_vecIndices.push_back(y * (xSegments + 1) + x + 1);
            m_vecIndices.push_back((y + 1) * (xSegments + 1) + x + 1);
        }
    }

    m_topology = TRIANGLES;
    Finalize();
}