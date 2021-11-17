/*!
@file Utility.h
@brief いろんな関数
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	namespace Utility {
		/**
		 * @brief 配列のサイズを返す関数
		 *
		 * @param 対象の配列のポインタ（[]なしのやつ）
		 * @return 配列のサイズ
		 */
		template<typename TYPE, size_t SIZE>
		size_t GetArrayLength(const TYPE(&)[SIZE]) {
			return SIZE;
		}

		/**
		 * @brief テクスチャのサイズを返す関数
		 *
		 * @param テクスチャキー（wstring）
		 * @return テクスチャサイズ（Vec2）
		 */
		const Vec2 GetTextureSize(const wstring& key);

		/**
		 * @brief テクスチャの座標をUV座標に変換する関数(1つのみ)
		 *
		 * @param テクスチャ座標の位置
		 * @param テクスチャサイズ
		 * @return UV座標
		 */
		const Vec2 ConvertToUVCoordinate(const Vec2& coordinate, const Vec2& textureSize);
		/**
		 * @brief テクスチャの座標をUV座標に変換する関数（単体）
		 *
		 * @param テクスチャ座標の位置
		 * @param テクスチャキー
		 * @return UV座標
		 */
		const Vec2 ConvertToUVCoordinate(const Vec2& coordinate, const wstring& textureName);
		/**
		 * @brief テクスチャの座標をUV座標に変換する関数（複数）
		 *
		 * @param テクスチャ座標の位置のvector配列
		 * @param テクスチャサイズ
		 * @param UV座標の位置のvector配列（出力）
		 */
		void ConvertToUVCoordinates(const vector<Vec2>& coordinates, const Vec2& textureSize, vector<Vec2>& uv);
		/**
		 * @brief テクスチャの座標をUV座標に変換する関数（複数）
		 *
		 * @param テクスチャ座標の位置のvector配列
		 * @param テクスチャキー
		 * @param UV座標の位置のvector配列（出力）
		 */
		void ConvertToUVCoordinates(const vector<Vec2>& coordinates, const wstring& textureName, vector<Vec2>& uv);
		/**
		 * @brief Vec3のDegをRadに変換
		 *
		 * @param deg
		 * @return rad
		 */
		Vec3 ConvertDegVecToRadVec(const Vec3& deg);
		/**
		 * @brief Vec3のDegをRadに変換
		 *
		 * @param deg
		 * @return rad
		 */
		Vec3 ConvertRadVecToDegVec(const Vec3& rad);

		/**
		 * @brief 2つの角度(deg)が同じかどうかを調べる
		 *
		 * @param 角度1
		 * @param 角度2
		 * @return true:等しい,false:異なる
		 */
		bool MatchAngle(float deg1, float deg2);

		/**
		 * @brief 角度(deg)をmin～maxの間に収める（minとmaxの差は360である必要がある）
		 *
		 * @param 最小角度
		 * @param 最大角度
		 * @param 収めたい角度
		 * @return min～maxの間のangle
		 */
		float ClampAngle(float min, float max, float angle);

		/**
		 * @brief wstringをboolに変換
		 *
		 * @param 文字列（wstring）
		 * @return bool型
		 */
		bool WStrToBool(wstring str);

		/**
		 * @brief Col4の0～255を0～1に収める
		 *
		 * @param Col4（0～255）
		 * @return Col4（0～1）
		 */
		Col4 ConvertColorZeroToOne(Col4 color);

		/**
		 * @brief ベクトルの長さを変更する
		 *
		 * @param vector 変更したいベクトル
		 * @param length 指定する長さ
		 * @return 長さがlengthのベクトル
		 */
		Vec3 ChangeVectorLength(const Vec3& vector, float length);

		Vec3 ConvertWorldToScreen(const shared_ptr<ViewBase>& view, const Vec3& position);
	}
}
//end basecross
