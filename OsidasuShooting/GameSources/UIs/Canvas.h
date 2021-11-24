#pragma once
#include "stdafx.h"
#include "BaseUI.h"

namespace basecross {
	class Canvas :public GameObject {
		// ��ɂ����ʃT�C�Y
		Vec2 m_standardToScreenSize;
		// BaseUI�̃X�P�[������̉�ʃT�C�Y�ɍ��킹�邩
		bool m_isFitScaleToStandard;
		// UI�̃I�u�W�F�N�g�z��
		vector<BaseUI> m_uiObjects;

		void Init();
	public:
		Canvas(const shared_ptr<Stage>& stage)
			:GameObject(stage), m_standardToScreenSize(Vec2(1270, 720)),
			m_isFitScaleToStandard(false)
		{}

		void OnCreate()override;
		void OnUpdate()override;

		template<typename T, typename... Ts>
		shared_ptr<T> AddUIObject(Ts&&... params) {
			auto ptr = GetStage()->AddGameObject<T>(params...);
			m_uiObjects.push_back(ptr);
			return ptr
		}
	};
}
