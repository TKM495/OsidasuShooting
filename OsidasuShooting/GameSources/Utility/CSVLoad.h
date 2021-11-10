/*!
@file   CSVLoad.h
@brief  CSV����f�[�^�����o���N���X
 */

#pragma once
#include "stdafx.h"

namespace basecross {
	// �X�v���C�g�̃f�[�^�`��
	struct SpriteDataFormat {
		wstring name;	// ����
		Vec2 origin;	// ���_�̍��W
		Vec2 size;		// �T�C�Y
	};

	// �X�v���C�g�̃^�C�v
	enum class SpriteType {
		String,
		Image,
		Number
	};

	class CSVLoad :public GameObject {
		// �X�v���C�g�f�[�^�̔z��
		vector<SpriteDataFormat> m_stringSpriteData;
	public:
		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param stage �X�e�[�W
		 */
		CSVLoad(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		virtual void OnCreate()override;

		/**
		 * @brief �f�[�^�̎��o��
		 *
		 * @param fileData	�t�@�C���f�[�^
		 * @param type		�X�v���C�g�̃^�C�v
		 */
		void SpriteDataExtraction(vector<wstring> fileData, SpriteType type);

		/**
		 * @brief �X�v���C�g�f�[�^�̎擾
		 *
		 * @return �X�v���C�g�f�[�^
		 */
		vector<SpriteDataFormat>& GetStringSpriteData() {
			return m_stringSpriteData;
		}
	};
}
//end basecross