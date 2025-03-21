#include "Mesh.h"
#include "../../Util/common.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_EBO);
    glDeleteBuffers(1, &m_VBO);
}

Mesh::Mesh(std::vector<Vector3> vecPos, std::vector<unsigned int> vecIndices)
{
    m_vecPos = vecPos;
    m_vecIndices = vecIndices;
}

Mesh::Mesh(std::vector<Vector3> vecPos, std::vector<Vector2> vecUV, std::vector<unsigned int> vecIndices)
{
    m_vecPos = vecPos;
    m_vecUV = vecUV;
    m_vecIndices = vecIndices;
}

Mesh::Mesh(std::vector<Vector3> vecPos, std::vector<Vector2> vecUV, std::vector<Vector3> vecNormal, std::vector<unsigned int> vecIndices)
{
    m_vecPos = vecPos;
    m_vecUV = vecUV;
    m_vecNormal = vecNormal;
    m_vecIndices = vecIndices;
}

Mesh::Mesh(std::vector<Vector3> vecPos, std::vector<Vector2> vecUV, std::vector<Vector3> vecNormal, std::vector<Vector3> vecTangent, std::vector<Vector3> vecBittangent, std::vector<unsigned int> vecIndices)
{
    m_vecPos = vecPos;
    m_vecUV = vecUV;
    m_vecNormal = vecNormal;
    m_vecTangent = vecTangent;
    m_vecBitangent = vecBittangent;
    m_vecIndices = vecIndices;
}

void Mesh::SetPositions(std::vector<Vector3> m_vecPos)
{
    m_vecPos = m_vecPos;
}

void Mesh::SetUVs(std::vector<Vector2> m_vecUV)
{
    m_vecUV = m_vecUV;
}

void Mesh::SetNormals(std::vector<Vector3> m_vecNormal)
{
    m_vecNormal = m_vecNormal;
}

void Mesh::SetTangents(std::vector<Vector3> vecTangent, std::vector<Vector3> vecBitTangent)
{
    m_vecTangent = vecTangent;
    m_vecBitangent = vecBitTangent;
}

void Mesh::SetName(string name)
{
    m_strName = name;
}

void Mesh::SetTopology(TOPOLOGY topology)
{
    m_topology = topology;
}

void Mesh::SetMaterialIndex(uint32 materialIndex)
{
    m_materialIndex = materialIndex;
}

void Mesh::Finalize(bool interleaved)
{
    if (!m_VAO)
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);
    }


    std::vector<float> data;
    if (interleaved)
    {
        for (int i = 0; i < m_vecPos.size(); ++i)
        {
            data.push_back(m_vecPos[i].x);
            data.push_back(m_vecPos[i].y);
            data.push_back(m_vecPos[i].z);
            if (m_vecUV.size() > 0)
            {
                data.push_back(m_vecUV[i].x);
                data.push_back(m_vecUV[i].y);
            }
            if (m_vecNormal.size() > 0)
            {
                data.push_back(m_vecNormal[i].x);
                data.push_back(m_vecNormal[i].y);
                data.push_back(m_vecNormal[i].z);
            }
            if (m_vecTangent.size() > 0)
            {
                data.push_back(m_vecTangent[i].x);
                data.push_back(m_vecTangent[i].y);
                data.push_back(m_vecTangent[i].z);
            }
            if (m_vecBitangent.size() > 0)
            {
                data.push_back(m_vecBitangent[i].x);
                data.push_back(m_vecBitangent[i].y);
                data.push_back(m_vecBitangent[i].z);
            }
        }
    }
    else
    {
        for (int i = 0; i < m_vecPos.size(); ++i)
        {
            data.push_back(m_vecPos[i].x);
            data.push_back(m_vecPos[i].y);
            data.push_back(m_vecPos[i].z);
        }
        for (int i = 0; i < m_vecUV.size(); ++i)
        {
            data.push_back(m_vecUV[i].x);
            data.push_back(m_vecUV[i].y);
        }
        for (int i = 0; i < m_vecNormal.size(); ++i)
        {
            data.push_back(m_vecNormal[i].x);
            data.push_back(m_vecNormal[i].y);
            data.push_back(m_vecNormal[i].z);
        }
        for (int i = 0; i < m_vecTangent.size(); ++i)
        {
            data.push_back(m_vecTangent[i].x);
            data.push_back(m_vecTangent[i].y);
            data.push_back(m_vecTangent[i].z);
        }
        for (int i = 0; i < m_vecBitangent.size(); ++i)
        {
            data.push_back(m_vecBitangent[i].x);
            data.push_back(m_vecBitangent[i].y);
            data.push_back(m_vecBitangent[i].z);
        }
    }

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

    if (m_vecIndices.size() > 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vecIndices.size() * sizeof(unsigned int), &m_vecIndices[0], GL_STATIC_DRAW);
    }
    if (interleaved)
    {

        size_t stride = 3 * sizeof(float);
        if (m_vecUV.size() > 0)         stride += 2 * sizeof(float);
        if (m_vecNormal.size() > 0)    stride += 3 * sizeof(float);
        if (m_vecTangent.size() > 0)   stride += 3 * sizeof(float);
        if (m_vecBitangent.size() > 0) stride += 3 * sizeof(float);

        size_t offset = 0;
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
        offset += 3 * sizeof(float);
        if (m_vecUV.size() > 0)
        {
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
            offset += 2 * sizeof(float);
        }
        if (m_vecNormal.size() > 0)
        {
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
            offset += 3 * sizeof(float);
        }
        if (m_vecTangent.size() > 0)
        {
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
            offset += 3 * sizeof(float);
        }
        if (m_vecBitangent.size() > 0)
        {
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
            offset += 3 * sizeof(float);
        }
    }
    else
    {
        size_t offset = 0;
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
        offset += m_vecPos.size() * sizeof(float);
        if (m_vecUV.size() > 0)
        {
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
            offset += m_vecUV.size() * sizeof(float);
        }
        if (m_vecNormal.size() > 0)
        {
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
            offset += m_vecNormal.size() * sizeof(float);
        }
        if (m_vecTangent.size() > 0)
        {
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
            offset += m_vecTangent.size() * sizeof(float);
        }
        if (m_vecBitangent.size() > 0)
        {
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
            offset += m_vecBitangent.size() * sizeof(float);
        }
    }
    glBindVertexArray(0);

    ComputeBoundingSphere();
}

