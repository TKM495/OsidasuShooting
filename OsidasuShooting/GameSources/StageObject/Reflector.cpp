/*!
@file   Reflector.cpp
@brief	リフレクターブロッククラスの実態
*/

#include "stdafx.h"
#include "Reflector.h"

namespace basecross {
	Reflector::Reflector(
		const shared_ptr<Stage>& stage,
		const TransformData transformData,
		const wstring& line
	):
		Block(stage, transformData)
	{
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
		m_transformData.Position = Vec3(
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str()),
			(float)_wtof(tokens[3].c_str())
		);
		m_transformData.Scale = Vec3(
			(float)_wtof(tokens[4].c_str()),
			(float)_wtof(tokens[5].c_str()),
			(float)_wtof(tokens[6].c_str())
		);
		m_transformData.Rotation = Vec3(
			XMConvertToRadians((float)_wtof(tokens[7].c_str())),
			XMConvertToRadians((float)_wtof(tokens[8].c_str())),
			XMConvertToRadians((float)_wtof(tokens[9].c_str()))
		);
	}

	void Reflector::OnCreate() {

	}

	void Reflector::OnUpdate() {

	}
}