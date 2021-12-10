/*!
@file Project.h
@brief 繧ｳ繝ｳ繝・Φ繝・畑縺ｮ繝倥ャ繝繧偵∪縺ｨ繧√ｋ
*/

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
#include "Stage/WatanabeStage.h"
#include "Stage/WatanabeStage2.h"
// その他
#include "DebugClass/Debug.h"
#include "Effekseer/EfkEffect.h"
#include "Utility/BaseSingleton.h"
#include "Utility/CSVLoad.h"
#include "Utility/GroundingDecision.h"
#include "Utility/PredictionLine.h"
#include "Utility/TimeCounter.h"
#include "Utility/Utility.h"
#include "Utility/AdvancedMeshUtil.h"
// ステージオブジェクト
#include "SpecialCamera/SpCamera.h"
#include "StageObject/AdvancedGameObject.h"
#include "StageObject/Block.h"
#include "StageObject/Bomb.h"
#include "StageObject/Bullet.h"
#include "StageObject/FallDecision.h"
#include "StageObject/ManualPlayer.h"
#include "StageObject/PlayerBase.h"
#include "StageObject/PlayerModel.h"
#include "StageObject/SpecialSkill.h"
//UI
#include "UIs/ArmorGauge.h"
#include "UIs/BaseUI.h"
#include "UIs/BattlePlayersUIs.h"
#include "UIs/BombReloadTimeGauge.h"
#include "UIs/BombRemainingCount.h"
#include "UIs/Canvas.h"
#include "UIs/CurrentFirst.h"
#include "UIs/HoverTimeGauge.h"
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
// コンポーネント
#include "Component/FadeComponent.h"
#include "Component/LifeSpan.h"
#include "Component/MySpriteBaseDraw.h"
#include "Component/PCTGaugeSprite.h"
#include "Component/PhysicalBehavior.h"
// メニュー
#include "UIs/Menu/BaseMenu.h"
// マネージャー
#include "Manager/ControllerManager.h"
#include "Manager/PlayerManager.h"
#include "Manager/SoundManager.h"







//
//
//
//調整したご削除してもかまいません
//JonyMd .. release するとき削除されてください
//JonyMd フォルダまま削除しても構いません

//GameObject
#include "JonyMd/Meteorite.h"
#include "JonyMd/MeteoriteCreation.h"
//GameObject...end

//Camera
#include "JonyMd/ShackingCamera.h"
//Camera...end

//調整したご削除してもかまいません。。。終
//
//
//
