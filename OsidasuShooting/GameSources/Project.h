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
#include "Stage/WatanabeStage.h"
#include "Stage/WatanabeStage2.h"
// ���̑�
#include "DebugClass/Debug.h"
#include "Effekseer/EfkEffect.h"
#include "Utility/BaseSingleton.h"
#include "Utility/CSVLoad.h"
#include "Utility/GroundingDecision.h"
#include "Utility/PredictionLine.h"
#include "Utility/TimeCounter.h"
#include "Utility/Utility.h"
// �X�e�[�W�I�u�W�F�N�g
#include "SpecialCamera/SpCamera.h"
#include "StageObject/AdvancedGameObject.h"
#include "StageObject/Block.h"
#include "StageObject/Bomb.h"
#include "StageObject/Bullet.h"
#include "StageObject/FallDecision.h"
#include "StageObject/ManualPlayer.h"
#include "StageObject/PlayerBase.h"
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
// �R���|�[�l���g
#include "Component/FadeComponent.h"
#include "Component/LifeSpan.h"
#include "Component/MySpriteBaseDraw.h"
#include "Component/PCTGaugeSprite.h"
#include "Component/PhysicalBehavior.h"
// ���j���[
#include "UIs/Menu/BaseMenu.h"
// �}�l�[�W���[
#include "Manager/ControllerManager.h"
#include "Manager/PlayerManager.h"

#include "JonyMd/Area.h"
#include "JonyMd/CountDown.h"
#include "JonyMd/Items.h"
#include "JonyMd/ItemsCreations.h"
