#pragma once
#include "znoTouch_main.h"
#include "znoTouch_renderer.h"
#include "scene.h"

#define FADE_SPEED 0.05f
#define FADE_WAIT (0.9f / FADE_SPEED)

enum TYPE
{
	FADENONE = 0,
	FADEIN = 1,
	FADEOUT = 2
};

struct FADE
{
	D3DXVECTOR2 Position;	//�\�����W
	D3DXVECTOR2 Size;	//�傫��
	D3DXVECTOR2 Offset;
	D3DXVECTOR2 Coordinate;

	D3DXCOLOR color;

	int imageNum;	//
	int flip;
	int TextNo;	//�e�N�X�`���ԍ�
	int type;

	float rotation;	//��]�p�x

	bool use;	//�\���̎g�p���t���O
};

HRESULT InitFade();
void UnInitFade();
void UpdateFade();
void DrawFade();

void SetFade(TYPE type);
void Fader(const bool condition, const SCENE scene);