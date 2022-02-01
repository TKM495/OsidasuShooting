#pragma once
#include "stdafx.h"
#include "BaseUI.h"
#include "UIs/NumberSprite.h"
#include "UIs/SimpleSprite.h"
#include "UIEffect.h"
#include "Utility/TimeCounter.h"

namespace basecross {
	class StartCountDown :public BaseUI {
		// ナンバーオブジェクト
		shared_ptr<Number> m_number;
		// スタート時のスプライト
		shared_ptr<SimpleSprite> m_startSprite;
		// エフェクトオブジェクト
		shared_ptr<UIEffect> m_uiEffect;
		// スタート時のカウントダウンタイマー
		TimeCounter m_countDownTimer;
		// スタート文字の表示タイマー
		TimeCounter m_startDisplayTimer;
		// ナンバーのオフセット位置
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
		// エフェクトオブジェクト
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
