/*!
@file   MoveBlock.h
@brief	リフレクターブロッククラス
*/
#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"

namespace basecross {
	class MoveBlock : public AdvancedGameObject {
		// 起動中
			// 起動中かどうか
		bool m_isSetUp;

		// 移動関連
			// 往復するポジション
		Vec3 m_startPosition;
		Vec3 m_markPosition;
		//// 往復する基準
		//bool m_posXorZ;
		// 2点の差
		Vec3 m_moveRoot;
		// 到着してからの待機時間
		float m_waitTime;
		// 待機中
		bool m_isWait;
		// 進むか戻るか
		bool m_isReturnBlock;

		// その他項目
			// 設置場所
		Vec3 m_setPosition;

	public:
		MoveBlock(
			shared_ptr<Stage>& stage,
			const TransformData transformData,
			const Vec3 markPosition//,
			//const bool posXorZ
		) :
			AdvancedGameObject(stage),
			// 起動中
			m_isSetUp(false),
			// 移動関連
			m_markPosition(markPosition),
			m_moveRoot(0),
			m_waitTime(0),
			m_isWait(false),
			m_isReturnBlock(false),
			// その他項目
			m_setPosition(0)
		{
			m_transformData = transformData;
		}

		MoveBlock(const shared_ptr<Stage>& stage,
			const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;

		void SetUpAnimation();
		void MovingBlock();
	};
}