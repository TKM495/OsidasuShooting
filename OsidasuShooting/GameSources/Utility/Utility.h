/*!
@file Utility.h
@brief �����Ȋ֐�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	namespace Utility {
		/**
		 * @brief �z��̃T�C�Y��Ԃ��֐�
		 *
		 * @param �Ώۂ̔z��̃|�C���^�i[]�Ȃ��̂�j
		 * @return �z��̃T�C�Y
		 */
		template<typename TYPE, size_t SIZE>
		size_t GetArrayLength(const TYPE(&)[SIZE]) {
			return SIZE;
		}

		/**
		 * @brief �e�N�X�`���̃T�C�Y��Ԃ��֐�
		 *
		 * @param �e�N�X�`���L�[�iwstring�j
		 * @return �e�N�X�`���T�C�Y�iVec2�j
		 */
		const Vec2 GetTextureSize(const wstring& key);

		/**
		 * @brief �e�N�X�`���̍��W��UV���W�ɕϊ�����֐�(1�̂�)
		 *
		 * @param �e�N�X�`�����W�̈ʒu
		 * @param �e�N�X�`���T�C�Y
		 * @return UV���W
		 */
		const Vec2 ConvertToUVCoordinate(const Vec2& coordinate, const Vec2& textureSize);
		/**
		 * @brief �e�N�X�`���̍��W��UV���W�ɕϊ�����֐��i�P�́j
		 *
		 * @param �e�N�X�`�����W�̈ʒu
		 * @param �e�N�X�`���L�[
		 * @return UV���W
		 */
		const Vec2 ConvertToUVCoordinate(const Vec2& coordinate, const wstring& textureName);
		/**
		 * @brief �e�N�X�`���̍��W��UV���W�ɕϊ�����֐��i�����j
		 *
		 * @param �e�N�X�`�����W�̈ʒu��vector�z��
		 * @param �e�N�X�`���T�C�Y
		 * @param UV���W�̈ʒu��vector�z��i�o�́j
		 */
		void ConvertToUVCoordinates(const vector<Vec2>& coordinates, const Vec2& textureSize, vector<Vec2>& uv);
		/**
		 * @brief �e�N�X�`���̍��W��UV���W�ɕϊ�����֐��i�����j
		 *
		 * @param �e�N�X�`�����W�̈ʒu��vector�z��
		 * @param �e�N�X�`���L�[
		 * @param UV���W�̈ʒu��vector�z��i�o�́j
		 */
		void ConvertToUVCoordinates(const vector<Vec2>& coordinates, const wstring& textureName, vector<Vec2>& uv);
		/**
		 * @brief Vec3��Deg��Rad�ɕϊ�
		 *
		 * @param deg
		 * @return rad
		 */
		Vec3 ConvertDegVecToRadVec(const Vec3& deg);
		/**
		 * @brief Vec3��Deg��Rad�ɕϊ�
		 *
		 * @param deg
		 * @return rad
		 */
		Vec3 ConvertRadVecToDegVec(const Vec3& rad);

		/**
		 * @brief 2�̊p�x(deg)���������ǂ����𒲂ׂ�
		 *
		 * @param �p�x1
		 * @param �p�x2
		 * @return true:������,false:�قȂ�
		 */
		bool MatchAngle(float deg1, float deg2);

		/**
		 * @brief �p�x(deg)��min�`max�̊ԂɎ��߂�imin��max�̍���360�ł���K�v������j
		 *
		 * @param �ŏ��p�x
		 * @param �ő�p�x
		 * @param ���߂����p�x
		 * @return min�`max�̊Ԃ�angle
		 */
		float ClampAngle(float min, float max, float angle);

		/**
		 * @brief wstring��bool�ɕϊ�
		 *
		 * @param ������iwstring�j
		 * @return bool�^
		 */
		bool WStrToBool(wstring str);

		/**
		 * @brief Col4��0�`255��0�`1�Ɏ��߂�
		 *
		 * @param Col4�i0�`255�j
		 * @return Col4�i0�`1�j
		 */
		Col4 ConvertColorZeroToOne(Col4 color);

		/**
		 * @brief �x�N�g���̒�����ύX����
		 *
		 * @param vector �ύX�������x�N�g��
		 * @param length �w�肷�钷��
		 * @return ������length�̃x�N�g��
		 */
		Vec3 ChangeVectorLength(const Vec3& vector, float length);

		Vec3 ConvertWorldToScreen(const shared_ptr<ViewBase>& view, const Vec3& position);
	}
}
//end basecross
