#pragma once
#include <functional>
#include <glm/glm.hpp>
#include <vector>
#include "../Shader/Texture.h"
#include "../Bounding/BoundingSphere.h"

#define MAX_BONE_INFLUENCE 4

#define DIFFUSE_TEXTURE "texture_diffuse"
#define SPECULAR_TEXTURE "texture_specular"
#define NORMAL_TEXTURE "texture_normal"
#define AMBIENT_TEXTURE "texture_ambient"

enum TOPOLOGY
{
    POINTSS,
    LINES,
    LINE_STRIP,
    TRIANGLES,
    TRIANGLE_STRIP,
    TRIANGLE_FAN,
};

struct Vertex
{
    Vector3 Position;
    Vector2 UV;
    Vector3 Normal;
    Vector3 Tangent;
    Vector3 Bitangent;
    int32 BoneIDs[MAX_BONE_INFLUENCE] = { -1 };
    float Weights[MAX_BONE_INFLUENCE] = { 0.0f };
};

struct MaterialProperties
{
    Color3 Ambient{ 0.8f, 0.8f, 0.8f };
    Color3 Diffuse{ 1.0f, 1.0f, 1.0f };
    Color3 Specular{ 0.9f, 0.9f, 0.9f };
    float Shininess{ 1.0f };
    bool HasDiffuseTexture{ false };
};

class Mesh
{

public:
    unsigned int m_VAO = 0;
    unsigned int m_VBO;
    unsigned int m_EBO;
public:
    std::string Name = "";
    
    std::vector<glm::vec3> Positions;
    std::vector<glm::vec2> UV;
    std::vector<glm::vec3> Normals;
    std::vector<glm::vec3> Tangents;
    std::vector<glm::vec3> Bitangents;
    
    std::vector<Vertex> Vertexs;
    MaterialProperties materialProperty;

    uint32 MaterialIndex;
    BoundingSphere m_boundingSphere;

    TOPOLOGY Topology = TOPOLOGY::TRIANGLES;
    std::vector<unsigned int> Indices;
    std::map<string, Texture*> Textures;

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
    void NewFinalize(bool interleaved = true);

    void FromSDF(std::function<float(glm::vec3)>& sdf, float maxDistance, uint16_t gridResolution);

    void Bind();
    void UnBind();

private:

    void calculateNormals(bool smooth = true);
    void calculateTangents();

    void ComputeBoundingSphere();
};