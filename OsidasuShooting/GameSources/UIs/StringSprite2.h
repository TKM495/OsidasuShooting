/*!
@file   StringSprite2.h
@brief  ������\���p�N���X
 */

#pragma once
#include "stdafx.h"
#include "Utility/CSVLoad.h"
#include "Component/FadeComponent.h"
#include "UIHeader.h"

namespace basecross {
	class StringSprite2 :public GameObject {
		// ���Ԍv���p
		float m_delta;
		// ��A�N�e�B�u�ɂȂ�܂ł̎���
		float m_deActiveTime;
		// ��A�N�e�B�u���ǂ���
		bool m_bDeactive;
		// �F
		Col4 m_color;
		// �����̃f�[�^
		SpriteDataFormat m_data;
		// �\�����镶���̖��O
		wstring m_name;
		// ���̐ݒ�
		Align::Horizontal m_horizontal;
		// �c�̐ݒ�
		Align::Vertical m_vertical;
		// ���_�f�[�^
		vector<VertexPositionColorTexture> vertices;

		int SearchDataIndex(const vector<SpriteDataFormat>& data);
	public:
		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param stage �X�e�[�W
		 * @param name �\������e�N�X�`��
		 * @param horizontal �����ʒu
		 * @param vertical �����ʒu
		 * @param color �F
		 */
		StringSprite2(const shared_ptr<Stage>& stage,
			wstring name,
			Align::Horizontal horizontal = Align::Horizontal::Center,
			Align::Vertical vertical = Align::Vertical::Center,
			Col4 color = Col4(0.0f, 0.0f, 0.0f, 1.0f))
			:GameObject(stage),
			m_name(name),
			m_horizontal(horizontal),
			m_vertical(vertical),
			m_color(color),
			m_delta(0.0f),
			m_deActiveTime(0.0f),
			m_bDeactive(false)
		{}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		/**
		 * @brief ���������̐ݒ�
		 *
		 * @param hor ���������̈ʒu
		 */
		void SetAlignHorizontal(Align::Horizontal hor);
		/**
		 * @brief ���������̐ݒ�
		 *
		 * @param ver ���������̈ʒu
		 */
		void SetAlignVertical(Align::Vertical ver);

		/**
		 * @brief �T�C�Y�̐ݒ�
		 *
		 * @param size �T�C�Y
		 */
		void SetSize(float size);
		/**
		 * @brief �ʒu�̐ݒ�
		 *
		 * @param pos �ʒu
		 */
		void SetPos(Vec2 pos);

		/**
		 * @brief �T�C�Y�̎擾
		 *
		 * @return �T�C�Y
		 */
		float GetSize();
		/**
		 * @brief �ʒu�̎擾
		 *
		 * @return �ʒu
		 */
		Vec3 GetPos();

		/**
		 * @brief �e�N�X�`���T�C�Y�̎擾
		 *
		 * @return �e�N�X�`���T�C�Y
		 */
		Vec2 GetTexSize() {
			return m_data.size;
		}

		/**
		 * @brief �t�F�[�h�R���|�[�l���g�̎擾
		 *
		 * @return �t�F�[�h�R���|�[�l���g
		 */
		shared_ptr<FadeComponent> GetFadeComp() {
			return GetComponent<FadeComponent>();
		}

		/**
		 * @brief �F�̐ݒ�
		 *
		 * @param color �F
		 */
		void SetColor(Col4 color);
		/**
		 * @brief �F�̎擾
		 *
		 * @return �F
		 */
		Col4 GetColor() {
			return m_color;
		}

		/**
		 * @brief ��A�N�e�B�u�ɂ���
		 *
		 * @param time ��A�N�e�B�u�܂ł̎���
		 */
		void Deactive(float time) {
			m_deActiveTime = time;
			SetUpdateActive(true);
		}
		/**
		 * @brief ��A�N�e�B�u�ɂ���
		 */
		void Deactive() {
			Deactive(0.0f);
		}
	};
}
//end basecross
