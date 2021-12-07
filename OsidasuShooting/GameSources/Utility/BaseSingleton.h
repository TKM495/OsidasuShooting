#pragma once
#include "stdafx.h"
#include "StageObject/AdvancedGameObject.h"

// 参考：https://gintenlabo.hatenablog.com/entry/20100423/1272041386
namespace basecross {
	/**
	 * @brief シングルトンクラス（純C++クラス用）
	 */
	template <class T>
	class BaseSingleton {
	protected:
		// カスタム削除子。インスタンスの削除はここからのみ行なう。
		struct Deleter {
			void operator()(T const* const p) const {
				delete p;
			}
		};
		// std::unique_ptr は削除子を指定出来る
		static unique_ptr<T, Deleter> m_instance;

		BaseSingleton() {}
		~BaseSingleton() {}

	public:
		/**
		 * @brief インスタンスの取得（必要があれば生成する）
		 *
		 * @return インスタンス
		 */
		static unique_ptr<T, Deleter>& GetInstance() {
			if (!m_instance) {
				m_instance.reset(new T);
			}
			return m_instance;
		}
		/**
		 * @brief インスタンスの強制削除
		 */
		static void DeleteInstance() {
			if (m_instance.get()) {
				m_instance.reset();
			}
		}
	};

	/**
	 * @brief シングルトンクラス（ゲームオブジェクト用）
	 */
	template <class T>
	class BaseSingletonGameObject : public AdvancedGameObject {
	private:
		// 自身のインスタンス
		static shared_ptr<T> m_ownInstance;

	protected:
		/**
		 * @brief インスタンスの生成
		 */
		void CreateInstance() {
			m_ownInstance = nullptr;
			m_ownInstance = GetThis<T>();
		}

	public:
		// ゲームオブジェクトの関係上コンストラクタはpublic
		BaseSingletonGameObject(const shared_ptr<Stage>& stage)
			: AdvancedGameObject(stage) {}

		/**
		 * @brief インスタンスを取得
		 *
		 * @return インスタンス
		 */
		static shared_ptr<T> GetInstance() {
			if (m_ownInstance.get() == 0) {
				throw BaseException(
					L"インスタンスが生成されていません",
					L"if (m_ownInstance.get() == 0)",
					L"BaseSingletonGameObject::GetInstance()");
			}
			return m_ownInstance;
		}
	};
}