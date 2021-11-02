#include "stdafx.h"
#include "Project.h"
#include "TestObject.h"

namespace basecross {
	void TestObject::OnCreate() {
		//�G�t�F�N�g�̏�����
		//wstring DataDir;
		//App::GetApp()->GetDataDirectory(DataDir);
		//wstring TestEffectStr = DataDir + L"Effects\\test2.efk";
		//auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();
		//m_efkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);
		//�G�t�F�N�g�̔����ʒu�̊m�F�̂���
	   // ���ʁF�G�t�F�N�g�̓I�u�W�F�N�g�̈ʒu�ɐ���
	   //GetComponent<Transform>()->SetPosition(Vec3(10.0f, 0.0f, 0.0f));

		AddComponent<EfkComponent>()->SetEffectResource(L"Test");

		Debug::GetInstance()->Log(L"Created");
	}

	void TestObject::OnUpdate() {
		const auto& key = App::GetApp()->GetInputDevice().GetKeyState();
		if (key.m_bPressedKeyTbl[VK_SPACE]) {
			//flg = true;
			//auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();
			//auto Ptr = GetComponent<Transform>();
			//m_efkPlay = ObjectFactory::Create<EfkPlay>(m_efkEffect, Ptr->GetPosition());
			GetComponent<EfkComponent>()->Play();
			Debug::GetInstance()->Log(L"Pressed Space");
		}
		//if (flg)
		//	m_efkPlay->AddLocation(Vec3(0.0f, 0.0f, 30.0f) * App::GetApp()->GetElapsedTime());
	}

	void Block::OnCreate() {
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(m_scale);
	}
}