/*!
@file   CSVLoad.h
@brief  CSV����f�[�^�����o���N���X
 */

#pragma once
#include "stdafx.h"
#include "Utility/BaseSingleton.h"

namespace basecross {
	class CSVLoad :public BaseSingleton<CSVLoad> {
	private:
		CSVLoad() {}
		~CSVLoad() {}
		friend class BaseSingleton<CSVLoad>;
	private:
		// �f�[�^
		map<wstring, vector<wstring>> m_data;
	public:
		/**
		 * @brief �t�@�C����o�^����
		 */
		void RegisterFile(const wstring& key, const wstring& filePath);
		/**
		 * @brief �f�[�^���擾����
		 */
		vector<wstring> GetData(const wstring& key)const;
	};
}
//end basecross