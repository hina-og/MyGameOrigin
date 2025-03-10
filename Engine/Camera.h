#pragma once
#include "GameObject.h"

struct DirVec
{
	XMVECTOR forward_;
	XMVECTOR right_;
};

namespace Camera
{
	//�������i�v���W�F�N�V�����s��쐬�j
	void Initialize();

	//�X�V�i�r���[�s��쐬�j
	void Update();

	//���_�i�J�����̈ʒu�j��ݒ�
	void SetPosition(XMVECTOR position);
	void SetPosition(float x, float y, float z);

	//�œ_�i����ʒu�j��ݒ�
	void SetTarget(XMVECTOR target);
	void SetTarget(float x, float y, float z);

	//�ʒu���擾
	XMVECTOR GetPositionXMVECTOR();
	XMFLOAT3 GetPositionXMFLOAT3();

	//�œ_���擾
	XMVECTOR GetTarget();

	//�r���[�s����擾
	XMMATRIX GetViewMatrix();

	//�v���W�F�N�V�����s����擾
	XMMATRIX GetProjectionMatrix();

	//�r���{�[�h�p��]�s����擾
	XMMATRIX GetBillboardMatrix();

	void SetSphericalCoordinates(XMFLOAT3 sphericalData);
	void SetSphericalCoordinates(float radius, float theta, float phi);

	void MouseToCamera(XMFLOAT3 sphericalData);
	void MouseToCamera(float _radius, float _theta, float _phi);
	DirVec UpdatePlayerPositionAndCamera();
};