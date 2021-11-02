#pragma once
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <EffekseerSoundXAudio2.h>

#if _DEBUG
#pragma comment(lib, "Effekseerd.lib" )
#pragma comment(lib, "EffekseerRendererDX11d.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2d.lib" )
#else
#pragma comment(lib, "Effekseer.lib" )
#pragma comment(lib, "EffekseerRendererDX11.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.lib" )
#endif

using namespace Effekseer;

#include "Effekseer/EfkInterface.h"
#include "Effekseer/EfkEffectResource.h"
#include "Effekseer/EfkComponent.h"

#include "DebugClass/Debug.h"
