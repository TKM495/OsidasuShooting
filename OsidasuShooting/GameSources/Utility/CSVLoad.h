/*!
@file   CSVLoad.h
@brief  CSV�̃f�[�^���Ǘ�����N���X
 */

#pragma once
#include "stdafx.h"
#include "Utility/BaseSingleton.h"

namespace basecross {
	// �V���O���g��
	class CSVLoad :public BaseSingleton<CSVLoad> {
	private:
		CSVLoad() {}
		~CSVLoad() {}
		friend class BaseSingleton<CSVLoad>;
	private:
		// �f�[�^�i�L�[,�f�[�^�j
		map<wstring, vector<wstring>> m_data;
	public:
		/**
		 * @brief �t�@�C����o�^����
		 *
		 * @param key �L�[
		 * @param filePath �t�@�C���p�X
		 */
		void RegisterFile(const wstring& key, const wstring& filePath);

		/**
		 * @brief �f�[�^���擾����
		 *
		 * @param key �L�[
		 * @return �L�[�ɕR�Â��Ă���f�[�^
		 */
		vector<wstring> GetData(const wstring& key)const;

		/**
		 * @brief �L�[�����݂��邩
		 *
		 * @param key �L�[
		 * @return ���łɑ��݂��Ă���ꍇtrue
		 */
		bool CheckData(const wstring& key);
	};
}
//end basecross