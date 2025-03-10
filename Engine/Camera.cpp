#include "camera.h"
#include "Direct3D.h"


XMMATRIX _billBoard;

namespace Camera {
	//変数
	XMVECTOR position_;	//カメラの位置（視点）
	XMVECTOR target_;	//見る位置（焦点）
	XMMATRIX viewMatrix_;	//ビュー行列
	XMMATRIX projMatrix_;	//プロジェクション行列

	float theta_;
	float phi_;
	float radius_;

	const float rotationSpeed{ 0.005f };
	const float phiMin = 0.1f;             // 下方向の制限（約5.7度）
	const float phiMax = XM_PI - 0.1f;     // 上方向の制限（約174度）
};

//初期化（プロジェクション行列作成）
void Camera::Initialize()
{
	position_ = XMVectorSet(0, 7, -12, 0);	//カメラの位置
	target_ = XMVectorSet(0, 0, 0, 0);	//カメラの焦点

	//プロジェクション行列
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//更新（ビュー行列作成）
void Camera::Update()
{
	//ビュー行列
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));



	////ビルボード行列
	////（常にカメラの方を向くように回転させる行列。パーティクルでしか使わない）
	////http://marupeke296.com/DXG_No11_ComeOnBillboard.html
	//_billBoard = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), XMLoadFloat3(&target_)- XMLoadFloat3(&position_), XMVectorSet(0, 1, 0, 0));
	//_billBoard = XMMatrixInverse(nullptr, _billBoard);
}

//焦点を設定
void Camera::SetTarget(XMVECTOR target) { target_ = target; }
void Camera::SetTarget(float x, float y, float z)
{
	target_ = { x,y,z };
}

//位置を設定
void Camera::SetPosition(XMVECTOR position) { position_ = position; }

void Camera::SetPosition(float x, float y, float z)
{
	position_ = { x,y,z };
}

//焦点を取得
XMVECTOR Camera::GetTarget() { return target_; }

//位置を取得
XMVECTOR Camera::GetPositionXMVECTOR() { return position_; }

XMFLOAT3 Camera::GetPositionXMFLOAT3()
{
	XMFLOAT3 fPos = { XMVectorGetX(position_),XMVectorGetY(position_),XMVectorGetZ(position_) };
	return fPos;
}

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix() { return viewMatrix_; }

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix() { return projMatrix_; }

//ビルボード用回転行列を取得
XMMATRIX Camera::GetBillboardMatrix(){	return _billBoard; }

void Camera::SetSphericalCoordinates(XMFLOAT3 _sphericalData)
{
	position_ = target_ +
		XMVectorSet(_sphericalData.z * sinf(_sphericalData.y) * cosf(_sphericalData.x),
			_sphericalData.z * cosf(_sphericalData.y),
			_sphericalData.z * sinf(_sphericalData.y) * sinf(_sphericalData.x),
			0.0f);

}

void Camera::SetSphericalCoordinates(float _radius, float _theta, float _phi)
{
	position_ = target_ +
		XMVectorSet(
			_radius * sinf(_phi) * cosf(_theta),
			_radius * cosf(_phi),
			_radius * sinf(_phi) * sinf(_theta),
			0.0f
		);
}

void Camera::MouseToCamera(XMFLOAT3 sphericalData)
{
	//マウスの移動量を角度に反映
	theta_ += sphericalData.x * rotationSpeed;      // 水平方向の回転
	phi_ -= sphericalData.y * rotationSpeed;        // 垂直方向の回転

	//垂直角度を制限
	if (phi_ < phiMin)
	{
		phi_ = phiMin;
	}
	if (phi_ > phiMax)
	{
		phi_ = phiMax;
	}

	//ズームイン/アウト
	if (radius_ > 0)
	{
		radius_ -= sphericalData.z * 0.1f;         // マウスホイールで距離を調整
	}

	if (radius_ < 2.0f)
	{
		radius_ = 2.0f;    // 最小距離
	}
	if (radius_ > 50.0f)
	{
		radius_ = 50.0f;  // 最大距離
	}

	radius_ = 8.0f;

	SetSphericalCoordinates(radius_, theta_, phi_);
}

void Camera::MouseToCamera(float _radius, float _theta, float _phi)
{
	//マウスの移動量を角度に反映
	theta_ += _theta * rotationSpeed;      // 水平方向の回転
	phi_ -= _phi * rotationSpeed;        // 垂直方向の回転

	//垂直角度を制限
	if (phi_ < phiMin)
	{
		phi_ = phiMin;
	}
	if (phi_ > phiMax)
	{
		phi_ = phiMax;
	}

	//ズームイン/アウト
	radius_ += _radius * 0.1f;         // マウスホイールで距離を調整
	if (radius_ < 5.0f)
	{
		radius_ = 5.0f;    // 最小距離
	}
	if (radius_ > 50.0f)
	{
		radius_ = 50.0f;  // 最大距離
	}

	radius_ = 8.0;

	//新しいカメラ位置を計算
	SetSphericalCoordinates(radius_, theta_, phi_);
}

DirVec Camera::UpdatePlayerPositionAndCamera()
{
	//// ビュー行列からカメラの前方向（第3列）と右方向（第1列）を取得
	//XMVECTOR forward_ = XMVector3Normalize(XMVectorSet(projMatrix_.r[2].m128_f32[0], 0, -projMatrix_.r[2].m128_f32[2], 0.0f));
	//XMVECTOR right_   = XMVector3Normalize(XMVectorSet(-projMatrix_.r[0].m128_f32[0], 0, projMatrix_.r[0].m128_f32[2], 0.0f));

	//return { forward_,right_ };

	// ビュー行列からカメラの前方向（第3列）と右方向（第1列）を取得
	XMVECTOR forward_ = XMVector3Normalize(XMVectorSet(viewMatrix_.r[2].m128_f32[0], 0.0f, -viewMatrix_.r[2].m128_f32[2], 0.0f));
	XMVECTOR right_   = XMVector3Normalize(XMVectorSet(-viewMatrix_.r[0].m128_f32[0], 0.0f, viewMatrix_.r[0].m128_f32[2], 0.0f));

	return { forward_, right_ };

}
