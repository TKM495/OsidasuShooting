#pragma once
#include "stdafx.h"
#include "Utility/TimeCounter.h"
#include "Component/FadeComponent.h"

namespace basecross {
	class UIEffect :public BaseUI {
	private:
		// テスクスチャキー
		wstring m_textureKey;
		// タイマー
		TimeCounter m_timer;
		// 分割数
		Vec2 m_divisionCount;
		// 現在のピースインデックス
		int m_pieceIndex;
		// フレームレ－ト
		int m_frameRate;
		// 最大枚数
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
