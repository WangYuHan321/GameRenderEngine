#pragma once

#include "../../Util/common.h"

enum class DEPTH_TEST_MODE { NONE, LARGE, LARGE_EQUAL, EQUAL, LESS_EQUAL,LESS, NOT_EQUAL, NEVER, ALWAYS };

enum class STENCIL_TEST_MODE { NONE, };

enum class CULL_FACE_MODE { NONE, FRONT, BACK };

enum class PIPELINE_TYPE { GRAPHIC, COMPUTE };

enum class PIPELINE_FLAG { NONE, SHADOW, DEBUG_DRAW };

enum class PIXEL_FORMAT {
    UNKNOWN,
    R8,
    RG8,
    RGB8,
    RGBA8,
    R16,
    RG16,
    RGB16,
    RGBA16,
    R32,
    RG32,
    RGB32,
    RGBA32,
    R10G10B10A2,
    R5G6B5,
    D24R8,
    D32
};

enum class A2V_TYPES {
    A2V_TYPES_NONE,
    A2V_TYPES_FULL,
    A2V_TYPES_SIMPLE,
    A2V_TYPES_POS_ONLY,
    A2V_TYPES_CUBE
};

struct PipelineState
{
    std::string pipelineStateName;
    PIPELINE_TYPE pipelineType{ PIPELINE_TYPE::GRAPHIC };

    std::string vertexShaderName;
    std::string pixelShaderName;
    std::string computeShaderName;
    std::string geometryShaderName;
    std::string tessControlShaderName;
    std::string tessEvaluateShaderName;
    std::string meshShaderName;

    DEPTH_TEST_MODE depthTestMode{ DEPTH_TEST_MODE::ALWAYS };
    bool bDepthWrite{ true };
    STENCIL_TEST_MODE stencilTestMode{ STENCIL_TEST_MODE::NONE };
    CULL_FACE_MODE cullFaceMode{ CULL_FACE_MODE::BACK };
    PIXEL_FORMAT pixelFormat{ PIXEL_FORMAT::RGBA8 };
    uint32_t sampleCount{ 1 };

    A2V_TYPES a2vType{ A2V_TYPES::A2V_TYPES_NONE };
    PIPELINE_FLAG flag;

};

