/*!
@file   StringSprite2.cpp
@brief  文字列表示用クラス実体
 */

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StringSprite2::OnCreate() {
		vector<SpriteDataFormat> data;
		// 目標のデータを探す
		int index = SearchDataIndex(data);
		if (index == -1) {
			throw BaseException(
				L"目標のデータが見つかりません",
				L"name : " + m_name,
				L"StringSprite2::OnCreate()"
			);
		}
		m_data = data[index];
		auto origin = m_data.origin;
		auto size = m_data.size;
		Rect2D<float> pos;
		// 水平位置の設定
		switch (m_horizontal)
		{
		case basecross::Align::Horizontal::Left:
			pos.left = 0.0f;
			pos.right = size.x;
			break;
		case basecross::Align::Horizontal::Center:
			pos.left = size.x / 2.0f;
			pos.right = size.x / 2.0f;
			break;
		case basecross::Align::Horizontal::Right:
			pos.left = size.x;
			pos.right = 0.0f;
			break;
		default:
			// エラー
			break;
		}
		// 垂直位置の設定
		switch (m_vertical)
		{
		case basecross::Align::Vertical::Top:
			pos.top = 0.0f;
			pos.bottom = size.y;
			break;
		case basecross::Align::Vertical::Center:
			pos.top = size.y / 2.0f;
			pos.bottom = size.y / 2.0f;
			break;
		case basecross::Align::Vertical::Bottom:
			pos.top = size.y;
			pos.bottom = 0.0f;
			break;
		default:
			// エラー
			break;
		}

		// テクスチャ座標でUVを定義
		vector<Vec2> uvs, uv = {
			origin,
			origin + Vec2(size.x,0.0f),
			origin + Vec2(0.0f, size.y),
			origin + size
		};
		// テクスチャ座標からUV座標に変換
		Utility::ConvertToUVCoordinates(uv, L"string", uvs);

		// 頂点のデータ (番号は左上から右下まで)
		vertices = {
			{Vec3(-pos.left,+pos.top,0.0f),m_color,uvs[0]}, //0
			{Vec3(+pos.right,+pos.top,0.0f),m_color,uvs[1]}, //1

			{Vec3(-pos.left,-pos.bottom,0.0f),m_color,uvs[2]}, //2
			{Vec3(+pos.right,-pos.bottom,0.0f),m_color,uvs[3]},  //3
		};
		// 頂点インデックス
		vector<uint16_t> indices = {
			0, 1, 2, // 上の三角形
			2, 1, 3  // 下の三角形
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(L"string");
		// テクスチャの繰り返し設定(Wrap)
		drawComp->SetSamplerState(SamplerState::AnisotropicWrap);
		drawComp->SetDepthStencilState(DepthStencilState::Read);

		auto fade = AddComponent<FadeComponent>();
		fade->SetFadeRange(m_color.w, 0);

		SetAlphaActive(true); // 透明をサポートする&両面描画になる
		SetDrawLayer(2);
		SetUpdateActive(false);
	}

	void StringSprite2::OnUpdate() {
		// フェードアウトの処理
		auto delta = App::GetApp()->GetElapsedTime();
		auto fade = GetComponent<FadeComponent>();
		if (m_delta > m_deActiveTime && !m_bDeactive) {
			fade->FadeOut();
			m_bDeactive = true;
		}

		if (!fade->IsFadeActive() && m_bDeactive) {
			m_delta = 0.0f;
			m_bDeactive = false;
			SetDrawActive(false);
			SetUpdateActive(false);
		}
		m_delta += delta;
	}

	void StringSprite2::SetAlignHorizontal(Align::Horizontal hor) {
		auto origin = m_data.origin;
		auto size = m_data.size;
		m_horizontal = hor;
		Rect2D<float> pos;
		// 水平位置の設定
		switch (m_horizontal)
		{
		case basecross::Align::Horizontal::Left:
			pos.left = 0.0f;
			pos.right = size.x;
			break;
		case basecross::Align::Horizontal::Center:
			pos.left = size.x / 2.0f;
			pos.right = size.x / 2.0f;
			break;
		case basecross::Align::Horizontal::Right:
			pos.left = size.x;
			pos.right = 0.0f;
			break;
		default:
			// エラー
			break;
		}
		vertices[0].position.x = vertices[2].position.x = -pos.left;
		vertices[1].position.x = vertices[3].position.x = +pos.right;
		GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
	}

	void StringSprite2::SetAlignVertical(Align::Vertical ver) {
		auto origin = m_data.origin;
		auto size = m_data.size;
		m_vertical = ver;
		Rect2D<float> pos;
		// 垂直位置の設定
		switch (m_vertical)
		{
		case basecross::Align::Vertical::Top:
			pos.top = 0.0f;
			pos.bottom = size.y;
			break;
		case basecross::Align::Vertical::Center:
			pos.top = size.y / 2.0f;
			pos.bottom = size.y / 2.0f;
			break;
		case basecross::Align::Vertical::Bottom:
			pos.top = size.y;
			pos.bottom = 0.0f;
			break;
		default:
			// エラー
			break;
		}
		vertices[0].position.y = vertices[1].position.y = +pos.top;
		vertices[2].position.y = vertices[3].position.y = -pos.bottom;
		GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
	}

	void StringSprite2::SetSize(float size) {
		GetComponent<Transform>()->SetScale(Vec3(size));
	}

	void StringSprite2::SetPos(Vec2 pos) {
		GetComponent<Transform>()->SetPosition((Vec3)pos);
	}

	float StringSprite2::GetSize() {
		// 大きさは同じなのでとりあえずxを返す
		return GetComponent<Transform>()->GetScale().x;
	}

	Vec3 StringSprite2::GetPos() {
		return GetComponent<Transform>()->GetPosition();
	}

	void StringSprite2::SetColor(Col4 color) {
		GetComponent<PCTSpriteDraw>()->SetDiffuse(color);
	}

	int StringSprite2::SearchDataIndex(const vector<SpriteDataFormat>& data) {
		for (int i = 0; i < data.size(); i++) {
			if (data[i].name == m_name) {
				return i;
			}
		}
		//ここに来たらそのデータは存在しない
		return -1;
	}
}
//end basecross