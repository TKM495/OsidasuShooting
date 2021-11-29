#pragma once
#include "stdafx.h"
#include "UIs/NumberSprite.h"

namespace basecross {
	class ResultScore : public GameObject {
	private:
		vector<std::shared_ptr<Number>> m_numbers;

		//OffSet
		int m_playerScore;				// プレイヤーの得点
		Vec3 m_setOffset;				// 一文字目のオブジェクト
		Vec3 m_addOffset;				// 一文字の大きさ
		Vec3 m_spaceOffset;				// 分と秒で分けるときのスペース
		Vec3 m_posOffset;				// オフセット

		float m_scaleValue;				// スケール
		Vec3 m_scaleOffset;				// スケールオフセット

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