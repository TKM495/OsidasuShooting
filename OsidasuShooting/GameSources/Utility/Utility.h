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
		 * @param TYPE �Ώۂ̔z��̃|�C���^
		 * @return size_t �z��̃T�C�Y
		 */
		template <typename TYPE, size_t SIZE>
		size_t GetArrayLength(const TYPE(&)[SIZE]) {
			return SIZE;
		}

		/**
		 * @brief �e�N�X�`���̃T�C�Y��Ԃ��֐�
		 *
		 * @param key �e�N�X�`���L�[
		 * @return const Vec2 �e�N�X�`���T�C�Y
		 */
		const Vec2 GetTextureSize(const wstring& key);

		/**
		 * @brief �e�N�X�`���̍��W��UV���W�ɕϊ�����֐��i�P�́j
		 *
		 * @param coordinate �e�N�X�`�����W�̈ʒu
		 * @param textureSize �e�N�X�`���T�C�Y
		 * @return const Vec2 UV���W
		 */
		const Vec2 ConvertToUVCoordinate(const Vec2& coordinate, const Vec2& textureSize);
		/**
		 * @brief �e�N�X�`���̍��W��UV���W�ɕϊ�����֐��i�P�́j
		 *
		 * @param coordinate �e�N�X�`�����W�̈ʒu
		 * @param textureName �e�N�X�`���L�[
		 * @return const Vec2 UV���W
		 */
		const Vec2 ConvertToUVCoordinate(const Vec2& coordinate, const wstring& textureName);
		/**
		 * @brief �e�N�X�`���̍��W��UV���W�ɕϊ�����֐��i�����j
		 *
		 * @param coordinates �e�N�X�`�����W�̈ʒu��vector�z��
		 * @param textureSize �e�N�X�`���T�C�Y
		 * @param uv UV���W�̈ʒu��vector�z��i�o�́j
		 */
		void ConvertToUVCoordinates(const vector<Vec2>& coordinates, const Vec2& textureSize, vector<Vec2>& uv);
		/**
		 * @brief �e�N�X�`���̍��W��UV���W�ɕϊ�����֐��i�����j
		 *
		 * @param coordinates �e�N�X�`�����W�̈ʒu��vector�z��
		 * @param textureName �e�N�X�`���L�[
		 * @param uv UV���W�̈ʒu��vector�z��i�o�́j
		 */
		void ConvertToUVCoordinates(const vector<Vec2>& coordinates, const wstring& textureName, vector<Vec2>& uv);

		/**
		 * @brief Vec3��Deg��Rad�ɕϊ�
		 *
		 * @param deg �p�x�iDeg�j
		 * @return Vec3 �p�x�iRad�j
		 */
		Vec3 ConvertDegVecToRadVec(const Vec3& deg);
		/**
		 * @brief Vec3��Rad��Deg�ɕϊ�
		 *
		 * @param rad �p�x�iRad�j
		 * @return Vec3 �p�x�iDeg�j
		 */
		Vec3 ConvertRadVecToDegVec(const Vec3& rad);

		/**
		 * @brief 2�̊p�x�iDeg�j���������ǂ����𒲂ׂ�
		 *
		 * @param deg1 �p�x1
		 * @param deg2 �p�x2
		 * @return bool true:������/false:�قȂ�
		 */
		bool MatchAngle(float deg1, float deg2);

		/**
		 * @brief �p�x�iDeg�j��min�`max�̊ԂɎ��߂�imin��max�̍���360�ł���K�v������j
		 *
		 * @param min �ŏ��p�x
		 * @param max �ő�p�x
		 * @param angle ���߂����p�x
		 * @return float min�`max�̊Ԃ�angle
		 */
		float ClampAngle(float min, float max, float angle);

		/**
		 * @brief wstring��bool�ɕϊ�
		 *
		 * @param str ������iwstring�j
		 * @return bool bool�^
		 */
		bool WStrToBool(wstring str);

		/**
		 * @brief Col4��0�`255��0�`1�Ɏ��߂�
		 *
		 * @param color 0�`255�͈̔͂̐F�f�[�^
		 * @return Col4 0�`1�͈̔͂̐F�f�[�^
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

		/**
		 * @brief ���[���h���W���X�N���[�����W�ɕύX����
		 *
		 * @param view �r���[
		 * @param position ���[���h���W
		 * @return Vec3 �X�N���[�����W
		 */
		Vec3 ConvertWorldToScreen(const shared_ptr<ViewBase>& view, const Vec3& position);

		/**
		 * @brief 2�̃x�N�g���̂Ȃ��p�����߂�
		 *
		 * @param vector1 �x�N�g��1
		 * @param vector2 �x�N�g��2
		 * @return float �p�x�ideg�j
		 */
		float GetTwoVectorAngle(const Vec3& vector1, const Vec3& vector2);

		Vec3 ClampVector3(const Vec3& value, const Vec3& _min, const Vec3& _max);

		template<typename T>
		T Clamp(T value, T low, T high) {
			return min(max(value, low), high);
		}

		/**
		 * @brief ���}�b�v
		 */
		float Remap(float val, float inMin, float inMax, float outMin, float outMax);
	}
}
//end basecross
