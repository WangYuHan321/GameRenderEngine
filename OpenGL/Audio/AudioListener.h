#pragma once

#include "../Util/common.h"
#include "../Event/Event.h"

class AudioListener
{
public:
	AudioListener();

	AudioListener(FTransform& p_transform);

	~AudioListener();

	FTransform& GetTransform();

	void SetEnabled(bool p_enable);

	bool IsEnabled() const;

private:

	void SetUp();

private:

	FTransform* const m_transform;
	const bool m_internalTransform;
	bool m_enable = true;

public:
	static Event<AudioListener&> CreateEvent;
	static Event<AudioListener&> DestroyEvent;

};

