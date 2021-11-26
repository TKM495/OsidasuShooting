#pragma once
#include "stdafx.h"

namespace basecross {
	/**
	 * @brief 位置、大きさ、回転の情報を持つ構造体
	 */
	struct TransformData {
		Vec3 Position;
		Vec3 Scale;
		Vec3 Rotation;
		TransformData() {
			this->Position = Vec3(0.0f);
			this->Scale = Vec3(1.0f);
			this->Rotation = Vec3(0.0f);
		}
		TransformData(const Vec3& position) {
			this->Position = position;
			this->Scale = Vec3(1.0f);
			this->Rotation = Vec3(0.0f);
		}
		TransformData(const Vec3& position, const Vec3& scale) {
			this->Position = position;
			this->Scale = scale;
			this->Rotation = Vec3(0.0f);
		}
		TransformData(const Vec3& position, const Vec3& scale, const Vec3& rotation) {
			this->Position = position;
			this->Scale = scale;
			this->Rotation = rotation;
		}
	};

	/**
	 * @brief 位置と方向を持つ構造体
	 */
	struct Ray {
		Vec3 Origin;
		Vec3 Direction;
		Ray(const Vec3& origin, const Vec3& direction) {
			this->Origin = origin;
			this->Direction = direction;
		}
		Ray() {}

		Vec3 GetPoint(float distance) {
			return Origin + (Direction * distance);
		}
	};

	/**
	 * @brief 位置と方向を持つ構造体
	 */
	using ObjectPositionForward = Ray;

	/**
	 * @brief 高度なゲームオブジェクトクラス
	 */
	class AdvancedGameObject :public GameObject {
		// OnCreate()前にトランスフォームをm_transformDataで初期化するか
		bool m_isTransformInit;
	protected:
		// トランスフォームデータ
		//（子クラス側でトランスフォームをいじっていもこれに反映はされない）
		TransformData m_transformData;
	public:
		AdvancedGameObject(const shared_ptr<Stage>& stage)
			:GameObject(stage), m_isTransformInit(true)
		{}

		virtual void OnPreCreate()override;

		/**
		 * @brief OnCreate()前にトランスフォームを初期化するか
		 *
		 * @param flg true:初期化する/false:初期化しない
		 */
		void SetTransformInit(bool flg) {
			m_isTransformInit = flg;
		}

		/**
		 * @brief トランスフォームデータをセット
		 *
		 * @param data セットするトランスフォームデータ
		 */
		void SetTransformData(const TransformData& data) {
			m_transformData = data;
			ApplyTransform();
		}

		/**
		 * @brief トランスフォームデータを適用
		 */
		void ApplyTransform();

		/**
		 * @brief トランスフォームコンポーネントを取得
		 *
		 * @return トランスフォームコンポーネント
		 */
		shared_ptr<Transform> GetTransform() {
			return GetComponent<Transform>();
		}

		/**
		 * @brief ゲームオブジェクトの生成
		 *
		 * @param ...params パラメータ
		 * @return 作成されたゲームオブジェクト
		 */
		template<class T, typename... Ts>
		shared_ptr<T> InstantiateGameObject(Ts&&... params) {
			return GetStage()->AddGameObject<T>(params ...);
		}

		/**
		 * @brief 自身の削除
		 */
		template<class T>
		void Destroy() {
			GetStage()->RemoveGameObject<T>(GetThis<T>());
		}
	};
}
