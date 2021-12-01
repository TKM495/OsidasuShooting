#pragma once
#include "stdafx.h"
#include "BaseUI.h"
#include "UIs/NumberSprite.h"
#include "UIs/SimpleSprite.h"
#include "Utility/TimeCounter.h"

namespace basecross {
	class StartCountDown :public BaseUI {
		// �i���o�[�I�u�W�F�N�g
		shared_ptr<Number> m_number;
		// �X�^�[�g���̃X�v���C�g
		shared_ptr<SimpleSprite> m_startSprite;
		// �X�^�[�g���̃J�E���g�_�E���^�C�}�[
		TimeCounter m_countDownTimer;
	public:
		StartCountDown(const shared_ptr<Stage>& stage,
			const TransformData& data)
			:BaseUI(stage, data), m_countDownTimer(3.0f)
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
