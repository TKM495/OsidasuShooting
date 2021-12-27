#pragma once
#include "stdafx.h"

namespace basecross {

	class FenceController : public GameObject
	{
		//�ȉ��̕ϐ��͕b�ł�
		int show;
		int hide;
		int start;

		//����A�������茻�ꂽ������邩
		//�@�O�@�͈�񂾂�
		//�@���O�@�͒l�܂�
		//�@���O�@�͖�����
		int repeat;

		//�@���߂�hide�A������show���I�������totalRepeated�̒l���オ��܂�
		int totalRepeated;

		
		//���݂̕b
		float countDown;


		//���݂̐i�W
		enum Status
		{
			Show,
			Hide,
			Start,
			Stop,
		};
		Status status;
		wstring currentStatus = L"Start";


		void ControllingFence(); // ���݁AAddGameObject �Ɓ@RemoveGameObject �Ő�������܂���
	public:
		FenceController(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate() override;
		void OnUpdate() override;

	};

}
