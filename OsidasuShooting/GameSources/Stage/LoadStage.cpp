/*!
@file LoadStage.cpp
@brief ���[�h�X�e�[�W�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	bool LoadStage::m_Loaded = false;
	mutex LoadStage::mtx;

	void LoadStage::LoadResourceFunc() {
		mtx.lock();
		m_Loaded = false;
		mtx.unlock();

		// ���\�[�X�ǂݍ���
		const auto& app = App::GetApp();
		auto dir = app->GetDataDirWString();

		// �X�v���C�g
		auto path = dir + L"Sprite/";

		app->RegisterTexture(L"AButton", path + L"AButton.png");
		app->RegisterTexture(L"BButton", path + L"BButton.png");
		app->RegisterTexture(L"Back", path + L"Back.png");
		app->RegisterTexture(L"Cancel", path + L"Cancel.png");
		app->RegisterTexture(L"Decision", path + L"Decision.png");
		app->RegisterTexture(L"Fream", path + L"Fream.png");
		app->RegisterTexture(L"GoToSelect", path + L"GoToSelect.png");
		app->RegisterTexture(L"GoToTitle", path + L"GoToTitle.png");
		app->RegisterTexture(L"Next", path + L"Next.png");
		app->RegisterTexture(L"OK", path + L"OK.png");
		app->RegisterTexture(L"PushAButton", path + L"PushAButton.png");

		app->RegisterTexture(L"SelectCursor", path + L"SelectCursor.png");

		app->RegisterTexture(L"Power", path + L"Power.png");
		app->RegisterTexture(L"Speed", path + L"Speed.png");
		app->RegisterTexture(L"Weight", path + L"Weight.png");

		// 3Way
		app->RegisterTexture(L"3WayIcon", path + L"3WayIcon.png");

		// LaserUI/Icon
		app->RegisterTexture(L"LaserIcon", path + L"LaserIcon.png");
		app->RegisterTexture(L"LaserPicture1", path + L"LaserPicture1.png");
		app->RegisterTexture(L"LaserPicture2", path + L"LaserPicture2.png");
		app->RegisterTexture(L"LaserPicture3", path + L"LaserPicture3.png");
		app->RegisterTexture(L"LaserPicture4", path + L"LaserPicture4.png");

		// Missile
		app->RegisterTexture(L"MissileIcon", path + L"MissileIcon.png");

		// TankUI/Icon
		app->RegisterTexture(L"TankIcon", path + L"Tank.png");
		app->RegisterTexture(L"TankPicture1", path + L"TankPicture1.png");
		app->RegisterTexture(L"TankPicture2", path + L"TankPicture2.png");
		app->RegisterTexture(L"TankPicture3", path + L"TankPicture3.png");
		app->RegisterTexture(L"TankPicture4", path + L"TankPicture4.png");

		app->RegisterTexture(L"CharacterSelect", path + L"CharacterSelect.png");
		app->RegisterTexture(L"ReTriangle", path + L"ReTriangle.png");
		app->RegisterTexture(L"Triangle", path + L"Triangle.png");

		app->RegisterTexture(L"ReadyToFight", path + L"ReadyToFight.png");

		app->RegisterTexture(L"Winner", path + L"Winner.png");
		app->RegisterTexture(L"Draw", path + L"Draw.png");

		app->RegisterTexture(L"BombBack", path + L"BombBackGround.png");
		app->RegisterTexture(L"GaugeBackGround", path + L"GaugeBackGround.png");
		app->RegisterTexture(L"Gauge", path + L"Gauge.png");

		app->RegisterTexture(L"Title", path + L"Title.png");
		app->RegisterTexture(L"PushAButton", path + L"PushAButton.png");
		app->RegisterTexture(L"Number", path + L"Number.png");
		app->RegisterTexture(L"BPsUIs", path + L"BattlePlayersUI256x256.png");	// �Q�[�����̃A�C�R��
		app->RegisterTexture(L"BPsUIs2", path + L"BattlePlayersUI256x256_2.png");//
		app->RegisterTexture(L"BomberUI", path + L"BomberUI.png");				// �Q�[�W���̔��e���A�C�R��
		app->RegisterTexture(L"CircleGauge", path + L"CircleGauge.png");
		app->RegisterTexture(L"BarGauge", path + L"BarGauge.png");
		app->RegisterTexture(L"GaugeColor", path + L"GaugeColor.png");
		app->RegisterTexture(L"Block", path + L"Block.png");
		app->RegisterTexture(L"Reflector", path + L"Reflector.png");
		app->RegisterTexture(L"BreakBlock", path + L"BreakBlock.png");

		app->RegisterTexture(L"Winner", path + L"Winner.png");
		app->RegisterTexture(L"KillIcon", path + L"KillIcon.png");
		app->RegisterTexture(L"DeadIcon", path + L"DeadIcon.png");
		app->RegisterTexture(L"Kill", path + L"Kill.png");
		app->RegisterTexture(L"Dead", path + L"Dead.png");
		app->RegisterTexture(L"RRUIs", path + L"ResultRankingUI256x256.png");


		app->RegisterTexture(L"BombBack", path + L"BombBackGround.png");
		app->RegisterTexture(L"GaugeBackGround", path + L"GaugeBackGround.png");

		app->RegisterTexture(L"Gauge", path + L"Gauge.png");
		app->RegisterTexture(L"Start", path + L"Fight.png");
		app->RegisterTexture(L"Finish", path + L"Finish.png");
		app->RegisterTexture(L"Planet", path + L"Planet.png");
		app->RegisterTexture(L"BackGround00", path + L"BackGround00.png");

		app->RegisterTexture(L"BombPlus", path + L"BombPlus.png");
		app->RegisterTexture(L"EnergyPlus", path + L"EnergyPlus.png");

		app->RegisterTexture(L"ImpactPoint", path + L"ImpactPoint.png");
		app->RegisterTexture(L"CircleShadow", path + L"CircleShadow.png");

		// �e�X�g�p�X�v���C�g
		app->RegisterTexture(L"Test", path + L"test.png");

		// CSV�t�@�C��
		path = dir + L"CSV/";
		CSVLoad::GetInstance()->RegisterFile(L"PlayerInfo", path + L"PlayerInfo.csv");
		CSVLoad::GetInstance()->RegisterFile(L"PlayerFollowUI", path + L"PlayerFollowUI.csv");
		CSVLoad::GetInstance()->RegisterFile(L"Camera", path + L"Camera.csv");
		CSVLoad::GetInstance()->RegisterFile(L"ModelAnimationData", path + L"ModelAnimationData.csv");

		//XML�t�@�C��
		path = dir + L"XML/";
		XMLLoad::GetInstance()->RegisterFile(L"PlayerStatus", path + L"PlayerStatus.xml");

		// ���f��
		// Laser
		path = dir + L"Models/LaserCharacter/";
		for (int i = 0; i < 4; i++) {
			auto number = Util::IntToWStr(i + 1);
			auto modelMesh = MultiMeshResource::CreateBoneModelMultiMesh(path + L"Player" + number + L"/", L"LaserPlayer" + number + L".bmf");
			app->RegisterResource(L"LaserPlayer" + number, modelMesh);
		}
		// Missile
		path = dir + L"Models/MissileCharacter/";
		for (int i = 0; i < 4; i++) {
			auto number = Util::IntToWStr(i + 1);
			auto modelMesh = MultiMeshResource::CreateBoneModelMultiMesh(path + L"Player" + number + L"/", L"TankPlayer" + number + L".bmf");
			app->RegisterResource(L"MissilePlayer" + number, modelMesh);
		}

		// �o���p�[
		path = dir + L"Models/Bumper/";
		auto modelMesh = MeshResource::CreateStaticModelMesh(path, L"Bumper.bmf");
		app->RegisterResource(L"Bumper", modelMesh);

		// �A�C�e��
		path = dir + L"Models/Item/";
		modelMesh = MeshResource::CreateStaticModelMesh(path, L"Energy.bmf");
		app->RegisterResource(L"EnergyItemModel", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(path, L"Bomb.bmf");
		app->RegisterResource(L"BombItemModel", modelMesh);

		// ���ʉ�
		path = dir + L"Sound/SE/";
		app->RegisterWav(L"EmptyBombSE", path + L"EmptyBomb.wav");
		app->RegisterWav(L"DecisionSE", path + L"Decision.wav");
		app->RegisterWav(L"CancelSE", path + L"Cancel.wav");
		app->RegisterWav(L"CharacterDecisionSE", path + L"CharacterDecision.wav");
		app->RegisterWav(L"CharacterSelectingSE", path + L"CharacterSelecting.wav");
		app->RegisterWav(L"FightSE", path + L"Fight.wav");
		app->RegisterWav(L"ExplosionSE", path + L"Explosion.wav");
		app->RegisterWav(L"FallSE", path + L"Fall.wav");
		app->RegisterWav(L"HoverSE", path + L"Hover.wav");
		app->RegisterWav(L"JumpSE", path + L"Jump.wav");
		app->RegisterWav(L"ShotSE", path + L"Shot.wav");
		app->RegisterWav(L"ThrowBombSE", path + L"ThrowBomb.wav");
		app->RegisterWav(L"WarningSE", path + L"Warning.wav");
		app->RegisterWav(L"GetItemSE", path + L"GetItem.wav");

		// BGM
		path = dir + L"Sound/BGM/";
		app->RegisterWav(L"Game1BGM", path + L"Game1.wav");
		app->RegisterWav(L"Game2BGM", path + L"Game2.wav");
		app->RegisterWav(L"ResultBGM", path + L"Result.wav");
		app->RegisterWav(L"SelectBGM", path + L"Select.wav");
		app->RegisterWav(L"TitleBGM", path + L"Title.wav");

		mtx.lock();
		m_Loaded = true;
		mtx.unlock();
	}

	void LoadStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void LoadStage::OnCreate() {
		auto& app = App::GetApp();
		auto dir = app->GetDataDirWString();
		// �X�v���C�g
		auto path = dir + L"Sprite/";
		app->RegisterTexture(L"Loading", path + L"NowLoading.png");

		AddGameObject<EfkInterface>();
		path = dir + L"Effects/";
		EfkEffectResource::RegisterEffectResource(L"Bullet", path + L"Bullet.efk");
		EfkEffectResource::RegisterEffectResource(L"Explosion", path + L"Explosion.efk");
		EfkEffectResource::RegisterEffectResource(L"Death", path + L"fire.efk");
		EfkEffectResource::RegisterEffectResource(L"Hit", path + L"Hit.efk");
		EfkEffectResource::RegisterEffectResource(L"HeavyHit", path + L"HeavyHit.efk");
		EfkEffectResource::RegisterEffectResource(L"Jump", path + L"Jump.efk");
		EfkEffectResource::RegisterEffectResource(L"Hover", path + L"Hover.efk");
		EfkEffectResource::RegisterEffectResource(L"Bomb", path + L"Bomb.efk");
		EfkEffectResource::RegisterEffectResource(L"Smoke", path + L"Smoke.efk");
		EfkEffectResource::RegisterEffectResource(L"Laser", path + L"Laser.efk");
		EfkEffectResource::RegisterEffectResource(L"Respawn", path + L"Respawn.efk");
		EfkEffectResource::RegisterEffectResource(L"BreakBlock", path + L"BreakBlock.efk");
		EfkEffectResource::RegisterEffectResource(L"Confetti", path + L"Confetti.efk");
		EfkEffectResource::RegisterEffectResource(L"Shield", path + L"Shield.efk");

		//���̃��\�[�X��ǂݍ��ރX���b�h�̃X�^�[�g
		thread LoadThread(LoadResourceFunc);
		//�I���܂ł͑҂��Ȃ�
		LoadThread.detach();

		CreateViewLight();
		AddGameObject<Debug>();
		Debug::GetInstance()->Log(L"CurrentStage : LoadStage");

		auto sprite = AddGameObject<SimpleSprite>(L"Loading",
			TransformData(Vec3(350.0f, -300.0f, 0.0f), Vec3(0.7f)));
		AddGameObject<TransitionSprite>();
	}

	void LoadStage::OnUpdate() {
		switch (m_state)
		{
		case State::Loading:
			if (m_Loaded && m_timer.Count()) {
				//���\�[�X�̃��[�h���I��&�w��̎��Ԃ��o�߂�����t�F�[�h�J�n
				TransitionSprite::GetInstance()->FadeIn();
				m_state = State::FadeOut;
				Debug::GetInstance()->Log(L"LoadComplete");
			}
			break;
		case State::FadeOut:
			if (!TransitionSprite::GetInstance()->GetFade()->IsFadeActive()) {
				//�t�F�[�h������������^�C�g���X�e�[�W�Ɉڍs
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToDebugStage");
			}
			break;
		}
	}
}
//end basecross