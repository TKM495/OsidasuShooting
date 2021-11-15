/*!
@file   BaseMenu.h
@brief  ���j���[�̊��N���X
 */

#pragma once
#include "Cursor.h"
#include "UIs/StringSprite2.h"
#include "stdafx.h"

namespace basecross {
	// ���j���[���ڂ̕\���ɕK�v�ȍ\���̂�p�ӂ���
	struct MenuElement {
		Vec2 pos;        // ���W�i�[�p�ϐ�
		wstring name;    // ���ږ��i�[�p�ϐ�
		wstring sendMsg; // ���郁�b�Z�[�W
		bool flg = true; // �L������
	};

	class BaseMenu : public GameObject {
	protected:
		// �J�[�\���̈ړ�����
		enum class MenuDirection {
			Vertical,  //��������
			Horizontal //��������
		};

	private:
		// ���j���[�v�f�̃x�N�^�[�z��
		vector<MenuElement> m_menuElement;
		// ���j���[�̕���
		vector<shared_ptr<StringSprite2>> m_stringSprite;
		// ���j���[�̕����̃t���[��
		//vector<shared_ptr<illusionFrame>> m_illusionFrame;
		// �I�[�f�B�I�擾�p
		shared_ptr<XAudio2Manager> m_audio;
		// ���j���[�̗v�f��
		int m_menuNum;
		// ���I�����Ă��郁�j���[
		int m_nowMenuNum;
		// �J�[�\���̈ړ�����
		MenuDirection m_dir;
		// �J�ڒx��
		float m_delayTime;
		// �J�ڃt���O
		bool m_bChange;
		// �x�����Ԍv���p
		float m_delayDelta;
		// �_�ł̎��Ԍv���p
		float m_delta;
		// �_�ł̃��[�g
		float m_rate;
		// �J�[�\���̈ړ����x
		float m_cursorSp;
		// ���j���[�̌��݂̏��
		bool m_bActive;
		// �J�[�\���A�N�e�B�u���̐F
		Col4 m_activeCol;
		// ���j���[�̕`�惌�C���[
		int m_drawLayer;
		/**
		 * @brief �`�惌�C���[�̃��Z�b�g
		 *
		 * @param layer �`�悷�郌�C���[
		 */
		void ResetDrawLayer(int layer);
	protected:
		/**
		 * @brief ���j���[�\�z
		 */
		void SetUpMenu();
		/**
		 * @brief �{�^���������ꂽ�Ƃ��̏���
		 *
		 * @param element �I�����ꂽ���j���[�v�f
		 */
		virtual void OnPushButton(MenuElement element);
		/**
		 * @brief �{�^���������ꂽ�Ƃ��̏���
		 *
		 * @param mes �I�����ꂽ���j���[������MenuElement��sendMsg
		 */
		virtual void OnPushButton(wstring mes);
		/**
		 * @brief �{�^���������ꂽ�Ƃ��̏���
		 */
		virtual void OnPushButton();
		/**
		 * @brief �V�[�����J�ڂ���Ƃ��̏���
		 *
		 * @param mes ���郁�b�Z�[�W
		 */
		virtual void SendEvent(wstring mes);
		/**
		 * @brief ���Z�b�g�O�̏���
		 */
		virtual void BeforeReset() {}
		/**
		 * @brief �I�����̍Đ�
		 */
		virtual void PlayDecisionSE();
		/**
		 * @brief �I�����̍Đ�
		 *
		 * @param mes ���������b�Z�[�W
		 */
		virtual void PlayDecisionSE(wstring mes);
		/**
		 * @brief �{�^����������Ă���J�ڂ܂ł̎��Ԃ̐ݒ�
		 *
		 * @param time �J�ڂ���܂ł̎���
		 */
		void SetDelayTime(float time) {
			m_delayTime = time;
		}
		/**
		 * @brief ���j���[�v�f��z��ɓ����
		 *
		 * @param element ����郁�j���[�v�f
		 */
		void PushBackElement(const MenuElement& element) {
			m_menuElement.push_back(element);
		}
		/**
		 * @brief ���j���[�̈ړ������̐ݒ�
		 *
		 * @param dir �ړ�����
		 */
		void SetMenuDirection(MenuDirection dir) {
			m_dir = dir;
		}
		/**
		 * @brief �J�ڃt���O�������Ă��邩
		 *
		 * @return �����Ă����true/�����Ă��Ȃ��Ƃ���false
		 */
		bool IsChange() {
			return m_bChange;
		}
		/**
		 * @brief ���ׂẴ��j���[�v�f�̎擾
		 *
		 * @return ���j���[�v�f�̃x�N�^�[�z��
		 */
		vector<MenuElement>& GetMenuElement() {
			return m_menuElement;
		}

	public:
		/**
		 * @brief �R���X�g���N�^
		 *
		 * @param stage �X�e�[�W
		 */
		BaseMenu(const shared_ptr<Stage>& stage)
			: GameObject(stage),
			m_menuNum(0),
			m_nowMenuNum(0),
			m_dir(MenuDirection::Vertical),
			m_delayTime(0.0f),
			m_bChange(false),
			m_delayDelta(0.0f),
			m_delta(0.0f),
			m_cursorSp(10.0f),
			m_audio(App::GetApp()->GetXAudio2Manager()),
			m_bActive(true),
			m_rate(4.0f),
			m_activeCol(Col4(240.0f, 168.0f, 0.0f, 1.0f) / 255.0f),
			m_drawLayer(0) {}

		virtual void OnCreate() override {}
		virtual void OnUpdate() override;

		/**
		 * @brief ���j���[�̕\���A��\��
		 *
		 * @param flg true:�\��/false:��\��
		 */
		void SetDrawMenu(bool flg);
		/**
		 * @brief ���Z�b�g
		 */
		virtual void Reset();

		/**
		 * @brief ���j���[�̕`�惌�C���[�̐ݒ�
		 *
		 * @param layer �`�惌�C���[
		 */
		void SetMenuDrawLayer(int layer) {
			m_drawLayer = layer;
			ResetDrawLayer(m_drawLayer);
		}
	};
}
//end basecross
