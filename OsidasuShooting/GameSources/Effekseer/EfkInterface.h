/*!
@file  EfkInterface.h
@brief Effekseer�G�t�F�N�g�̃C���^�[�t�F�C�X
*/

#pragma once
#include "stdafx.h"
#include "Effekseer/EfkEffect.h"

namespace basecross {
	/**
	 * @brief Effekseer�̃C���^�[�t�F�C�X
	 */
	class EfkInterface : public GameObject {
		// Effekseer�̃}�l�[�W���[�|�C���^
		Effekseer::ManagerRef m_Manager;
		EffekseerRenderer::RendererRef m_Renderer;
		// ���g�̃C���X�^���X
		static shared_ptr<EfkInterface> m_ownInstance;

		/**
		 * @brief �r���[�Ǝˉe�s���ݒ肷��
		 *
		 * @param view �r���[�s��
		 * @param proj �ˉe�s��
		 */
		void SetViewProj(const bsm::Mat4x4& view, const bsm::Mat4x4& proj);
	public:
		EfkInterface(const shared_ptr<Stage>& stage);
		virtual ~EfkInterface();

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDraw()override;

		/**
		 * @brief �C���X�^���X�̎擾
		 *
		 * @return EfkInterface�̃C���X�^���X��
		 */
		static shared_ptr<EfkInterface> GetInstance();

		/**
		 * @brief �}�l�[�W���[�̎擾
		 *
		 * @return �}�l�[�W���[�̃|�C���^
		 */
		Effekseer::ManagerRef GetManager() {
			return m_Manager;
		}
	};
}
//end basecross
