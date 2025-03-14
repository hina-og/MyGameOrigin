#include "SphereCollider.h"
#include "BoxCollider.h"
#include "NoHitSphereCollider.h"
#include "Model.h"

//コンストラクタ（当たり判定の作成）
//引数：basePos	当たり判定の中心位置（ゲームオブジェクトの原点から見た位置）
//引数：size	当たり判定のサイズ
SphereCollider::SphereCollider(XMFLOAT3 center, float radius)
{
	center_ = center;
	size_ = XMFLOAT3(radius, radius, radius);
	type_ = COLLIDER_CIRCLE;

	//リリース時は判定枠は表示しない
#ifdef _DEBUG
	//テスト表示用判定枠
	hDebugModel_ = Model::Load("DebugCollision/sphereCollider.fbx");
#endif
}

//接触判定
//引数：target	相手の当たり判定
//戻値：接触してればtrue
bool SphereCollider::IsHit(Collider* target)
{
	switch (target->type_)
	{
	case COLLIDER_BOX:
		return IsHitBoxVsCircle((BoxCollider*)target, this);
	case COLLIDER_CIRCLE:
		return IsHitCircleVsCircle((SphereCollider*)target, this);
	case COLLIDER_CIRCLE_NOHIT:
		return IsHitNoHitCircleVsCircle(this, (NoHitSphereCollider*)target);
	default:
		break;
	}
}