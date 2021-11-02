#pragma once
#include "stdafx.h"

namespace basecross {
	// 基本的にコンポーネントをつけないためGameObjectでなくてもいいかもしれない
	// ただもしかしたらトランスフォームを使用するかもしれない
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
