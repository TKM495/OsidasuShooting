/*!
@file GameCamera.h
@brief �Q�[���J����
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameCamera :public Camera {
		/**
		 * @brief �X�e�[�g
		 */
		enum class State {
			Init,	// ������
			Update,	// �X�V
		};
		// At����ɂ���Eye�̈ʒu
		Vec3 m_defaultLocalEye;
		// ������At�̈ʒu
		Vec3 m_defaultAt;
		// �Ǐ]���x
		float m_followUpVelocity;

		float m_minZoom = 50;
		float m_maxZoom = 30;
		float m_zoomLimiter = 40;

		// ���݂̃X�e�[�g
		State m_state;
		// ����������
		void Init();
		// �X�V����
		void Update();
		/**
		 * @brief At��Eye��ݒ�
		 *
		 * @param at At�̈ʒu
		 */
		void SetAtAndEye(const Vec3& at);
		void SetZoomLevel(float level);
		/**
		 * @brief �e�v���C���[������AABB���擾
		 *
		 * @return �e�v���C���[������AABB
		 */
		AABB GetAABB();
		/**
		 * @brief ���S�_���擾
		 *
		 * @return �e�v���C���[�̒��S�_
		 */
		Vec3 GetCenterPoint();
		/**
		 * @brief �e�v���C���[�̍ő勗�����擾
		 *
		 * @return �e�v���C���[�̍ő勗��
		 */
		float GetGreatestDistance();
	public:
		GameCamera();

		void OnCreate() override;
		void OnUpdate() override;
	};
}

//end basecross
