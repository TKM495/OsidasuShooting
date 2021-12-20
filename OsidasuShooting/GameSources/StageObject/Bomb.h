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

		// ���e�̉e�����a
		float m_radius;
		// ���e�̈З�
		float m_power;

		// �����������i1�̔��e�����i�q�b�g����̂�h���t���O�j
		bool m_isExploded;

		// �I�[�i�[
		weak_ptr<PlayerBase> m_owner;
	public:
		Bomb(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& owner,
			const PredictionLine& predictionLine,
			const Vec3& startPoint,
			const Vec3& endPoint,
			float power)
			:AdvancedGameObject(stage), m_owner(owner),
			m_predictionLine(predictionLine),
			m_delta(0.0f), m_startPoint(startPoint), m_endPoint(endPoint),
			m_timeRate(2.0f), m_radius(3.0f), m_power(power), m_lifeSpan(5.0f),
			m_isExploded(false)
		{
			m_transformData.Position = m_startPoint;
			m_transformData.Scale = Vec3(0.5f);
		}

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;
	};
}
