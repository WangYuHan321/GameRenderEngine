#pragma once

class ResourceJob
{
public:
	enum //����״̬
	{
		LS_PENDING,//�ȴ���
		LS_LOADED,//���غ�
		LS_FAIL, // error
	};

	enum //��������
	{
		JT_TEXTURE,
		JT_MATERIAL,
		JT_ANIM,
		JT_ACTOR,
		JT_MODEL,
		JT_FONT,
	};
	enum //����״̬
	{
		JS_NONE,
		JS_DELETE,
	};

	ResourceJob();

};