///*!
//@file Player.cpp
//@brief ÉvÉåÉCÉÑÅ[Ç»Ç«é¿ëÃ
//*/
//
#include "stdafx.h"
//#include "Project.h"
//
//namespace basecross
//{
//	EfkObj::EfkObj(const shared_ptr<Stage>& stage,
//		const wstring& path,
//		const Vec3& pos,
//		const float destroyTime
//	) :
//		GameObject(stage),
//		m_path(path),
//		m_pos(pos),
//		m_looped(false),
//		waitTime(0.0f),
//		m_count(0.0f),
//		m_destroyTime(destroyTime),
//		m_destroyCount(0.0f)
//	{
//	}
//	EfkObj::EfkObj(const shared_ptr<Stage>& stage,
//		const wstring& path,
//		const Vec3& pos,
//		const bool looped,
//		const float waitTime
//	) :
//		GameObject(stage),
//		m_path(path),
//		m_pos(pos),
//		m_looped(looped),
//		waitTime(waitTime),
//		m_count(0.0f),
//		m_destroyTime(waitTime),
//		m_destroyCount(0.0f)
//	{
//	}
//
//	EfkObj::EfkObj(const shared_ptr<Stage>& stage,
//		const wstring& path,
//		const Vec3& pos,
//		const float destroyTime,
//		const shared_ptr<GameObject>& parent
//	) :
//		GameObject(stage),
//		m_path(path),
//		m_pos(pos),
//		m_parent(parent),
//		m_looped(false),
//		waitTime(0.0f),
//		m_count(0.0f),
//		m_destroyTime(destroyTime),
//		m_destroyCount(0.0f)
//	{
//	}
//
//	EfkObj::EfkObj(const shared_ptr<Stage>& stage,
//		const wstring& path,
//		const Vec3& pos,
//		const shared_ptr<GameObject>& parent,
//		const bool looped,
//		const float waitTime
//	) :
//		GameObject(stage),
//		m_path(path),
//		m_pos(pos),
//		m_parent(parent),
//		m_looped(looped),
//		waitTime(waitTime),
//		m_count(0.0f),
//		m_destroyTime(waitTime),
//		m_destroyCount(0.0f)
//	{
//	}
//
//	EfkObj::~EfkObj()
//	{
//	}
//
//	void EfkObj::Start()
//	{
//		auto& trans = GetComponent<Transform>();
//		auto pos = trans->GetPosition();
//		if (m_parent)
//		{
//			pos += m_parent->GetComponent<Transform>()->GetPosition();
//		}
//		m_efkPlay = ObjectFactory::Create<EfkPlay>(m_efk, pos);
//	}
//
//	void EfkObj::OnCreate()
//	{
//		auto& trans = GetComponent<Transform>();
//		trans->SetParent(m_parent);
//		trans->SetPosition(m_pos);
//
//		wstring DataDir;
//		App::GetApp()->GetDataDirectory(DataDir);
//		wstring efkPath = DataDir + m_path;
//		auto& efkInterface = GetTypeStage<BaseStage>()->GetEfkInterface();
//		m_efk = ObjectFactory::Create<EfkEffect>(efkInterface, efkPath);
//
//		Start();
//	}
//
//	void EfkObj::OnUpdate()
//	{
//		if (m_parent)
//		{
//			auto& trans = GetComponent<Transform>();
//			auto beforPos = trans->GetBeforePosition();
//			auto pos = trans->GetPosition();
//			if (m_parent)
//			{
//				auto& parentTrans = m_parent->GetComponent<Transform>();
//				beforPos += parentTrans->GetBeforePosition();
//				pos += parentTrans->GetPosition();
//			}
//			m_efkPlay->AddLocation(pos - beforPos);
//		}
//
//		auto delta = App::GetApp()->GetElapsedTime();
//		if (m_looped)
//		{
//			if (m_count > waitTime)
//			{
//				Start();
//				m_count = 0.0f;
//			}
//			else
//			{
//				m_count += delta;
//			}
//		}
//		else
//		{
//			if (m_destroyCount >= m_destroyTime)
//			{
//				auto& trans = GetComponent<Transform>();
//				trans->SetParent(nullptr);
//				GetStage()->RemoveGameObject<EfkObj>(GetThis<EfkObj>());
//			}
//			else
//			{
//				m_destroyCount += delta;
//			}
//		}
//	}
//
//	void EfkObj::OnDestroy()
//	{
//		m_efkPlay->StopEffect();
//	}
//}