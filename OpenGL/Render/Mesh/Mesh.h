#pragma once
#include <functional>
#include <glm/glm.hpp>
#include <vector>

enum TOPOLOGY
{
    POINTSS,
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

    TOPOLOGY Topology = TOPOLOGY::TRIANGLES;
    std::vector<unsigned int> Indices;

    Mesh();
    ~Mesh();
    Mesh(std::vector<glm::vec3> positions, std::vector<unsigned int> indices);
    Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv, std::vector<unsigned int> indices);
    Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv, std::vector<glm::vec3> normals, std::vector<unsigned int> indices);
    Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv, std::vector<glm::vec3> normals, std::vector<glm::vec3> tangents, std::vector<glm::vec3> bitangents, std::vector<unsigned int> indices);

    void SetPositions(std::vector<glm::vec3> positions);
    void SetUVs(std::vector<glm::vec2> uv);
    void SetNormals(std::vector<glm::vec3> normals);
    void SetTangents(std::vector<glm::vec3> tangents, std::vector<glm::vec3> bitangents); // NOTE(Joey): you can only set both tangents and bitangents at the same time to prevent mismatches

    void Finalize(bool interleaved = true);

    void FromSDF(std::function<float(glm::vec3)>& sdf, float maxDistance, uint16_t gridResolution);

private:
    void calculateNormals(bool smooth = true);
    void calculateTangents();
};