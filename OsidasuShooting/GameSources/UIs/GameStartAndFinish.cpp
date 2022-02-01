#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StartCountDown::OnCreate() {
		m_number = ObjectFactory::Create<Number>(GetStage(), 3);
		m_number->GetTransform()->SetPosition(m_offsetPos);

		m_uiEffect = ObjectFactory::Create<UIEffect>(GetStage(),
			L"StartEffect", Vec2(5, 6), 30);
		m_uiEffect->GetTransform()->SetScale(Vec3(2));

		m_startSprite = ObjectFactory::Create<SimpleSprite>(
			GetStage(), L"Start", TransformData(Vec3(0), Vec3(1.2f)));

		auto trigger = AddComponent<OnceTrigger>();
		trigger->SetFunction(L"Start",
			[] {
				SoundManager::GetInstance()->Play(L"StartSE");
			}
		);
	}
	void StartCountDown::OnUpdate() {
		auto trigger = GetComponent<OnceTrigger>();

		if (!m_countDownTimer.Count()) {
			auto number = (int)(m_countDownTimer.GetLeftTime() + 1.0f);
			m_number->SetValue(number);
			if (number != m_lastValue && number != 0) {
				SoundManager::GetInstance()->Play(L"CountDownSE");
			}
			m_lastValue = number;
		}
		if (m_countDownTimer.IsTimeUp()) {
			m_uiEffect->OnUpdate();
			m_uiEffect->SetUpdateActive(true);
			trigger->LaunchFunction(L"Start");
		}
	}

	void StartCountDown::OnDraw() {
		if (!m_countDownTimer.IsTimeUp()) {
			m_number->OnDraw();
		}
		else {
			if (!m_startDisplayTimer.Count()) {
				m_uiEffect->OnDraw();
				m_startSprite->OnDraw();
			}
			else {
				SetActive(false);
			}
		}
	}

	//--------------------------------------------------------------
	//--------------------------------------------------------------

	void FinishSprite::OnCreate() {
		m_finishSprite = ObjectFactory::Create<SimpleSprite>(
			GetStage(), L"Finish", TransformData(Vec3(0), Vec3(1.2f)));

		m_uiEffect = ObjectFactory::Create<UIEffect>(GetStage(),
			L"StartEffect", Vec2(5, 6), 30);
		m_uiEffect->GetTransform()->SetScale(Vec3(2));
		m_uiEffect->SetUpdateActive(true);
		SoundManager::GetInstance()->Play(L"FinishSE");
	}

	void FinishSprite::OnUpdate() {
		m_uiEffect->OnUpdate();
	}

	void FinishSprite::OnDraw() {
		m_uiEffect->OnDraw();
		m_finishSprite->OnDraw();
	}

	//--------------------------------------------------------------
	//--------------------------------------------------------------

	void CountDown10Sec::OnCreate() {
		Vec2 origin(0.0f);
		auto size = Vec2(256);
		// テクスチャ座標でUVを定義
		vector<Vec2> uvs, uv = {
			origin,
			origin + Vec2(size.x,0.0f),
			origin + Vec2(0.0f, size.y),
			origin + size
		};
		auto halfSize = size / 2.0f;
		// テクスチャ座標からUV座標に変換
		Utility::ConvertToUVCoordinates(uv, m_textureKey, uvs);
		Col4 color(1);
		// 頂点のデータ (番号は左上から右下まで)
		vertices = {
			{Vec3(-halfSize.x,+halfSize.y,0.0f),color,uvs[0]}, //0
			{Vec3(+halfSize.x,+halfSize.y,0.0f),color,uvs[1]}, //1

			{Vec3(-halfSize.x,-halfSize.y,0.0f),color,uvs[2]}, //2
			{Vec3(+halfSize.x,-halfSize.y,0.0f),color,uvs[3]},  //3
		};
		// 頂点インデックス
		vector<uint16_t> indices = {
			0, 1, 2, // 上の三角形
			2, 1, 3  // 下の三角形
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(m_textureKey);
		// テクスチャの繰り返し設定(Wrap)
		drawComp->SetSamplerState(SamplerState::AnisotropicWrap);
		drawComp->SetDepthStencilState(DepthStencilState::Read);
		drawComp->SetDiffuse(Col4(1, 1, 1, 0.5f));

		SetAlphaActive(true); // 透明をサポートする&両面描画になる
	}

	void CountDown10Sec::OnUpdate() {
		auto countDown = GetStage()->GetSharedGameObject<CountDown>(L"ForCountDown");

		if (countDown) {
			auto time = countDown->GetTime();
			if (time >= 1) {
				auto size = Vec2(256);
				Vec2 origin(0.0f);
				origin.x = size.x * (int)(11 - time);
				// テクスチャ座標でUVを定義
				vector<Vec2> uvs, uv = {
					origin,
					origin + Vec2(size.x,0.0f),
					origin + Vec2(0.0f, size.y),
					origin + size
				};
				auto halfSize = size / 2.0f;
				// テクスチャ座標からUV座標に変換
				Utility::ConvertToUVCoordinates(uv, m_textureKey, uvs);

				for (int i = 0; i < vertices.size(); i++) {
					vertices[i].textureCoordinate = uvs[i];
				}

				auto drawComp = GetComponent<PCTSpriteDraw>();
				drawComp->UpdateVertices(vertices);
			}
			else {
				SetActive(false);
			}
		}
	}
}