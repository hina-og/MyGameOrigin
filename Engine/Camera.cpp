#include "camera.h"
#include "Direct3D.h"


XMMATRIX _billBoard;

namespace Camera {
	//�ϐ�
	XMVECTOR position_;	//�J�����̈ʒu�i���_�j
	XMVECTOR target_;	//����ʒu�i�œ_�j
	XMMATRIX viewMatrix_;	//�r���[�s��
	XMMATRIX projMatrix_;	//�v���W�F�N�V�����s��

	float theta_;
	float phi_;
	float radius_;

	const float rotationSpeed{ 0.005f };
	const float phiMin = 0.1f;             // �������̐����i��5.7�x�j
	const float phiMax = XM_PI - 0.1f;     // ������̐����i��174�x�j
};

//�������i�v���W�F�N�V�����s��쐬�j
void Camera::Initialize()
{
	position_ = XMVectorSet(0, 7, -12, 0);	//�J�����̈ʒu
	target_ = XMVectorSet(0, 0, 0, 0);	//�J�����̏œ_

	//�v���W�F�N�V�����s��
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//�X�V�i�r���[�s��쐬�j
void Camera::Update()
{
	//�r���[�s��
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));



	////�r���{�[�h�s��
	////�i��ɃJ�����̕��������悤�ɉ�]������s��B�p�[�e�B�N���ł����g��Ȃ��j
	////http://marupeke296.com/DXG_No11_ComeOnBillboard.html
	//_billBoard = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), XMLoadFloat3(&target_)- XMLoadFloat3(&position_), XMVectorSet(0, 1, 0, 0));
	//_billBoard = XMMatrixInverse(nullptr, _billBoard);
}

//�œ_��ݒ�
void Camera::SetTarget(XMVECTOR target) { target_ = target; }
void Camera::SetTarget(float x, float y, float z)
{
	target_ = { x,y,z };
}

//�ʒu��ݒ�
void Camera::SetPosition(XMVECTOR position) { position_ = position; }

void Camera::SetPosition(float x, float y, float z)
{
	position_ = { x,y,z };
}

//�œ_���擾
XMVECTOR Camera::GetTarget() { return target_; }

//�ʒu���擾
XMVECTOR Camera::GetPositionXMVECTOR() { return position_; }

XMFLOAT3 Camera::GetPositionXMFLOAT3()
{
	XMFLOAT3 fPos = { XMVectorGetX(position_),XMVectorGetY(position_),XMVectorGetZ(position_) };
	return fPos;
}

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix() { return viewMatrix_; }

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix() { return projMatrix_; }

//�r���{�[�h�p��]�s����擾
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
	//�}�E�X�̈ړ��ʂ��p�x�ɔ��f
	theta_ += sphericalData.x * rotationSpeed;      // ���������̉�]
	phi_ -= sphericalData.y * rotationSpeed;        // ���������̉�]

	//�����p�x�𐧌�
	if (phi_ < phiMin)
	{
		phi_ = phiMin;
	}
	if (phi_ > phiMax)
	{
		phi_ = phiMax;
	}

	//�Y�[���C��/�A�E�g
	if (radius_ > 0)
	{
		radius_ -= sphericalData.z * 0.1f;         // �}�E�X�z�C�[���ŋ����𒲐�
	}

	if (radius_ < 2.0f)
	{
		radius_ = 2.0f;    // �ŏ�����
	}
	if (radius_ > 50.0f)
	{
		radius_ = 50.0f;  // �ő勗��
	}

	radius_ = 8.0f;

	SetSphericalCoordinates(radius_, theta_, phi_);
}

void Camera::MouseToCamera(float _radius, float _theta, float _phi)
{
	//�}�E�X�̈ړ��ʂ��p�x�ɔ��f
	theta_ += _theta * rotationSpeed;      // ���������̉�]
	phi_ -= _phi * rotationSpeed;        // ���������̉�]

	//�����p�x�𐧌�
	if (phi_ < phiMin)
	{
		phi_ = phiMin;
	}
	if (phi_ > phiMax)
	{
		phi_ = phiMax;
	}

	//�Y�[���C��/�A�E�g
	radius_ += _radius * 0.1f;         // �}�E�X�z�C�[���ŋ����𒲐�
	if (radius_ < 5.0f)
	{
		radius_ = 5.0f;    // �ŏ�����
	}
	if (radius_ > 50.0f)
	{
		radius_ = 50.0f;  // �ő勗��
	}

	radius_ = 8.0;

	//�V�����J�����ʒu���v�Z
	SetSphericalCoordinates(radius_, theta_, phi_);
}

DirVec Camera::UpdatePlayerPositionAndCamera()
{
	//// �r���[�s�񂩂�J�����̑O�����i��3��j�ƉE�����i��1��j���擾
	//XMVECTOR forward_ = XMVector3Normalize(XMVectorSet(projMatrix_.r[2].m128_f32[0], 0, -projMatrix_.r[2].m128_f32[2], 0.0f));
	//XMVECTOR right_   = XMVector3Normalize(XMVectorSet(-projMatrix_.r[0].m128_f32[0], 0, projMatrix_.r[0].m128_f32[2], 0.0f));

	//return { forward_,right_ };

	// �r���[�s�񂩂�J�����̑O�����i��3��j�ƉE�����i��1��j���擾
	XMVECTOR forward_ = XMVector3Normalize(XMVectorSet(viewMatrix_.r[2].m128_f32[0], 0.0f, -viewMatrix_.r[2].m128_f32[2], 0.0f));
	XMVECTOR right_   = XMVector3Normalize(XMVectorSet(-viewMatrix_.r[0].m128_f32[0], 0.0f, viewMatrix_.r[0].m128_f32[2], 0.0f));

	return { forward_, right_ };

}
