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
			{Vec3(m_sideSize, m_zeroSize, m_zeroSize), color, Vec2( m_oneSize, m_zeroSize)},
			{Vec3(m_zeroSize, m_highSize, m_zeroSize), color, Vec2(m_zeroSize,  m_oneSize)},
			{Vec3(m_sideSize, m_highSize, m_zeroSize), color, Vec2( m_oneSize,  m_oneSize)}
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

	void BaseSprite::SettingScale(Vec3 sizes) {
		m_scale = sizes;
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
	void DecisionSpriteUI::OnCreate(){
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
		BaseSprite::SettingScale(Vec3(0.75f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// Icon
	void CharaIcon::OnCreate() {
		auto texture = L"";
		switch (m_iconNumber)
		{
		case 0:
			texture = L"LaserIcon";
			break;

		case 1:
			texture = L"TankIcon";
			break;

		default:
			texture = L"LaserIcon";
		}

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.675f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// カーソルスプライトを表示するための情報
	void SelectCursor::OnCreate() {
		auto texture = L"SelectCursor";

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.675f));
	}

	// アイコンのそれぞれの位置とアイコンの最大値
	void SelectCursor::GetIconDatas(int number,Vec3 pos) {
		m_iconPos[number] = pos;
		m_iconMaxNumber = number;
	}

	void SelectCursor::OnUpdate() {
		CursorController();
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();

		//MoveCursor();
		WaitAnimetion();
	}

	void SelectCursor::CursorController() {
		// スティック、方向パッド
		const auto& ctrlVec = 
			App::GetApp()->GetInputDevice().GetControlerVec()[m_gamePadID];
		auto ctrlX = 0.0f;
		//auto ctrlY = 0.0f;
		if (ctrlVec.bConnected) {
			ctrlX = ctrlVec.fThumbLX;
			//ctrlY = ctrlVec.fThumbLY;
		}
		auto trans = GetComponent<Transform>();
		auto transPos  = trans->GetPosition();
		auto moveRight = ctrlX >=  1.0f || ctrlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
		auto moveLeft  = ctrlX <= -1.0f || ctrlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT;
		//auto moveDown  = ctrlY <= -1.0f || ctrlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN;
		//auto moveUp	   = ctrlY >=  1.0f || ctrlVec.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP;	

		if (!m_isSetStick) {
			m_moveTime = 0; // 初期化
			// 右へ
			if (moveRight) {
				m_isSetStick = true;
				if (m_iconNumber < m_iconMaxNumber) {
					m_iconNumber++;
					SoundManager::GetInstance()->Play(L"CharacterSelectingSE");
					//m_nowPos = GetComponent<Transform>()->GetPosition();
				}
				else NotMoveAnimetion();
			}
			// 左へ
			else if(moveLeft) {
				m_isSetStick = true;
				if (m_iconNumber > 0) {
					m_iconNumber--;
					SoundManager::GetInstance()->Play(L"CharacterSelectingSE");
					//m_nowPos = GetComponent<Transform>()->GetPosition();
				}
				else NotMoveAnimetion();
			}
		}
		else if (!moveLeft && !moveRight) m_isSetStick = false;
		//MoveCursor();
		GetComponent<Transform>()->SetPosition(m_iconPos[m_iconNumber]);
	}

	void SelectCursor::CursorControl() {}

	void SelectCursor::WaitAnimetion() {
		const auto& app = App::GetApp();
		const auto& delta = app->GetElapsedTime();

		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		auto color = ptrDraw->GetDiffuse();

		auto ptrTrans = GetComponent<Transform>();
		auto scale = ptrTrans->GetScale();
		auto pos = ptrTrans->GetPosition();

		if (color.w <= 0)  m_waitAnime = true;
		else if (color.w >= 1) m_waitAnime = false;

		if (m_waitAnime) {
			color.w += delta;
			scale -= delta * 0.005f;
			//pos.x += delta;
			//pos.y -= delta ;
		}
		else{
			color.w -= delta;
			scale += delta * 0.005f;
			//pos.x -= delta * 2;
			//pos.y += delta * 2;
		}

		ptrDraw->SetDiffuse(color);
		//ptrTrans->SetScale(scale);
		//ptrTrans->SetPosition(pos);
	}

	void SelectCursor::NotMoveAnimetion() {}

	void SelectCursor::MoveCursor() {
		//if (m_moveTime >= m_moveSpeed) {
		//	const auto& app = App::GetApp();
		//	const auto& delta = app->GetElapsedTime();

		//	m_moveTime += delta;
		//}

		//if (m_nowPos != m_iconPos[m_iconNumber]) {
		//	Vec3 easPos;
		//	Easing<Vec3> easing;
		//	easPos = easing.EaseInOut(EasingType::Quadratic, m_nowPos, m_iconPos[m_iconNumber], m_moveTime, m_moveSpeed);
		//	GetComponent<Transform>()->SetPosition(easPos);
		//}
	}

	int SelectCursor::SetCharacterID() { return m_iconNumber; }

	Vec3 SelectCursor::GetIconPos(int iconNum) { return m_iconPos[iconNum]; }

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

	//-----------------------------------------------------------------//

	// ステータスを表示するための情報
	void StatusGauge::OnCreate() {
		auto texture = L"Gauge";
		auto color = Col4{};	
		switch (m_spriteNumber)
		{
		case 0:
			break;

		case 1:
			break;

		case 2:
			break;

		default:
			break;
		}

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.675f, 0.5f, 1.0f)* 0.75f);

		m_defaultGauge = ptrTrans->GetScale().x;
		//BaseSprite::SettingPositionSenter(m_setPos);
	}

	void StatusGauge::GetCharaStutas(int charaNumber, int stutasNumber) {
		switch (charaNumber) {
		case 0:
			m_setScale = GetLaserStutas(stutasNumber);
			break;

		case 1:
			m_setScale = GetTankStutas(stutasNumber);
			break;
		}

		auto ptrTrans = GetComponent<Transform>();
		auto gauge = ptrTrans->GetScale();
		auto scl = m_setScale;
		ptrTrans->SetScale(scl);

	}

	Vec3 StatusGauge::GetLaserStutas(int stutasNumber) {
		auto gauge = GetComponent<Transform>()->GetScale();
		switch (stutasNumber) {
		case 0:
			m_power = Vec3(m_defaultGauge * 0.5f, gauge.y, gauge.z);
			return m_power;
			break;
		case 1:
			m_speed = Vec3(m_defaultGauge * 0.5f, gauge.y, gauge.z);
			return m_speed;
			break;
		case 2:
			m_weight = Vec3(m_defaultGauge * 0.5f, gauge.y, gauge.z);
			return m_weight;
			break;
		}
	}

	Vec3 StatusGauge::GetTankStutas(int stutasNumber) {
		auto gauge = GetComponent<Transform>()->GetScale();
		switch (stutasNumber) {
		case 0:
			m_power = Vec3(m_defaultGauge * 0.75f, gauge.y, gauge.z);
			return m_power;
			break;
		case 1:
			m_speed = Vec3(m_defaultGauge * 0.25f, gauge.y, gauge.z);
			return m_speed;
			break;
		case 2:
			m_weight = Vec3(m_defaultGauge * 0.75f, gauge.y, gauge.z);
			return m_weight;
			break;
		}
	}

	void StatusGauge::SetCharaStutas(float power, float speed, float weight) {
		//m_power = power;
		//m_speed = speed;
		//m_weight = weight;
	}

	void StatusGauge::OnUpdate() {
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
}