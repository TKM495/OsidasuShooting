/*!
@file TitleSprite.h
@brief ƒ^ƒCƒgƒ‹
*/

#pragma once
#include "stdafx.h"

namespace basecross 
{
	class TitleSprite : public GameObject {
		bool m_trace;
		Vec2 m_startScale;
		Vec2 m_startPos;
		wstring m_textureKey;	

	public:
		TitleSprite(const shared_ptr<Stage>& stage,const wstring& TextureKey,bool Trace,
			const Vec2& StartScale,const Vec2& StartPos) :
			GameObject(stage),
			m_textureKey(TextureKey),
			m_trace(Trace),
			m_startScale(StartScale),
			m_startPos(StartPos)
		{}
			
		virtual ~TitleSprite() {};

		void OnCreate() ;
		void OnUpdate() {};

	};

	class PushAButtonSprite : public GameObject {
		bool m_trace;
		Vec2 m_startScale;
		Vec2 m_startPos;
		wstring m_textureKey;	

	public:
		PushAButtonSprite(const shared_ptr<Stage>& stage,const wstring& TextureKey,bool Trace,
			const Vec2& StartScale,const Vec2& StartPos) :
			GameObject(stage),
			m_textureKey(TextureKey),
			m_trace(Trace),
			m_startScale(StartScale),
			m_startPos(StartPos)
		{}
			
		virtual ~PushAButtonSprite() {};

		void OnCreate() ;
		void OnUpdate() {};

	};
}