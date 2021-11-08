/*!
@file SpecialCamera.h
@brief �K�E�Z���g�����Ƃ��̃J����
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	// �K�E�Z�̉��o�p�J����
	class SpecialCamera : public GameObject {
		// ���o�p
		Vec3 m_cameraPos[2]; // ����
		Vec3 m_lPos; // ���[�U�[�̉��o

		Vec3 m_startPos;
		Vec3 m_startRot;

		// �^�[�Q�b�g�̃L�����N�^���
		enum m_playCharacters
		{
			laser
		};

		// ���o�̃C�[�W���O�p
		float m_move;
		float m_totalTime;
		float m_easingTime;

		// �^�[�Q�b�g�̏��擾
		Vec3 m_playerPos;
		Vec3 m_playerRot;

	public:
		SpecialCamera(const shared_ptr<Stage>& stage);
		virtual ~SpecialCamera() {};

		virtual void PlayerTrans();
		virtual void LookAtTarget();

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};



}