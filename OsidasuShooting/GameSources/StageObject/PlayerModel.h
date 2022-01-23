#pragma once
#include "stdafx.h"
#include "AdvancedGameObject.h"

namespace basecross {
	class PlayerModel :public AdvancedGameObject {
		// �I�[�i�[
		shared_ptr<PlayerBase> m_owner;
		// �I�t�Z�b�g�ʒu
		Vec3 m_offsetPos;
		// �X�e�[�g�}�V��
		unique_ptr<StateMachine<PlayerModel>> m_stateMachine;
	public:
		PlayerModel(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& gameObject,
			const TransformData& transformData)
			:AdvancedGameObject(stage), m_owner(gameObject),
			m_offsetPos(Vec3(0.0f))
		{
			m_transformData = transformData;
			m_offsetPos.y += -0.5f * m_transformData.Scale.y;
		}
		void OnCreate()override;
		void OnUpdate()override;

		void StartWaitAnimation();
		void StartWinAnimation();

	private:
		// �ҋ@���̃X�e�[�g
		class ModelWaitState :public ObjState<PlayerModel> {
			ModelWaitState() {}
		public:
			static shared_ptr<ModelWaitState> Instance();
			virtual void Enter(const shared_ptr<PlayerModel>& Obj) override;
			virtual void Execute(const shared_ptr<PlayerModel>& Obj) override;
			virtual void Exit(const shared_ptr<PlayerModel>& Obj) override;
		};

		// ������
		class ModelWinStartState :public ObjState<PlayerModel> {
			ModelWinStartState() {}
		public:
			static shared_ptr<ModelWinStartState> Instance();
			virtual void Enter(const shared_ptr<PlayerModel>& Obj) override;
			virtual void Execute(const shared_ptr<PlayerModel>& Obj) override;
			virtual void Exit(const shared_ptr<PlayerModel>& Obj) override;
		};

		class ModelWinLoopState :public ObjState<PlayerModel> {
			ModelWinLoopState() {}
		public:
			static shared_ptr<ModelWinLoopState> Instance();
			virtual void Enter(const shared_ptr<PlayerModel>& Obj) override;
			virtual void Execute(const shared_ptr<PlayerModel>& Obj) override;
			virtual void Exit(const shared_ptr<PlayerModel>& Obj) override;
		};
	};
}
