/*!
@file  EfkInterface.h
@brief Effekseerエフェクトのインターフェイス
*/

#pragma once
#include "stdafx.h"
#include "Effekseer/EfkEffect.h"

namespace basecross {
	/**
	 * @brief Effekseerのインターフェイス
	 */
	class EfkInterface : public GameObject {
		// Effekseerのマネージャーポインタ
		Effekseer::ManagerRef m_Manager;
		EffekseerRenderer::RendererRef m_Renderer;
		// 自身のインスタンス
		static shared_ptr<EfkInterface> m_ownInstance;

		/**
		 * @brief ビューと射影行列を設定する
		 *
		 * @param view ビュー行列
		 * @param proj 射影行列
		 */
		void SetViewProj(const bsm::Mat4x4& view, const bsm::Mat4x4& proj);
	public:
		EfkInterface(const shared_ptr<Stage>& stage);
		virtual ~EfkInterface();

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDraw()override;

		/**
		 * @brief インスタンスの取得
		 *
		 * @return EfkInterfaceのインスタンスの
		 */
		static shared_ptr<EfkInterface> GetInstance();

		/**
		 * @brief マネージャーの取得
		 *
		 * @return マネージャーのポインタ
		 */
		Effekseer::ManagerRef GetManager() {
			return m_Manager;
		}
	};
}
//end basecross
