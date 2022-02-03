#pragma once
#include "stdafx.h"
#include "BaseUI.h"
#include "Utility/TimeCounter.h"

namespace basecross {
	class OneShotUI :public BaseUI {
		enum class State {
			FadeIn,
			Normal,
			FadeOut
		};
		State m_state;

		// ����
		float m_lifeSpan;
		// �e�N�X�`���L�[
		wstring m_textureKey;
		TimeCounter m_timer;
		shared_ptr<GameObject> m_owner;
		// ��������
		Vec3 m_movingDirection;
	public:
		OneShotUI(const shared_ptr<Stage>& stage,
			const shared_ptr<GameObject>& owner,
			float lifeSpan, const wstring& texKey,
			const TransformData& transformData);

		void OnCreate()override;
		void OnUpdate()override;

		void SetColor(const Col4 color) {
			GetComponent<PCTSpriteDraw>()->SetDiffuse(color);
		}

		void SetMovingDirection(const Vec3& dir) {
			m_movingDirection = dir;
		}
	};
}
