#include "stdafx.h"
#include "Project.h"

namespace basecross {
	namespace modifiedClass {
		void CountDown::OnCreate() {
			currentTime = initialTime;

			auto transComp = GetComponent<Transform>();
			Vec3 pos(200.0f, 400.0f, 0.0f);
			//transComp->SetScale(0.5f, 0.5f, 0.5f);
			//transComp->SetPosition(pos);

			CountDownSpriteCreate();
		}

		// �^�C�}�[�̐������ꕶ�����쐬
		void CountDown::CountDownSpriteCreate() {
			m_numbersOffset = 0;			// �����b�����ʗp
			m_isMinutes = false;			// �����b��
			m_setOffset = Vec3(-102.5f, 360, 0);	// �ꕶ���ڂ̃I�u�W�F�N�g
			m_addOffset = Vec3(45.0f, 0, 0);	// �ꕶ���̑傫��
			m_spaceOffset = Vec3(20.0f, 0, 0);	// ���ƕb�ŕ�����Ƃ��̃X�y�[�X
			m_posOffset = m_setOffset;		// �I�b�t�Z�b�g

			m_scaleValue = 0.7f;
			m_scaleOffset = Vec3(m_scaleValue, m_scaleValue, m_scaleValue);

			m_numbers.resize(4);			// ���ƕb��4��������
			for (auto& number : m_numbers) {
				++m_numbersOffset;

				number = ObjectFactory::Create<Number>(GetStage(), 0);
				auto numberTrans = number->GetComponent<Transform>();
				numberTrans->SetPosition(m_posOffset);
				numberTrans->SetScale(m_scaleOffset);
				m_posOffset += m_addOffset;

				numberTrans->SetPivot(GetComponent<Transform>()->GetPosition());

				if (m_numbersOffset == 2 && !m_isMinutes) {
					m_isMinutes = false;
					m_posOffset += m_spaceOffset;
					AddTimerColonSpriteCreate(m_posOffset, m_scaleOffset);
				}
			}
		}

		void CountDown::AddTimerColonSpriteCreate(Vec3 posValue, Vec3 scaleValue) {
			auto colon = GetStage()->AddGameObject<Number>(10);
			auto colonTrans = colon->GetComponent<Transform>();
			auto posSetting(-m_spaceOffset * 1.6f);
			colonTrans->SetPosition(posValue + posSetting);
			colonTrans->SetScale(scaleValue);
		}

		void CountDown::SetTimerNumbers() {
			auto& app = App::GetApp();
			float deltaTime = app->GetElapsedTime();

			//if (m_timeCount > 1.0f && m_timerNumbers < pow(10, m_numbers.size()) - 1)
			//{
			//}

			// number�Ɉ�����n��
			int place = static_cast<int>(pow(10, m_numbers.size() - 1));
			for (auto& number : m_numbers) {
				int value = m_timerNumbers / place % 10;
				place /= 10;

				number->SetValue(value);
			}
		}

		void CountDown::OnUpdate() {
			auto& app = App::GetApp();
			float deltaTime = app->GetElapsedTime();

			int minutes;
			int hour;
			int seconds;

			wstring clocks = L"00:00:00";

			if (reset)
			{
				currentTime = initialTime;
				reset = false;
			}

			if (start)
			{
				currentTime -= deltaTime;
			}

			// �b�A���A���Ԃ̐��l�����߂�
			minutes = (int)(currentTime / 60);
			hour = (int)(minutes / 60);
			seconds = (int)currentTime - (hour * 60 + minutes) * 60;

			// ��ɂ܂Ƃ߂�
			m_timerNumbers = minutes * 100 + seconds;

			//clocks = L"";
			//if (hour <= 9)
			//{
			//	clocks += L"0";
			//}
			//clocks += Util::FloatToWStr(hour) + L":";

			//if (minutes <= 9)
			//{
			//	clocks += L"0";
			//}
			//clocks += Util::FloatToWStr(minutes) + L":";

			//if (seconds <= 9)
			//{
			//	clocks += L"0";
			//}
			//clocks += Util::FloatToWStr(seconds);

			//auto m_ssComp = AddComponent<StringSprite>();
			//m_ssComp->SetText(clocks);

			//m_timerNumbers = minutes * 100 + seconds;

			SetTimerNumbers();
		}

		void CountDown::OnDraw() {
			GameObject::OnDraw();
			for (auto& number : m_numbers) {
				number->OnDraw();
			}
		}
	}
}