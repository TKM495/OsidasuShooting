#pragma once
#include "stdafx.h"

namespace basecross {
	// ���x�ȃ��b�V���쐬�⏕�N���X
	class AdvancedMeshUtil {
		// �@���Ɖe�����󂯂�X�P�[���̃f�[�^
		struct NormalAndUVData {
			Vec3 Normal;		// �@��
			Vec2 AffectedScale;	// �e�����󂯂�X�P�[��
		};

		/**
		 * @brief �x�N�g�����m�̊|���Z
		 *
		 * @param vec1 �x�N�g��1
		 * @param vec2 �x�N�g�� 2
		 * @return ���ꂼ���x��y���������l
		 */
		static Vec2 VectorRate(const Vec2& vec1, const Vec2& vec2);
	public:
		/**
		 * @brief �X�P�[���ɍ��킹��UV������Cube�̐���
		 *
		 * @param textureSize �e�N�X�`���̑傫��
		 * @param scale �I�u�W�F�N�g�̑傫��
		 * @param vertices ���_�f�[�^
		 * @param indices �C���f�b�N�X�f�[�^
		 */
		static void CreateCube(float textureSize, const Vec3& scale,
			vector<VertexPositionNormalTexture>& vertices, vector<uint16_t>& indices);
	};
}