#pragma once
#include "stdafx.h"
#include "Utility/TimeCounter.h"

namespace basecross {
	class UIEffect :public BaseUI {
	private:
		// �e�X�N�X�`���L�[
		wstring m_textureKey;
		// �^�C�}�[
		TimeCounter m_timer;
		// ������
		Vec2 m_divisionCount;
		// ���݂̃s�[�X�C���f�b�N�X
		int m_pieceIndex;
		// �t���[�����|�g
		int m_frameRate;
		int m_maxIndex;
	private:
		// 1�Ђ�����̕\������
		float m_displayTime;
		vector<VertexPositionColorTexture> vertices;
		Vec2 m_textureSize;
	public:
		UIEffect(const shared_ptr<Stage>& stage,
			const wstring& texKey, const Vec2& divisionCount, int maxPiece)
			:BaseUI(stage, TransformData()), m_textureKey(texKey),
			m_divisionCount(divisionCount), m_timer(1.0f), m_pieceIndex(0),
			m_frameRate(60), m_displayTime(1 / (float)60), m_maxIndex(maxPiece)
		{}

		void OnCreate()override;
		void OnUpdate()override;
	};
}
