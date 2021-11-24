#pragma once
#include "stdafx.h"
#include "StageObject/AdvancedGameObject.h"

namespace basecross {
	// �X�v���C�g�̃f�[�^�`��
	struct SpriteDataFormat {
		wstring name;	// ����
		Vec2 origin;	// ���_�̍��W
		Vec2 size;		// �T�C�Y
	};

	struct Extracter {
		/**
		 * @brief 1�s��CSV�f�[�^��z��Ɋi�[
		 *
		 * @param line 1�s��CSV�f�[�^
		 * @return �z��
		 */
		static vector<wstring> DelimitData(const wstring& line) {
			vector<wstring> tokens;
			Util::WStrToTokenVector(tokens, line, L',');
			return tokens;
		}

		/**
		 * @brief �g�����X�t�H�[���f�[�^�𒊏o
		 *
		 * @param tokens
		 * @return
		 */
		static TransformData TransformDataExtraction(const vector<wstring>& tokens) {
			TransformData data;
			data.Position = Vec3(
				(float)_wtof(tokens[1].c_str()),
				(float)_wtof(tokens[2].c_str()),
				(float)_wtof(tokens[3].c_str())
			);
			data.Scale = Vec3(
				(float)_wtof(tokens[4].c_str()),
				(float)_wtof(tokens[5].c_str()),
				(float)_wtof(tokens[6].c_str())
			);
			data.Rotation = Vec3(
				XMConvertToRadians((float)_wtof(tokens[7].c_str())),
				XMConvertToRadians((float)_wtof(tokens[8].c_str())),
				XMConvertToRadians((float)_wtof(tokens[9].c_str()))
			);
			return data;
		}
	};
}
