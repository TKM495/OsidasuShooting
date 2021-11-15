#pragma once
#include "stdafx.h"
#include "UIs/NumberSprite.h"

namespace basecross {

	class CountDown : public GameObject
	{
	private:
		bool start;
		bool reset;

		float initialTime; //秒の値です
		float currentTime;

		int m_timerNumbers;
		float m_timeCount;
		vector<std::shared_ptr<Number>> m_numbers;

		//OffSet
		int  m_numbersOffset;			// 分か秒か判別用
		bool m_isMinutes;				// 分か秒か
		Vec3 m_setOffset;				// 一文字目のオブジェクト
		Vec3 m_addOffset;				// 一文字の大きさ
		Vec3 m_spaceOffset;				// 分と秒で分けるときのスペース
		Vec3 m_posOffset;	// オッフセット

		float m_scaleValue;				// スケール
		Vec3 m_scaleOffset;				// スケールオフセット


	public:
		CountDown(const shared_ptr <Stage>& stage)
			:GameObject(stage),
			start(false),
			reset(false),
			initialTime(180.0f),
			currentTime(),
			m_timerNumbers(0),
			m_timeCount(0.0f),

			m_numbersOffset(),
			m_isMinutes(false),
			m_setOffset(),
			m_addOffset(),
			m_spaceOffset(),
			m_posOffset(),

			m_scaleValue(),
			m_scaleOffset()


		{}

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override;

		void Start() {
			start = true;
		}
		void Stop() {
			start = false;
		}
		void Reset() {
			reset = true;
		}

		void Adjust(float adjust) {
			currentTime += adjust;
			if (currentTime > initialTime)
			{
				currentTime = initialTime;
			}
			else if (currentTime < 0)
			{
				currentTime = 0;
			}
		}
		//void ClockCreation();


		// タイマーをスプライトで表示するための関数
		void CountDownSpriteCreate();
		void AddTimerColonSpriteCreate(Vec3 posValue, Vec3 scaleValue);
		
		// カウントダウンをさせるための数値
		void SetTimerNumbers();

	};

}
