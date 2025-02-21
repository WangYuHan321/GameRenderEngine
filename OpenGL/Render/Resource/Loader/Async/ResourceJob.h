#pragma once

class ResourceJob
{
public:
	enum //加载状态
	{
		LS_PENDING,//等待中
		LS_LOADED,//加载好
		LS_FAIL, // error
	};

	enum //任务类型
	{
		JT_TEXTURE,
		JT_MATERIAL,
		JT_ANIM,
		JT_ACTOR,
		JT_MODEL,
		JT_FONT,
	};
	enum //任务状态
	{
		JS_NONE,
		JS_DELETE,
	};

	ResourceJob();

};