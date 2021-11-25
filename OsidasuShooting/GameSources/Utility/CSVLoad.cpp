/*!
@file   CSVLoad.cpp
@brief  CSV�̃f�[�^���Ǘ�����N���X����
 */

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// �C���X�^���X�̏�����
	unique_ptr<CSVLoad, CSVLoad::Deleter> CSVLoad::m_instance = nullptr;

	void CSVLoad::RegisterFile(const wstring& key, const wstring& filePath) {
		CsvFile csvFile;
		csvFile.SetFileName(filePath);
		csvFile.ReadCsv();
		m_data[key] = csvFile.GetCsvVec();
	}

	vector<wstring> CSVLoad::GetData(const wstring& key)const {
		return m_data.at(key);
	}

	bool CSVLoad::CheckData(const wstring& key) {
		return m_data.count(key) != 0;
	}
}
//end basecross