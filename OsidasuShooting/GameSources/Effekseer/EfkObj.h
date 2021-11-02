///*!
//@file Player.h
//@brief ÉvÉåÉCÉÑÅ[Ç»Ç«
//*/
//
//#pragma once
//#include "stdafx.h"
//
//namespace basecross
//{
//	class EfkObj : public GameObject
//	{
//	private:
//		wstring m_path;
//		Vec3 m_pos;
//		shared_ptr<GameObject> m_parent;
//		bool m_looped;
//		float waitTime;
//
//		float m_count;
//
//		float m_destroyTime;
//		float m_destroyCount;
//
//		shared_ptr<EfkEffect> m_efk;
//		shared_ptr<EfkPlay> m_efkPlay;
//
//		void Start();
//
//	public:
//		EfkObj(const shared_ptr<Stage>& stage,
//			const wstring& path,
//			const Vec3& pos,
//			const float destroyTime);
//		EfkObj(const shared_ptr<Stage>& stage,
//			const wstring& path,
//			const Vec3& pos,
//			const bool looped,
//			const float waitTime);
//		EfkObj(const shared_ptr<Stage>& stage,
//			const wstring& path,
//			const Vec3& pos,
//			const float destroyTime,
//			const shared_ptr<GameObject>& parent);
//		EfkObj(const shared_ptr<Stage>& stage,
//			const wstring& path,
//			const Vec3& pos,
//			const shared_ptr<GameObject>& parent,
//			const bool looped,
//			const float waitTime);
//		~EfkObj();
//
//		void OnCreate() override;
//		void OnUpdate() override;
//		void OnDestroy() override;
//	};
//}