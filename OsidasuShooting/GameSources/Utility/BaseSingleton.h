#pragma once
#include "stdafx.h"
#include "StageObject/AdvancedGameObject.h"

// �Q�l�Fhttps://gintenlabo.hatenablog.com/entry/20100423/1272041386
namespace basecross {
	/**
	 * @brief �V���O���g���N���X�i��C++�N���X�p�j
	 */
	template <class T>
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

	/**
	 * @brief �V���O���g���N���X�i�Q�[���I�u�W�F�N�g�p�j
	 */
	template <class T>
	class BaseSingletonGameObject : public AdvancedGameObject {
	private:
		// ���g�̃C���X�^���X
		static shared_ptr<T> m_ownInstance;

	protected:
		/**
		 * @brief �C���X�^���X�̐���
		 */
		void CreateInstance() {
			m_ownInstance = nullptr;
			m_ownInstance = GetThis<T>();
		}

	public:
		// �Q�[���I�u�W�F�N�g�̊֌W��R���X�g���N�^��public
		BaseSingletonGameObject(const shared_ptr<Stage>& stage)
			: AdvancedGameObject(stage) {}

		/**
		 * @brief �C���X�^���X���擾
		 *
		 * @return �C���X�^���X
		 */
		static shared_ptr<T> GetInstance() {
			if (m_ownInstance.get() == 0) {
				throw BaseException(
					L"�C���X�^���X����������Ă��܂���",
					L"if (m_ownInstance.get() == 0)",
					L"BaseSingletonGameObject::GetInstance()");
			}
			return m_ownInstance;
		}
	};
}