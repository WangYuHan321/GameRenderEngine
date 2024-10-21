#include "Quad.h"

Quad::Quad()
{
    m_vecPos =
    {
        { -1.0f,  1.0f, 0.0f, },
        { -1.0f, -1.0f, 0.0f, },
        {  1.0f,  1.0f, 0.0f, },
        {  1.0f, -1.0f, 0.0f, },
    };
    m_vecUV = {
    { 0.0f, 1.0f, },
    { 0.0f, 0.0f, },
    { 1.0f, 1.0f, },
    { 1.0f, 0.0f, },
         };
    m_topology = TRIANGLE_STRIP;

    Finalize();
}

Quad::Quad(float width, float height)
{
    m_vecPos =
    {
            { -width,  height, 0.0f, },
            { -width, -height, 0.0f, },
            {  width,  height, 0.0f, },
            {  width, -height, 0.0f, },
    };
    m_vecUV = {
        { 0.0f, 1.0f, },
        { 0.0f, 0.0f, },
        { 1.0f, 1.0f, },
        { 1.0f, 0.0f, },
    };
    m_topology = TRIANGLE_STRIP;

    Finalize();
}

//void Quad::Finalize()
//{
//
//    glGenVertexArrays(1, &m_VAO);
//    glGenBuffers(1, &m_VBO);
//    glGenBuffers(1, &m_EBO);
//    
//    std::vector<float> data;
//
//    for (int i = 0; i < Positions.size(); i++)
//    {
//        data.push_back(Positions[i].x);
//        data.push_back(Positions[i].y);
//        data.push_back(Positions[i].z);
//        data.push_back(UV[i].x);
//        data.push_back(UV[i].y);
//    }
//
//    glBindVertexArray(m_VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data, GL_STATIC_DRAW);
//
//    size_t stride = 3 * sizeof(float);
//    if (UV.size() > 0)         stride += 2 * sizeof(float);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*) (3 * sizeof(float)));
//
//    glBindVertexArray(0);
//}

