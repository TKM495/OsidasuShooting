/*!
@file LoadStage.h
@brief リソースのロードのためのステージ
*/

#pragma once
#include "stdafx.h"
#include "Utility/TimeCounter.h"

namespace basecross {
	class LoadStage :public Stage {
		enum class State {
			Loading,
			FadeOut
		};

		//カウンター（最小表示時間）
		TimeCounter m_timer;
		//ステート
		State m_state;

		void CreateViewLight();
		//リソースロード用のスレッド（スタティック関数）
		static void LoadResourceFunc();
		//リソースを読み込んだことを知らせるフラグ（スタティック変数）
		static bool m_Loaded;
		//ミューテックス
		static mutex mtx;
	public:
		LoadStage()
			:Stage(), m_state(State::Loading), m_timer(2.0f)
		{}
		~LoadStage() {}
		void OnCreate()override;
		void OnUpdate()override;
	};
}
//end basecross