#pragma once
#include "stdafx.h"
#include "Effekseer/EfkEffect.h"

namespace basecross {
	class EfkEffectResource :public BaseResource {
		wstring m_filePath;
		EffectRef m_effect;
	public:
		EfkEffectResource(const wstring& path);

		wstring GetEffectFilePath()const {
			return m_filePath;
		}
		EffectRef GetEffectData()const {
			return m_effect;
		}
		static shared_ptr<EfkEffectResource> RegisterEffectResource(
			const wstring& key, const wstring& filePath);
	};
}
