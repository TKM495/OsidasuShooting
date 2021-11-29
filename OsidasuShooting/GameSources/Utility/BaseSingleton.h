#pragma once
#include "stdafx.h"
#include "StageObject/AdvancedGameObject.h"

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

	template<class T>
	class BaseSingletonGameObject :public AdvancedGameObject {
	private:
		// ���g�̃C���X�^���X
		static shared_ptr<T> m_ownInstance;
	protected:
		void CreateInstance() {
			m_ownInstance = nullptr;
			m_ownInstance = GetThis<T>();
		}
	public:
		BaseSingletonGameObject(const shared_ptr<Stage>& stage)
			:AdvancedGameObject(stage)
		{}

		/**
		 * @brief Debug�̃C���X�^���X���擾
		 *
		 * @return shared_ptr<Debug>
		 */
		static shared_ptr<T> GetInstance() {
			if (m_ownInstance.get() == 0)
			{
				throw BaseException(
					L"Debug����������Ă��܂���",
					L"if (m_ownInstance.get() == 0)",
					L"Debug::GetInstance()"
				);
			}
			return m_ownInstance;
		}
	};
}