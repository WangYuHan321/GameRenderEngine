#pragma once
#include "../GraphicsManager.h"

class OpenGLGraphicsManager : public GraphicsManager
{
public:
	OpenGLGraphicsManager();
	~OpenGLGraphicsManager();

public:

	void SetPipeline() override;
};

