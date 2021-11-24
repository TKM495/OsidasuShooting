#pragma once
#include "stdafx.h"

namespace basecross {
	// 参考：https://gintenlabo.hatenablog.com/entry/20100423/1272041386
	template<class T>
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
}