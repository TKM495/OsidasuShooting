/*!
@file   ResultStage.cpp
@brief  ���U���g�X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ResultStage::CreateViewLight() {
		//const Vec3 eye(0.0f, 5.0f, -5.0f);
		//const Vec3 at(0.0f);
		const Vec3 eye(0.0f, 0.0f, -4.0f);
		const Vec3 at(0.4f, 0.0f, -2.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	// Winner���邢��Draw��\������
	void ResultStage::AddWinnerSprite(int player)
	{
		// �g�b�v����l�̏ꍇ
		if (m_isTopOnly) {
			// Winner�̈ʒu��ݒ肷��
			Vec3 winnerUIsPos = Vec3(-280, -220, 0); // �ʒu��ݒ肷��
			auto winnerUIs = AddGameObject<ResultWinOrDrowSprite>(winnerUIsPos, m_isTopOnly);
			auto winnerUIsTrans = winnerUIs->GetComponent<Transform>();
			winnerUIsPos = winnerUIsTrans->GetPosition(); // ���m�Ȑݒu�ꏊ�ɍX�V

			// �v���C���[�i���o�[�̈ʒu�����肷��
			auto playerNumber = AddGameObject<BattlePlayersUIs>(L"BPsUIs", player, Vec3(0));
			playerNumber->GetComponent<PCTSpriteDraw>()->SetDiffuse(m_playerTopColor);	// �v���C���[�̃J���[
			auto playUIsTrans = playerNumber->GetComponent<Transform>();
			// �v���C���[�̃i���o�[�̏ꏊ
			Vec3 playerNumberPos = winnerUIsPos - Vec3(-412.0f, -27.0f, 0);				// �i���o�[�̐ݒu�ꏊ��ݒ�
			playUIsTrans->SetPosition(playerNumberPos);
			Vec3 scale = Vec3(1.1f);
			playUIsTrans->SetScale(scale);
		}
		// �g�b�v����l�ȏ�̏ꍇ
		else {
			// Draw�̕����̕\���ʒu
			Vec3 drawUIsPos = Vec3(-160, -120, 0);
			float posX = drawUIsPos.x; // �ق��̏ꏊ�ł��g�p����̂ŕϐ��ɂ���
			auto drawUIs = AddGameObject<ResultWinOrDrowSprite>(drawUIsPos, m_isTopOnly);
			auto drawUIsTrans = drawUIs->GetComponent<Transform>();
			drawUIsPos = drawUIsTrans->GetPosition();

			auto resultDrawPlayer = 1;	// 1�l�ȏ�͊m���ɕ\�����邽�߁A���炩����1����
			auto maxDrawPlayer = 3;		// for�����[�v�񐔁A�ǉ��ōX�ɍő�3�l�\������̂�3����
			for (int i = 0; i < maxDrawPlayer; i++) {
				if (m_isPlayerDraw[i] == true) {
					resultDrawPlayer++;
				}
			}

			// ���Ԃ������v���C���[�̕\��
			auto playerNum = 0;
			auto playerNumber = AddGameObject<BattlePlayersUIs>(L"BPsUIs", player, Vec3(0));	// �z�u
			playerNumber->GetComponent<PCTSpriteDraw>()->SetDiffuse(m_playerColor[playerNum]);	// �J���[���Z�b�g
			auto playUIsTrans = playerNumber->GetComponent<Transform>();

			// �|�W�V����
			auto setPosition = Vec3(posX * 2.175f, -170.0f, 1.0f);
			// �X�P�[��
			Vec3 v3Scale = Vec3(0.75f);
			float fScale = 1.1f;
			auto setScale = v3Scale * (1 - 0.1f * (resultDrawPlayer * fScale));

			playUIsTrans->SetPosition(setPosition);
			playUIsTrans->SetScale(Vec3(setScale));

			// ����ȍ~�̃v���C���[
			auto setPosX = posX * 2.25f / resultDrawPlayer;
			for (int i = 0; i < maxDrawPlayer; i++) {
				playerNum++;
				if (m_isPlayerDraw[i] == true) {
					setPosition.x -= setPosX;
					auto playerNumber = AddGameObject<BattlePlayersUIs>(L"BPsUIs", player + playerNum, Vec3(0));
					playerNumber->GetComponent<PCTSpriteDraw>()->SetDiffuse(m_playerColor[playerNum]);
					auto playUIsTrans = playerNumber->GetComponent<Transform>();
					playUIsTrans->SetPosition(setPosition);
					playUIsTrans->SetScale(Vec3(setScale));
				}
			}
		}
	}

	// �e�v���C���[�̏���\��
	void ResultStage::AddResultSprites(Vec3 pos, int playerNum, int score, int dead, int rank)
	{
		// �t���[����z�u
		Vec3 scale = Vec3(1.2f);
		auto fream = AddGameObject<FreamSprite>(L"Fream", pos, scale);
		auto freamTrans = fream->GetComponent<Transform>();
		auto freamPos = freamTrans->GetPosition();
		fream->SetDrawLayer(1);

		// �J���[�擾
		auto playerColor = PlayerStatus::GetInstance()->GetPlayerColor(playerNum);
		// �ݒu����|�W�V����
		auto playerNumPos = pos + Vec3(-200.0f, 115.0f, 0.0f);
		// �v���C���[�̃i���o�[��\������
		auto playerNumber = AddGameObject<BattlePlayersUIs>(L"BPsUIs", playerNum, Vec3(0));
		// �i���o�[�ɐF��t����
		playerNumber->GetComponent<PCTSpriteDraw>()->SetDiffuse(playerColor);

		// �v���C���[�i���o�[�̐ݒu
		auto playUIsTrans = playerNumber->GetComponent<Transform>();
		playUIsTrans->SetPosition(playerNumPos);

		scale = Vec3(0.4f);
		playUIsTrans->SetScale(scale);
		playerNumber->SetDrawLayer(2);

		// �v���C���[�̏��ʂ�\��
		RankingPlayerSet(pos, rank);

		// �v���C���[�̃L���X�R�A
		auto scorePos = pos + Vec3(50.0f, 65.0f, 1.0f);			// �L���X�R�A�̃|�W�V�����ݒ�
		m_score = AddGameObject<ResultScore>(score, scorePos);	// �z�u
		m_score->SetDrawLayer(2);
		
		auto addIconPos = Vec3(-50.0f, -36.0f, 0.0f);

		auto killIconPos = scorePos + addIconPos;				// �A�C�R���̃|�W�V����
		AddGameObject<KillIcon>(killIconPos)->SetDrawLayer(2);	// �z�u

		// �v���C���[�̃f�X�X�R�A
		auto deadPos = Vec3(scorePos.x, scorePos.y - 60.0f, scorePos.z);	// �L���X�R�A�̃|�W�V�����ݒ�
		m_dead = AddGameObject<ResultScore>(dead, deadPos);					// �z�u
		m_dead->SetDrawLayer(2);
		auto deadIconPos = deadPos + addIconPos;							// �A�C�R���̃|�W�V����
		AddGameObject<DeadIcon>(deadIconPos)->SetDrawLayer(2);				// �z�u
	}

	// �v���C���[�̏��ʕ\��
	void ResultStage::RankingPlayerSet(Vec3 pos, int value) {
		auto playerRank = AddGameObject<BattlePlayersUIs>(L"RRUIs", value, Vec3(0));
		Vec3 addPos = Vec3(-165.0f, 75.0f, 0.0f);
		auto rankIconPos = pos + addPos;
		auto rankIconTrans = playerRank->GetComponent<Transform>();
		rankIconTrans->SetPosition(rankIconPos);
	}

	// �v���C���[�̏���
	void ResultStage::PlayersResult() {
		float addVec = 0;
		float setPosY = 0;

		auto allPlayer = PlayerManager::GetInstance()->GetSortedAllPlayer();
		int  loopCount = 0;	// for��
		int  drawPlayer = 0;// �\������v���C���[�̐�
		int  draw = 0;		// ��������
		bool isDraw = false;

		// ���ʂ��������ɏ��������
		for (auto player : allPlayer) {
			str = L"";
			switch (player->GetPlayerNumber())
			{
			case PlayerNumber::P1:
				str = L"P1";
				m_playersNumber = player->GetPlayerNumber();
				m_playersScore = player->GetCountKilledPlayer();
				m_playersDead = player->GetDeadCount();
				m_playerColor[loopCount] = PlayerStatus::GetInstance()->GetPlayerColor(PlayerNumber::P1);
				break;
			case PlayerNumber::P2:
				str = L"P2";
				m_playersNumber = player->GetPlayerNumber();
				m_playersScore = player->GetCountKilledPlayer();
				m_playersDead = player->GetDeadCount();
				m_playerColor[loopCount] = PlayerStatus::GetInstance()->GetPlayerColor(PlayerNumber::P2);
				break;
			case PlayerNumber::P3:
				str = L"P3";
				m_playersNumber = player->GetPlayerNumber();
				m_playersScore = player->GetCountKilledPlayer();
				m_playersDead = player->GetDeadCount();
				m_playerColor[loopCount] = PlayerStatus::GetInstance()->GetPlayerColor(PlayerNumber::P3);
				break;
			case PlayerNumber::P4:
				str = L"P4";
				m_playersNumber = player->GetPlayerNumber();
				m_playersScore = player->GetCountKilledPlayer();
				m_playersDead = player->GetDeadCount();
				m_playerColor[loopCount] = PlayerStatus::GetInstance()->GetPlayerColor(PlayerNumber::P4);
				break;
			default:
				break;
			}

			// �v���C���[�̏��ʂ̏���
			auto top = m_playersScore > m_playerTopScore;		// �Q�Ƃ��ꂽ�v���C���[�̃L���X�R�A���b��g�b�v��荂���ꍇ
			auto killeDraw = m_playersScore == m_playerTopScore;// �Q�Ƃ��ꂽ�v���C���[�̃L���X�R�A���b��g�b�v�Ɠ����ȏꍇ
			
			// �g�b�v�̃f�X�X�R�A��r
			auto topDeadWin  = killeDraw && m_playersDead  < m_playerTopDead; // �f�X�X�R�A���b��g�b�v��菭�Ȃ��Ƃ�
			auto topDrawDead = killeDraw && m_playersDead == m_playerTopDead; // �f�X�X�R�A���b��g�b�v�Ɠ����Ƃ�
			auto drawDead = 
				 m_previousScore == m_playersScore && m_previousDead == m_playersDead; // �f�X�X�R�A���O�̏��ʂ̃v���C���[�Ɠ����Ƃ�

			// ��r
			// �g�b�v�ɂȂ����ꍇ
			if (loopCount == 0 || top || topDeadWin) {
				m_playerTop = m_playersNumber;
				m_playerTopScore = m_playersScore;
				m_playerTopDead = m_playersDead;
				m_playerTopColor = m_playerColor[loopCount];
				m_isTopOnly = true;
			}
			else if (topDrawDead || drawDead) {
				m_playerDraw[drawPlayer] = m_playersNumber;
				if (topDrawDead) {
					m_isTopOnly = false;
					m_isPlayerDraw[drawPlayer] = true;
				}
				drawPlayer++;
				draw++;
				isDraw = true;
			}
			else {
				draw = 0;
			}
			auto rankingNum = loopCount - draw;

			// �v���C���[�̌��ʂ�\������
			AddResultSprites(Vec3(400 + addVec, 250 + setPosY, 0),
				(UINT)m_playersNumber + 1, m_playersScore, m_playersDead, rankingNum);

			//Debug::GetInstance()->Log(draw);
			addVec += 12.5f;
			setPosY -= 170;

			loopCount++;

			// ��r�p�ɕʂ̊֐��ɑ��
			m_previousScore = m_playersScore;
			m_previousDead = m_playersDead;
		}

		// �g�b�v�̃v���C���[
		//m_playerTop = allPlayer[0]->GetPlayerNumber();
	}

	// �s������v���C���[
	void ResultStage::WinnerPlayer() {
		PlayersResult();

		// �g�b�v����l�̂Ƃ�
		if (m_isTopOnly) {
			auto scale = Vec3(0.75f);
			auto topPlayer = AddGameObject<ResultPlayer>(
				TransformData(Vec3(0.0f, 1.0f, 0.0f), scale, Vec3(0, XMConvertToRadians(180.0f), 0)),
				m_playerTop, StageManager::GetInstance()->GetPlayerType(m_playerTop));

			auto playerPos = topPlayer->GetComponent<Transform>()->GetPosition();
			playerPos += Vec3(-1.0f, 2.0f,0);
			auto confetti = AddGameObject<Confetti>(playerPos);
			topPlayer->PlayWin();
		}
		// �g�b�v����l�ȏ�̂Ƃ�
		else {
			auto maxDrawPlayer = 3;
			auto resultDrawPlayer = 0;
			auto posX = 0.5f;
			for (int i = 0; i < maxDrawPlayer; i++) {
				if (m_isPlayerDraw[i] == true) {
					resultDrawPlayer++;
				}
			}

			auto resultPosX = -resultDrawPlayer;
			auto setPosX = 0.75f;
			auto setPosZ = (float)resultDrawPlayer;
			auto setScale = Vec3(0.65f) * (1 - 0.1f * (resultDrawPlayer * 1.25f));

			auto topPlayer = AddGameObject<ResultPlayer>(
				TransformData(Vec3(resultPosX * setPosX, 1.0f, setPosZ), setScale, Vec3(0, XMConvertToRadians(180.0f), 0)),
				m_playerTop, StageManager::GetInstance()->GetPlayerType(m_playerTop));

			for (int i = 0; i < maxDrawPlayer; i++) {
				if (m_isPlayerDraw[i] == true) {
					resultPosX += 2;
					auto drawPlayer = AddGameObject<ResultPlayer>(
						TransformData(Vec3(resultPosX * setPosX, 1.0f, setPosZ), setScale, Vec3(0, XMConvertToRadians(180.0f), 0)),
						m_playerDraw[i], StageManager::GetInstance()->GetPlayerType(m_playerDraw[i]));
					posX += 1.0f;
					resultDrawPlayer++;
				}
			}
		}
		AddGameObject<Block>(TransformData(Vec3(0, -1, 0), Vec3(100, 1, 100)));
	}

	void ResultStage::OnCreate() {
		try {
			AddGameObject<EfkInterface>();
			auto efkpath = App::GetApp()->GetDataDirWString() + L"Effects/";
			EfkEffectResource::RegisterEffectResource(L"Bullet", efkpath + L"Bullet.efk");
			EfkEffectResource::RegisterEffectResource(L"Explosion", efkpath + L"fire.efk");
			EfkEffectResource::RegisterEffectResource(L"Hit", efkpath + L"Hit.efk");
			EfkEffectResource::RegisterEffectResource(L"Jump", efkpath + L"Jump.efk");
			EfkEffectResource::RegisterEffectResource(L"Hover", efkpath + L"Hover.efk");
			EfkEffectResource::RegisterEffectResource(L"Bomb", efkpath + L"Bomb.efk");
			EfkEffectResource::RegisterEffectResource(L"Smoke", efkpath + L"Smoke.efk");
			EfkEffectResource::RegisterEffectResource(L"Smoke", efkpath + L"Smoke.efk");

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//AddGameObject<Debug>();
			//Debug::GetInstance()->Log(L"CurrentStage : ResultStage");

			AddGameObject<SimpleSprite>(L"BackGround00")->SetDrawLayer(-1);

			//PlayersResult();
			WinnerPlayer();

			PlayerManager::DeleteInstance();

			AddWinnerSprite((UINT)m_playerTop + 1);

			//Debug::GetInstance()->Log(L"Button A : CharacterSelect");
			//Debug::GetInstance()->Log(L"Button B : Title");

			SoundManager::GetInstance()->PlayLoop(L"ResultBGM");

			AddGameObject<GoToSelectSpriteUI>(Vec3(-0, -320, 0));
			AddGameObject<GoToTitleSpriteUI>(Vec3(-430, -320, 0));
			AddGameObject<AButtonSpriteUI>(Vec3(120, -320, 0));
			AddGameObject<BButtonSpriteUI>(Vec3(-310, -320, 0));
		}
		catch (...) {
			throw;
		}
	}

	void ResultStage::OnUpdate() {
		auto& app = App::GetApp();
		const auto& cntlPad = app->GetInputDevice().GetControlerVec();

		auto cntl = 4 - 1; // �ő�R���g���[���� - 1
		for (int i = 0; i <= cntl; i++) {
			if (!m_sceneChangeBlock) {
				// �L�����N�^�[�Z���N�g�ɖ߂�
				if (cntlPad[i].wPressedButtons & XINPUT_GAMEPAD_A) {
					SoundManager::GetInstance()->Play(L"DecisionSE");
					PostEvent(0.5f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToCharacterSelectStage");
					m_sceneChangeBlock = true;
				}
				// �^�C�g����ʂɖ߂�
				if (cntlPad[i].wPressedButtons & XINPUT_GAMEPAD_B) {
					SoundManager::GetInstance()->Play(L"DecisionSE");
					PostEvent(0.5f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToTitleStage");
					m_sceneChangeBlock = true;
				}
			}
		}
	}

	void ResultStage::OnDestroy() {
		SoundManager::GetInstance()->StopAll();
	}
}