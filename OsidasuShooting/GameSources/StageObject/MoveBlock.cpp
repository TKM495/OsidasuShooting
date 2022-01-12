/*!
@file   MoveBlock.cpp
@brief	リフレクターブロッククラスの実態
*/

#include "stdafx.h"
#include "Project.h"
#include "Bullet.h"

namespace basecross {
	MoveBlock::MoveBlock(
		const shared_ptr<Stage>& stage,
		const wstring& line
	) :
		AdvancedGameObject(stage)
	{
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
		m_transformData.Position = Vec3(
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str()),
			(float)_wtof(tokens[3].c_str())
		);
		m_transformData.Scale = Vec3(
			(float)_wtof(tokens[4].c_str()),
			(float)_wtof(tokens[5].c_str()),
			(float)_wtof(tokens[6].c_str())
		);
		m_transformData.Rotation = Vec3(
			XMConvertToRadians((float)_wtof(tokens[7].c_str())),
			XMConvertToRadians((float)_wtof(tokens[8].c_str())),
			XMConvertToRadians((float)_wtof(tokens[9].c_str()))
		);
		// 往復地点
		m_markPosition = Vec3(
			(float)_wtof(tokens[10].c_str()),
			(float)_wtof(tokens[11].c_str()),
			(float)_wtof(tokens[12].c_str())
		);
		// 移動速度
		m_moveSpeed = (float)_wtof(tokens[13].c_str());
		// 待機時間
		m_latency = (float)_wtof(tokens[14].c_str());

		// 文字列→enumの変換
		auto data = tokens[15];
		if (data == L"Block") {
			m_type = BlockType::Normal;
		}
		else if (data == L"Bumper") {
			m_type = BlockType::Bumper;
		}
		else if (data == L"Reflector") {
			m_type = BlockType::Reflector;
		}
		else {
			throw BaseException(
				L"不正な値です。",
				L"if(data == L\"\")",
				L"MoveBlock::MoveBlock()"
			);
		}
	}

	void MoveBlock::OnCreate() {
		//auto ptrDraw = AddComponent<PNTStaticDraw>();
		//ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetAfterCollision(AfterCollision::None);
		//// ブロックとの当たり判定を無視
		//ptrColl->AddExcludeCollisionTag(L"Block");
		//ptrColl->SetFixed(true);

		switch (m_type)
		{
		case BlockType::Normal:
			m_block = InstantiateGameObject<Block>(m_transformData);
			break;
		case BlockType::Bumper:
			m_block = InstantiateGameObject<Bumper>(m_transformData);
			break;
		case BlockType::Reflector:
			m_block = InstantiateGameObject<ReflectorBlock>(m_transformData);
			break;
		default:
			throw BaseException(
				L"未定義の値です。",
				L"switch (m_type)",
				L"void MoveBlock::OnCreate()"
			);
			break;
		}

		auto ptrTrans = GetTransform();
		m_startPosition = ptrTrans->GetPosition();

		m_moveRoot = m_startPosition - m_markPosition; // 距離の取得
		m_moveRoot.normalize(); // 正規化
		m_waitTime = 0;
		m_isWait = true;

		//// 本来の一個下に設置
		//m_setPosition = GetTransform()->GetPosition();
		//auto setPos = m_setPosition;
		//setPos.y = -1;
		//GetTransform()->SetPosition(setPos);
		//ApplyTransform();

		AddTag(L"MoveBlock");
	}

	void MoveBlock::MoveSwitch() {
		auto ptrTrans = GetTransform();
		auto pos = ptrTrans->GetPosition();

	}

	void MoveBlock::MovingBlock() {
		// デルタタイム取得
		const auto& app = App::GetApp();
		const auto delta = app->GetElapsedTime();

		// 現在のポジション
		auto ptrTrans = GetTransform();
		auto pos = ptrTrans->GetPosition();

		Easing<Vec3> easing;

		//auto rootMoving = m_moveRoot * delta * 0.1f;// 移動

		if (!m_isWait) {
			m_totalTime += delta;
			if (m_totalTime >= 4.0f) {
				m_totalTime = 0;
				m_isWait = true;
				m_waitTime = 0;

				if (m_isGotoMarkPos) m_isGotoMarkPos = false;
				else m_isGotoMarkPos = true;
			}
			Vec3 rootMoving;
			if (!m_isGotoMarkPos)
				rootMoving = easing.EaseInOut(
					EasingType::Quadratic, m_startPosition, m_markPosition, m_totalTime, 4.0f);
			else
				rootMoving = easing.EaseInOut(
					EasingType::Quadratic, m_markPosition, m_startPosition, m_totalTime, 4.0f);

			ptrTrans->SetPosition(rootMoving);
		}
		else {
			if (m_waitTime > m_latency) {
				m_isWait = false;
			}
			else {
				m_waitTime += delta;
			}
		}
	}

	void MoveBlock::OnUpdate() {
		//auto ptrColl = GetComponent<CollisionObb>();
		//ptrColl->SetAfterCollision(AfterCollision::Auto);
		MovingBlock();
		auto currentLocation = GetTransform()->GetPosition();
		m_block->GetTransform()->SetPosition(currentLocation);
	}
}