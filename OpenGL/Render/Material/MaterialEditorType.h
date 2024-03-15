#include <gl/glew.h>


enum class DepthFunc
{
	OpenGL_LESS = 0x0201,
	OpenGL_NEVER = 0x0200,
	OpenGL_EQUAL = 0x0202,
	OpenGL_GREATER = 0x0204,
	OpenGL_NOTEQUAL = 0x0205,
	OpenGL_GEQUAL = 0x0206,
	OpenGL_ALWAYS = 0x0207
};

enum class BlendParam
{
	OpenGL_ZERO = 0,
	OpenGL_ONE = 1,
	OpenGL_SRC_COLOR = 0x0300,
	OpenGL_ONE_MINUS_SRC_COLOR = 0x0301,//(1, 1, 1, 1)−(RskR, GskG, BskB, AskA)
	OpenGL_DST_COLOR = 0x0306, //(RdkR, GdkG, BdkB, AdkA)
	OpenGL_ONE_MINUS_DST_COLOR = 0x0307,//(1, 1, 1, 1)−(RdkR, GdkG, BdkB, AdkA)
	OpenGL_SRC_ALPHA = 0x0302,//(AskA, AskA, AskA, AskA)
	OpenGL_ONE_MINUS_SRC_ALPHA = 0x0303,// (1, 1, 1, 1)−(AskA, AskA, AskA, AskA)
	OpenGL_DST_ALPHA = 0x0304,//(AdkA, AdkA, AdkA, AdkA)
	OpenGL_ONE_MINUS_DST_ALPHA = 0x0305,//(1, 1, 1, 1)−(AdkA, AdkA, AdkA, AdkA)
	OpenGL_CONSTANT_COLOR = 0x8001,//(Rc, Gc, Bc, Ac)
	OpenGL_ONE_MINUS_CONSTANT_COLOR = 0x8002,//(1, 1, 1, 1)−(Rc, Gc, Bc, Ac)
	OpenGL_CONSTANT_ALPHA = 0x8003,//(Ac, Ac, Ac, Ac)
	OpenGL_ONE_MINUS_CONSTANT_ALPHA = 0x8004,//(1, 1, 1, 1)−(Ac, Ac, Ac, Ac)
	OpenGL_SRC_ALPHA_SATURATE = 0x0308,
};

enum class BlendFunc
{
	OpenGL_FUNC_ADD = 0x8006,	//Rr = RssR + RddR Gr = GssG + GddG Br = BssB + BddB	Ar = AssA + AddA
	OpenGL_FUNC_SUBTRACT = 0x800A,	//Rr = RssR−RddR Gr = GssG−GddG Br = BssB−BddB	Ar = AssA−AddA
	OpenGL_FUNC_REVERSE_SUBTRACT = 0x800B,	//Rr = RddR−RssR Gr = GddG−GssG Br = BddB−BssB	Ar = AddA−AssA
	OpenGL_MIN = 0x8007,	//Rr = min(Rs, Rd) Gr = min(Gs, Gd) Br = min(Bs, Bd)	Ar = min(As, Ad)
	OpenGL_MAX = 0x8008,	//Rr = max(Rs, Rd) Gr = max(Gs, Gd) Br = max(Bs, Bd)	Ar = max(As, Ad)
};

enum class CullFace
{
	OpenGL_FRONT = 0x0404,
	OpenGL_BACK = 0x0405,
	OpenGL_FRONT_AND_BACKT = 0x0408,
};

enum class FrontFace
{
	OpenGL_CW = 0x0900,
	OpenGL_CCW = 0x0901,
};



