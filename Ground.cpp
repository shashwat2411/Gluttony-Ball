
#include	"ground.h"
#include	"select_stage.h"

//===============================================================================================================================================
//	グラウンドクラスプログラム
//===============================================================================================================================================
void	GROUND::Update()
{
	if (use == true)
	{
		
	}
}

void	GROUND::Prepare()
{
	use = false;							//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	active = false;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	animation = false;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	gravity = false;						//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する

	MoveX = false;
	MoveY = false;
	display = true;

	texSize_W = 1.0f;
	texSize_H = 1.0f;

	frictionRate = 0.0f;
	collisionBool = true;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。

	texNo = LoadTexture((char*)"data/texture/ground.png");				//	LoadTextureの戻り値を記録する変数

	pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 4 / 5);					//	オブジェクトの現在地
	r_pos = pos;					//	posのReset値
	size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE);					//	オブジェクトの描画範囲

	color = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	オブジェクトから見た当たり判定の中心座標
	collisionSize = D3DXVECTOR2(size.x, size.y);				//	当たり判定のサイズ
}

void	GROUND::Reset()
{

}

//===============================================================================================================================================
//	グラウンド管理プログラム
//===============================================================================================================================================
GROUND	ground[GROUND_MAX];
OUT_LINE	out_line[OUT_LINE_MAX];
/*==================================
	グラウンド初期化
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
	グラウンド終了処理
====================================*/
void	UninitGround()
{
	for (int i = 0; i < GROUND_MAX; i++)
	{
		ground[i].Uninit();
	}
}

/*==================================
	グラウンド更新処理
====================================*/
void	UpdateGround()
{
	for (int i = 0; i < GROUND_MAX; i++)
	{
		ground[i].Update();
	}
}

/*==================================
	グラウンド描画処理
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
			// テクスチャのセット
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(out_line[i].texNo));

			//	ポリゴン配置
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
	//	上線のサーチ
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
	//	下線のサーチ
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

void	SetGround(const	D3DXVECTOR2&	pos, const	D3DXVECTOR2&	size)	//	足場のセット
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

void	SetGround(const	D3DXVECTOR2&	pos, const	D3DXVECTOR2&	size, bool display)	//	足場のセット
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
	グラウンド取得
====================================*/
GROUND*	GetGround()
{
	return	ground;
}

OUT_LINE*	GetOutLine()
{
	return	out_line;
}
















