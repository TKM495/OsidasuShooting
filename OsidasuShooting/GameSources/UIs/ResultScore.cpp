#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ResultScore::OnCreate() {

		NumbersDrawSpriteCreate();

		// number�Ɉ�����n��
		int place = static_cast<int>(pow(10, m_numbers.size() - 1));
		for (auto& number : m_numbers) {
			int value = m_playerScore / place % 10;
			place /= 10;

			number->SetValue(value);
		}
	}

	void ResultScore::NumbersDrawSpriteCreate() {

		m_addOffset = Vec3(40.0f, 0, 0);	// �ꕶ���̑傫��
		m_spaceOffset = Vec3(10.0f, 0, 0);	// ���ƕb�ŕ�����Ƃ��̃X�y�[�X
		m_posOffset = m_setOffset;		// �I�b�t�Z�b�g

		m_scaleValue = 0.55f;
		m_scaleOffset = Vec3(m_scaleValue);

		m_numbers.resize(2);
		for (auto& number : m_numbers) {
			number = ObjectFactory::Create<Number>(GetStage(), 0);
			auto numberTrans = number->GetComponent<Transform>();
			numberTrans->SetPosition(m_posOffset);
			numberTrans->SetScale(m_scaleOffset);
			m_posOffset += m_addOffset;
		}	
	}

	void ResultScore::OnDraw() {
		GameObject::OnDraw();
		for (auto& number : m_numbers) {
			number->OnDraw();
		}
	}
}