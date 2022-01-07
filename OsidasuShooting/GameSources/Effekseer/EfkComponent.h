/*!
@file   EfkComponent.h
@brief  Effekseer���g�p���邽�߂̃R���|�[�l���g
*/

#pragma once
#include "stdafx.h"
#include "Effekseer/EfkEffect.h"
#include "StageObject/AdvancedGameObject.h"

namespace basecross {
	/**
	 * @brief ��ԃ^�C�v
	 */
	enum class SpaceType {
		World,	// ���[���h
		Local	// ���[�J��
	};
	/**
	 * @brief ���W�w��
	 */
	enum class CoordinateType {
		Absolute,	// ���
		Relative	// ����
	};
	/**
	 * @brief �G�t�F�N�g�R���|�[�l���g
	 */
	class EfkComponent : public Component {
	private:
		// �G�t�F�N�g�f�[�^�\����
		struct EfkData {
			// �G�t�F�N�g�f�[�^�̃|�C���^
			Effekseer::EffectRef EffectData;
			// �G�t�F�N�g�n���h��
			Effekseer::Handle Handle;
			// �Đ����̃I�t�Z�b�g�f�[�^
			TransformData Offset;
			// �O��̃G�t�F�N�g���~�����ɍĐ����J�n���邩
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
		// �L�[,�G�t�F�N�g�f�[�^�̃}�b�v
		map<wstring, EfkData> m_effectDataMap;
		// �}�l�[�W���[�̃|�C���^
		Effekseer::ManagerRef m_manager;
		// �Đ����x
		float m_playSpeed;
		// �g�p������
		SpaceType m_useSpace;
		// ���W�w��
		CoordinateType m_coordinateType;
		/**
		 * @brief �Q�[���I�u�W�F�N�g�̈ʒu���擾
		 *
		 * @return �Q�[���I�u�W�F�N�g�̈ʒu
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
		 * @brief �g�p����G�t�F�N�g�̐ݒ�
		 *
		 * @param key �G�t�F�N�g�̃L�[
		 * @param offset �I�t�Z�b�g�f�[�^
		 * @param noStopLastEffect �O��̃G�t�F�N�g���~�����ɍĐ����J�n���邩
		 */
		void SetEffectResource(const wstring& key, const TransformData& offset, bool noStopLastEffect);
		/**
		 * @brief �g�p����G�t�F�N�g�̐ݒ�
		 *
		 * @param key �G�t�F�N�g�̃L�[
		 * @param offset �I�t�Z�b�g�f�[�^
		 */
		void SetEffectResource(const wstring& key, const TransformData& offset);
		/**
		 * @brief �g�p����G�t�F�N�g�̐ݒ�
		 *
		 * @param key �G�t�F�N�g�̃L�[
		 */
		void SetEffectResource(const wstring& key);

		/**
		 * @brief �G�t�F�N�g�̍Đ�
		 *
		 * @param key �G�t�F�N�g�̃L�[
		 */
		void Play(const wstring& key);
		/**
		 * @brief �G�t�F�N�g�̒�~
		 *
		 * @param key �G�t�F�N�g�̃L�[
		 */
		void Stop(const wstring& key);
		/**
		 * @brief ���ׂẴG�t�F�N�g���~
		 */
		void StopAll();
		/**
		 * @brief �G�t�F�N�g�̈ꎞ��~�i���łɈꎞ��~���Ă���ꍇ�͂�������Đ��j
		 *
		 * @param key �G�t�F�N�g�̃L�[
		 */
		void Pause(const wstring& key);

		void SetRotation(const wstring& key, const Vec3& rotation);


		/**
		 * @brief �ʒu�̓���
		 *
		 * @param key �G�t�F�N�g�̃L�[
		 */
		void SyncPosition(const wstring& key);

		void SetPosition(const wstring& key, const Vec3& position);

		/**
		 * @brief �L�[�̃G�t�F�N�g���Đ�����
		 *
		 * @param key �G�t�F�N�g�̃L�[
		 * @return �Đ����Ă���:true/�Đ����Ă��Ȃ�:false
		 */
		bool IsPlaying(const wstring& key);

		/**
		 * @brief �R���|�[�l���g�ɓo�^����Ă��邷�ׂẴG�t�F�N�g���Đ�����
		 *
		 * @return �Đ����Ă���:true/�Đ����Ă��Ȃ�:false
		 */
		bool IsPlaying();

		void SetCoordinateType(CoordinateType coordinateType);
	};
}
