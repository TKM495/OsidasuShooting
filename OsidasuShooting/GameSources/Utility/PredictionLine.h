/*!
@file   PredictionLine.h
@brief  �\�����v�Z�N���X
*/

#pragma once
#include "stdafx.h"
#include "LinePoint.h"
#include "UIs/SimpleSprite.h"

namespace basecross {
	class PredictionLine {
	public:
		// �\�����̎��
		enum class Type {
			Bullet,
			Bomb
		};
	private:
		// �\�����^�C�v
		Type m_type;
		// �d��
		float m_gravity;
		// �_�̐�
		int m_pointCount;
		// �؋󎞊�
		float m_flightTime;
		// �\�����\���̂��߂̃I�u�W�F�N�g
		vector<shared_ptr<LinePoint>> m_linePoints;
		// ���e�̒��e�n�_�X�v���C�g
		shared_ptr<BoardPoly> m_impactPoint;
		// �X�e�[�W�ւ̃|�C���^
		const shared_ptr<Stage>& stages;
		// �e�̗\�����̌v�Z
		vector<Vec3> BulletCalculate(const Vec3& startPoint, const Vec3& endPoint);
		// ���e�̗\�����̌v�Z
		vector<Vec3> BombCalculate(const Vec3& startPoint, const Vec3& endPoint);
		// �I�u�W�F�N�g�̐���
		void CreateLinePoint();
	public:
		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param stage	�X�e�[�W�ւ̃|�C���^
		 * @param pointCount �_�̐�
		 * @param flightTime ���e�̔��Ď���
		 * @param gravity �d�͉����x
		 */
		PredictionLine(
			const shared_ptr<Stage>& stage,
			int pointCount,
			float flightTime,
			float gravity = -9.8f);

		/**
		 * @brief �\�����̍X�V
		 *
		 * @param startPoint �J�n�_
		 * @param endPoint �I���_
		 * @param type �^�C�v
		 */
		void Update(const Vec3& startPoint, const Vec3& endPoint, Type type);

		/**
		 * @brief �������̌v�Z
		 *
		 * @param startPoint �J�n�_
		 * @param endPoint �I���_
		 * @param time m_flightTime���ő�Ƃ�������
		 * @return time�̎��̈ʒu
		 */
		Vec3 ParabolaCalculate(const Vec3& startPoint, const Vec3& endPoint, float time);

		/**
		 * @brief �F�̐ݒ�
		 *
		 * @param color �F
		 */
		void SetColor(const Col4& color);

		/**
		 * @brief �L��������ݒ�
		 *
		 * @param flg true:�L��
		 */
		void SetActive(bool flg);
	};
}
