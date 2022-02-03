#include "stdafx.h"
#include "Project.h"

namespace basecross {
	OneShotUI::OneShotUI(const shared_ptr<Stage>& stage,
		const shared_ptr<GameObject>& owner,
		float lifeSpan, const wstring& texKey,
		const TransformData& transformData)
		:BaseUI(stage, transformData),
		m_owner(owner), m_lifeSpan(lifeSpan),
		m_textureKey(texKey), m_state(State::FadeIn), m_timer(lifeSpan),
		m_movingDirection(Vec3(0, 10, 0))
	{}

	void OneShotUI::OnCreate() {
		Vec2 origin(0.0f);
		auto size = Utility::GetTextureSize(m_textureKey);
		// �e�N�X�`�����W��UV���`
		vector<Vec2> uvs, uv = {
			origin,
			origin + Vec2(size.x,0.0f),
			origin + Vec2(0.0f, size.y),
			origin + size
		};
		// �e�N�X�`�����W����UV���W�ɕϊ�
		Utility::ConvertToUVCoordinates(uv, m_textureKey, uvs);
		Col4 color(1.0f);
		// ���_�̃f�[�^ (�ԍ��͍��ォ��E���܂�)
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-size.x,+size.y,0.0f),color,uvs[0]}, //0
			{Vec3(+size.x,+size.y,0.0f),color,uvs[1]}, //1

			{Vec3(-size.x,-size.y,0.0f),color,uvs[2]}, //2
			{Vec3(+size.x,-size.y,0.0f),color,uvs[3]},  //3
		};
		// ���_�C���f�b�N�X
		vector<uint16_t> indices = {
			0, 1, 2, // ��̎O�p�`
			2, 1, 3  // ���̎O�p�`
		};

		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_textureKey);

		SetAlphaActive(true);

		AddComponent<LifeSpan>(m_lifeSpan + 0.5f);
		auto fadeComp = AddComponent<FadeComponent>();
		fadeComp->SetFadeTime(0.25f);
		fadeComp->FadeIn();
	}

	void OneShotUI::OnUpdate() {
		auto fadeComp = GetComponent<FadeComponent>();
		switch (m_state)
		{
		case State::FadeIn:
			if (!fadeComp->IsFadeActive())
				m_state = State::Normal;
			break;
		case State::Normal:
			if (m_timer.Count()) {
				m_state = State::FadeOut;
				fadeComp->FadeOut();
			}
			break;
		case State::FadeOut:
			if (!fadeComp->IsFadeActive())
				Destroy<OneShotUI>();
			break;
		default:
			break;
		}

		if (m_owner) {
			auto ownerPos = m_owner->GetComponent<Transform>()->GetPosition();
			auto uiPos = Utility::ConvertWorldToScreen(GetStage()->GetView(), ownerPos);
			GetTransform()->SetPosition(uiPos + m_transformData.Position);
		}
		m_transformData.Position += m_movingDirection * App::GetApp()->GetElapsedTime();
	}
}