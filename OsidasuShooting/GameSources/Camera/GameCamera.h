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
		// �ŏ��Y�[��
		float m_minZoom;
		// �ő�Y�[��
		float m_maxZoom;
		// �Y�[���l�͈̔�
		float m_zoomLimiter;
		// �ŏ�Y���W
		float m_minimumY;
		// ���݂̃X�e�[�g
		State m_state;
		// �ړ��ł���͈�
		Vec2 m_area;
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
		/**
		 * @brief �Y�[���̃Z�b�g
		 *
		 * @param level ����p(rad)
		 */
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

		void SetArea(const Vec2& area) {
			m_area = area;
		}
	};
}

//end basecross
