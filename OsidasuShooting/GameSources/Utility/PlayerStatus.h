#pragma once
#include "stdafx.h"
#include "Utility/BaseSingleton.h"
#include "StageObject/PlayerBase.h"
#include "Manager/PlayerManager.h"

namespace basecross {
	class PlayerStatus :public BaseSingleton<PlayerStatus> {
	private:
		PlayerStatus() :BaseSingleton() {
			DataExtraction();
		}
		~PlayerStatus() {}
		friend class BaseSingleton<PlayerStatus>;
	private:
		map<PlayerNumber, Col4> m_colorTable;
	public:
		void DataExtraction();
		Col4 GetPlayerColor(PlayerNumber number);
		Col4 GetPlayerColor(int number);
	};
}
