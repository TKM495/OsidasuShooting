#pragma once
#include "stdafx.h"
#include "BaseUI.h"
#include "UIs/NumberSprite.h"
#include "UIs/SimpleSprite.h"
#include "UIEffect.h"
#include "Utility/TimeCounter.h"

namespace basecross {
	class StartCountDown :public BaseUI {
		// �i���o�[�I�u�W�F�N�g
		shared_ptr<Number> m_number;
		// �X�^�[�g���̃X�v���C�g
		shared_ptr<SimpleSprite> m_startSprite;
		// �G�t�F�N�g�I�u�W�F�N�g
		shared_ptr<UIEffect> m_uiEffect;
		// �X�^�[�g���̃J�E���g�_�E���^�C�}�[
		TimeCounter m_countDownTimer;
		// �X�^�[�g�����̕\���^�C�}�[
		TimeCounter m_startDisplayTimer;
		// �i���o�[�̃I�t�Z�b�g�ʒu
		Vec3 m_offsetPos;
		int m_lastValue;
	public:
		StartCountDown(const shared_ptr<Stage>& stage,
			const TransformData& data)
			:BaseUI(stage, data),
			m_countDownTimer(3.0f),
			m_startDisplayTimer(1.0f),
			m_offsetPos(Vec3(-32.0f, 64.0f, 0.0f)),
			m_lastValue(0)
		{}

		void OnCreate()override;
		void OnUpdate()override;
		void OnDraw()override;

		TimeCounter GetTimer()const {
			return m_countDownTimer;
		}
	};

	class FinishSprite :public BaseUI {
		shared_ptr<SimpleSprite> m_finishSprite;
		// �G�t�F�N�g�I�u�W�F�N�g
		shared_ptr<UIEffect> m_uiEffect;
	public:
		FinishSprite(const shared_ptr<Stage>& stage,
			const TransformData& data)
			:BaseUI(stage, data)
		{}

		void OnCreate()override;
		void OnUpdate()override;
		void OnDraw()override;
	};
}
