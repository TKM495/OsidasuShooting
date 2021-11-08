#pragma once
#include "stdafx.h"

namespace basecross {
	struct TransformData {
		Vec3 Position;
		Vec3 Scale;
		Vec3 Rotation;
		TransformData() {
			this->Position = Vec3(0.0f);
			this->Scale = Vec3(1.0f);
			this->Rotation = Vec3(0.0f);
		}
		TransformData(const Vec3& position) {
			this->Position = position;
			this->Scale = Vec3(1.0f);
			this->Rotation = Vec3(0.0f);
		}
		TransformData(const Vec3& position, const Vec3& scale) {
			this->Position = position;
			this->Scale = scale;
			this->Rotation = Vec3(0.0f);
		}
		TransformData(const Vec3& position, const Vec3& scale, const Vec3& rotation) {
			this->Position = position;
			this->Scale = scale;
			this->Rotation = rotation;
		}
	};

	struct Ray {
		Vec3 origin;
		Vec3 dir;
		Ray(const Vec3& origin, const Vec3& dir) {
			this->origin = origin;
			this->dir = dir;
		}
		Ray() {}
	};

	using ObjectPositionForward = Ray;

	class StageObject :public GameObject {
	protected:
		TransformData m_transformData;
	public:
		StageObject(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void ObjectSetUp();
		shared_ptr<Transform> GetTransform();
	};
}
