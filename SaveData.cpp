
#include	"saveData.h"
#include	<stdio.h>

const	char*	filename = "game_data.bin";

typedef	struct SPRITE
{
	bool	use;

	unsigned	int	texNo;

	D3DXVECTOR2	pos;
	D3DXVECTOR2	size;

	bool	animation;
	bool	animationOver;

	float			animTimer;			//	�A�j���[�V�����^�C�}�[
	unsigned	int	animTimeMax;		//	animTimer�����̒l�𒴂����0�ɖ߂�
	float			animOneFlameTime;	//	animTimer�ɉ��Z��������ϐ�

	unsigned	int	animFlame_W;		//	�e�N�X�`���̉�������
	unsigned	int	animFlame_H;		//	�e�N�X�`���̏c������

	unsigned	int		animationNo_H;	//	�e�N�X�`���̏c�̃A�j���[�V�����l
	float				animationNo_W;	//	�e�N�X�`���̉��̃A�j���[�V�����l

	float	texSize_W;					//	�e�N�X�`���̉��̕\���T�C�Y
	float	texSize_H;					//	�e�N�X�`���̏c�̕\���T�C�Y
};

#define	Numbers_Max	(4)

SAVE_DATA	save_data[SAVE_DATA_MAX];

SPRITE	DataText;
SPRITE	numbers[Numbers_Max];

static	D3DXCOLOR	color;

bool	StickBool;
bool	SelectBool;

int	SelectDataNum;

float	timer;
const	float	PlusTimeNum = 0.4f;
const	float	TimeMax = 60 / 3;

unsigned	int	g_SelectDataSE;
unsigned	int	g_CollectDataSE;

//==============================================================
//	�Z�[�u�f�[�^�Ǘ��v���O����
void	InitSaveData()		//	�Z�[�u�f�[�^������
{
	Load(save_data);

	StickBool = false;
	SelectBool = false;
	SelectDataNum = 0;
	timer = 0.0f;

	color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	g_SelectDataSE = LoadSound((char*)"data/SE/select_SE.wav");
	g_CollectDataSE = LoadSound((char*)"data/SE/collectData_SE.wav");

	//===========================================================================
	DataText.texNo = LoadTexture((char*)"data/texture/data_text.png");
	DataText.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	DataText.size = D3DXVECTOR2(4, 1) * 200;

	DataText.use = true;
	DataText.animation = false;
	DataText.animationOver = false;

	DataText.animTimer = 0.0f;
	DataText.animOneFlameTime = 0.0f;
	DataText.animTimeMax = 0.0f;

	DataText.animFlame_W = 1;
	DataText.animFlame_H = 1;

	DataText.texSize_W = 1.0f;
	DataText.texSize_H = 1.0f;

	DataText.animationNo_W = 0.0f;
	DataText.animationNo_H = 0;
	//===========================================================================
	for (int i = 0; i < Numbers_Max; i++)
	{
		numbers[i].texNo = LoadTexture((char*)"data/texture/data_numbers.png");
		//numbers[i].pos = D3DXVECTOR2(SCREEN_WIDTH / 2 + (i - 2) * 50, SCREEN_HEIGHT / 2);
		numbers[i].size = D3DXVECTOR2(2, 3) * 30;

		numbers[i].use = true;
		if (save_data[SelectDataNum].life < 10 && i == 2)
			numbers[i].use = false;
		numbers[i].animation = false;
		numbers[i].animationOver = false;

		numbers[i].animTimer = 0.0f;
		numbers[i].animOneFlameTime = 0.0f;
		numbers[i].animTimeMax = 0.0f;

		numbers[i].animFlame_W = 10;
		numbers[i].animFlame_H = 10;

		numbers[i].texSize_W = 1.0f / 10;
		numbers[i].texSize_H = 1.0f;

		numbers[i].animationNo_W = 0.0f;
		numbers[i].animationNo_H = 0;
	}
	numbers[0].pos = DataText.pos - D3DXVECTOR2(DataText.size.x / 5, DataText.size.y / 4);
	numbers[0].animationNo_W = save_data[SelectDataNum].dataNum;
	numbers[1].pos = DataText.pos + D3DXVECTOR2(DataText.size.x * 3 / 8, DataText.size.y / 4);
	numbers[1].animationNo_W = save_data[SelectDataNum].life % 10;
	numbers[2].pos = DataText.pos + D3DXVECTOR2(DataText.size.x * 3 / 8 - numbers[2].size.x, DataText.size.y / 4);
	numbers[2].animationNo_W = (int)(save_data[SelectDataNum].life / 10);
	numbers[3].pos = DataText.pos + D3DXVECTOR2(DataText.size.x * 3 / 8, -DataText.size.y / 4);
	numbers[3].animationNo_W = save_data[SelectDataNum].stageNum;
	//===========================================================================
}

