/*!
@file   MoveBlock.h
@brief	リフレクターブロッククラス
*/
#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"

namespace basecross {
	class MoveBlock : public AdvancedGameObject {
	public:
		// ブロックの種類
		enum class BlockType {
			Normal,
			Bumper,
			Reflector
		};
	private:
		// 移動関連
			// 往復するポジション
		Vec3 m_startPosition;
		Vec3 m_markPosition;
		//// 往復する基準
		//bool m_posXorZ;
		// 2点の差
		Vec3 m_moveRoot;
		// 移動
		float m_totalTime;
		// 到着してからの待機時間
		float m_waitTime;
		// 待機中
		bool m_isWait;
		// 進むか戻るか
		bool m_isGotoMarkPos;

		// その他項目
			// 設置場所
		Vec3 m_setPosition;

		// ブロックのタイプ
		BlockType m_type;
		// ブロックのオブジェクト
		shared_ptr<AdvancedGameObject> m_block;
		// 移動速度
		float m_moveSpeed;
		// 待機時間
		float m_latency;
	public:
		MoveBlock(
			shared_ptr<Stage>& stage,
			const TransformData transformData,
			const Vec3 markPosition,
			BlockType type//,
			//const bool posXorZ
		) :
			AdvancedGameObject(stage),
			// 移動関連
			m_markPosition(markPosition),
			m_moveRoot(0),
			m_totalTime(0),
			m_waitTime(0),
			m_isWait(false),
			m_isGotoMarkPos(false),
			// その他項目
			m_setPosition(0),
			m_type(type),
			m_moveSpeed(1.0f),
			m_latency(1.0f)
		{
			m_transformData = transformData;
		}

		MoveBlock(const shared_ptr<Stage>& stage,
			const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;

		void MovingBlock();
		void MoveSwitch();
	};
}