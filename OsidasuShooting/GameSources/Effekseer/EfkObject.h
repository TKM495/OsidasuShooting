#pragma once
#include "stdafx.h"

namespace basecross {
	// ��{�I�ɃR���|�[�l���g�����Ȃ�����GameObject�łȂ��Ă�������������Ȃ�
	// ����������������g�����X�t�H�[�����g�p���邩������Ȃ�
	class EfkObject :public GameObject {
	public:
		EfkObject(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;

		void Play();
		void Stop();
		void Pause();
	};
}
