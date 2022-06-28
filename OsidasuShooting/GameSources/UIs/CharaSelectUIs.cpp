/*!
@file CharaSelectUILetter.cpp
@brief キャラクターセレクト画面の文字UIの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void BaseSprite::CreateSprite(wstring textureKey, float sideSize, float highSize) {
		m_textureKey = textureKey;	// テクスチャ
		Vec2 origin(0.0f);
		auto size = Utility::GetTextureSize(m_textureKey);
		// テクスチャ座標でUVを定義
		vector<Vec2> uvs, uv = {
			origin,
			origin + Vec2(size.x,0.0f),
			origin + Vec2(0.0f, size.y),
			origin + size
		};

		if (sideSize == NULL) m_sideSize = m_oneSize;
		else m_sideSize = sideSize;	// 横幅

		if (m_highSize == NULL) m_highSize = m_oneSize;
		else m_highSize = highSize;	// 縦幅

		m_fSidSize = size.x;		// 使用する画像の横幅全体
		m_fHigSize = -size.y;		// 使用する画像の縦幅全体

		m_sideSize = m_fSidSize / m_sideSize;
		m_highSize = m_fHigSize / m_highSize;

		auto color = Col4{ 1.0f };

		vector<VertexPositionColorTexture> vertices = {
			{Vec3(m_zeroSize, m_zeroSize, m_zeroSize), color, Vec2(m_zeroSize, m_zeroSize)},
			{Vec3(m_sideSize, m_zeroSize, m_zeroSize), color, Vec2(m_oneSize, m_zeroSize)},
			{Vec3(m_zeroSize, m_highSize, m_zeroSize), color, Vec2(m_zeroSize,  m_oneSize)},
			{Vec3(m_sideSize, m_highSize, m_zeroSize), color, Vec2(m_oneSize,  m_oneSize)}
		};

		vector<uint16_t> indeces = {
			0,1,2,
			1,3,2
		};

		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indeces);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_textureKey);

		SetAlphaActive(true);
	}

	void BaseSprite::SettingScale(Vec3 scale) {
		m_scale = scale;
		auto ptrTrans = GetComponent<Transform>();
		auto scl = m_scale;
		ptrTrans->SetScale(scl);
	}

	// ポジションをセンターに合わせる
	void BaseSprite::SettingPositionSenter(Vec3 position) {
		auto ptrTrans = GetComponent<Transform>();
		auto xSntrPos = m_sideSize * m_helfSize;
		auto ySntrPos = m_highSize * m_helfSize;

		auto pos = ptrTrans->GetPosition();
		Vec3 senterPos(xSntrPos, ySntrPos, 0);
		pos.x = (pos.x - senterPos.x * m_scale.x) + position.x;
		pos.y = (pos.y - senterPos.y * m_scale.y) + position.y;
		ptrTrans->SetPosition(pos);
	}

	// ピボットポイント設定
	void BaseSprite::SettingPivot() {
		auto ptrTrans = GetComponent<Transform>();
		auto xPivot = m_sideSize * m_helfSize;
		auto yPivot = m_highSize * m_helfSize;
		ptrTrans->SetPivot(Vec3(xPivot, -yPivot, 1.0f));
		//ptrTrans->SetPivot(GetComponent<Transform>()->GetPosition());
	}

	//-----------------------------------------------------------------//

	// CharacterSelectと書かれたスプライトを表示するための情報
	void CharacterStringUI::OnCreate() {
		auto texture = L"CharacterSelect";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.525f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// ケッテイ(決定)と書かれたスプライトを表示するための情報
	void DecisionSpriteUI::OnCreate() {
		auto texture = L"Decision";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.375f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// キャンセルと書かれたスプライトを表示するための情報
	void CancelSpriteUI::OnCreate() {
		auto texture = L"Cancel";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.375f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//
	// 
	// モドル(戻る)と書かれたスプライトを表示するための情報
	void GoToTitleSpriteUI::OnCreate() {
		auto texture = L"GoToTitle";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.375f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// ススム(進む)と書かれたスプライトを表示するための情報
	void GoToSelectSpriteUI::OnCreate() {
		auto texture = L"GoToSelect";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.375f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// Aと書かれたスプライトを表示するための情報
	void AButtonSpriteUI::OnCreate() {
		auto texture = L"AButton";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.3f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// Bと書かれたスプライトを表示するための情報
	void BButtonSpriteUI::OnCreate() {
		auto texture = L"BButton";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.3f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// ReadytoFightと書かれたスプライトを表示するための情報
	void ReadyToFightUI::OnCreate() {
		auto texture = L"ReadyToFight";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.75f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// OK!!と書かれたスプライトを表示するための情報
	void OKSpriteUI::OnCreate() {
		auto texture = L"OK";

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.65f));
		//BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// Icon
	void CharaIcon::OnCreate() {
		auto texture = L"";
		switch (m_iconNumber)
		{
		case 0:
			texture = L"LaserMark";
			break;

		case 1:
			texture = L"TankMark";
			break;

		default:
			texture = L"LaserIcon";
		}

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(texture, NULL, NULL); 
		BaseSprite::SettingScale(Vec3(0.675f));
		//BaseSprite::SettingPositionSenter(m_setPos);
	}

	void CharaIcon::OnUpdate() {
		//auto ptrTrans = GetComponent<Transform>();
		//auto scl = ptrTrans->GetScale();
		//ptrTrans->SetScale(scl * 1.01f);
	}

	//-----------------------------------------------------------------//

	// 各ステータス項目を表示するための情報
	void StatusSpriteUI::OnCreate() {
		auto texture = L"";
		switch (m_spriteNumber)
		{
		case 0:
			texture = L"Power";
			break;

		case 1:
			texture = L"Speed";
			break;

		case 2:
			texture = L"Weight";
			break;

		default:
			break;
		}

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.325f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	Col4 StatusSpriteUI::StetusColor() {
		auto color = Col4();
		switch (m_spriteNumber)
		{
		case 0:
			color = Col4(1.0f, 0.5f, 0.5f, 1.0f);
			break;

		case 1:
			color = Col4(0.5f, 1.0f, 1.0f, 1.0f);
			break;

		case 2:
			color = Col4(1.0f, 1.0f, 0.5f, 1.0f);
			break;

		default:
			break;
		}

		return color;
	}

	//-----------------------------------------------------------------//

	// ステータスを表示するための情報
	void StatusGauge::OnCreate() {
		auto texture = L"Gauge";

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.8675f, 0.55f, 1.0f)* 0.75f);

		m_defaultGauge = ptrTrans->GetScale().x;
		m_setScale = ptrTrans->GetScale();
		//BaseSprite::SettingPositionSenter(m_setPos);
	}

	void StatusGauge::GetCharaStutas(int charaNumber, int stutasNumber) {
		const auto& app = App::GetApp();
		const auto& delta = app->GetElapsedTime();

		auto ptrTrans = GetComponent<Transform>();

		// 前の情報を渡す
		if (charaNumber != m_nowCharaNum) {
			// 時間を初期化
			m_easingTime = 0;
		
			// 今のナンバーを渡す
			m_nowCharaNum = charaNumber;

			// 今のゲージの数値を代入
			m_beforeStatus = ptrTrans->GetScale().x;
		}

		// イージングが完了した時
		if (m_easingTime >= m_easingAllTime) {
			// 今の数値を代入
			m_beforeStatus = m_setStutas;
		}
		else m_easingTime += delta;


		// キャラクターの各ステータスを取得する
		switch (charaNumber) {
		case 0: // レーザー
			m_setStutas = GetLaserStutas(stutasNumber);
			break;

		case 1: // タンク
			m_setStutas = GetTankStutas(stutasNumber);
			break;
		}

		// イージング処理
		Easing <float> easingGauge;	
		 
		//auto gauge = ptrTrans->GetScale();
		auto setGauge =  easingGauge.EaseInOut(EasingType::Exponential, m_beforeStatus, m_setStutas, m_easingTime,m_easingAllTime);

		m_setScale.x = setGauge;
		ptrTrans->SetScale(m_setScale);

	}

	float StatusGauge::GetLaserStutas(int stutasNumber) {
		auto gauge = GetComponent<Transform>()->GetScale();
		switch (stutasNumber) {
		case 0:
			m_power = m_defaultGauge * 0.5f;
			return m_power;
			break;
		case 1:
			m_speed = m_defaultGauge * 0.5f;
			return m_speed;
			break;
		case 2:
			m_weight = m_defaultGauge * 0.5f;
			return m_weight;
			break;
		}
	}

	float StatusGauge::GetTankStutas(int stutasNumber) {
		auto gauge = GetComponent<Transform>()->GetScale();
		switch (stutasNumber) {
		case 0:
			m_power = m_defaultGauge * 0.9f;
			return m_power;
			break;
		case 1:
			m_speed = m_defaultGauge * 0.25f;
			return m_speed;
			break;
		case 2:
			m_weight = m_defaultGauge * 0.75f;
			return m_weight;
			break;
		}
	}

	//-----------------------------------------------------------------//

	// ゲージの後ろを表示するための情報
	void StatusGaugeBack::OnCreate() {
		auto texture = L"GaugeBackGround";

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.675f, 0.5f, 1.0f));
		//BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//
	
	// 三角形を表示するための情報
	void TriangleSprite::OnCreate() {
		auto texture = L"";
		texture = L"Triangle";

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(texture, NULL, NULL);

		BaseSprite::SettingScale(Vec3(0.675f));
		BaseSprite::SettingPositionSenter(m_setPos);

		pos = ptrTrans->GetPosition();
		m_defPos = pos.x;
	}

	// 左右いずれかが入力されたときに指定位置に移動する
	void TriangleSprite::CharacterSelectingAnimation(const CONTROLER_STATE& getStick,bool stick,int gamePadID) {
		const auto& ctrlVec = App::GetApp()->GetInputDevice().GetControlerVec()[gamePadID];
		auto ctrlX = 0.0f;
		if (ctrlVec.bConnected) {
			ctrlX = ctrlVec.fThumbLX;
		}

		auto moveLeft = ctrlX <= -1.0f || ctrlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT;
		auto moveRight = ctrlX >= 1.0f || ctrlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT;

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();

		// 左へ
		if (moveLeft) {
			auto move = m_defPos - m_movePos;
			pos.x = move;
		}
		// 右へ
		else if (moveRight) {
			auto move = m_defPos + m_movePos;
			pos.x = move;
		}

		ptrTrans->SetPosition(pos);
			
	}

	void TriangleSprite::OnUpdate() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();

		// 定位置に戻る
		if (pos.x != m_defPos)
		{
			if (!m_isReTriangle) {
				pos.x += 1;
				if (m_defPos <= pos.x) {
					pos.x = m_defPos;
				}
			}
			else {
				pos.x -= 1;
				if (m_defPos >= pos.x) {
					pos.x = m_defPos;
				}
			}
		}
		ptrTrans->SetPosition(pos);
	}

	//-----------------------------------------------------------------//

	// Bボタン長押しで反応するゲージ
	void GoBackTitleGauge::OnCreate() {
		auto texture = L"Gauge";

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.685f, 0.075f, 1.0f));
		//BaseSprite::SettingPositionSenter(m_setPos);

		auto transComp = GetComponent<Transform>();
		auto scale = transComp->GetScale();	// スケール取得
		m_maxGauge = scale.x;				// 最大値取得
		scale.x = 0;						// ゲージを0にする
		transComp->SetScale(scale);

		m_isGoBackTitle = false;
	}

	void GoBackTitleGauge::GaugeMove() {
		auto& app = App::GetApp();

		auto transComp = GetComponent<Transform>();
		auto scale = transComp->GetScale();

		const auto& ctrlVec = app->GetInputDevice().GetControlerVec();

		// 誰か一人以上Bボタンを押していた場合true
		auto PushBButton = (
			(ctrlVec[0].bConnected && ctrlVec[0].wButtons & XINPUT_GAMEPAD_B));

		// ゲージが最大に達していないとき
		if (!m_isGoBackTitle) {
			if (PushBButton) {
				if (m_maxGauge < scale.x) {
					scale.x = m_maxGauge;
					PushBButton = false;
					m_isGoBackTitle = true;
				}

				scale.x += m_delta * m_maxGauge * m_addGaugeMlt;
			}
			else {
				scale.x = 0;
			}
		}

		SetDrawActive(PushBButton || m_isGoBackTitle);

		transComp->SetScale(scale);
	}
	
	void GoBackTitleGauge::OnUpdate() {
		auto& app = App::GetApp();
		m_delta = app->GetElapsedTime();
		GaugeMove();
	}

	bool GoBackTitleGauge::GetGoBackTitle() {
		return m_isGoBackTitle;
	}

	//-----------------------------------------------------------------//

	// ゲージの後ろを表示するための情報
	void GoBackTitleGaugeBack::OnCreate() {
		auto texture = L"GaugeBackGround";

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.7f, 0.125f, 1.0f));
		//BaseSprite::SettingPositionSenter(m_setPos);
	}

	void GoBackTitleGaugeBack::OnUpdate() {
		SetDrawActive(m_Gauge->GetDrawActive());
	}

	//-----------------------------------------------------------------//
}