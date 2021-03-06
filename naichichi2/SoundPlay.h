﻿#pragma once

#ifdef _MSC_VER
#else
#include <alsa/asoundlib.h>
#endif

//音楽の再生.
class SoundPlay
{
public:
	SoundPlay();
	virtual ~SoundPlay();
	void Play(const string & filename);
private:
	void Init();
	void Free();
};
