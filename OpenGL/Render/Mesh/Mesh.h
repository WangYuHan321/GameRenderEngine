#pragma once
#include <functional>
#include <glm/glm.hpp>
#include <vector>
#include "../Shader/Texture.h"
#include "../Bounding/BoundingSphere.h"
#include "../../Render/Mesh/Material.h"

#define MAX_BONE_INFLUENCE 4

//#define DIFFUSE_TEXTURE "texture_diffuse"
//#define SPECULAR_TEXTURE "texture_specular"
//#define NORMAL_TEXTURE "texture_normal"
//#define AMBIENT_TEXTURE "texture_ambient"

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
    std::string m_strName = "";
    
    std::vector<Vector3> m_vecPos;
    std::vector<Vector2> m_vecUV;
    std::vector<Vector3> m_vecNormal;
    std::vector<Vector3> m_vecTangent;
    std::vector<Vector3> m_vecBitangent;
    
    std::vector<Vertex> m_vecVertex;
    MaterialProperties m_materialProperty;

    uint32 m_materialIndex;
    BoundingSphere m_boundingSphere;

    TOPOLOGY m_topology = TOPOLOGY::TRIANGLES;
    std::vector<uint32> m_vecIndices;
    std::map<string, Texture*> m_vecTextures;

    Mesh();
    ~Mesh();
    Mesh(std::vector<Vector3> positions, std::vector<uint32> indices);
    Mesh(std::vector<Vector3> positions, std::vector<Vector2> uv, std::vector<uint32> indices);
    Mesh(std::vector<Vector3> positions, std::vector<Vector2> uv, std::vector<Vector3> normals, std::vector<uint32> indices);
    Mesh(std::vector<Vector3> positions, std::vector<Vector2> uv, std::vector<Vector3> normals, std::vector<Vector3> tangents, std::vector<Vector3> bitangents, std::vector<uint32> indices);

    void SetPositions(std::vector<Vector3> positions);
    void SetUVs(std::vector<Vector2> uv);
    void SetNormals(std::vector<Vector3> normals);
    void SetTangents(std::vector<Vector3> tangents, std::vector<Vector3> bitangents); // NOTE(Joey): you can only set both tangents and bitangents at the same time to prevent mismatches

    void SetName(string name);
    void SetTopology(TOPOLOGY topology);
    void SetMaterialIndex(uint32 materialIndex);
    TOPOLOGY GetTopology() { return m_topology; }

    void Finalize(bool interleaved = true);
    void NewFinalize(bool interleaved = true);

    void FromSDF(std::function<float(Vector3)>& sdf, float maxDistance, uint16_t gridResolution);

    void Bind();
    void UnBind();

private:

    void calculateNormals(bool smooth = true);
    void calculateTangents();

    void ComputeBoundingSphere();
};