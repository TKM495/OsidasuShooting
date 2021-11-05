#include "stdafx.h"
#include "Project.h"

namespace basecross {
	namespace Utility {
		const Vec2 GetTextureSize(const wstring& key)
		{
			auto resource = App::GetApp()->GetResource<TextureResource>(key);
			ID3D11Resource* id3d11resource;
			resource->GetShaderResourceView()->GetResource(&id3d11resource);
			D3D11_TEXTURE2D_DESC textureDesc;
			auto texture = static_cast<ID3D11Texture2D*>(id3d11resource);
			texture->GetDesc(&textureDesc);
			float width = (float)textureDesc.Width;
			float height = (float)textureDesc.Height;
			return Vec2(width, height);
		}

		const Vec2 ConvertToUVCoordinate(const Vec2& coordinate, const wstring& textureName) {
			return ConvertToUVCoordinate(coordinate, GetTextureSize(textureName));
		}

		const Vec2 ConvertToUVCoordinate(const Vec2& coordinate, const Vec2& textureSize) {
			Vec2 uv;
			uv.x = coordinate.x / textureSize.x;
			uv.y = coordinate.y / textureSize.y;
			return uv;
		}

		void ConvertToUVCoordinates(const vector<Vec2>& coordinates, const wstring& textureName, vector<Vec2>& uv) {
			ConvertToUVCoordinates(coordinates, GetTextureSize(textureName), uv);
		}

		void ConvertToUVCoordinates(const vector<Vec2>& coordinates, const Vec2& textureSize, vector<Vec2>& uv) {
			for (auto& coordinate : coordinates) {
				float x = coordinate.x / textureSize.x;
				float y = coordinate.y / textureSize.y;
				uv.push_back(Vec2(x, y));
			}
		}

		Vec3 ConvertDegVecToRadVec(const Vec3& deg) {
			Vec3 rad(
				XMConvertToRadians(deg.x),
				XMConvertToRadians(deg.y),
				XMConvertToRadians(deg.z)
			);
			return rad;
		}
		Vec3 ConvertRadVecToDegVec(const Vec3& rad) {
			Vec3 deg(
				XMConvertToDegrees(rad.x),
				XMConvertToDegrees(rad.y),
				XMConvertToDegrees(rad.z)
			);
			return deg;
		}

		bool MatchAngle(float deg1, float deg2) {
			if (ClampAngle(0.0f, 360.0f, deg1) == ClampAngle(0.0f, 360.0f, deg2)) {
				return true;
			}
			else {
				return false;
			}
		}

		float ClampAngle(float min, float max, float angle) {
			if (min >= max) {
				throw BaseException(
					L"ˆø”‚ª‹t‚Å‚·B",
					L"min:" + to_wstring(min) + L" ,max:" + to_wstring(max),
					L"Utility::ClampAngle(float min, float max, float angle);"
				);
			}
			if (max - min != 360) {
				throw BaseException(
					L"max‚Æmin‚Ì·‚ª360‚Å‚Í‚ ‚è‚Ü‚¹‚ñ",
					L"max - min != 360",
					L"Utility::ClampAngle(float min, float max, float angle);"
				);
			}

			if (angle > max) {
				angle -= max;
				angle += min;
			}
			else if (angle < min) {
				angle += max;
				angle -= min;
			}

			return angle;
		}

		bool WStrToBool(wstring str) {
			if (str == L"TRUE" || str == L"True" || str == L"true") {
				return true;
			}
			else if (str == L"FALSE" || str == L"False" || str == L"false") {
				return false;
			}
			else {
				throw BaseException(
					L"•s³‚È•¶Žš—ñ‚Å‚·B",
					L"str : " + str,
					L"Utility::WStrToBool(wstring str)"
				);
				return false;
			}
		}

		Col4 ConvertColorZeroToOne(Col4 color) {
			return color / 255;
		}

		Vec3 ChangeVectorLength(const Vec3& vector, float length) {
			auto vec = vector;
			auto normalizedVec = vec.normalize();
			return normalizedVec * length;
		}
	}
}