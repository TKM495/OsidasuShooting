#pragma once
#include "stdafx.h"

namespace basecross {
	/**
	 * @brief �ʒu�A�傫���A��]�̏������\����
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
	 * @brief �ʒu�ƕ��������\����
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
	 * @brief �ʒu�ƕ��������\����
	 */
	using ObjectPositionForward = Ray;

	/**
	 * @brief ���x�ȃQ�[���I�u�W�F�N�g�N���X
	 */
	class AdvancedGameObject :public GameObject {
		// OnCreate()�O�Ƀg�����X�t�H�[����m_transformData�ŏ��������邩
		bool m_isTransformInit;
	protected:
		// �g�����X�t�H�[���f�[�^
		//�i�q�N���X���Ńg�����X�t�H�[�����������Ă�������ɔ��f�͂���Ȃ��j
		TransformData m_transformData;
	public:
		AdvancedGameObject(const shared_ptr<Stage>& stage)
			:GameObject(stage), m_isTransformInit(true)
		{}

		virtual void OnPreCreate()override;

		/**
		 * @brief OnCreate()�O�Ƀg�����X�t�H�[�������������邩
		 *
		 * @param flg true:����������/false:���������Ȃ�
		 */
		void SetTransformInit(bool flg) {
			m_isTransformInit = flg;
		}

		/**
		 * @brief �g�����X�t�H�[���f�[�^���Z�b�g
		 *
		 * @param data �Z�b�g����g�����X�t�H�[���f�[�^
		 */
		void SetTransformData(const TransformData& data) {
			m_transformData = data;
			ApplyTransform();
		}

		/**
		 * @brief �g�����X�t�H�[���f�[�^��K�p
		 */
		void ApplyTransform();

		/**
		 * @brief �g�����X�t�H�[���R���|�[�l���g���擾
		 *
		 * @return �g�����X�t�H�[���R���|�[�l���g
		 */
		shared_ptr<Transform> GetTransform() {
			return GetComponent<Transform>();
		}

		/**
		 * @brief �Q�[���I�u�W�F�N�g�̐���
		 *
		 * @param ...params �p�����[�^
		 * @return �쐬���ꂽ�Q�[���I�u�W�F�N�g
		 */
		template<class T, typename... Ts>
		shared_ptr<T> InstantiateGameObject(Ts&&... params) {
			return GetStage()->AddGameObject<T>(params ...);
		}

		/**
		 * @brief ���g�̍폜
		 */
		template<class T>
		void Destroy() {
			GetStage()->RemoveGameObject<T>(GetThis<T>());
		}
	};
}
