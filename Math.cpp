
#include	"Math.h"


/*
=============================================================================
	•¡G‚ÈŒvZ‚ğ‚±‚±‚Ås‚¤
=============================================================================
*/
const	float&	VecToAng(D3DXVECTOR2	base_vec, D3DXVECTOR2	pur_vec)	//	base_vec‚©‚çpur_vec‚ÌŠÔ‚ÌŠp“x‚ğæ“¾‚·‚é
{
	D3DXVec2Normalize(&base_vec, &base_vec);
	D3DXVec2Normalize(&pur_vec, &pur_vec);

	return	D3DXToDegree(atan2(pur_vec.y - base_vec.y, pur_vec.x - base_vec.x));
}
