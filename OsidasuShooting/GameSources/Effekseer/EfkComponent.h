/*!
@file   EfkComponent.h
@brief  Effekseer���g�p���邽�߂̃R���|�[�l���g
*/

#pragma once
#include "stdafx.h"
#include "Effekseer/EfkEffect.h"

namespace basecross {
	/**
	 * @brief �G�t�F�N�g�R���|�[�l���g
	 */
	class EfkComponent : public Component {
		// �G�t�F�N�g�f�[�^�̃|�C���^
		Effekseer::EffectRef m_effectData;
		// �G�t�F�N�g�n���h��
		Effekseer::Handle m_handle;
		// �}�l�[�W���[�̃|�C���^
		Effekseer::ManagerRef m_manager;
		// �Đ����x
		float m_playSpeed;
		// �X�P�[��
		Vec3 m_scale;
		//��]
		Vec3 m_rotation;
		/**
		 * @brief �Đ����Ă��邩�ǂ���
		 *
		 * @return �Đ����Ă���:true/�Đ����Ă��Ȃ�:false
		 */
		bool IsPlaying();
		/**
		 * @brief �Q�[���I�u�W�F�N�g�̈ʒu���擾
		 *
		 * @return �Q�[���I�u�W�F�N�g�̈ʒu
		 */
		Vec3 GetGameObjectPosition();
	public:
		EfkComponent(const shared_ptr<GameObject>& gameObjectPtr);
		~EfkComponent() {}

		void OnCreate() override {}
		void OnUpdate() override {}
		void OnDraw()override {}

		/**
		 * @brief �g�p����G�t�F�N�g�̐ݒ�
		 *
		 * @param key �G�t�F�N�g�̃L�[
		 */
		void SetEffectResource(const wstring& key);
		/**
		 * @brief �g�p����G�t�F�N�g�̐ݒ�
		 *
		 * @param effectRes	shared_ptr<EfkEffectResource>
		 */
		void SetEffectResource(const shared_ptr<EfkEffectResource>& effectRes);

		/**
		 * @brief �G�t�F�N�g�̍Đ�
		 */
		void Play();
		/**
		 * @brief �G�t�F�N�g�̒�~
		 */
		void Stop();
		/**
		 * @brief �G�t�F�N�g�̈ꎞ��~�i���łɈꎞ��~���Ă���ꍇ�͂�������Đ��j
		 */
		void Pause();

		/**
		 * @brief �Đ����x�̐ݒ�
		 *
		 * @param speed �Đ����x�i�f�t�H���g��1�j
		 */
		void SetPlaySpeed(float speed = 1.0f);

		/**
		 * @brief ��]���Z�b�g�ideg�j
		 *
		 * @param rotation ��]��
		 */
		void SetRotation(const Vec3& rotation);

		/**
		 * @brief �X�P�[�����Z�b�g
		 *
		 * @param scale �X�P�[��
		 */
		void SetScale(const Vec3& scale);

		/**
		 * @brief �ʒu�̓���
		 */
		void SyncPosition();

		/**
		 * @brief �G�t�F�N�g�̈ʒu�����炷
		 *
		 * @param position ���炷��
		 */
		void AddLocation(const Vec3& position);
	};
}