void	UninitSaveData()	//	�Z�[�u�f�[�^�I������
{

}

void	UpdateSaveData()	//	�Z�[�u�f�[�^�X�V����
{
	if (SelectBool)
	{
		timer += PlusTimeNum;

		color = D3DXCOLOR(1.0f - 0.5f * fabs(cosf(timer)),
			1.0f - 0.5f * fabs(cosf(timer)),
			1.0f - 0.5f * fabs(cosf(timer)), 1.0f);

		if (timer > TimeMax)
		{
			color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			Fader(true, SELECT_STAGE);
		}
	}
	else
	{
		if (!StickBool)
		{
			if (GetButtonTriggerA())
			{
				SelectBool = true;
				PlaySound(g_CollectDataSE, 0);
			}
			if (GetButtonTriggerStart())
			{
				save_data[SelectDataNum].dataNum = SelectDataNum + 1;
				save_data[SelectDataNum].life = 15;
				save_data[SelectDataNum].stageNum = 1;

				Save(save_data);

				numbers[0].animationNo_W = save_data[SelectDataNum].dataNum;
				numbers[1].animationNo_W = save_data[SelectDataNum].life % 10;
				numbers[2].animationNo_W = (int)(save_data[SelectDataNum].life / 10);
				numbers[3].animationNo_W = save_data[SelectDataNum].stageNum;
			
				if (save_data[SelectDataNum].life > 9)	numbers[2].use = true;
				else numbers[2].use = false;
			}
		}

		if (GetStickL().x > 0.5f && !StickBool)
		{
			StickBool = true;

			SelectDataNum++;
			if (SelectDataNum >= SAVE_DATA_MAX)	SelectDataNum = 0;

			numbers[0].animationNo_W = save_data[SelectDataNum].dataNum;
			numbers[1].animationNo_W = save_data[SelectDataNum].life % 10;
			numbers[2].animationNo_W = (int)(save_data[SelectDataNum].life / 10);
			numbers[3].animationNo_W = save_data[SelectDataNum].stageNum;

			if (save_data[SelectDataNum].life > 9)	numbers[2].use = true;
			else numbers[2].use = false;

			PlaySound(g_SelectDataSE, 0);
		}
		else if (GetStickL().x < -0.5f && !StickBool)
		{
			StickBool = true;

			SelectDataNum--;
			if (SelectDataNum < 0)	SelectDataNum = SAVE_DATA_MAX - 1;

			numbers[0].animationNo_W = save_data[SelectDataNum].dataNum;
			numbers[1].animationNo_W = save_data[SelectDataNum].life % 10;
			numbers[2].animationNo_W = (int)(save_data[SelectDataNum].life / 10);
			numbers[3].animationNo_W = save_data[SelectDataNum].stageNum;

			if (save_data[SelectDataNum].life > 9)	numbers[2].use = true;
			else numbers[2].use = false;

			PlaySound(g_SelectDataSE, 0);
		}

		if (GetStickL().x == 0 && StickBool)	StickBool = false;
	}
}

