#pragma once
#include "stdafx.h"
#include "Effekseer/EfkEffect.h"

namespace basecross {
	/**
	 * @brief .efk�t�@�C���̃f�[�^�N���X
	 */
	class EfkEffectResource :public BaseResource {
		// �t�@�C���p�X
		wstring m_filePath;
		// �G�t�F�N�g�f�[�^�̃|�C���^
		Effekseer::EffectRef m_effect;
	public:
		EfkEffectResource(const wstring& path);

		/**
		 * @brief �G�t�F�N�g�f�[�^�̃t�@�C���p�X���擾
		 *
		 * @return �t�@�C���p�X
		 */
		wstring GetEffectFilePath()const {
			return m_filePath;
		}

		/**
		 * @brief �G�t�F�N�g�f�[�^���擾
		 *
		 * @return �G�t�F�N�g�f�[�^�̃|�C���^
		 */
		Effekseer::EffectRef GetEffectData()const {
			return m_effect;
		}

		/**
		 * @brief �G�t�F�N�g�f�[�^��o�^
		 *
		 * @param key		���ʗp�L�[
		 * @param filePath	�t�@�C���p�X
		 * @return �f�[�^�N���X�̃|�C���^
		 */
		static shared_ptr<EfkEffectResource> RegisterEffectResource(
			const wstring& key, const wstring& filePath);
	};
}
