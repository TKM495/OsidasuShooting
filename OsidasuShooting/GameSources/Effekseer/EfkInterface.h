/*!
@file EfkInterface.h
@brief Effekseerエフェクトのインターフェイス
*/

#pragma once

#include "stdafx.h"

#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <EffekseerSoundXAudio2.h>

#if _DEBUG
#pragma comment(lib, "Effekseerd.lib" )
#pragma comment(lib, "EffekseerRendererDX11d.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2d.lib" )
#else
#pragma comment(lib, "Effekseer.lib" )
#pragma comment(lib, "EffekseerRendererDX11.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.lib" )
#endif

using namespace Effekseer;

namespace basecross {
	class EfkInterface;

	/**
	 * @brief Effekseerのエフェクトファイルの管理クラス
	 */
	class EfkEffect : public ObjectInterface {
		// ファイルの名前
		wstring m_FileName;
		// エフェクトポインタ
		EffectRef m_Effect;
		// インターフェイスへのポインタ
		weak_ptr<EfkInterface> m_EfkInterface;
		friend class EfkPlay;
	public:
		/**
		 * @brief コンスラトクタ
		 *
		 * @param iface		インターフェイス
		 * @param filename	エフェクトファイル名
		 */
		EfkEffect(const shared_ptr<EfkInterface>& iface, const wstring& filename);

		/**
		@brief	デストラクタ
		*/
		virtual ~EfkEffect();

		/**
		 * @brief 初期化
		 */
		virtual void OnCreate() override;
	};

	/**
	 * @brief EffekseerのPlayオブジェクトクラス（実際に再生中のオブジェクト）
	 */
	class EfkPlay : public ObjectInterface {
		// Effekseerのハンドル
		Handle m_Handle;
		// インターフェイスのポインタ
		weak_ptr<EfkInterface> m_EfkInterface;
	public:
		/**
		 * @brief コンスラトクタ
		 *
		 * @param effect	エフェクト
		 * @param Emitter	エミッター（生成場所）
		 */
		EfkPlay(const shared_ptr<EfkEffect>& effect, const bsm::Vec3& Emitter);
		virtual ~EfkPlay();

		/**
		 * @brief 初期化（空関数）
		 */
		void OnCreate() override {}

		/**
		 * @brief エフェクトをストップさせる
		 */
		void StopEffect();

		/**
		 * @brief エフェクトを移動する
		 *
		 * @param Location 移動ベクトル（相対方向）
		 */
		void AddLocation(const bsm::Vec3& Location);
	};

	/**
	 * @brief Effekseerのインターフェイス
	 */
	class EfkInterface : public ObjectInterface, public ShapeInterface {
		// Effekseerのマネージャーポインタ
		ManagerRef m_Manager;
		EffekseerRenderer::RendererRef m_Renderer;

		friend class EfkPlay;
		friend class EfkEffect;
	public:
		EfkInterface();
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
	};
}
//end basecross
