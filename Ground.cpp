
#include	"ground.h"
#include	"select_stage.h"

//===============================================================================================================================================
//	�O���E���h�N���X�v���O����
//===============================================================================================================================================
void	GROUND::Update()
{
	if (use == true)
	{
		
	}
}

void	GROUND::Prepare()
{
	use = false;							//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	active = false;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	animation = false;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	gravity = false;						//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����

	MoveX = false;
	MoveY = false;
	display = true;

	texSize_W = 1.0f;
	texSize_H = 1.0f;

	frictionRate = 0.0f;
	collisionBool = true;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B

	texNo = LoadTexture((char*)"data/texture/ground.png");				//	LoadTexture�̖߂�l���L�^����ϐ�

	pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 4 / 5);					//	�I�u�W�F�N�g�̌��ݒn
	r_pos = pos;					//	pos��Reset�l
	size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE);					//	�I�u�W�F�N�g�̕`��͈�

	color = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = D3DXVECTOR2(size.x, size.y);				//	�����蔻��̃T�C�Y
}

void	GROUND::Reset()
{

}

//===============================================================================================================================================
//	�O���E���h�Ǘ��v���O����
//===============================================================================================================================================
GROUND	ground[GROUND_MAX];
OUT_LINE	out_line[OUT_LINE_MAX];
/*==================================
	�O���E���h������
====================================*/
void	InitGround()
{
	for (int i = 0; i < GROUND_MAX; i++)
	{
		ground[i].Init();
		ground[i].Prepare();
	}
	InitOutLine();
}

/*==================================
	�O���E���h�I������
====================================*/
void	UninitGround()
{
	for (int i = 0; i < GROUND_MAX; i++)
	{
		ground[i].Uninit();
	}
}

/*==================================
	�O���E���h�X�V����
====================================*/
void	UpdateGround()
{
	for (int i = 0; i < GROUND_MAX; i++)
	{
		ground[i].Update();
	}
}

/*==================================
	�O���E���h�`�揈��
====================================*/
void	DrawGround()
{
	for (int i = 0; i < GROUND_MAX; i++)
	{
		ground[i].Draw();
	}
	DrawOutLine();
}

//=================================================================================
void	InitOutLine()
{
	for (int i = 0; i < OUT_LINE_MAX; i++)
	{
		out_line[i].use = false;
		out_line[i].texNo = LoadTexture((char*)"data/texture/block_outLine.png");
		out_line[i].angle = 0;
		out_line[i].texSize_W = 1.0f;
		out_line[i].pos = D3DXVECTOR2(0, 0);
		out_line[i].size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE);
		out_line[i].color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	}
}
//=================================================================================
void	DrawOutLine()
{
	for (int i = 0; i < OUT_LINE_MAX; i++)
	{
		if (out_line[i].use)
		{
			// �e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(out_line[i].texNo));

			//	�|���S���z�u
			DrawSpriteColorRotate(out_line[i].pos.x, out_line[i].pos.y, out_line[i].size.x, out_line[i].size.y, out_line[i].angle, out_line[i].color,
				0, out_line[i].texSize_W, 1.0f, 0);
		}
	}
}

