#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerModel::OnCreate() {
		auto number = Util::IntToWStr((int)m_owner->GetPlayerNumber() + 1);
		wstring typeKey;
		switch (m_owner->GetPlayerType())
		{
		case PlayerType::Laser:
			typeKey = L"Laser";
			break;
		case PlayerType::Missile:
			typeKey = L"Missile";
			break;
		default:
			throw BaseException(
				L"定義されていないか未実装です。",
				L"switch (m_owner->GetPlayerType())",
				L"PlayerModel::OnCreate()"
			);
			break;
		}

		auto modelKey = typeKey + L"Player" + number;

		// 描画コンポーネントの追加
		auto drawComp = AddComponent<PNTBoneModelDraw>();
		drawComp->SetMultiMeshResource(modelKey);
		//drawComp->SetOwnShadowActive(true);

		auto data = CSVLoad::GetInstance()->GetData(L"ModelAnimationData");

		for (auto line : data) {
			auto c = DataExtracter::DelimitData(line);
			if (c[0] == typeKey) {
				auto name = c[1];
				auto start = (float)_wtof(c[2].c_str());
				auto end = (float)_wtof(c[3].c_str());
				auto loop = c[4] == L"TRUE";
				drawComp->AddAnimation(name, start, end - start, loop);
			}
		}

		// 影の追加
		auto stage = GetTypeStage<ResultStage>(false);
		if (stage) {
			auto shadowComp = AddComponent<Shadowmap>();
			shadowComp->SetMultiMeshResource(modelKey);
		}
		else {
			AddComponent<CircleShadow>(2.5f);
		}

		// ステートマシンの初期化
		m_stateMachine.reset(new StateMachine<PlayerModel>(GetThis<PlayerModel>()));
		StartWaitAnimation();
	}

	void PlayerModel::OnUpdate() {
		// 位置や回転を同期
		auto ownerTrans = m_owner->GetTransform();
		GetTransform()->SetPosition(ownerTrans->GetPosition() + m_offsetPos);
		GetTransform()->SetQuaternion(ownerTrans->GetQuaternion());
		m_stateMachine->Update();
	}

	void PlayerModel::StartWaitAnimation() {
		m_stateMachine->ChangeState(ModelWaitState::Instance());
	}
	void PlayerModel::StartWinAnimation() {
		m_stateMachine->ChangeState(ModelWinStartState::Instance());
	}

	// 待機時のステート
	shared_ptr<PlayerModel::ModelWaitState> PlayerModel::ModelWaitState::Instance() {
		static shared_ptr<ModelWaitState> instance(new ModelWaitState);
		return instance;
	}
	void PlayerModel::ModelWaitState::Enter(const shared_ptr<PlayerModel>& Obj) {
		auto drawComp = Obj->GetComponent<PNTBoneModelDraw>();
		drawComp->ChangeCurrentAnimation(L"Wait");
	}
	void PlayerModel::ModelWaitState::Execute(const shared_ptr<PlayerModel>& Obj) {
		auto delta = App::GetApp()->GetElapsedTime();
		auto drawComp = Obj->GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(delta);
	}
	void PlayerModel::ModelWaitState::Exit(const shared_ptr<PlayerModel>& Obj) {}

	// 勝利時
	shared_ptr<PlayerModel::ModelWinStartState> PlayerModel::ModelWinStartState::Instance() {
		static shared_ptr<ModelWinStartState> instance(new ModelWinStartState);
		return instance;
	}
	void PlayerModel::ModelWinStartState::Enter(const shared_ptr<PlayerModel>& Obj) {
		auto drawComp = Obj->GetComponent<PNTBoneModelDraw>();
		drawComp->ChangeCurrentAnimation(L"Win_Start");
	}
	void PlayerModel::ModelWinStartState::Execute(const shared_ptr<PlayerModel>& Obj) {
		auto delta = App::GetApp()->GetElapsedTime();
		auto drawComp = Obj->GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(delta);
		if (drawComp->IsTargetAnimeEnd()) {
			Obj->m_stateMachine->ChangeState(ModelWinLoopState::Instance());
		}
	}
	void PlayerModel::ModelWinStartState::Exit(const shared_ptr<PlayerModel>& Obj) {}

	shared_ptr<PlayerModel::ModelWinLoopState> PlayerModel::ModelWinLoopState::Instance() {
		static shared_ptr<ModelWinLoopState> instance(new ModelWinLoopState);
		return instance;
	}
	void PlayerModel::ModelWinLoopState::Enter(const shared_ptr<PlayerModel>& Obj) {
		auto drawComp = Obj->GetComponent<PNTBoneModelDraw>();
		drawComp->ChangeCurrentAnimation(L"Win_Loop");
	}
	void PlayerModel::ModelWinLoopState::Execute(const shared_ptr<PlayerModel>& Obj) {
		auto delta = App::GetApp()->GetElapsedTime();
		auto drawComp = Obj->GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(delta);
	}
	void PlayerModel::ModelWinLoopState::Exit(const shared_ptr<PlayerModel>& Obj) {}
}