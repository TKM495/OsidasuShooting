/*!
@file   Block.h
@brief  ブロッククラス
*/

#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"

namespace basecross {
	class Block :public AdvancedGameObject {
	public:
		// 手動追加用コンストラクタ
		Block(const shared_ptr<Stage>& stage, const TransformData& transData)
			:AdvancedGameObject(stage)
		{
			m_transformData = transData;
		}
		// オブジェクトビルダー用のコンストラクタ
		Block(const shared_ptr<Stage>& stage, const wstring& line);

		void OnCreate()override;
	};

	class Bumper :public AdvancedGameObject {
		bool m_isAnimation;
	public:
		// 手動追加用コンストラクタ
		Bumper(const shared_ptr<Stage>& stage, const TransformData& transData)
			:AdvancedGameObject(stage), m_isAnimation(false)
		{
			m_transformData = transData;
		}
		// オブジェクトビルダー用のコンストラクタ
		Bumper(const shared_ptr<Stage>& stage, const wstring& line);

		void OnCreate()override;
		void OnUpdate()override;

		void PlayAnimation();
	};
}
