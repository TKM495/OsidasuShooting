/*!
@file GameCamera.h
@brief ���C���J����
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameCamera :public Camera {
		enum class State {
			Init,	// ������
			Update,	// �X�V
		};
		Vec3 m_defaultLocalEye;
		Vec3 m_defaultAt;
		Vec3 m_def;
		State m_state;
		void Init();
		void Update();
		void SetAtAndEye(const Vec3& at);
	public:
		GameCamera();

		void OnCreate() override;
		void OnUpdate() override;
	};
}

//end basecross
