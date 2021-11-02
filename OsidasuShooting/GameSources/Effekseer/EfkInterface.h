/*!
@file EfkInterface.h
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
		ManagerRef m_Manager;
		EffekseerRenderer::RendererRef m_Renderer;
		// 自身のインスタンス
		static shared_ptr<EfkInterface> m_ownInstance;
		friend class EfkPlay;
		friend class EfkEffect;
	public:
		EfkInterface(const shared_ptr<Stage>& stage);
		virtual ~EfkInterface();

		/**
		 * @brief ビューと射影行列を設定する
		 *
		 * @param view ビュー行列
		 * @param proj 射影行列
		 */
		void SetViewProj(const bsm::Mat4x4& view, const bsm::Mat4x4& proj);

		virtual void OnCreate() override;
		virtual void OnUpdate()override;
		virtual void OnDraw()override;

		static shared_ptr<EfkInterface> GetInstance();

		ManagerRef GetManager() {
			return m_Manager;
		}
	};
}
//end basecross
