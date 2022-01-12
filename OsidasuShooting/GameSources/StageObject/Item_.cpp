//adjust the variable .... Item

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	namespace modifiedClass {
		void Item::OnCreate()
		{
			auto drawComp = AddComponent<PNTStaticDraw>();
			drawComp->SetMeshResource(L"DEFAULT_CUBE");

			if (m_isRandom) {
				drawComp->SetTextureResource(L"RandomItem");
			}
			else {
				switch (spawnItem)
				{
				case ItemType::Bomb:
					drawComp->SetTextureResource(L"BombItem");
					break;
				case ItemType::Energy:
					drawComp->SetTextureResource(L"EnergyItem");
					break;
					//case ItemType::Debuff:
						//break;
				case ItemType::totalItems:
					break;
				default:
					break;
				}
			}
			//auto transform = GetComponent<Transform>();

			auto gravity = AddComponent<Gravity>();
			auto collision = AddComponent<CollisionObb>();

			auto shadowComp = AddComponent<Shadowmap>();
			shadowComp->SetMeshResource(L"DEFAULT_CUBE");
		}
		void Item::OnUpdate()
		{
			auto& app = App::GetApp();
			float deltaTime = app->GetElapsedTime();

			if (stayTime > 0)
			{
				stayTime -= deltaTime;//�@���܂鎞��
				return;
			}
			//���܂邪���Ԃ��I�������_�ł��n�܂�܂�

			//�_�ł̏���
			blinkingTime -= deltaTime;
			timeChecker += deltaTime;
			float colorAdjustment;

			if (timeChecker < blinkFadeInTime)
			{
				colorAdjustment = timeChecker / blinkFadeInTime;
			}
			else if (timeChecker < (blinkFadeInTime + blinkStayTime))
			{
				colorAdjustment = 1.0f;
			}
			else if (timeChecker < (blinkFadeInTime + blinkStayTime + blinkFadeOutTime))
			{
				colorAdjustment = 1.0f - (timeChecker - (blinkFadeInTime + blinkStayTime)) / blinkFadeOutTime;
			}
			else
			{
				timeChecker = 0;
				colorAdjustment = 0.0f;

				// ����_�ł��I�������_�ł̑��x��������
				blinkingSpeed += 0.0001f;
				blinkFadeInTime -= blinkingSpeed;
				blinkFadeOutTime -= blinkingSpeed;

				if (blinkFadeInTime < 0)
				{
					blinkFadeInTime = blinkingSpeed;
				}
				if (blinkFadeOutTime < 0)
				{
					blinkFadeOutTime = blinkingSpeed;
				}
				// ����_�ł��I�������_�ł̑��x��������..�I��
			}

			SetAdjustColor(colorAdjustment);
			//�_�ł̏���..�I��

			//�@�_�ł̎��Ԃ��I������畨�̂�������
			if (blinkingTime < 0)
			{
				GetStage()->RemoveGameObject<Item>(GetThis<Item>());
			}
		}
	}
}