#pragma once

#include	<Windows.h>
#include	"xaudio2.h"		//XAudioを利用したいときにインクルード


bool	InitSound(HWND	hWnd);	//	サウンド初期化
void	UninitSound(void);		//	サウンド終了

int		LoadSound(char*	pFilename);		//	データのロード
void	PlaySound(int index, int loopCount);	//	データの再生	フラグ0で一回、-1でループ再生
void	StopSound(int	index);			//	データの再生停止


void	StopSoundAll(void);						//	全ての再生を停止
void	SetVolume(int	index, float	vol);	//	ボリュームの変更


//	サウンド追加
//	1	コントローラーと同じタイミングで初期化＆終了処理を行う
//	2	タイトルなどのシーンの初期化でデータロード＆再生開始（BGM）
//		終了処理で再生停止（BGM）
//	3	弾・爆発なども初期化でロードしておく。
//		再生時はそれぞれのタイミングで行うが、ループごとに毎回再生されないように
//		注意が必要。
//		同様にロードも初期化の一回のみになるよう注意。
//
