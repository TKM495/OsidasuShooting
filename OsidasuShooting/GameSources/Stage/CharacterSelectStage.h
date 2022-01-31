#pragma once
#include "stdafx.h"
#include "UIs/CharaSelectUIs.h"
#include "UIs/CharaSelectUISprites.h"
#include "UIs/FreamSprite.h"
#include "UIs/PlayerCharaPicture.h"
#include "UIs/SimpleSprite.h"

namespace basecross {
	class CharacterSelectStage :public Stage {
		void CreateViewLight();

		//wstring m_charaName[3];
		Vec3 m_freamPos[4];

		const int m_loopForPlayer = 4;	// �v���C���[��
		const int m_loopForIcon = 2;		// �A�C�R����
		int m_gamePadIDs[4];
		int m_charaID[4];

		float m_posOffsetX;
		float m_posOffsetY;
		float m_shiftMovePos;

		bool m_ifEntryPlayer[4];
		bool m_isBPushPlayer[4];
		bool m_isDecisionPlayer[4];
		
		shared_ptr<CharaIcon> m_Icons[2 * 4];			 // �L������ * �v���C���[��
		const int m_iconMaxID = 2 - 1;					 // �L������ - 1
		shared_ptr<TriangleSprite> m_Triangle[2 * 4 * 2];// �L������ * �v���C���[����2��1�Z�b�g
		shared_ptr<PlayerCharaPicture> m_Picture[2 * 4]; // �L������ * �v���C���[��
		int m_pictureNum;								 // �L������ * gamePadID
		//shared_ptr<SelectCursor> m_SelectCursor[4];	 // �v���C���[��
		shared_ptr<OKSpriteUI> m_SelectOK[4];			 // �v���C���[��
		shared_ptr<ReadyToFightUI> m_Ready;				 // 
		shared_ptr<SimpleSprite> m_BackGround;			 //
		shared_ptr<StatusGauge> m_Gauge[3 * 4];			 // �Q�[�W�� * �v���C���[��
		int m_gaugeNum;									 // �Q�[�W�� * gamePadID

		bool m_isSetStick[4];
		bool m_sceneChangeBlock;
		//shared_ptr<CharacterIcon> charaIcon;
	public:
		CharacterSelectStage(
		) :
			Stage(),
			//m_charaName{},
			//m_loopForPlayer(4),
			//m_loopForIcon(2),
			m_posOffsetX(-18.0f),
			m_posOffsetY(-28.0f),
			m_shiftMovePos(180),
			m_gamePadIDs{},
			m_charaID{},
			m_ifEntryPlayer{ false,false,false,false },
			m_isBPushPlayer{ false,false,false,false },
			m_isDecisionPlayer{ false,false,false,false },
			m_pictureNum(),
			m_gaugeNum(),
			m_isSetStick{false},
			m_sceneChangeBlock(false)
		{}
		~CharacterSelectStage() {}

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;

		void PlayerFreamPosition(Vec3 pos, int gamePadID);
		void PlayerCharacterSelect(int gamePadID,Vec3 pos);
		//void PlayerCursorCreate(int gamePadID);
		void GetCharacterID(int gamePadID);
		void SelectCharacter(int gamePadID);
		//void PlayerSelectTriangle(Vec3 pos, Vec3 scl, int gamePadID);
		void UIsSet();
		//void SetCharaName();

		void CharacterSelectingPlayers(int gamePadID);
		void CharacterSelectedPlayers(int gamePadID);
		void CharacterStetusGauge(int gamePadID);

		void CharacterSelectingAnimation(const CONTROLER_STATE& stick,bool left ,bool right, int gamePadID);

		void CheckSelectedPlayers();

		void DrawCharaPicture(int gamePadID);

	};
}

