#pragma once
#include "stdafx.h"

namespace basecross {

	class ListsOfVariable : public GameObject
	{
	public:
		float executeTime = 10.0f; //�Q�[���I�u�W�F�N�g�����������莞�Ԍo�߂����ꍇ�������邽��
		float speed = 5.0f; //���Ƃ��΁A�v���C���[�I�u�W�F�N�g����ݒ肳�ꂽ���x
		Vec3 direction = Vec3(1,0,0);//���Ƃ��΁A�v���C���[�I�u�W�F�N�g����ݒ肳�ꂽ����

		ListsOfVariable(const shared_ptr <Stage>& stage)
			:GameObject(stage)
		{}
	};

}
