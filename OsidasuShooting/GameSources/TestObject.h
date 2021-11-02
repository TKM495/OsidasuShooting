#pragma once
#include "stdafx.h"
#include "Effekseer/EfkInterface.h"

namespace basecross {
	class TestObject :public GameObject {
		shared_ptr<EfkEffect> m_efkEffect;
		shared_ptr<EfkPlay> m_efkPlay;
		bool flg;
	public:
		TestObject(const shared_ptr<Stage>& stage)
			:GameObject(stage), flg(false)
		{}
		void OnCreate()override;
		void OnUpdate()override;
	};

	class Block :public GameObject {
		Vec3 m_position;
		Vec3 m_scale;
	public:
		Block(const shared_ptr<Stage>& stage, Vec3 pos, Vec3 scale)
			:GameObject(stage), m_position(pos), m_scale(scale)
		{}

		Block(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate()override;
	};
}