void Mesh::NewFinalize(bool interleaved)
{
    if (!m_VAO)
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);
    }

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vecVertex.size() * sizeof(Vertex), &m_vecVertex[0], GL_STATIC_DRAW);

    if (m_vecIndices.size() > 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vecIndices.size() * sizeof(unsigned int), &m_vecIndices[0], GL_STATIC_DRAW);
    }
    
    size_t stride = sizeof(Vertex);

    size_t offset = 0;
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
    offset += 3 * sizeof(float);
    {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
        offset += 2 * sizeof(float);
    }

    {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
        offset += 3 * sizeof(float);
    }

    {
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
        offset += 3 * sizeof(float);
    }

    {
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
        offset += 3 * sizeof(float);
    }

    {
        glEnableVertexAttribArray(5);
        glVertexAttribIPointer(5, 4, GL_INT, stride, (GLvoid*)offset);
        offset += 4 * sizeof(int32);
    }

    {
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
        offset += 4 * sizeof(float);
    }
 
    glBindVertexArray(0);

    ComputeBoundingSphere();
}

void Mesh::FromSDF(std::function<float(Vector3)>& sdf, float maxDistance, uint16_t gridResolution)
{
    LOG_INFO("Generating 3D mesh from SDF");

    // tables from: http://paulbourke.net/geometry/polygonise/
    static int edgeTable[256] =
    {
        0x0  , 0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c,
        0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00,
        0x190, 0x99 , 0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c,
        0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90,
        0x230, 0x339, 0x33 , 0x13a, 0x636, 0x73f, 0x435, 0x53c,
        0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30,
        0x3a0, 0x2a9, 0x1a3, 0xaa , 0x7a6, 0x6af, 0x5a5, 0x4ac,
        0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0,
        0x460, 0x569, 0x663, 0x76a, 0x66 , 0x16f, 0x265, 0x36c,
        0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60,
        0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0xff , 0x3f5, 0x2fc,
        0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0,
        0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x55 , 0x15c,
        0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950,
        0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0xcc ,
        0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0,
        0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc,
        0xcc , 0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0,
        0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c,
        0x15c, 0x55 , 0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650,
        0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc,
        0x2fc, 0x3f5, 0xff , 0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0,
        0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c,
        0x36c, 0x265, 0x16f, 0x66 , 0x76a, 0x663, 0x569, 0x460,
        0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac,
        0x4ac, 0x5a5, 0x6af, 0x7a6, 0xaa , 0x1a3, 0x2a9, 0x3a0,
        0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c,
        0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x33 , 0x339, 0x230,
        0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c,
        0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x99 , 0x190,
        0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c,
        0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x0
    };
    static int triTable[256][16] =
    {
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {9, 2, 10, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {2, 8, 3, 2, 10, 8, 10, 9, 8, -1, -1, -1, -1, -1, -1, -1},
        {3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 11, 2, 8, 11, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 9, 0, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 11, 2, 1, 9, 11, 9, 8, 11, -1, -1, -1, -1, -1, -1, -1},
        {3, 10, 1, 11, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 10, 1, 0, 8, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1, -1},
        {3, 9, 0, 3, 11, 9, 11, 10, 9, -1, -1, -1, -1, -1, -1, -1},
        {9, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {4, 3, 0, 7, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 1, 9, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {4, 1, 9, 4, 7, 1, 7, 3, 1, -1, -1, -1, -1, -1, -1, -1},
        {1, 2, 10, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {3, 4, 7, 3, 0, 4, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1},
        {9, 2, 10, 9, 0, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
        {2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1, -1, -1, -1},
        {8, 4, 7, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {11, 4, 7, 11, 2, 4, 2, 0, 4, -1, -1, -1, -1, -1, -1, -1},
        {9, 0, 1, 8, 4, 7, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
        {4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1, -1, -1, -1},
        {3, 10, 1, 3, 11, 10, 7, 8, 4, -1, -1, -1, -1, -1, -1, -1},
        {1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1, -1, -1, -1},
        {4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1, -1, -1, -1},
        {4, 7, 11, 4, 11, 9, 9, 11, 10, -1, -1, -1, -1, -1, -1, -1},
        {9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {9, 5, 4, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 5, 4, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {8, 5, 4, 8, 3, 5, 3, 1, 5, -1, -1, -1, -1, -1, -1, -1},
        {1, 2, 10, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {3, 0, 8, 1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
        {5, 2, 10, 5, 4, 2, 4, 0, 2, -1, -1, -1, -1, -1, -1, -1},
        {2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1, -1, -1, -1},
        {9, 5, 4, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 11, 2, 0, 8, 11, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
        {0, 5, 4, 0, 1, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
        {2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1, -1, -1, -1},
        {10, 3, 11, 10, 1, 3, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1},
        {4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1, -1, -1, -1},
        {5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1, -1, -1, -1},
        {5, 4, 8, 5, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1},
        {9, 7, 8, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {9, 3, 0, 9, 5, 3, 5, 7, 3, -1, -1, -1, -1, -1, -1, -1},
        {0, 7, 8, 0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, -1},
        {1, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {9, 7, 8, 9, 5, 7, 10, 1, 2, -1, -1, -1, -1, -1, -1, -1},
        {10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1, -1, -1, -1},
        {8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1, -1, -1, -1},
        {2, 10, 5, 2, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1},
        {7, 9, 5, 7, 8, 9, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1},
        {9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1, -1, -1, -1},
        {2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1, -1, -1, -1},
        {11, 2, 1, 11, 1, 7, 7, 1, 5, -1, -1, -1, -1, -1, -1, -1},
        {9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1, -1, -1, -1},
        {5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0, -1},
        {11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0, -1},
        {11, 10, 5, 7, 11, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 8, 3, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {9, 0, 1, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 8, 3, 1, 9, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
        {1, 6, 5, 2, 6, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 6, 5, 1, 2, 6, 3, 0, 8, -1, -1, -1, -1, -1, -1, -1},
        {9, 6, 5, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, -1},
        {5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1, -1, -1, -1},
        {2, 3, 11, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {11, 0, 8, 11, 2, 0, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
        {0, 1, 9, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
        {5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1, -1, -1, -1},
        {6, 3, 11, 6, 5, 3, 5, 1, 3, -1, -1, -1, -1, -1, -1, -1},
        {0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1, -1, -1, -1},
        {3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1, -1, -1, -1},
        {6, 5, 9, 6, 9, 11, 11, 9, 8, -1, -1, -1, -1, -1, -1, -1},
        {5, 10, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {4, 3, 0, 4, 7, 3, 6, 5, 10, -1, -1, -1, -1, -1, -1, -1},
        {1, 9, 0, 5, 10, 6, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
        {10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1, -1, -1, -1},
        {6, 1, 2, 6, 5, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1},
        {1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1, -1, -1, -1},
        {8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1, -1, -1, -1},
        {7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9, -1},
        {3, 11, 2, 7, 8, 4, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
        {5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1, -1, -1, -1},
        {0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1},
        {9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6, -1},
        {8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6, -1, -1, -1, -1},
        {5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11, -1},
        {0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7, -1},
        {6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9, -1, -1, -1, -1},
        {10, 4, 9, 6, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {4, 10, 6, 4, 9, 10, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1},
        {10, 0, 1, 10, 6, 0, 6, 4, 0, -1, -1, -1, -1, -1, -1, -1},
        {8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10, -1, -1, -1, -1},
        {1, 4, 9, 1, 2, 4, 2, 6, 4, -1, -1, -1, -1, -1, -1, -1},
        {3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4, -1, -1, -1, -1},
        {0, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {8, 3, 2, 8, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1},
        {10, 4, 9, 10, 6, 4, 11, 2, 3, -1, -1, -1, -1, -1, -1, -1},
        {0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6, -1, -1, -1, -1},
        {3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10, -1, -1, -1, -1},
        {6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1, -1},
        {9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3, -1, -1, -1, -1},
        {8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1, -1},
        {3, 11, 6, 3, 6, 0, 0, 6, 4, -1, -1, -1, -1, -1, -1, -1},
        {6, 4, 8, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {7, 10, 6, 7, 8, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, -1},
        {0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10, -1, -1, -1, -1},
        {10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0, -1, -1, -1, -1},
        {10, 6, 7, 10, 7, 1, 1, 7, 3, -1, -1, -1, -1, -1, -1, -1},
        {1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7, -1, -1, -1, -1},
        {2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9, -1},
        {7, 8, 0, 7, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1, -1},
        {7, 3, 2, 6, 7, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7, -1, -1, -1, -1},
        {2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7, -1},
        {1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11, -1},
        {11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1, -1, -1, -1, -1},
        {8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6, -1},
        {0, 9, 1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0, -1, -1, -1, -1},
        {7, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {3, 0, 8, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 1, 9, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {8, 1, 9, 8, 3, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
        {10, 1, 2, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 2, 10, 3, 0, 8, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
        {2, 9, 0, 2, 10, 9, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
        {6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8, -1, -1, -1, -1},
        {7, 2, 3, 6, 2, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {7, 0, 8, 7, 6, 0, 6, 2, 0, -1, -1, -1, -1, -1, -1, -1},
        {2, 7, 6, 2, 3, 7, 0, 1, 9, -1, -1, -1, -1, -1, -1, -1},
        {1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6, -1, -1, -1, -1},
        {10, 7, 6, 10, 1, 7, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1},
        {10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8, -1, -1, -1, -1},
        {0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7, -1, -1, -1, -1},
        {7, 6, 10, 7, 10, 8, 8, 10, 9, -1, -1, -1, -1, -1, -1, -1},
        {6, 8, 4, 11, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {3, 6, 11, 3, 0, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1},
        {8, 6, 11, 8, 4, 6, 9, 0, 1, -1, -1, -1, -1, -1, -1, -1},
        {9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6, -1, -1, -1, -1},
        {6, 8, 4, 6, 11, 8, 2, 10, 1, -1, -1, -1, -1, -1, -1, -1},
        {1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, -1},
        {4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9, -1, -1, -1, -1},
        {10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3, -1},
        {8, 2, 3, 8, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1},
        {0, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8, -1, -1, -1, -1},
        {1, 9, 4, 1, 4, 2, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1},
        {8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1, -1, -1, -1, -1},
        {10, 1, 0, 10, 0, 6, 6, 0, 4, -1, -1, -1, -1, -1, -1, -1},
        {4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3, -1},
        {10, 9, 4, 6, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {4, 9, 5, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 8, 3, 4, 9, 5, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
        {5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
        {11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5, -1, -1, -1, -1},
        {9, 5, 4, 10, 1, 2, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
        {6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5, -1, -1, -1, -1},
        {7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2, -1, -1, -1, -1},
        {3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6, -1},
        {7, 2, 3, 7, 6, 2, 5, 4, 9, -1, -1, -1, -1, -1, -1, -1},
        {9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7, -1, -1, -1, -1},
        {3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0, -1, -1, -1, -1},
        {6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8, -1},
        {9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7, -1, -1, -1, -1},
        {1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4, -1},
        {4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10, -1},
        {7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10, -1, -1, -1, -1},
        {6, 9, 5, 6, 11, 9, 11, 8, 9, -1, -1, -1, -1, -1, -1, -1},
        {3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5, -1, -1, -1, -1},
        {0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11, -1, -1, -1, -1},
        {6, 11, 3, 6, 3, 5, 5, 3, 1, -1, -1, -1, -1, -1, -1, -1},
        {1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6, -1, -1, -1, -1},
        {0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10, -1},
        {11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5, -1},
        {6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3, -1, -1, -1, -1},
        {5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2, -1, -1, -1, -1},
        {9, 5, 6, 9, 6, 0, 0, 6, 2, -1, -1, -1, -1, -1, -1, -1},
        {1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8, -1},
        {1, 5, 6, 2, 1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6, -1},
        {10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0, -1, -1, -1, -1},
        {0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {10, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {11, 5, 10, 7, 5, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {11, 5, 10, 11, 7, 5, 8, 3, 0, -1, -1, -1, -1, -1, -1, -1},
        {5, 11, 7, 5, 10, 11, 1, 9, 0, -1, -1, -1, -1, -1, -1, -1},
        {10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1, -1, -1, -1, -1},
        {11, 1, 2, 11, 7, 1, 7, 5, 1, -1, -1, -1, -1, -1, -1, -1},
        {0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11, -1, -1, -1, -1},
        {9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7, -1, -1, -1, -1},
        {7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2, -1},
        {2, 5, 10, 2, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1},
        {8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5, -1, -1, -1, -1},
        {9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2, -1, -1, -1, -1},
        {9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2, -1},
        {1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 8, 7, 0, 7, 1, 1, 7, 5, -1, -1, -1, -1, -1, -1, -1},
        {9, 0, 3, 9, 3, 5, 5, 3, 7, -1, -1, -1, -1, -1, -1, -1},
        {9, 8, 7, 5, 9, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {5, 8, 4, 5, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1},
        {5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0, -1, -1, -1, -1},
        {0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5, -1, -1, -1, -1},
        {10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4, -1},
        {2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8, -1, -1, -1, -1},
        {0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11, -1},
        {0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5, -1},
        {9, 4, 5, 2, 11, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4, -1, -1, -1, -1},
        {5, 10, 2, 5, 2, 4, 4, 2, 0, -1, -1, -1, -1, -1, -1, -1},
        {3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9, -1},
        {5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2, -1, -1, -1, -1},
        {8, 4, 5, 8, 5, 3, 3, 5, 1, -1, -1, -1, -1, -1, -1, -1},
        {0, 4, 5, 1, 0, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5, -1, -1, -1, -1},
        {9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {4, 11, 7, 4, 9, 11, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1},
        {0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11, -1, -1, -1, -1},
        {1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11, -1, -1, -1, -1},
        {3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4, -1},
        {4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2, -1, -1, -1, -1},
        {9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3, -1},
        {11, 7, 4, 11, 4, 2, 2, 4, 0, -1, -1, -1, -1, -1, -1, -1},
        {11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4, -1, -1, -1, -1},
        {2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1, -1, -1, -1},
        {9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7, -1},
        {3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10, -1},
        {1, 10, 2, 8, 7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {4, 9, 1, 4, 1, 7, 7, 1, 3, -1, -1, -1, -1, -1, -1, -1},
        {4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1, -1, -1, -1, -1},
        {4, 0, 3, 7, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {4, 8, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {9, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {3, 0, 9, 3, 9, 11, 11, 9, 10, -1, -1, -1, -1, -1, -1, -1},
        {0, 1, 10, 0, 10, 8, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1},
        {3, 1, 10, 11, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 2, 11, 1, 11, 9, 9, 11, 8, -1, -1, -1, -1, -1, -1, -1},
        {3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1, -1},
        {0, 2, 11, 8, 0, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {3, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {2, 3, 8, 2, 8, 10, 10, 8, 9, -1, -1, -1, -1, -1, -1, -1},
        {9, 10, 2, 0, 9, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8, -1, -1, -1, -1},
        {1, 10, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 3, 8, 9, 1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
    };

    // container object for all voxel data required for an individual algorithm march
    struct MCube
    {
        union
        {
            Vector4 Corners[8]; // <xyz: position, w: isosurface distance>
            struct
            {
                // notation: L = Left, R = Right, B = Bottom, T = Top, F = Front, B = Back (XYZ in right-handed system)
                Vector4 LBB;
                Vector4 RBB;
                Vector4 RBF;
                Vector4 LBF;
                Vector4 LTB;
                Vector4 RTB;
                Vector4 RTF;
                Vector4 LTF;
            };
        };
        MCube() { }
        int GetEdgeIndex()
        {
            int index = 0;
            if (Corners[0].w < 0.0f) index |= 1;
            if (Corners[1].w < 0.0f) index |= 2;
            if (Corners[2].w < 0.0f) index |= 4;
            if (Corners[3].w < 0.0f) index |= 8;
            if (Corners[4].w < 0.0f) index |= 16;
            if (Corners[5].w < 0.0f) index |= 32;
            if (Corners[6].w < 0.0f) index |= 64;
            if (Corners[7].w < 0.0f) index |= 128;
            return index;
        }
    };

    // cube-march aware lerp
    static auto mLerp = [](const Vector4& p1, const Vector4& p2) -> Vector3
    {
        const float epsilon = 0.0001f;
        if (std::abs(0.0f - p1.w) < epsilon)
            return Vector3(p1.x, p1.y, p1.z);
        if (std::abs(0.0f - p2.w) < epsilon)
            return Vector3(p2.x, p2.y, p2.z);;
        if (std::abs(p1.w - p2.w) < epsilon)
            return Vector3(p1.x, p1.y, p1.z);;
        float t = (0.0f - p1.w) / (p2.w - p1.w);
        Vector3 result({
            p1.x + t * (p2.x - p1.x),
            p1.y + t * (p2.y - p1.y),
            p1.z + t * (p2.z - p1.z)
            });
        return result;
    };


    const uint16_t gridSize = gridResolution;
    const float    scale = maxDistance;
    const float    cubeScale = (1.0f / static_cast<float>(gridSize)) * 2.0f * scale; // range => [-scale, scale] => 2*scale

                                                                                     // traverse the voxel grid
    for (uint16_t z = 0; z < gridSize; ++z) {
        for (uint16_t y = 0; y < gridSize; ++y) {
            for (uint16_t x = 0; x < gridSize; ++x) {
                // calculate voxel's 3D m_vecPos and evaluate SDF at each of its corners
                float halfCube = cubeScale * 0.5f;
                Vector3 center({
                    -scale + x * cubeScale + halfCube,
                    -scale + y * cubeScale + halfCube,
                    -scale + z * cubeScale + halfCube
                    });

                MCube voxel;
                Vector3 offset;
                // left-bottom-back
                offset = Vector3(-halfCube, -halfCube, -halfCube);
                voxel.LBB = Vector4(center + offset, 0.0f);
                voxel.LBB.w = sdf(Vector3(voxel.LBB.x, voxel.LBB.y, voxel.LBB.z));
                // right-bottom-back
                offset = Vector3(halfCube, -halfCube, -halfCube);
                voxel.RBB = Vector4(center + offset, 0.0f);
                voxel.RBB.w = sdf(Vector3(voxel.RBB.x, voxel.RBB.y, voxel.RBB.z));
                // right-bottom-front
                offset = Vector3(halfCube, -halfCube, halfCube);
                voxel.RBF = Vector4(center + offset, 0.0f);
                voxel.RBF.w = sdf(Vector3(voxel.RBF.x, voxel.RBF.y, voxel.RBF.z));
                // left-bottom-front
                offset = Vector3(-halfCube, -halfCube, halfCube);
                voxel.LBF = Vector4(center + offset, 0.0f);
                voxel.LBF.w = sdf(Vector3(voxel.LBF.x, voxel.LBF.y, voxel.LBF.z));
                // left-top-back
                offset = Vector3(-halfCube, halfCube, -halfCube);
                voxel.LTB = Vector4(center + offset, 0.0f);
                voxel.LTB.w = sdf(Vector3(voxel.LTB.x, voxel.LTB.y, voxel.LTB.z));
                // right-top-back
                offset = Vector3(halfCube, halfCube, -halfCube);
                voxel.RTB = Vector4(center + offset, 0.0f);
                voxel.RTB.w = sdf(Vector3(voxel.RTB.x, voxel.RTB.y, voxel.RTB.z));
                // right-top-front
                offset = Vector3(halfCube, halfCube, halfCube);
                voxel.RTF = Vector4(center + offset, 0.0f);
                voxel.RTF.w = sdf(Vector3(voxel.RTF.x, voxel.RTF.y, voxel.RTF.z));
                // left-top-front
                offset = Vector3(-halfCube, halfCube, halfCube);
                voxel.LTF = Vector4(center + offset, 0.0f);
                voxel.LTF.w = sdf(Vector3(voxel.LTF.x, voxel.LTF.y, voxel.LTF.z));

                // given all calculated data, generate this voxel's vertices
                std::vector<Vector3> vertList(12);

                int index = voxel.GetEdgeIndex();
                // edge table indexing from: http://paulbourke.net/geometry/polygonise/
                if (edgeTable[index] == 0) {} // cube is in/out of surface, do nothing
                if (edgeTable[index] & 1) { vertList[0] = mLerp(voxel.Corners[0], voxel.Corners[1]); }
                if (edgeTable[index] & 2) { vertList[1] = mLerp(voxel.Corners[1], voxel.Corners[2]); }
                if (edgeTable[index] & 4) { vertList[2] = mLerp(voxel.Corners[2], voxel.Corners[3]); }
                if (edgeTable[index] & 8) { vertList[3] = mLerp(voxel.Corners[3], voxel.Corners[0]); }
                if (edgeTable[index] & 16) { vertList[4] = mLerp(voxel.Corners[4], voxel.Corners[5]); }
                if (edgeTable[index] & 32) { vertList[5] = mLerp(voxel.Corners[5], voxel.Corners[6]); }
                if (edgeTable[index] & 64) { vertList[6] = mLerp(voxel.Corners[6], voxel.Corners[7]); }
                if (edgeTable[index] & 128) { vertList[7] = mLerp(voxel.Corners[7], voxel.Corners[4]); }
                if (edgeTable[index] & 256) { vertList[8] = mLerp(voxel.Corners[0], voxel.Corners[4]); }
                if (edgeTable[index] & 512) { vertList[9] = mLerp(voxel.Corners[1], voxel.Corners[5]); }
                if (edgeTable[index] & 1024) { vertList[10] = mLerp(voxel.Corners[2], voxel.Corners[6]); }
                if (edgeTable[index] & 2048) { vertList[11] = mLerp(voxel.Corners[3], voxel.Corners[7]); }

                // generate triangle vertices
                for (uint16_t i = 0; triTable[index][i] != -1; i += 3)
                {
                    Vector3 pos1 = vertList[triTable[index][i + 0]];
                    Vector3 pos2 = vertList[triTable[index][i + 1]];
                    Vector3 pos3 = vertList[triTable[index][i + 2]];
                    m_vecPos.push_back(pos1);
                    m_vecPos.push_back(pos2);
                    m_vecPos.push_back(pos3);

                    // calculate per-face m_vecNormal from position data
                    Vector3 normal = glm::cross(glm::normalize(pos2 - pos1), glm::normalize(pos3 - pos1));
                    m_vecNormal.push_back(normal);
                    m_vecNormal.push_back(normal);
                    m_vecNormal.push_back(normal);

                    // dirty local-space m_vecUV mapping approximation (to give some detail to objects)
                    m_vecUV.push_back(Vector2(vertList[triTable[index][i + 0]].x, vertList[triTable[index][i + 0]].y));
                    m_vecUV.push_back(Vector2(vertList[triTable[index][i + 1]].y, vertList[triTable[index][i + 1]].z));
                    m_vecUV.push_back(Vector2(vertList[triTable[index][i + 2]].x, vertList[triTable[index][i + 2]].y) * 0.5f + Vector2(vertList[triTable[index][i + 2]].y, vertList[triTable[index][i + 2]].z) * 0.5f);
                }
            }
        }
    }

    m_topology = TRIANGLES;
    Finalize();

    LOG_INFO("SDF mesh generation complete!");
}

void Mesh::Bind()
{
    glBindVertexArray(m_VAO);
}

void Mesh::UnBind()
{
    glBindVertexArray(0);
}

void Mesh::ComputeBoundingSphere()
{
    m_boundingSphere.position = Vector3(0.0f);
    m_boundingSphere.radius = 0.0f;

    if (!m_vecPos.empty())
    {
        float minX = std::numeric_limits<float>::max();
        float minY = std::numeric_limits<float>::max();
        float minZ = std::numeric_limits<float>::max();

        float maxX = std::numeric_limits<float>::min();
        float maxY = std::numeric_limits<float>::min();
        float maxZ = std::numeric_limits<float>::min();

        for (const auto& vertex : m_vecPos)
        {
            minX = std::min(minX, vertex.x);
            minY = std::min(minY, vertex.y);
            minZ = std::min(minZ, vertex.z);

            maxX = std::max(maxX, vertex.x);
            maxY = std::max(maxY, vertex.y);
            maxZ = std::max(maxZ, vertex.z);
        }

        m_boundingSphere.position = Vector3{ minX + maxX, minY + maxY, minZ + maxZ } / 2.0f;

        for (const auto& vertex : m_vecPos)
        {
            const auto& position = reinterpret_cast<const Vector3&>(vertex);
            m_boundingSphere.radius = std::max(m_boundingSphere.radius, glm::distance(m_boundingSphere.position, position));
        }
    }
}

// --------------------------------------------------------------------------------------------
void Mesh::calculateNormals(bool smooth)
{
    // TODO(Joey): manually calculate the m_vecNormal of each vertex
}
// --------------------------------------------------------------------------------------------
void Mesh::calculateTangents()
{
    // TODO(Joey): walk overall the vertices and calculate the tangent space vectors manually
    // TODO: based on topology, handle some of the winding orders differently.
    //m_vecTangent.resize(m_vecPos.size());
    //bim_vecTangent.resize(m_vecPos.size());
    //for (unsigned int i = 0; i < m_vecIndices.size() - 2; ++i)
    //{
    //    unsigned int index1 = m_vecIndices[i + 0];
    //    unsigned int index2 = m_vecIndices[i + 1];
    //    unsigned int index3 = m_vecIndices[i + 2];
    //    // TODO: do we take different winding order into account for triangle strip?
    //    Vector3 pos1 = m_vecPos[index1];
    //    Vector3 pos2 = m_vecPos[index2];
    //    Vector3 pos3 = m_vecPos[index3];

    //    Vector2 m_vecUV1 = m_vecUV[index1];
    //    Vector2 m_vecUV2 = m_vecUV[index2];
    //    Vector2 m_vecUV3 = m_vecUV[index3];

    //    // due to winding order getting changed each next triangle (as we render as triangle strip) we 
    //    // change the order of the cross product to account for winding order switch
    //    Vector3 edge1 = pos2 - pos1;
    //    Vector3 edge2 = pos3 - pos1;
    //    Vector2 deltam_vecUV1 = m_vecUV2 - m_vecUV1;
    //    Vector2 deltam_vecUV2 = m_vecUV3 - m_vecUV1;

    //    GLfloat f = 1.0f / (deltam_vecUV1.x * deltam_vecUV2.y - deltam_vecUV2.x * deltam_vecUV1.y);

    //    Vector3 tangent, bitangent;
    //    tangent.x = f * (deltam_vecUV2.y * edge1.x - deltam_vecUV1.y * edge2.x);
    //    tangent.y = f * (deltam_vecUV2.y * edge1.y - deltam_vecUV1.y * edge2.y);
    //    tangent.z = f * (deltam_vecUV2.y * edge1.z - deltam_vecUV1.y * edge2.z);
    //    /*    if (i % 2 == 0)
    //    {*/
    //    bitangent.x = f * (-deltam_vecUV2.x * edge1.x + deltam_vecUV1.x * edge2.x);
    //    bitangent.y = f * (-deltam_vecUV2.x * edge1.y + deltam_vecUV1.x * edge2.y);
    //    bitangent.z = f * (-deltam_vecUV2.x * edge1.z + deltam_vecUV1.x * edge2.z);
    //    //} 
    //    /*    else
    //    {
    //    bitangent.x = f * (-deltam_vecUV2.x * edge2.x + deltam_vecUV1.x * edge1.x);
    //    bitangent.y = f * (-deltam_vecUV2.x * edge2.y + deltam_vecUV1.x * edge1.y);
    //    bitangent.z = f * (-deltam_vecUV2.x * edge2.z + deltam_vecUV1.x * edge1.z);
    //    }*/
    //    m_vecTangent[index1] += tangent;
    //    m_vecTangent[index2] += tangent;
    //    m_vecTangent[index3] += tangent;
    //    bim_vecTangent[index1] += bitangent;
    //    bim_vecTangent[index2] += bitangent;
    //    bim_vecTangent[index3] += bitangent;
    //}
    //// normalize all m_vecTangent/bi-m_vecTangent
    //for (int i = 0; i < m_vecTangent.size(); ++i)
    //{
    //    m_vecTangent[i] = glm::normalize(m_vecTangent[i]);
    //    bim_vecTangent[i] = glm::normalize(bim_vecTangent[i]);
    //}
}