//=================================================================================
void	SetOutLine(const	int&	stage_num, const	D3DXVECTOR2&	leftup, const	D3DXVECTOR2&	rightdown)
{
	bool	upBool = false;
	for (int i = 0; i < OUT_LINE_MAX; i++)
	{
		if (!out_line[i].use && !upBool)
		{
			upBool = true;
			out_line[i].use = true;
			out_line[i].angle = 0;
			out_line[i].texSize_W = rightdown.x - leftup.x;
			out_line[i].pos.x = ((rightdown.x - leftup.x) / 2 + leftup.x) * BASE_SIZE;
			out_line[i].pos.y = (leftup.y + 0.5f) * BASE_SIZE;
			out_line[i].size = D3DXVECTOR2((rightdown.x - leftup.x) * BASE_SIZE, BASE_SIZE);
			out_line[i].color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		}
		else if (!out_line[i].use && upBool)
		{
			out_line[i].use = true;
			out_line[i].angle = 180;
			out_line[i].texSize_W = rightdown.x - leftup.x;
			out_line[i].pos.x = ((rightdown.x - leftup.x) / 2 + leftup.x) * BASE_SIZE;
			out_line[i].pos.y = (rightdown.y - 0.5f) * BASE_SIZE;
			out_line[i].size = D3DXVECTOR2((rightdown.x - leftup.x) * BASE_SIZE, BASE_SIZE);
			out_line[i].color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

			break;
		}
	}

	/*int	outLineNum = 0;
	bool	outSideBool = false;
	OUT_LINE	forSet[OUT_LINE_MAX];

	forSet[outLineNum].size.x = 0;
	forSet[outLineNum].angle = 0;
	//==========================================================================
	//	����̃T�[�`
	for (int x = 0; x < rightdown.x - leftup.x; x++)
	{
		if (leftup.y > 0)
		{
			if (GetStageChar(stage_num, x + leftup.x, leftup.y - 1) == 'g' || GetStageChar(stage_num, x + leftup.x, leftup.y - 1) == 'Q')
			{
				if (outSideBool)
				{
					forSet[outLineNum].pos = D3DXVECTOR2(forSet[outLineNum].size.x / 2 + leftup.x, leftup.y + 0.5f) * BASE_SIZE;

					outSideBool = false;
					outLineNum++;
					forSet[outLineNum].size.x = 0;
					forSet[outLineNum].angle = 0;
				}
			}
			else
			{
				outSideBool = true;
				forSet[outLineNum].size.x++;
			}
		}
	}
	if (outSideBool)	forSet[outLineNum].pos = D3DXVECTOR2(forSet[outLineNum].size.x / 2 + leftup.x, leftup.y + 0.5f) * BASE_SIZE;
	//==========================================================================
	outSideBool = false;
	outLineNum++;
	forSet[outLineNum].size.x = 0;
	forSet[outLineNum].angle = 180;
	//==========================================================================
	//	�����̃T�[�`
	for (int x = 0; x < rightdown.x - leftup.x; x++)
	{
		if (rightdown.y < STAGE_HEIGHT_MAX - 1)
		{
			if (GetStageChar(stage_num, x + leftup.x, rightdown.y + 1) == 'g' || GetStageChar(stage_num, x + leftup.x, rightdown.y + 1) == 'Q')
			{
				if (outSideBool)
				{
					forSet[outLineNum].pos = D3DXVECTOR2(forSet[outLineNum].size.x / 2 + leftup.x, rightdown.y - 0.5f) * BASE_SIZE;

					outSideBool = false;
					outLineNum++;
					forSet[outLineNum].size.x = 0;
					forSet[outLineNum].angle = 180;
				}
			}
			else
			{
				outSideBool = true;
				forSet[outLineNum].size.x++;
			}
		}
	}
	if (outSideBool)	forSet[outLineNum].pos = D3DXVECTOR2(forSet[outLineNum].size.x / 2 + leftup.x, rightdown.y - 0.5f) * BASE_SIZE;
	//==========================================================================
	
	for (int i = 0; i < OUT_LINE_MAX; i++)
	{
		if (!out_line[i].use)
		{
			for (int j = 0; j <= outLineNum; j++)
			{
				out_line[i + j].pos = forSet[j].pos;

				out_line[i + j].use = true;
				out_line[i + j].texSize_W = forSet[j].size.x;
				out_line[i + j].size.x = forSet[j].size.x * BASE_SIZE;
				out_line[i + j].angle = forSet[j].angle;
				linesEndNum = i + j + 1;
			}

			break;
		}
	}*/
}
//=================================================================================

