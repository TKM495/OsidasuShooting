#pragma once
#include "stdafx.h"
#include "UIs/NumberSprite.h"

namespace basecross {

	class CountDown : public GameObject
	{
	private:
		bool start;
		bool reset;

		float initialTime; //�b�̒l�ł�
		float currentTime;
		
		int m_timer;
		int m_timerNumbers;
		float m_timeCount;
		vector<std::shared_ptr<Number>> m_numbers;

	public:
		CountDown(const shared_ptr <Stage>& stage)
			:GameObject(stage),
			start(false),
			reset(false),
			initialTime(180.0f),
			currentTime(),
			m_timerNumbers(0),
			m_timeCount(0.0f)

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


		// �^�C�}�[���X�v���C�g�ŕ\�����邽�߂̊֐�
		void CreateCount();
		
		// �J�E���g�_�E���������邽�߂̐��l
		void SetTimerNumbers();

	};

}
