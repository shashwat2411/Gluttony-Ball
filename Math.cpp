
#include	"Math.h"


/*
=============================================================================
	���G�Ȍv�Z�������ōs��
=============================================================================
*/
const	float&	VecToAng(D3DXVECTOR2	base_vec, D3DXVECTOR2	pur_vec)	//	base_vec����pur_vec�̊Ԃ̊p�x���擾����
{
	D3DXVec2Normalize(&base_vec, &base_vec);
	D3DXVec2Normalize(&pur_vec, &pur_vec);

	return	D3DXToDegree(atan2(pur_vec.y - base_vec.y, pur_vec.x - base_vec.x));
}
