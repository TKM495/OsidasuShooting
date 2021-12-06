#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// インスタンスの初期化
	unique_ptr<XMLLoad, XMLLoad::Deleter> XMLLoad::m_instance = nullptr;

	void XMLLoad::RegisterFile(const wstring& key, const wstring& filePath) {
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		//XMLの読み込み
		auto ptr = shared_ptr<XmlDocReader>(new XmlDocReader(filePath));
		m_data[key] = ptr;
	}

	shared_ptr<XmlDocReader> XMLLoad::GetData(const wstring& key) const {
		return m_data.at(key);
	}
}