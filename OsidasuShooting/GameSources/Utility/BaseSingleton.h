#pragma once
#include "stdafx.h"

namespace basecross {
	// �Q�l�Fhttps://gintenlabo.hatenablog.com/entry/20100423/1272041386
	template<class T>
	class BaseSingleton {
	protected:
		// �J�X�^���폜�q�B�C���X�^���X�̍폜�͂�������̂ݍs�Ȃ��B
		struct Deleter {
			void operator()(T const* const p) const {
				delete p;
			}
		};
		// std::unique_ptr �͍폜�q���w��o����
		static unique_ptr<T, Deleter> m_instance;

		BaseSingleton() {}
		~BaseSingleton() {}
	public:
		/**
		 * @brief �C���X�^���X�̎擾�i�K�v������ΐ�������j
		 *
		 * @return �C���X�^���X
		 */
		static unique_ptr<T, Deleter>& GetInstance() {
			if (!m_instance) {
				m_instance.reset(new T);
			}
			return m_instance;
		}
		/**
		 * @brief �C���X�^���X�̋����폜
		 */
		static void DeleteInstance() {
			if (m_instance.get()) {
				m_instance.reset();
			}
		}
	};
}