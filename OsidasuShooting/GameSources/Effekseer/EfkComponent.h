/*!
@file   EfkComponent.h
@brief  Effekseerを使用するためのコンポーネント
*/

#pragma once
#include "stdafx.h"
#include "Effekseer/EfkEffect.h"
#include "StageObject/AdvancedGameObject.h"

namespace basecross {
	/**
	 * @brief 空間タイプ
	 */
	enum class SpaceType {
		World,	// ワールド
		Local	// ローカル
	};
	/**
	 * @brief 座標指定
	 */
	enum class CoordinateType {
		Absolute,	// 絶対
		Relative	// 相対
	};
	/**
	 * @brief エフェクトコンポーネント
	 */
	class EfkComponent : public Component {
	private:
		// エフェクトデータ構造体
		struct EfkData {
			// エフェクトデータのポインタ
			Effekseer::EffectRef EffectData;
			// エフェクトハンドル
			Effekseer::Handle Handle;
			// 再生時のオフセットデータ
			TransformData Offset;
			// 前回のエフェクトを停止せずに再生を開始するか
			bool NoStopLastEffect;
			EfkData()
				:EfkData(nullptr, TransformData(), false)
			{}
			EfkData(const Effekseer::EffectRef& data, const TransformData& offset, bool flg) {
				this->EffectData = data;
				this->Handle = -1;
				this->Offset = offset;
				this->NoStopLastEffect = flg;
			}
		};
		// キー,エフェクトデータのマップ
		map<wstring, EfkData> m_effectDataMap;
		// マネージャーのポインタ
		Effekseer::ManagerRef m_manager;
		// 再生速度
		float m_playSpeed;
		// 使用する空間
		SpaceType m_useSpace;
		// 座標指定
		CoordinateType m_coordinateType;
		/**
		 * @brief ゲームオブジェクトの位置を取得
		 *
		 * @return ゲームオブジェクトの位置
		 */
		Vec3 GetGameObjectPosition();
	public:
		EfkComponent(const shared_ptr<GameObject>& gameObjectPtr);
		EfkComponent(const shared_ptr<GameObject>& gameObjectPtr, SpaceType useSpace);
		~EfkComponent() {}

		void OnCreate() override {}
		void OnUpdate() override {}
		void OnDraw()override {}

		/**
		 * @brief 使用するエフェクトの設定
		 *
		 * @param key エフェクトのキー
		 * @param offset オフセットデータ
		 * @param noStopLastEffect 前回のエフェクトを停止せずに再生を開始するか
		 */
		void SetEffectResource(const wstring& key, const TransformData& offset, bool noStopLastEffect);
		/**
		 * @brief 使用するエフェクトの設定
		 *
		 * @param key エフェクトのキー
		 * @param offset オフセットデータ
		 */
		void SetEffectResource(const wstring& key, const TransformData& offset);
		/**
		 * @brief 使用するエフェクトの設定
		 *
		 * @param key エフェクトのキー
		 */
		void SetEffectResource(const wstring& key);

		/**
		 * @brief エフェクトの再生
		 *
		 * @param key エフェクトのキー
		 */
		void Play(const wstring& key);
		/**
		 * @brief エフェクトの停止
		 *
		 * @param key エフェクトのキー
		 */
		void Stop(const wstring& key);
		/**
		 * @brief すべてのエフェクトを停止
		 */
		void StopAll();
		/**
		 * @brief エフェクトの一時停止（すでに一時停止している場合はそこから再生）
		 *
		 * @param key エフェクトのキー
		 */
		void Pause(const wstring& key);

		void SetRotation(const wstring& key, const Vec3& rotation);


		/**
		 * @brief 位置の同期
		 *
		 * @param key エフェクトのキー
		 */
		void SyncPosition(const wstring& key);

		void SetPosition(const wstring& key, const Vec3& position);

		/**
		 * @brief キーのエフェクトが再生中か
		 *
		 * @param key エフェクトのキー
		 * @return 再生している:true/再生していない:false
		 */
		bool IsPlaying(const wstring& key);

		/**
		 * @brief コンポーネントに登録されているすべてのエフェクトが再生中か
		 *
		 * @return 再生している:true/再生していない:false
		 */
		bool IsPlaying();

		void SetCoordinateType(CoordinateType coordinateType);
	};
}
