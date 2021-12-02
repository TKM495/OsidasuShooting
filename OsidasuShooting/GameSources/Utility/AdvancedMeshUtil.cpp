#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void AdvancedMeshUtil::CreateCube(float textureSize, const Vec3& scale,
		vector<VertexPositionNormalTexture>& vertices, vector<uint16_t>& indices) {
		try {
			// �e�N�X�`���̑傫���ɉ�����UV�̒l
			const float uvRate = 1 / textureSize;
			// �e�N�X�`��UV
			const Vec2 textureCoordinates[4] =
			{
				{ uvRate, 0      },
				{ uvRate, uvRate },
				{ 0     , uvRate },
				{ 0     , 0      },
			};

			// �@���Ɖe�����󂯂�T�C�Y�̎�
			const vector<NormalAndUVData> data = {
				{{ 0 ,  0,  1 },Vec2(scale.x,scale.y)},
				{{ 0 ,  0, -1 },Vec2(scale.x,scale.y)},
				{{ 1 ,  0,  0 },Vec2(scale.z,scale.y)},
				{{ -1,  0,  0 },Vec2(scale.z,scale.y)},
				{{ 0 ,  1,  0 },Vec2(scale.x,scale.z)},
				{{ 0 , -1,  0 },Vec2(scale.x,scale.z)},
			};

			// ��ӂ̔����̒���
			const float size = 0.5f;
			//Face����6
			const int FaceCount = 6;
			for (int i = 0; i < FaceCount; i++)
			{
				//�@��
				XMVECTOR normal = data[i].Normal;

				XMVECTOR basis = (i >= 4) ? g_XMIdentityR2 : g_XMIdentityR1;

				XMVECTOR side1 = XMVector3Cross(normal, basis);
				XMVECTOR side2 = XMVector3Cross(normal, side1);

				//�C���f�b�N�X�̓o�^
				size_t vbase = vertices.size();
				indices.push_back((uint16_t)vbase + 0);
				indices.push_back((uint16_t)vbase + 1);
				indices.push_back((uint16_t)vbase + 2);

				indices.push_back((uint16_t)vbase + 0);
				indices.push_back((uint16_t)vbase + 2);
				indices.push_back((uint16_t)vbase + 3);

				vertices.push_back(VertexPositionNormalTexture((normal - side1 - side2) * size, normal, VectorRate(data[i].AffectedScale, textureCoordinates[0])));
				vertices.push_back(VertexPositionNormalTexture((normal - side1 + side2) * size, normal, VectorRate(data[i].AffectedScale, textureCoordinates[1])));
				vertices.push_back(VertexPositionNormalTexture((normal + side1 + side2) * size, normal, VectorRate(data[i].AffectedScale, textureCoordinates[2])));
				vertices.push_back(VertexPositionNormalTexture((normal + side1 - side2) * size, normal, VectorRate(data[i].AffectedScale, textureCoordinates[3])));
			}
			//RH����LH�ɕύX
			MeshUtill::ReverseWinding(indices, vertices);
		}
		catch (...) {
			throw;
		}
	}

	Vec2 AdvancedMeshUtil::VectorRate(const Vec2& vec1, const Vec2& vec2) {
		return Vec2(vec1.x * vec2.x, vec1.y * vec2.y);
	}
}