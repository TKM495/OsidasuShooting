#pragma once
#include "stdafx.h"
#include "UIs/NumberSprite.h"

namespace basecross {
	class ResultScore : public GameObject {
	private:
		vector<std::shared_ptr<Number>> m_numbers;

		//OffSet
		int m_playerScore;				// �v���C���[�̓��_
		Vec3 m_setOffset;				// �ꕶ���ڂ̃I�u�W�F�N�g
		Vec3 m_addOffset;				// �ꕶ���̑傫��
		Vec3 m_spaceOffset;				// ���ƕb�ŕ�����Ƃ��̃X�y�[�X
		Vec3 m_posOffset;				// �I�t�Z�b�g

		float m_scaleValue;				// �X�P�[��
		Vec3 m_scaleOffset;				// �X�P�[���I�t�Z�b�g

	public:
		ResultScore(
			const shared_ptr<Stage>& stage,
			int score,
			Vec3 pos
			):
			GameObject(stage),
			m_playerScore(score),
			m_setOffset(pos),
			m_addOffset(),
			m_spaceOffset(),
			m_posOffset(),

			m_scaleValue(),
			m_scaleOffset()
		{}

		void OnCreate() override;
		void OnUpdate() {};
		void OnDraw() override;

		void NumbersDrawSpriteCreate();
	};
}