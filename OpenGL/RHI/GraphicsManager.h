#pragma once
class GraphicsManager
{
public:
	GraphicsManager();
	virtual ~GraphicsManager() {};


	virtual void SetPipeline() = 0;

};

