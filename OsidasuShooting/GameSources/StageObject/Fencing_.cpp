#include "stdafx.h"
#include "Project.h"

namespace basecross {
	namespace modifiedClass {
		Fencing::Fencing(const shared_ptr<Stage>& stage, const wstring& line)
			:AdvancedGameObject(stage)
		{
			auto tokens = DataExtracter::DelimitData(line);
			m_transformData = DataExtracter::TransformDataExtraction(tokens);

			showTime = (float)_wtof(tokens[10].c_str());
			hideTime = (float)_wtof(tokens[11].c_str());
		}

		void Fencing::OnCreate()
		{
			blinkingTime = 3.0f;
			blinkShowTime = 0.1f;
			blinkHideTime = 0.3f;

			//showTime = 1.0f;
			//hideTime = 1.0f;

			vector<VertexPositionNormalTexture> vertices;
			vector<uint16_t> indices;

			AdvancedMeshUtil::CreateCube(2.0f, m_transformData.Scale, vertices, indices);

			auto drawComp = AddComponent<PNTStaticDraw>();
			drawComp->CreateOriginalMesh(vertices, indices);
			drawComp->SetOriginalMeshUse(true);
			drawComp->SetTextureResource(L"Block");
			drawComp->SetOwnShadowActive(true);
			drawComp->SetSamplerState(SamplerState::LinearWrap);

			auto collComp = AddComponent<CollisionObb>();
			collComp->AddExcludeCollisionTag(L"Block");
			collComp->SetFixed(true);

			auto shadowComp = AddComponent<Shadowmap>();
			shadowComp->SetMeshResource(L"DEFAULT_CUBE");

			auto stage = GetStage();
			auto blinking = AddComponent<Blinking>();
		}

		void Fencing::OnUpdate()
		{
			auto& app = App::GetApp();
			auto deltaTime = app->GetElapsedTime();

			timeChecker -= deltaTime;

			auto blinking = GetComponent<Blinking>();
			if (status == Fencing::Status::Hiding || status == Fencing::Status::Showing)
			{
				bool showHideStatus = blinking->GetShowHideStatus();
				SetDrawActive(showHideStatus);
			}

			if (timeChecker > 0)
			{
				return;
			}

			switch (status)
			{
			case Fencing::Status::Showing:
				timeChecker = showTime - blinkingTime;
				status = Fencing::Status::BlinkingToHide;
				SetDrawActive(true);
				break;
			case Fencing::Status::BlinkingToHide:
				blinking->SetToggleTime(blinkShowTime, blinkHideTime, blinkingTime);
				blinking->SetShowHide();
				blinking->StartBlinking();

				timeChecker = blinkingTime;
				status = Fencing::Status::Hiding;

				break;
			case Fencing::Status::Hiding:
				timeChecker = hideTime - blinkingTime;
				status = Fencing::Status::BlinkingToShow;
				SetDrawActive(false);
				break;
			case Fencing::Status::BlinkingToShow:
				SetDrawActive(true);

				//blinking->SetToggleTime(blinkShowTime, blinkHideTime, blinkingTime);// showTime and hideTime has been swaped
				//blinking->SetShowHide();
				//blinking->StartBlinking();

				timeChecker = blinkingTime;
				status = Fencing::Status::Showing;
				break;
			default:
				break;
			}
		}
	}
}