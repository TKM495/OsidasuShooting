#pragma once

// 蝓ｺ譛ｬ
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
// その他
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
#include "Utility/PlayerStatus.h"
// ステージオブジェクト
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
#include "StageObject/area_.h"
#include "StageObject/Item_.h"
#include "StageObject/ItemCreation_.h"
#include "StageObject/Blinking_.h"
#include "StageObject/Confetti.h"
//UI
#include "UIs/InfoGauge.h"
#include "UIs/BackPlanet.h"
#include "UIs/BaseUI.h"
#include "UIs/BattlePlayersUIs.h"
#include "UIs/BombReloadTimeGauge.h"
#include "UIs/BombRemainingCount.h"
#include "UIs/Canvas.h"
#include "UIs/CharaSelectUIs.h"
#include "UIs/CharaSelectUISprites.h"
#include "UIs/CurrentFirst.h"
#include "UIs/FreamSprite.h"
#include "UIs/NumberSprite.h"
#include "UIs/PlayerFollowUI.h"
#include "UIs/PlayerInfo.h"
#include "UIs/PlayerCharaPicture.h"
#include "UIs/ResultScore.h"
#include "UIs/ResultSprite.h"
#include "UIs/SimpleSprite.h"
#include "UIs/StringSprite2.h"
#include "UIs/TitleSprite.h"
#include "UIs/UIHeader.h"
#include "UIs/CurrentFirst.h"
#include "UIs/TransitionSprite.h"
#include "UIs/GameStartAndFinish.h"
//#include "UIs/CountDown_.h"
#include "UIs/OneShotUI.h"
// コンポーネント
#include "Component/FadeComponent.h"
#include "Component/LifeSpan.h"
#include "Component/MySpriteBaseDraw.h"
#include "Component/PCTGaugeSprite.h"
#include "Component/PhysicalBehavior.h"
#include "Component/CircleShadow.h"
// メニュー
#include "UIs/Menu/BaseMenu.h"
// マネージャー
#include "Manager/PlayerManager.h"
#include "Manager/SoundManager.h"
#include "Manager/StageManager.h"
#include "Manager/PlayerBuilder.h"
#include "Manager/SpecialSkillManager.h"

// カメラ
#include "Camera/GameCamera.h"
#include "Camera/TitleCamera.h"

//JonyMd Folder
//Empty GameObject
#include "JonyMd/ItemCreation.h"
#include "JonyMd/MeteoriteCreation.h"
#include "JonyMd/Blinking.h"
#include "JonyMd/CountDown.h"
//Empty GameObject

//GameObject
#include "JonyMd/Item.h"
#include "JonyMd/Area.h"
#include "JonyMd/Meteorite.h"
#include "JonyMd/Fencing.h"
//GameObject...end

//Camera
#include "JonyMd/ShackingCamera.h"
//Camera...end
//
