#include "DebugScreenQuad.h"
DebugScreenQuad::DebugScreenQuad(float cellXSize, float cellYSize):
    cellXSizeValue(2.0f / cellXSize),
    cellYSizeValue(2.0f / cellYSize)
{
    //the 2.0f beacuse of Screen Range (-1.0f, 1.0f)
}

void DebugScreenQuad::FinalizeMesh(int index)
{

    Positions =
    {
        { -1.0f + index * cellXSizeValue,  -cellYSizeValue, 0.0f, },
        { -1.0f + index * cellXSizeValue, -1.0f, 0.0f, },
        {  -1.0f + index * cellXSizeValue + cellXSizeValue,  -cellYSizeValue, 0.0f, },
        {  -1.0f + index * cellXSizeValue + cellXSizeValue, -1.0f, 0.0f, },
    };

    UV = {
        { 0.0f, 1.0f, },
        { 0.0f, 0.0f, },
        { 1.0f, 1.0f, },
        { 1.0f, 0.0f, },
    };

    Topology = TRIANGLE_STRIP;

    Finalize();
}

