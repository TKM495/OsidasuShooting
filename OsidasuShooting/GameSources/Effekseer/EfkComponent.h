#pragma once
#include "stdafx.h"
#include "Effekseer/EfkEffect.h"

namespace basecross {
	/**
	 * @brief エフェクトコンポーネント
	 */
	class EfkComponent : public Component {
		// エフェクトデータのポインタ
		Effekseer::EffectRef m_effectData;
		// エフェクトハンドル
		Effekseer::Handle m_handle;
		// マネージャーのポインタ
		Effekseer::ManagerRef m_manager;
		// 再生速度
		float m_playSpeed;
	public:
		EfkComponent(const shared_ptr<GameObject>& gameObjectPtr);
		~EfkComponent() {}

		void OnCreate() override {}
		void OnUpdate() override {}
		void OnDraw()override {}

		/**
		 * @brief 使用するエフェクトの設定
		 *
		 * @param key エフェクトのキー
		 */
		void SetEffectResource(const wstring& key);
		/**
		 * @brief 使用するエフェクトの設定
		 *
		 * @param effectRes	shared_ptr<EfkEffectResource>
		 */
		void SetEffectResource(const shared_ptr<EfkEffectResource>& effectRes);

		/**
		 * @brief エフェクトの再生
		 */
		void Play();
		/**
		 * @brief エフェクトの停止
		 */
		void Stop();
		/**
		 * @brief エフェクトの一時停止（すでに一時停止している場合はそこから再生）
		 */
		void Pause();

		/**
		 * @brief 再生速度の設定
		 *
		 * @param speed 再生速度（デフォルトは1）
		 */
		void SetPlaySpeed(float speed = 1.0f);
	};
}
