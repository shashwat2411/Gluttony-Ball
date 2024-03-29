
#include	"Math.h"


/*
=============================================================================
	複雑な計算をここで行う
=============================================================================
*/
const	float&	VecToAng(D3DXVECTOR2	base_vec, D3DXVECTOR2	pur_vec)	//	base_vecからpur_vecの間の角度を取得する
{
	D3DXVec2Normalize(&base_vec, &base_vec);
	D3DXVec2Normalize(&pur_vec, &pur_vec);

	return	D3DXToDegree(atan2(pur_vec.y - base_vec.y, pur_vec.x - base_vec.x));
}
