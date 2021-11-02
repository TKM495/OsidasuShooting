/*!
@file   EfkEffect.h
@brief  Efk関係のヘッダー
*/

#pragma once
// ヘッダー
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <EffekseerSoundXAudio2.h>

// ライブラリ
#if _DEBUG
#pragma comment(lib, "Effekseerd.lib" )
#pragma comment(lib, "EffekseerRendererDX11d.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2d.lib" )
#else
#pragma comment(lib, "Effekseer.lib" )
#pragma comment(lib, "EffekseerRendererDX11.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.lib" )
#endif

// キー重複を防ぐための文字列
#define EfkKey L"_Efk"

#include "Effekseer/EfkInterface.h"
#include "Effekseer/EfkEffectResource.h"
#include "Effekseer/EfkComponent.h"
