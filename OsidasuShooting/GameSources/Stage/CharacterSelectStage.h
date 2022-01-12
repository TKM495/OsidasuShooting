#pragma once
#include "stdafx.h"
#include "UIs/CharaSelectUIs.h"
#include "UIs/CharaSelectUISprites.h"
#include "UIs/SimpleSprite.h"

namespace basecross {
	class CharacterSelectStage :public Stage {
		void CreateViewLight();

		wstring m_charaName[3];
		Vec3 m_freamPos[4];

		int m_loopForPlayer;	// 
		int m_loopForIcon;
		int m_gamePadIDs[4];

		float m_posOffsetX;
		float m_posOffsetY;
		float m_shiftMovePos;

		bool m_ifEntryPlayer[4];
		bool m_isBPushPlayer[4];
		bool m_isDecisionPlayer[4];

		shared_ptr<CharacterIcon> m_Icons[12];		// キャラ数 * プレイヤー数
		shared_ptr<SelectTriangle> m_Triangle[8];	// 三角1セット * プレイヤー数
		shared_ptr<ReadyToFightUI> m_Ready;
		shared_ptr<SimpleSprite> m_BackGround;

		bool m_sceneChangeBlock;
		//shared_ptr<CharacterIcon> charaIcon;
	public:
		CharacterSelectStage(
		) :
			Stage(),
			m_charaName{},
			m_loopForPlayer(4),
			m_loopForIcon(2),
			m_posOffsetX(-18.0f),
			m_posOffsetY(-28.0f),
			m_shiftMovePos(180),
			m_gamePadIDs{},
			m_ifEntryPlayer{ false,false,false,false },
			m_isBPushPlayer{ false,false,false,false },
			m_isDecisionPlayer{ false,false,false,false },
			m_sceneChangeBlock(false)
		{}
		~CharacterSelectStage() {}

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;

		void PlayerFreamPosition(Vec3 pos, int gamePadID);
		void PlayerCharacterSelect(Vec3 pos, int gamePadID);
		void PlayerSelectTriangle(Vec3 pos, Vec3 scl, int gamePadID);
		void UIsSet();
		void SetCharaName();

		void CharacterSelectingPlayers(int gamePadID);
		void CharacterSelectedPlayers(int gamePadID);
		void CheckSelectedPlayers();

	};
}

