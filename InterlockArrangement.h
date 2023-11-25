#pragma once

#include "znoTouch_BaseOfPerformer.h"

#ifndef INTERLOCKARRANGEMENT_H_

#define	INTERLOCKARRANGEMENT_H_

//当たり判定は足場ブロックと同様の判定

//============================================================
//	ボタンに連動して作動するものクラス
//=============================================================
#define INTERLOCKARRANGEMENT_MAX (10)//ボタンに連動して作動するものの配置個数上限

//INTERLOCKARRANGEMENTの個数はボタンの個数と同じ
class INTERLOCKARRANGEMENT :public	BASE_OF_PERFORMER
{
public:

	void	Update();
	void	Prepare();
	void	Reset();
	void	SetOn_Off_InterlockArrangement(const bool on_off) { On_OffSwitch = on_off; };
	void	SetInterlockArrangement(D3DXVECTOR2 pos, D3DXVECTOR2 size);
	bool	GetOn_Off_InterlockArrangement() { return On_OffSwitch; };

private:
	bool On_OffSwitch;	//trueならスイッチがオンになりギミックが作動する ボタンの同スイッチを使えればそれでOK

	unsigned int	texture1;
	unsigned int texture2;
};

//=============================================
//	ボタンに連動して作動するもの管理プログラム
//=============================================
void	InitInterlockArrangement();		//ボタンと連動して作動するものを初期化
void	UninitInterlockArrangement();		//ボタンと連動して作動するもの終了処理
void	UpdateInterlockArrangement();		//ボタンと連動して作動するもの更新処理
void	DrawInterlockArrangement();		//ボタンと連動して作動するもの描画処理

void SetInterlockArrangements(D3DXVECTOR2 pos, D3DXVECTOR2 size, int index); //ボタンと連動して作動するもののセット
INTERLOCKARRANGEMENT* GetInterlockArrangement();//ボタンと連動して作動するものの取得


#endif