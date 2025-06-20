#pragma once
#include "../../Util/common.h"
#include "../../Thread/Thread.h"

#ifdef WINDOWS_PLATFORM
	#include "../../Thread/WinThread.h"
#endif

class RenderCommand
{
public:
	RenderCommand() {}
	virtual ~RenderCommand() {}
	virtual uint32 Execute() = 0;
	virtual const char* DescribeCommand() = 0;
};

#define DECLARE_UNIQUE_RENDER_COMMAND(TypeName, Code) \
class TypeName : public RenderCommand \
{ \
	public:\
	TypeName(){} \
	~TypeName(){} \
	virtual uint32 Execute() \
	{\
		Code;\
		return sizeof(*this);\
	}\
	virtual const char* DescribeCommand()\
	{\
		return _T(#TypeName);\
	}\
};\

#define DECLARE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(TypeName, ParamType1, ParamName1, Code) \
class TypeName : public RenderCommand \
{ \
public:\
	typedef ParamType1 _ParamType1; \
	TypeName(){} \
	TypeName(const _ParamType1& In##ParamName1): \
	ParamName1(In##ParamName1) \
	~TypeName(){} \
	virtual uint32 Execute() \
	{\
		Code;\
		return sizeof(*this);\
	}\
	virtual const char* DescribeCommand()\
	{\
		return _T(#TypeName);\
	}\
private: \
	ParamType1 ParamName1; \
};\

#define DECLARE_UNIQUE_RENDER_COMMAND_TWOPARAMETER(TypeName, ParamType1, ParamName1, Code) \
class TypeName : public RenderCommand \
{ \
public:\
	typedef ParamType1 _ParamType1; \
	typedef ParamType2 _ParamType2; \
	TypeName(){} \
	TypeName(const _ParamType1& In##ParamName1, const _ParamType2& In##ParamName2): \
	ParamName1(In##ParamName1) \
	ParamName2(In##ParamName2) \
	{} \
	~TypeName(){} \
	virtual uint32 Execute() \
	{\
		Code;\
		return sizeof(*this);\
	}\
	virtual const char* DescribeCommand()\
	{\
		return _T(#TypeName);\
	}\
private: \
	ParamType1 ParamName1; \
	ParamType2 ParamName2; \
};\

#define DECLARE_UNIQUE_RENDER_COMMAND_THREEPARAMETER(TypeName, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, Code) \
class TypeName : public RenderCommand \
{ \
public:\
	typedef ParamType1 _ParamType1; \
	typedef ParamType2 _ParamType2; \
	typedef ParamType3 _ParamType3; \
	TypeName(){} \
	TypeName(const _ParamType1& In##ParamName1,const _ParamType2& In##ParamName2,const _ParamType3& In##ParamName3): \
	ParamName1(In##ParamName1) \
	ParamName2(In##ParamName2) \
	ParamName3(In##ParamName3) \
	{} \
	~TypeName(){} \
	virtual uint32 Execute() \
	{\
		Code;\
		return sizeof(*this);\
	}\
	virtual const char* DescribeCommand()\
	{\
		return _T(#TypeName);\
	}\
private: \
	ParamType1 ParamName1; \
	ParamType2 ParamName2; \
	ParamType3 ParamName3; \
};\
