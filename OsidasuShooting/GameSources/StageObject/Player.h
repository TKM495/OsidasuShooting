/*!
@file   Player.h
@brief  �v���C���[
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
#include "Utility/BombPredictionLine.h"

namespace basecross {
	enum class PlayerNumber {
		P1,
		P2,
		P3,
		P4
	};

	class Player :public StageObject {
		// �ړ����x�i�ǂ��炩�Ƃ����Ƃ�����́j
		float m_moveSpeed;
		// �\�����\���N���X
		BombPredictionLine line;
		Vec3 m_bombPoint;
		//�X�e�[�g�}�V�[��
		unique_ptr<StateMachine<Player>> m_stateMachine;
		void Move();
		void JumpAndHover();
		void SpecialSkill();
	public:
		Player(const shared_ptr<Stage>& stage, const TransformData& transData)
			:StageObject(stage), m_moveSpeed(20.0f), line(stage, 10, 2.0f)
			, m_bombPoint(Vec3(0.0f))
		{
			m_transformData = transData;
		}

		void OnCreate()override;
		void OnUpdate()override;

		void OnCollisionEnter(shared_ptr<GameObject>& other);

		const unique_ptr<StateMachine<Player>>& GetStateMachine() {
			return m_stateMachine;
		}

		void BulletAim();
		void BombAim();
		void BulletLaunch();
		void BombLaunch();
	};

	class PlayerBulletModeState : public ObjState<Player> {
		PlayerBulletModeState() {}
	public:
		static shared_ptr<PlayerBulletModeState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	class PlayerBombModeState : public ObjState<Player> {
		PlayerBombModeState() {}
	public:
		static shared_ptr<PlayerBombModeState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
}
