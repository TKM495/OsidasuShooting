#pragma once
#include "stdafx.h"
#include "Utility/TimeCounter.h"
#include "Component/FadeComponent.h"

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
		// �ő喇��
		int m_maxPiece;
		bool m_isLoop;
	private:
		vector<VertexPositionColorTexture> vertices;
		Vec2 m_textureSize;
	public:
		UIEffect(const shared_ptr<Stage>& stage,
			const wstring& texKey, const Vec2& divisionCount, int maxPiece)
			:BaseUI(stage, TransformData()), m_textureKey(texKey),
			m_divisionCount(divisionCount), m_timer(1.0f), m_pieceIndex(0),
			m_frameRate(60), m_maxPiece(maxPiece), m_isLoop(false)
		{}

		void OnCreate()override;
		void OnUpdate()override;

		void SetFrameRate(int rate) {
			m_frameRate = rate;
			m_timer.SetIntervalTime(m_maxPiece / (float)m_frameRate);
		}

		void IsLoop(bool flg) {
			m_isLoop = flg;
		}

		shared_ptr<FadeComponent> GetFadeComponent() {
			return GetComponent<FadeComponent>();
		}
	};
}