void	SetSideOutLine(const	int&	stage_num)
{
	int	linesEndNum;
	for (linesEndNum = 0; out_line[linesEndNum].use; linesEndNum++);

	for (int y = 0; y < STAGE_HEIGHT_MAX; y++)
	{
		for (int x = 0; x < STAGE_WIDTH_MAX; x++)
		{
			if (GetStageChar(stage_num, x, y) == 'Q')
			{
				if (linesEndNum < OUT_LINE_MAX - 1)
				{
					if (x < STAGE_WIDTH_MAX - 1)
					{
						if (GetStageChar(stage_num, x + 1, y) != 'Q')
						{
							out_line[linesEndNum].use = true;
							out_line[linesEndNum].angle = 90;
							out_line[linesEndNum].texSize_W = 1.0f;
							out_line[linesEndNum].pos = D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y + 0.5f) * BASE_SIZE);
							out_line[linesEndNum].size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE);

							if (y > 0 && y < STAGE_HEIGHT_MAX - 1)
							{
								if (GetStageChar(stage_num, x + 1, y - 1) == 'Q')
								{
									out_line[linesEndNum].size.x += 5.8f;
									out_line[linesEndNum].pos.y -= 2.0f;
								}
								if (GetStageChar(stage_num, x + 1, y + 1) == 'Q')
								{
									out_line[linesEndNum].size.x += 5.8f;
									out_line[linesEndNum].pos.y += 2.0f;
								}
							}

							linesEndNum++;
						}
					}
					if (x > 0)
					{
						if (GetStageChar(stage_num, x - 1, y) != 'Q')
						{
							out_line[linesEndNum].use = true;
							out_line[linesEndNum].angle = 270;
							out_line[linesEndNum].texSize_W = 1.0f;
							out_line[linesEndNum].pos = D3DXVECTOR2(((float)x + 0.5f) * BASE_SIZE, ((float)y + 0.5f) * BASE_SIZE);
							out_line[linesEndNum].size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE);

							if (y > 0 && y < STAGE_HEIGHT_MAX - 1)
							{
								if (GetStageChar(stage_num, x - 1, y - 1) == 'Q')
								{
									out_line[linesEndNum].size.x += 5.8f;
									out_line[linesEndNum].pos.y -= 2.0f;
								}
								if (GetStageChar(stage_num, x - 1, y + 1) == 'Q')
								{
									out_line[linesEndNum].size.x += 5.8f;
									out_line[linesEndNum].pos.y += 2.0f;
								}
							}

							linesEndNum++;
						}
					}
				}
				//SetStageChar(stage_num, x, y, '-');
			}
		}
	}
}

void	SetGround(const	D3DXVECTOR2&	pos, const	D3DXVECTOR2&	size)	//	����̃Z�b�g
{
	for (int i = 0; i < GROUND_MAX; i++)
	{
		if (!ground[i].GetUse())
		{
			ground[i].SetUse(true);
			ground[i].SetPosi(pos);
			ground[i].SetSize(size * BASE_SIZE);
			ground[i].SetCollisionSize(size * BASE_SIZE);

			break;
		}
	}
}

void	SetGround(const	D3DXVECTOR2&	pos, const	D3DXVECTOR2&	size, bool display)	//	����̃Z�b�g
{
	for (int i = 0; i < GROUND_MAX; i++)
	{
		if (!ground[i].GetUse())
		{
			ground[i].SetUse(true);
			ground[i].SetPosi(pos);
			ground[i].SetSize(size * BASE_SIZE);
			ground[i].SetCollisionSize(size * BASE_SIZE);
			ground[i].SetTexSizeWidth(size.x);
			ground[i].SetTexSizeHeight(size.y);
			ground[i].SetDisplay(display);
			break;
		}
	}
}

/*==================================
	�O���E���h�擾
====================================*/
GROUND*	GetGround()
{
	return	ground;
}

OUT_LINE*	GetOutLine()
{
	return	out_line;
}
















