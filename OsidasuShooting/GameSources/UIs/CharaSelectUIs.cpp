/*!
@file CharaSelectUILetter.cpp
@brief �L�����N�^�[�Z���N�g��ʂ̕���UI�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void BaseSprite::CreateSprite(wstring textureKey, float sideSize, float highSize) {
		m_textureKey = textureKey;	// �e�N�X�`��
		Vec2 origin(0.0f);
		auto size = Utility::GetTextureSize(m_textureKey);
		// �e�N�X�`�����W��UV���`
		vector<Vec2> uvs, uv = {
			origin,
			origin + Vec2(size.x,0.0f),
			origin + Vec2(0.0f, size.y),
			origin + size
		};

		if (sideSize == NULL) m_sideSize = m_oneSize;
		else m_sideSize = sideSize;	// ����

		if (m_highSize == NULL) m_highSize = m_oneSize;
		else m_highSize = highSize;	// �c��

		m_fSidSize = size.x;		// �g�p����摜�̉����S��
		m_fHigSize = -size.y;		// �g�p����摜�̏c���S��

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

	// �|�W�V�������Z���^�[�ɍ��킹��
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

	// �s�{�b�g�|�C���g�ݒ�
	void BaseSprite::SettingPivot() {
		auto ptrTrans = GetComponent<Transform>();
		auto xPivot = m_sideSize * m_helfSize;
		auto yPivot = m_highSize * m_helfSize;
		ptrTrans->SetPivot(Vec3(xPivot, -yPivot, 1.0f));
		//ptrTrans->SetPivot(GetComponent<Transform>()->GetPosition());
	}

	//-----------------------------------------------------------------//

	// CharacterSelect�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void CharacterStringUI::OnCreate() {
		auto texture = L"CharacterSelect";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.525f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// �P�b�e�C(����)�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void DecisionSpriteUI::OnCreate() {
		auto texture = L"Decision";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.375f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// �L�����Z���Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void CancelSpriteUI::OnCreate() {
		auto texture = L"Cancel";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.375f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//
	// 
	// ���h��(�߂�)�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void GoToTitleSpriteUI::OnCreate() {
		auto texture = L"GoToTitle";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.375f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// �X�X��(�i��)�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void GoToSelectSpriteUI::OnCreate() {
		auto texture = L"GoToSelect";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.375f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// A�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void AButtonSpriteUI::OnCreate() {
		auto texture = L"AButton";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.3f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// B�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void BButtonSpriteUI::OnCreate() {
		auto texture = L"BButton";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.3f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// ReadytoFight�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
	void ReadyToFightUI::OnCreate() {
		auto texture = L"ReadyToFight";

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.75f));
		BaseSprite::SettingPositionSenter(m_setPos);
	}

	//-----------------------------------------------------------------//

	// OK!!�Ə����ꂽ�X�v���C�g��\�����邽�߂̏��
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

	// �e�X�e�[�^�X���ڂ�\�����邽�߂̏��
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

	// �X�e�[�^�X��\�����邽�߂̏��
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

		// �O�̏���n��
		if (charaNumber != m_nowCharaNum) {
			// ���Ԃ�������
			m_easingTime = 0;
		
			// ���̃i���o�[��n��
			m_nowCharaNum = charaNumber;

			// ���̃Q�[�W�̐��l����
			m_beforeStatus = ptrTrans->GetScale().x;
		}

		// �C�[�W���O������������
		if (m_easingTime >= m_easingAllTime) {
			// ���̐��l����
			m_beforeStatus = m_setStutas;
		}
		else m_easingTime += delta;


		// �L�����N�^�[�̊e�X�e�[�^�X���擾����
		switch (charaNumber) {
		case 0: // ���[�U�[
			m_setStutas = GetLaserStutas(stutasNumber);
			break;

		case 1: // �^���N
			m_setStutas = GetTankStutas(stutasNumber);
			break;
		}

		// �C�[�W���O����
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

	// �Q�[�W�̌���\�����邽�߂̏��
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
	
	// �O�p�`��\�����邽�߂̏��
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

	// ���E�����ꂩ�����͂��ꂽ�Ƃ��Ɏw��ʒu�Ɉړ�����
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

		// ����
		if (moveLeft) {
			auto move = m_defPos - m_movePos;
			pos.x = move;
		}
		// �E��
		else if (moveRight) {
			auto move = m_defPos + m_movePos;
			pos.x = move;
		}

		ptrTrans->SetPosition(pos);
			
	}

	void TriangleSprite::OnUpdate() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();

		// ��ʒu�ɖ߂�
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

	// B�{�^���������Ŕ�������Q�[�W
	void GoBackTitleGauge::OnCreate() {
		auto texture = L"Gauge";

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(m_setPos);

		BaseSprite::CreateSprite(texture, NULL, NULL);
		BaseSprite::SettingScale(Vec3(0.685f, 0.075f, 1.0f));
		//BaseSprite::SettingPositionSenter(m_setPos);

		auto transComp = GetComponent<Transform>();
		auto scale = transComp->GetScale();	// �X�P�[���擾
		m_maxGauge = scale.x;				// �ő�l�擾
		scale.x = 0;						// �Q�[�W��0�ɂ���
		transComp->SetScale(scale);

		m_isGoBackTitle = false;
	}

	void GoBackTitleGauge::GaugeMove() {
		auto& app = App::GetApp();

		auto transComp = GetComponent<Transform>();
		auto scale = transComp->GetScale();

		const auto& ctrlVec = app->GetInputDevice().GetControlerVec();

		// �N����l�ȏ�B�{�^���������Ă����ꍇtrue
		auto PushBButton = (
			(ctrlVec[0].bConnected && ctrlVec[0].wButtons & XINPUT_GAMEPAD_B));

		// �Q�[�W���ő�ɒB���Ă��Ȃ��Ƃ�
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

	// �Q�[�W�̌���\�����邽�߂̏��
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