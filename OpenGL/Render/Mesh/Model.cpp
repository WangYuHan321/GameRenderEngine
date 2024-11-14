#pragma once

#if 0
#include <vector>
#include <functional>
#include <GLM/glm.hpp>
#include <vector>

enum TOPOLOGY
{
    POINTS,
    LINES,
    LINE_STRIP,
    TRIANGLES,
    TRIANGLE_STRIP,
    TRIANGLE_FAN,
};

class Mesh
{
   
public:
    unsigned int m_VAO = 0;
    unsigned int m_VBO;
    unsigned int m_EBO;
public:
    std::vector<glm::vec3> Positions;
    std::vector<glm::vec2> UV;
    std::vector<glm::vec3> Normals;
    std::vector<glm::vec3> Tangents;
    std::vector<glm::vec3> Bitangents;

    TOPOLOGY Topology = TRIANGLES;
    std::vector<unsigned int> Indices;

    // support multiple ways of initializing a mesh
    Mesh();
    Mesh(std::vector<glm::vec3> positions, std::vector<unsigned int> indices);
    Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv, std::vector<unsigned int> indices);
    Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv, std::vector<glm::vec3> normals, std::vector<unsigned int> indices);
    Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv, std::vector<glm::vec3> normals, std::vector<glm::vec3> tangents, std::vector<glm::vec3> bitangents, std::vector<unsigned int> indices);

    // set vertex data manually
    // TODO(Joey): not sure if these are required if we can directly set vertex data from public fields; construct several use-cases to test.
    void SetPositions(std::vector<glm::vec3> positions);
    void SetUVs(std::vector<glm::vec2> uv);
    void SetNormals(std::vector<glm::vec3> normals);
    void SetTangents(std::vector<glm::vec3> tangents, std::vector<glm::vec3> bitangents); // NOTE(Joey): you can only set both tangents and bitangents at the same time to prevent mismatches

    // commits all buffers and attributes to the GPU driver
    void Finalize(bool interleaved = true);

    // generate triangulated mesh from signed distance field
    void FromSDF(std::function<float(glm::vec3)>& sdf, float maxDistance, uint16_t gridResolution);

private:
    void calculateNormals(bool smooth = true);
    void calculateTangents();
};

#endif

#include "Model.h"
#include "Mesh.h"
#include "Material.h"
#include "../Bounding/BoundingSphere.h"
#include <GLM/glm.hpp>

Model::Model(std::vector<Mesh*>& p_mesh, std::vector<std::string>& p_material):
    m_meshes(p_mesh),
    m_materialNames(p_material)
{
    ComputeBoundingSphere();
}

Model::Model()
{
}

Model::~Model()
{
    for (auto mesh : m_meshes)
        delete mesh;
}

std::vector<Mesh*>& Model::GetMeshes()
{
    return m_meshes;
}

const BoundingSphere& Model::GetBoundingSphere() const
{
    return m_boundingSphere;
}

std::unordered_map<string, BoneInfo>& Model::GetBoneInfoMap()
{
    return m_BoneInfoMap;
}

uint32& Model::GetBoneCount()
{
    return m_BoneCounter;
}

void Model::ComputeBoundingSphere()
{
    if (m_meshes.size() == 1)
    {
        m_boundingSphere = m_meshes[0]->m_boundingSphere;
    }
    else
    {
        m_boundingSphere.position = glm::vec3(0.0f);
        m_boundingSphere.radius = 0.0f;

        if (!m_meshes.empty())
        {
            float minX = std::numeric_limits<float>::max();
            float minY = std::numeric_limits<float>::max();
            float minZ = std::numeric_limits<float>::max();

            float maxX = std::numeric_limits<float>::min();
            float maxY = std::numeric_limits<float>::min();
            float maxZ = std::numeric_limits<float>::min();

            for (const auto& mesh : m_meshes)
            {
                const auto& boundingSphere = mesh->m_boundingSphere;
                minX = std::min(minX, boundingSphere.position.x - boundingSphere.radius);
                minY = std::min(minY, boundingSphere.position.y - boundingSphere.radius);
                minZ = std::min(minZ, boundingSphere.position.z - boundingSphere.radius);

                maxX = std::max(maxX, boundingSphere.position.x + boundingSphere.radius);
                maxY = std::max(maxY, boundingSphere.position.y + boundingSphere.radius);
                maxZ = std::max(maxZ, boundingSphere.position.z + boundingSphere.radius);
            }

            m_boundingSphere.position = Vector3{ minX + maxX, minY + maxY, minZ + maxZ } / 2.0f;
            m_boundingSphere.radius = glm::distance(m_boundingSphere.position, { minX, minY, minZ });
        }
    }
}

