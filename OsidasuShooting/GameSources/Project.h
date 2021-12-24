/*!
@file Project.h
@brief コンチE��チE��のヘッダをまとめる
*/

#pragma once

// 基本
#include "Scene.h"
#include "Stage/DebugStage.h"
#include "Stage/GameStage.h"
#include "Stage/JONYMDStage.h"
#include "Stage/ResultStage.h"
#include "Stage/SatoStage.h"
#include "Stage/TitleStage.h"
#include "Stage/CharacterSelectStage.h"
#include "Stage/LoadStage.h"
#include "Stage/WatanabeStage.h"
#include "Stage/WatanabeStage2.h"
// ���̑�
#include "DebugClass/Debug.h"
#include "Effekseer/EfkEffect.h"
#include "Utility/BaseSingleton.h"
#include "Utility/CSVLoad.h"
#include "Utility/XMLLoad.h"
#include "Utility/GroundingDecision.h"
#include "Utility/PredictionLine.h"
#include "Utility/TimeCounter.h"
#include "Utility/Utility.h"
#include "Utility/AdvancedMeshUtil.h"
#include "Utility/DataExtracter.h"
#include "Utility/GameController.h"
// �X�e�[�W�I�u�W�F�N�g
#include "SpecialCamera/SpCamera.h"
#include "StageObject/AdvancedGameObject.h"
#include "StageObject/Block.h"
#include "StageObject/Bomb.h"
#include "StageObject/BreakBlock.h"
#include "StageObject/Bullet.h"
#include "StageObject/FallDecision.h"
#include "StageObject/ManualPlayer.h"
#include "StageObject/MoveBlock.h"
#include "StageObject/PlayerBase.h"
#include "StageObject/PlayerModel.h"
#include "StageObject/ReflectorBlock.h"
#include "StageObject/SpecialSkill.h"
//UI
#include "UIs/InfoGauge.h"
#include "UIs/BaseUI.h"
#include "UIs/BattlePlayersUIs.h"
#include "UIs/BombReloadTimeGauge.h"
#include "UIs/BombRemainingCount.h"
#include "UIs/Canvas.h"
#include "UIs/CharaSelectUILetter.h"
#include "UIs/CharaSelectUISprites.h"
#include "UIs/CurrentFirst.h"
#include "UIs/FreamSprite.h"
#include "UIs/NumberSprite.h"
#include "UIs/PlayerFollowUI.h"
#include "UIs/PlayerInfo.h"
#include "UIs/ResultScore.h"
#include "UIs/ResultSprite.h"
#include "UIs/SimpleSprite.h"
#include "UIs/StringSprite2.h"
#include "UIs/TitleSprite.h"
#include "UIs/UIHeader.h"
#include "UIs/CurrentFirst.h"
#include "UIs/TransitionSprite.h"
#include "UIs/GameStartAndFinish.h"
// �R���|�[�l���g
#include "Component/FadeComponent.h"
#include "Component/LifeSpan.h"
#include "Component/MySpriteBaseDraw.h"
#include "Component/PCTGaugeSprite.h"
#include "Component/PhysicalBehavior.h"
// ���j���[
#include "UIs/Menu/BaseMenu.h"
// �}�l�[�W���[
#include "Manager/PlayerManager.h"
#include "Manager/SoundManager.h"
#include "Manager/StageManager.h"
#include "Manager/PlayerBuilder.h"
#include "Manager/SpecialSkillManager.h"



//JonyMd Folder
//Empty GameObject
#include "JonyMd/ItemCreation.h"
#include "JonyMd/MeteoriteCreation.h"
//Empty GameObject

//GameObject
#include "JonyMd/Item.h"
#include "JonyMd/Area.h"
#include "JonyMd/Meteorite.h"
//GameObject...end

//Camera
#include "JonyMd/ShackingCamera.h"
//Camera...end
//
