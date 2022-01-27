#pragma once
#include "stdafx.h"
#include "Utility/TimeCounter.h"

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
		int m_maxIndex;
	private:
		// 1片あたりの表示時間
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
