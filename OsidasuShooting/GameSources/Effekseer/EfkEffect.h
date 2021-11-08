/*!
@file   EfkEffect.h
@brief  Efk�֌W�̃w�b�_�[
*/

#pragma once
// �w�b�_�[
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <EffekseerSoundXAudio2.h>

// ���C�u����
#if _DEBUG
#pragma comment(lib, "Effekseerd.lib" )
#pragma comment(lib, "EffekseerRendererDX11d.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2d.lib" )
#else
#pragma comment(lib, "Effekseer.lib" )
#pragma comment(lib, "EffekseerRendererDX11.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.lib" )
#endif

// �L�[�d����h�����߂̕�����
#define EfkKey L"_Efk"

#include "Effekseer/EfkInterface.h"
#include "Effekseer/EfkEffectResource.h"
#include "Effekseer/EfkComponent.h"

#include "DebugClass/Debug.h"
#include "Utility/Utility.h"
