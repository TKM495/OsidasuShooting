#pragma once
#include "stdafx.h"
#include "UIs/NumberSprite.h"

namespace basecross {
	class CountDown : public GameObject
	{
	private:
		shared_ptr<SimpleSprite> remaining30sec;
		shared_ptr<SimpleSprite> remaining60sec;

		bool start;
		bool reset;

		float initialTime; //�b�̒l�ł�
		float currentTime;

		int m_timerNumbers;
		float m_timeCount;
		float m_warningTime;
		Col4 redColor;

		//�_�ŗp
		//�S�@�����@�͕b�Ƃ��ĕ\������Ă��܂��B
		float m_blinkTime;//�@���̂̓_�ł��鎞��
		float m_cur_blinkTime = 0;
		float m_blinkTimeChecker = m_blinkTime;//�@���̂̓_�ł��鎞��

		float m_fadeInTime;
		float m_fadeOutTime;
		//�_�ŗp..�I��
		vector<std::shared_ptr<Number>> m_numbers;

		//OffSet
		int  m_numbersOffset;			// �����b�����ʗp
		bool m_isMinutes;				// �����b��
		Vec3 m_setOffset;				// �ꕶ���ڂ̃I�u�W�F�N�g
		Vec3 m_addOffset;				// �ꕶ���̑傫��
		Vec3 m_spaceOffset;				// ���ƕb�ŕ�����Ƃ��̃X�y�[�X
		Vec3 m_posOffset;	// �I�b�t�Z�b�g

		float m_scaleValue;				// �X�P�[��
		Vec3 m_scaleOffset;				// �X�P�[���I�t�Z�b�g
		float m_max_scaleValue;
		float m_cur_scaleValue;
		bool isContinuousIncreasion = false;
		float expansionMaxRate;

		bool doAdjustAlpha = false;
		bool doAdjustColor = false;
		bool doAdjustScale = false;

		void BlinkingCreation();
		void BlinkingProcess();
		void BlinkingProcessStart();
		void BlinkingProcessContinuation();

		void RemainingSpriteShowing();
		void RemainingSpriteCreation();

		void UpdatingTimers();
	public:
		CountDown(const shared_ptr <Stage>& stage,
			float time = 60.0f)
			:GameObject(stage),
			start(false),
			reset(false),
			initialTime(time),
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

		float GetTime() {
			return currentTime;
		}

		// �^�C�}�[���X�v���C�g�ŕ\�����邽�߂̊֐�
		void CountDownSpriteCreate();
		void AddTimerColonSpriteCreate(Vec3 posValue, Vec3 scaleValue);

		// �J�E���g�_�E���������邽�߂̐��l
		void SetTimerNumbers();
	};
}
