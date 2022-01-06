#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// �C���X�^���X�̏�����
	unique_ptr<PlayerStatus, PlayerStatus::Deleter> PlayerStatus::m_instance = nullptr;

	void PlayerStatus::DataExtraction() {
		// XML�̃f�[�^���擾
		auto xmlData = XMLLoad::GetInstance()->GetData(L"PlayerStatus");
		// �v���C���[�̐F�����擾
		auto data = XMLHelper::GetSingleNodeWString(xmlData, L"Player/PlayerColor");
		// 4�v���C���[���̐F���󔒂�4�̃f�[�^�ɕ�����
		auto colorStrVec = DataExtracter::DelimitData(data, L' ');
		for (int i = 0; i < 4; i++) {
			// ���g�̃v���C���[�ԍ��ɉ������F�f�[�^��RGBA�ɕ���
			auto colorStr = DataExtracter::DelimitData(colorStrVec[i]);
			// ���ނ������̂�Col4�ɕϊ�
			auto color = DataExtracter::ColorDataExtraction(colorStr);
			// 0�`1�ɕϊ�
			m_colorTable[PlayerNumber(i)] = Utility::ConvertColorZeroToOne(color);
		}
	}

	Col4 PlayerStatus::GetPlayerColor(PlayerNumber number) {
		return m_colorTable[number];
	}
	Col4 PlayerStatus::GetPlayerColor(int number) {
		return GetPlayerColor(PlayerNumber(number - 1));
	}
}