#pragma once
#include "stdafx.h"
#include "BaseUI.h"
#include "StageObject/PlayerBase.h"

namespace basecross {
	class PlayerFollowUI :public BaseUI {
		// UI�̃^�C�v
		enum class UIType {
			Normal,	// ����
			Bomb,	// ���e�֌W
		};
		// �I�u�W�F�N�g�f�[�^
		struct ObjectData {
			UIType Type;
			shared_ptr<BaseUI> UIObject;
			ObjectData(UIType type, const shared_ptr<BaseUI> ui) {
				this->Type = type;
				this->UIObject = ui;
			}
		};
		// �I�[�i�[
		shared_ptr<PlayerBase> m_owner;
		// �I�u�W�F�N�g�f�[�^
		vector<ObjectData> m_objectsData;
		// �I�t�Z�b�g
		Vec3 m_offset;
	public:
		PlayerFollowUI(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& player,
			const TransformData& transformData)
			:BaseUI(stage, transformData), m_owner(player),
			m_offset(Vec3(0.0f, 0.0f, 0.0f))
		{
			SetTransformInit(false);
		}

		void OnCreate()override;
		void OnUpdate()override;
		void OnDraw()override;
	};

	class PlayerPositionUI :public BaseUI {
		// �I�[�i�[
		shared_ptr<PlayerBase> m_owner;
		// �I�t�Z�b�g
		Vec3 m_offset;
		vector<shared_ptr<BaseUI>> m_uiObject;
		/**
		 * @brief ��ʓ��ɃN�����v
		 *
		 * @param value �x�N�g��
		 * @return ��ʓ��ɃN�����v���ꂽ�x�N�g��
		 */
		Vec3 ClampInScreen(const Vec3& value);
	public:
		PlayerPositionUI(const shared_ptr<Stage>& stage,
			const shared_ptr<PlayerBase>& player,
			const TransformData& transformData)
			:BaseUI(stage, transformData), m_owner(player),
			m_offset(Vec3(0.0f, 0.0f, 0.0f))
		{
			SetTransformInit(false);
		}
		void OnCreate()override;
		void OnUpdate()override;
		void OnDraw()override;
	};
}
