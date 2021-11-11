/*!
@file Project.h
@brief �R���e���c�p�̃w�b�_���܂Ƃ߂�
*/

#pragma once

// ��{
#include "Scene.h"
#include "Stage/TitleStage.h"
#include "Stage/GameStage.h"
#include "Stage/ResultStage.h"
#include "Stage/DebugStage.h"
#include "Stage/WatanabeStage.h"
#include "Stage/SatoStage.h"
#include "Stage/JONYMDStage.h"
// ���̑�
#include "DebugClass/Debug.h"
#include "Utility/Utility.h"
#include "Utility/BombPredictionLine.h"
#include "Utility/GroundingDecision.h"
#include "Utility/CSVLoad.h"
#include "Utility/TimeCounter.h"
#include "Effekseer/EfkEffect.h"
// �X�e�[�W�I�u�W�F�N�g
#include "StageObject/StageObject.h"
#include "StageObject/Player.h"
#include "StageObject/Block.h"
#include "SpecialCamera/SpCamera.h"
#include "StageObject/Bullet.h"
//UI
#include "UIs/Canvas.h"
#include "UIs/BaseUI.h"
#include "UIs/TitleSprite.h"
#include "UIs/StringSprite2.h"
#include "UIs/UIHeader.h"
#include "UIs/SimpleSprite.h"
// �R���|�[�l���g
#include "Component/PhysicalBehavior.h"
#include "Component/FadeComponent.h"
// ���j���[
#include "UIs/Menu/BaseMenu.h"
