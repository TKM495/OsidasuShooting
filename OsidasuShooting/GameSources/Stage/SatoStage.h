/*!
@file   SatoStage.h
@brief
*/

#pragma once
#include "stdafx.h"
#include "JonyMd/CountDown.h"
#include "UIs/ResultScore.h"

namespace basecross {
	class SatoStage : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		SatoStage() :Stage() {}
		virtual ~SatoStage() {}
		//初期化

		//void SetPlayer();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		
		void AddWinnerSprite();
		void AddResultSprites(Vec3 pos, int playerNum, int score);

		void JMDSeitchSystem()
		{

			const auto& app = App::GetApp();
			const auto& keyState = app->GetInputDevice().GetKeyState();
			if (keyState.m_bPressedKeyTbl['W']) {
				GetSharedGameObject<CountDown>(L"CountDown")->Start();
			}
			if (keyState.m_bPressedKeyTbl['S']) {
				GetSharedGameObject<CountDown>(L"CountDown")->Stop();
			}
			if (keyState.m_bPressedKeyTbl['R']) {
				GetSharedGameObject<CountDown>(L"CountDown")->Reset();
			}



			if (keyState.m_bPressedKeyTbl['A']) {
				GetSharedGameObject<CountDown>(L"CountDown")->Adjust(5);
			}
			if (keyState.m_bPressedKeyTbl['M']) {
				GetSharedGameObject<CountDown>(L"CountDown")->Adjust(-5);
			}		
		}

		shared_ptr<CountDown> m_timer;
		shared_ptr<ResultScore> m_score;

		void BattlePlayerUISet(int value);

	};
}