void	DrawSaveData()		//	�Z�[�u�f�[�^�`�揈��
{
	if (DataText.use)
	{
		// �e�N�X�`���̃Z�b�g
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(DataText.texNo));

		//	�|���S���z�u
		DrawSpriteColorRotate(DataText.pos.x, DataText.pos.y,
			DataText.size.x, DataText.size.y, 0.0f, color,
			DataText.animationNo_W, DataText.texSize_W, DataText.texSize_H, DataText.animationNo_H);
	}

	for (int i = 0; i < Numbers_Max; i++)
	{
		if (numbers[i].use)
		{
			// �e�N�X�`���̃Z�b�g
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(numbers[i].texNo));

			//	�|���S���z�u
			DrawSpriteColorRotate(numbers[i].pos.x, numbers[i].pos.y,
				numbers[i].size.x, numbers[i].size.y, 0.0f, color,
				numbers[i].animationNo_W, numbers[i].texSize_W, numbers[i].texSize_H, numbers[i].animationNo_H);
		}
	}
}


void	Load(SAVE_DATA*	data)
{
	char	dataChar[SAVE_DATA_MAX * SAVE_DATA_LIST_NUM + 1];

	FILE*	fp;
	fopen_s(&fp, filename, "rb");

	if (fp != NULL)
	{
		fread(dataChar, sizeof(unsigned	char), sizeof(dataChar) / sizeof(dataChar[0]), fp);

		fclose(fp);

		if (dataChar[0] - '0' > 0)
		{
			for (int i = 0; i < SAVE_DATA_MAX; i++)
			{
				data[i].dataNum = dataChar[i * SAVE_DATA_LIST_NUM + 0] - '0';
				data[i].life = dataChar[i * SAVE_DATA_LIST_NUM + 1] - '0';
				data[i].stageNum = dataChar[i * SAVE_DATA_LIST_NUM + 2] - '0';
			}
		}
	}
	else
	{
		for (int i = 0; i < SAVE_DATA_MAX; i++)
		{
			data[i].dataNum = i + 1;
			data[i].life = 15;
			data[i].stageNum = 1;
		}
	}
}

void	Save(SAVE_DATA*	data)
{
	char	dataChar[SAVE_DATA_MAX * SAVE_DATA_LIST_NUM + 1];

	for (int i = 0; i < SAVE_DATA_MAX * SAVE_DATA_LIST_NUM + 1; i++)
	{
		dataChar[i] = 0x00;
	}

	for (int i = 0; i < SAVE_DATA_MAX; i++)
	{
		for (int dataNum = 0; dataNum < data[i].dataNum; dataNum++)
		{
			dataChar[i * SAVE_DATA_LIST_NUM + 0] += 0x01;
		}
		dataChar[i * SAVE_DATA_LIST_NUM + 0] += '0';
		for (int life = 0; life < data[i].life; life++)
		{
			dataChar[i * SAVE_DATA_LIST_NUM + 1] += 0x01;
		}
		dataChar[i * SAVE_DATA_LIST_NUM + 1] += '0';
		for (int stageNum = 0; stageNum < data[i].stageNum; stageNum++)
		{
			dataChar[i * SAVE_DATA_LIST_NUM + 2] += 0x01;
		}
		dataChar[i * SAVE_DATA_LIST_NUM + 2] += '0';
	}

	FILE*	fp;
	fopen_s(&fp, filename, "wb");

	if (fp != NULL)
	{
		fwrite(dataChar, sizeof(unsigned char), sizeof(dataChar) / sizeof(dataChar[0]), fp);

		fclose(fp);
	}
}

SAVE_DATA*	GetSaveData()	//	�Z�[�u�f�[�^�̎擾
{
	return	save_data;
}

const	int&	GetSelectDataNum()
{
	return	SelectDataNum;
}











