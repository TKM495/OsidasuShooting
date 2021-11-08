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
				L"EfkEffectResource::EfkEffectResource()"
			);
		}
		// �C���^�[�t�F�C�X�̃C���X�^���X���擾
		auto iface = EfkInterface::GetInstance();
		// �G�t�F�N�g�̓ǂݍ���
		m_effect = Effekseer::Effect::Create(iface->GetManager(), (const char16_t*)m_filePath.c_str());

		// ���s�����ꍇ
		if (m_effect == nullptr) {
			throw BaseException(
				L"�G�t�F�N�g�̐����Ɏ��s���܂����B",
				L"if (m_effect == nullptr)",
				L"EfkEffectResource::EfkEffectResource()"
			);
		}
	}

	shared_ptr<EfkEffectResource> EfkEffectResource::RegisterEffectResource(const wstring& key, const wstring& filePath) {
		const auto& app = App::GetApp();
		// ���łɑ��݂���ꍇ�͊����̃|�C���^��Ԃ�
		if (app->CheckResource<EfkEffectResource>(key + EfkKey)) {
			return app->GetResource<EfkEffectResource>(key + EfkKey);
		}
		auto effectPtr = ObjectFactory::Create<EfkEffectResource>(filePath);
		app->RegisterResource(key + EfkKey, effectPtr);
		return effectPtr;
	}
}