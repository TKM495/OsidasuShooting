/*!
@file EfkInterface.h
@brief Effekseer�G�t�F�N�g�̃C���^�[�t�F�C�X
*/

#pragma once

#include "stdafx.h"

#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <EffekseerSoundXAudio2.h>

#if _DEBUG
#pragma comment(lib, "Effekseerd.lib" )
#pragma comment(lib, "EffekseerRendererDX11d.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2d.lib" )
#else
#pragma comment(lib, "Effekseer.lib" )
#pragma comment(lib, "EffekseerRendererDX11.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.lib" )
#endif

using namespace Effekseer;

namespace basecross {
	class EfkInterface;

	/**
	 * @brief Effekseer�̃G�t�F�N�g�t�@�C���̊Ǘ��N���X
	 */
	class EfkEffect : public ObjectInterface {
		// �t�@�C���̖��O
		wstring m_FileName;
		// �G�t�F�N�g�|�C���^
		EffectRef m_Effect;
		// �C���^�[�t�F�C�X�ւ̃|�C���^
		weak_ptr<EfkInterface> m_EfkInterface;
		friend class EfkPlay;
	public:
		/**
		 * @brief �R���X���g�N�^
		 *
		 * @param iface		�C���^�[�t�F�C�X
		 * @param filename	�G�t�F�N�g�t�@�C����
		 */
		EfkEffect(const shared_ptr<EfkInterface>& iface, const wstring& filename);

		/**
		@brief	�f�X�g���N�^
		*/
		virtual ~EfkEffect();

		/**
		 * @brief ������
		 */
		virtual void OnCreate() override;
	};

	/**
	 * @brief Effekseer��Play�I�u�W�F�N�g�N���X�i���ۂɍĐ����̃I�u�W�F�N�g�j
	 */
	class EfkPlay : public ObjectInterface {
		// Effekseer�̃n���h��
		Handle m_Handle;
		// �C���^�[�t�F�C�X�̃|�C���^
		weak_ptr<EfkInterface> m_EfkInterface;
	public:
		/**
		 * @brief �R���X���g�N�^
		 *
		 * @param effect	�G�t�F�N�g
		 * @param Emitter	�G�~�b�^�[�i�����ꏊ�j
		 */
		EfkPlay(const shared_ptr<EfkEffect>& effect, const bsm::Vec3& Emitter);
		virtual ~EfkPlay();

		/**
		 * @brief �������i��֐��j
		 */
		void OnCreate() override {}

		/**
		 * @brief �G�t�F�N�g���X�g�b�v������
		 */
		void StopEffect();

		/**
		 * @brief �G�t�F�N�g���ړ�����
		 *
		 * @param Location �ړ��x�N�g���i���Ε����j
		 */
		void AddLocation(const bsm::Vec3& Location);
	};

	/**
	 * @brief Effekseer�̃C���^�[�t�F�C�X
	 */
	class EfkInterface : public ObjectInterface, public ShapeInterface {
		// Effekseer�̃}�l�[�W���[�|�C���^
		ManagerRef m_Manager;
		EffekseerRenderer::RendererRef m_Renderer;

		friend class EfkPlay;
		friend class EfkEffect;
	public:
		EfkInterface();
		virtual ~EfkInterface();

		/**
		 * @brief �r���[�Ǝˉe�s���ݒ肷��
		 *
		 * @param view �r���[�s��
		 * @param proj �ˉe�s��
		 */
		void SetViewProj(const bsm::Mat4x4& view, const bsm::Mat4x4& proj);

		virtual void OnCreate() override;
		virtual void OnUpdate()override;
		virtual void OnDraw()override;
	};
}
//end basecross
