#pragma once
#include "stdafx.h"
#include "Utility/BaseSingleton.h"

namespace basecross {
	class XMLLoad :public BaseSingleton<XMLLoad> {
	private:
		XMLLoad() :BaseSingleton() {}
		~XMLLoad() {}
		friend class BaseSingleton<XMLLoad>;
	private:
		// �f�[�^�i�L�[,�f�[�^�j
		map<wstring, shared_ptr<XmlDocReader>> m_data;
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
		shared_ptr<XmlDocReader> GetData(const wstring& key)const;
	};

	struct XMLHelper {
		static wstring GetSingleNodeWString(const shared_ptr<XmlDocReader>& reader, const wstring nodeText);
	};
}
