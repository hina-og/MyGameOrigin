#include "SphereCollider.h"
#include "BoxCollider.h"
#include "NoHitSphereCollider.h"
#include "Model.h"

//�R���X�g���N�^�i�����蔻��̍쐬�j
//�����FbasePos	�����蔻��̒��S�ʒu�i�Q�[���I�u�W�F�N�g�̌��_���猩���ʒu�j
//�����Fsize	�����蔻��̃T�C�Y
NoHitSphereCollider::NoHitSphereCollider(XMFLOAT3 center, float radius)
{
	center_ = center;
	size_ = XMFLOAT3(radius, radius, radius);
	type_ = COLLIDER_CIRCLE_NOHIT;

	//�����[�X���͔���g�͕\�����Ȃ�
#ifdef _DEBUG
	//�e�X�g�\���p����g
	hDebugModel_ = Model::Load("DebugCollision/sphereCollider.fbx");
#endif
}

//�ڐG����
//�����Ftarget	����̓����蔻��
//�ߒl�F�ڐG���Ă��true
bool NoHitSphereCollider::IsHit(Collider* target)
{
	switch (target->type_)
	{
	case COLLIDER_CIRCLE:
		return IsHitNoHitCircleVsCircle((SphereCollider*)target, this);
	default:
		break;
	}
}