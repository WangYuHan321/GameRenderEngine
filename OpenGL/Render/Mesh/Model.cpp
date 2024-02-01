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
#include <GLM/glm.hpp>

Model::Model(std::vector<Mesh*>& p_mesh, std::vector<Material*>& p_material):
    m_meshes(p_mesh),
    m_materials(p_material)
{
    ComputeBoundingSphere();
}

Model::~Model()
{

}

const BoundingSphere& Model::GetBoundingSphere() const
{
    return m_boundingSphere;
}

void Model::ComputeBoundingSphere()
{
    for (auto& item : m_meshes)
    {
        m_boundingSphere.position = glm::vec3(0.0f);
        m_boundingSphere.radius = 0.0f;

        if (!item->Positions.empty())
        {
            float minX = std::numeric_limits<float>::max();
            float minY = std::numeric_limits<float>::max();
            float minZ = std::numeric_limits<float>::max();

            float maxX = std::numeric_limits<float>::min();
            float maxY = std::numeric_limits<float>::min();
            float maxZ = std::numeric_limits<float>::min();

            for (const auto& vertex : item->Positions)
            {
                minX = std::min(minX, vertex.x);
                minY = std::min(minY, vertex.y);
                minZ = std::min(minZ, vertex.z);

                maxX = std::max(maxX, vertex.x);
                maxY = std::max(maxY, vertex.y);
                maxZ = std::max(maxZ, vertex.z);
            }

            m_boundingSphere.position = glm::vec3{ minX + maxX, minY + maxY, minZ + maxZ } / 2.0f;

            for (const auto& vertex : item->Positions)
            {
                const auto& position = reinterpret_cast<const glm::vec3&>(vertex);
                m_boundingSphere.radius = std::max(m_boundingSphere.radius, glm::distance(m_boundingSphere.position, position));
            }
        }
    }
}

