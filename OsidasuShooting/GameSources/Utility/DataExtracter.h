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

	/**
	 * @brief ������̔z�񂩂�e��f�[�^�𒊏o����N���X
	 */
	struct DataExtracter {
		/**
		 * @brief 1�s��CSV�f�[�^��z��Ɋi�[
		 *
		 * @param line 1�s��CSV�f�[�^
		 * @return �z��
		 */
		static vector<wstring> DelimitData(const wstring& line, wchar_t delimiter = L',') {
			vector<wstring> tokens;
			Util::WStrToTokenVector(tokens, line, delimiter);
			return tokens;
		}

		/**
		 * @brief �g�����X�t�H�[���f�[�^�𒊏o
		 *
		 * @param tokens ������
		 * @param firstIndex �ŏ��̃C���f�b�N�X�i�f�t�H���g�F1�j
		 * @return �g�����X�t�H�[���f�[�^
		 */
		static TransformData TransformDataExtraction(const vector<wstring>& tokens, size_t firstIndex = 1) {
			TransformData data;
			data.Position = Vec3(
				(float)_wtof(tokens[firstIndex].c_str()),
				(float)_wtof(tokens[firstIndex + 1].c_str()),
				(float)_wtof(tokens[firstIndex + 2].c_str())
			);
			data.Scale = Vec3(
				(float)_wtof(tokens[firstIndex + 3].c_str()),
				(float)_wtof(tokens[firstIndex + 4].c_str()),
				(float)_wtof(tokens[firstIndex + 5].c_str())
			);
			data.Rotation = Vec3(
				XMConvertToRadians((float)_wtof(tokens[firstIndex + 6].c_str())),
				XMConvertToRadians((float)_wtof(tokens[firstIndex + 7].c_str())),
				XMConvertToRadians((float)_wtof(tokens[firstIndex + 8].c_str()))
			);
			return data;
		}

		/**
		 * @brief �J���[�f�[�^�𒊏o
		 *
		 * @param tokens ������
		 * @return �J���[�f�[�^
		 */
		static Col4 ColorDataExtraction(const vector<wstring>& tokens)
		{
			Col4 color;
			color = Col4(
				(float)_wtof(tokens[0].c_str()),
				(float)_wtof(tokens[1].c_str()),
				(float)_wtof(tokens[2].c_str()),
				(float)_wtof(tokens[3].c_str())
			);
			return color;
		};
	};
}
