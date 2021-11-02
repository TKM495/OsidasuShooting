#include "stdafx.h"
#include "Effekseer/EfkEffect.h"

namespace basecross {
	EfkEffectResource::EfkEffectResource(const wstring& path)
		:m_filePath(path)
	{
		if (m_filePath == L"") {
			throw BaseException(
				L"�G�t�F�N�g�t�@�C�������󔒂ł��B",
				L"if (m_filePath == L\"\")",
				L"EfkEffect::EfkEffect()"
			);
		}
		auto iface = EfkInterface::GetInstance();
		// �G�t�F�N�g�̓ǂݍ���
		m_effect = Effect::Create(iface->GetManager(), (const char16_t*)m_filePath.c_str());

		if (m_effect == nullptr) {
			// �����ŗ�O���o���ƂȂ���������
			throw BaseException(
				L"�G�t�F�N�g�̐����Ɏ��s���܂����B",
				L"if (m_Effect == nullptr)",
				L"EfkEffect::EfkEffect()"
			);
		}
	}

	shared_ptr<EfkEffectResource> EfkEffectResource::RegisterEffectResource(const wstring& key, const wstring& filePath) {
		const auto& app = App::GetApp();
		if (app->CheckResource<EfkEffectResource>(key)) {
			return app->GetResource<EfkEffectResource>(key);
		}
		//
		auto effectPtr = ObjectFactory::Create<EfkEffectResource>(filePath);
		app->RegisterResource(key, effectPtr);
		return effectPtr;
	}
}