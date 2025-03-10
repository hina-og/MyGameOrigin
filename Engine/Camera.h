#pragma once
#include "GameObject.h"

struct DirVec
{
	XMVECTOR forward_;
	XMVECTOR right_;
};

namespace Camera
{
	//初期化（プロジェクション行列作成）
	void Initialize();

	//更新（ビュー行列作成）
	void Update();

	//視点（カメラの位置）を設定
	void SetPosition(XMVECTOR position);
	void SetPosition(float x, float y, float z);

	//焦点（見る位置）を設定
	void SetTarget(XMVECTOR target);
	void SetTarget(float x, float y, float z);

	//位置を取得
	XMVECTOR GetPositionXMVECTOR();
	XMFLOAT3 GetPositionXMFLOAT3();

	//焦点を取得
	XMVECTOR GetTarget();

	//ビュー行列を取得
	XMMATRIX GetViewMatrix();

	//プロジェクション行列を取得
	XMMATRIX GetProjectionMatrix();

	//ビルボード用回転行列を取得
	XMMATRIX GetBillboardMatrix();

	void SetSphericalCoordinates(XMFLOAT3 sphericalData);
	void SetSphericalCoordinates(float radius, float theta, float phi);

	void MouseToCamera(XMFLOAT3 sphericalData);
	void MouseToCamera(float _radius, float _theta, float _phi);
	DirVec UpdatePlayerPositionAndCamera();
};