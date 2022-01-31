/*!
@file ColorOut.h
@brief ブラックアウトなどのクラス
*/

#pragma once
#include "stdafx.h"
#include "BaseUI.h"

namespace basecross {
	class ColorOut :public BaseUI {
		//色
		Col4 m_color;
		//最大透過率
		float m_max;
		//最小透過率
		float m_min;
		//速度
		float m_rate;
		//時間計測用
		float m_delta;

		bool RangeCheck(float max, float min);
	public:
		ColorOut(const shared_ptr<Stage>& stage,
			const Col4& color = Col4(1.0f),
			float max = 1.0f, float min = 0.0f, float rate = 1.0f)
			:BaseUI(stage, TransformData()),
			m_color(color), m_max(max), m_min(min), m_rate(rate),
			m_delta(0.0f)
		{
			RangeCheck(m_max, m_min);
		}

		void OnCreate()override;
		void OnUpdate()override;
		void Reset() {
			m_delta = 0.0f;
		}
		void SetColor(Col4 color) {
			m_color = color;
		}
		void SetRange(float max, float min);
		void SetRate(float rate) {
			m_rate = rate;
		}
		void SetActive(bool flg) {
			SetUpdateActive(flg);
			SetDrawActive(flg);
		}
	};
}
//end basecross
