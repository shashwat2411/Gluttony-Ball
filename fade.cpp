#include "fade.h"
#include "znoTouch_texture.h"
#include "znoTouch_sprite.h"

//============================
//マクロ定義
//============================

//============================
//プロトタイプ宣言
//============================

//============================
//グローバル変数
//============================
FADE g_Fade;

static bool over = true;
bool out = false;

bool FadeNext = false;
int FadeTimer = 0;

char TextNoFade[] = "data/texture/fade.png";
//============================
//初期化
//============================
HRESULT InitFade()
{
	{
		g_Fade.TextNo = LoadTexture(TextNoFade);

		g_Fade.Position.x = SCREEN_WIDTH / 2;
		g_Fade.Position.y = SCREEN_HEIGHT / 2;

		g_Fade.Size.x = SCREEN_WIDTH;
		g_Fade.Size.y = SCREEN_HEIGHT;

		g_Fade.use = true;

		g_Fade.rotation = 0.0f;

		g_Fade.Offset = D3DXVECTOR2(0.0f, 0.0f);
		g_Fade.Coordinate = D3DXVECTOR2(1.0f, 1.0f);

		g_Fade.color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		g_Fade.flip = 0;
	}


	return S_OK;
}

//============================
//終了処理
//============================
void UnInitFade()
{

}


//============================
//描画処理
//============================
void DrawFade()
{
	if (g_Fade.use == true)
	{

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Fade.TextNo));

		DrawSpriteColorRotate
		(
			g_Fade.Position.x, 
			g_Fade.Position.y, 
			g_Fade.Size.x, 
			g_Fade.Size.y, 
			g_Fade.rotation, 
			g_Fade.color, 
			0, 
			1, 
			1, 
			1
		);

		GetDeviceContext()->Draw(4, 0);
	}
}

//============================
//更新処理
//============================
void UpdateFade()
{
	if (g_Fade.use == true)
	{
		over = false;
		if (g_Fade.type == FADEIN)
		{
			g_Fade.color.a -= FADE_SPEED;
			if (g_Fade.color.a <= 0.0f)
			{
				g_Fade.color.a = 0;
				over = true;
			}
		}
		if (g_Fade.type == FADEOUT)
		{
			g_Fade.color.a += FADE_SPEED;
			if (g_Fade.color.a >= 1.0f)
			{
				g_Fade.type = FADENONE;
				over = true;
			}
		}
		if (g_Fade.type == FADENONE)
		{
			g_Fade.color.a = 0.0f;
		}
	}
}


void SetFade(TYPE type)
{
	if (g_Fade.use == true)
	{
		g_Fade.type = type;

		if (g_Fade.type == FADEIN) { g_Fade.color.a = 1.0f; }
		else if (g_Fade.type == FADEOUT) { g_Fade.color.a = 0.0f; }
	}
}


void Fader(const bool condition, const SCENE scene)
{
	if (condition == true)
	{
		SetFade(FADEOUT);
		FadeNext = true;
	}
	if (FadeNext == true)
	{
		FadeTimer += 1;
		if (FadeTimer >= FADE_WAIT)
		{
			SetScene(scene);
			FadeNext = false;
			FadeTimer = 0;
		}
	}
}