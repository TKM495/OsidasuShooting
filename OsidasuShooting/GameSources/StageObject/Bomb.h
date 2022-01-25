/*!
@file   Bomb.h
@brief  ���e�N���X
*/

#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"
#include "PlayerBase.h"

namespace basecross {
	class Bomb :public AdvancedGameObject {
		// PredictionLine�̃C���X�^���X
		PredictionLine m_predictionLine;
		// �J�n�ʒu
		Vec3 m_startPoint;
		// �I���ʒu
		Vec3 m_endPoint;
		// �^�C�����[�g
		float m_timeRate;
		// �o�ߎ���
		float m_delta;
		// ��������
		float m_lifeSpan;

		// ���e�̍ŏ����a�i�����Ȃ��̈З͔͈́j
		float m_minimumRadius;
		// ���e�̍ő唼�a�i�ő�З͔͈́j
		float m_maxRadius;

		// ���e�̈З�
		float m_power;

		// �����������i1�̔��e�����i�q�b�g����̂�h���t���O�j
		bool m_isExploded;

		// �I�[�i�[
		weak_ptr<PlayerBase> m_owner;
		float PowerCalc(float distance);
	public:
		Bomb(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& owner,
			const PredictionLine& predictionLine,
			const Vec3& startPoint,
			const Vec3& endPoint,
			float power);

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;
	};
}
