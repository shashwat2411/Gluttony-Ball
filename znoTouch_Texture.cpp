#include	"znoTouch_texture.h"


//===================================================
//マクロ定義
//===================================================
#define		MAX_TEXTURE_NUM		(200)		// ロード限界数


//===================================================
//グローバル変数
//===================================================

//テクスチャ情報のポインタの配列
static	ID3D11ShaderResourceView*	g_pTexture[MAX_TEXTURE_NUM];

//ロード済のテクスチャの数
static	UINT	g_TextureIndex;

//テクスチャファイル名のバッファ	ファイル名255文字まで
static	char	g_TextureName[MAX_TEXTURE_NUM][256];

//============================================
//
//
//============================================


//============================================
//テクスチャの終了処理
//ロード済のテクスチャを全て解放
//============================================
void	UninitTexture()
{
	for (int i = 0; i < g_TextureIndex; i++)
	{
		if (g_pTexture[i] != NULL)		//	何かデータが入っていたら
		{
			g_pTexture[i]->Release();	//	解放する
			g_pTexture[i] = NULL;		//	初期化しておく
		}
	}
}


//=======================================================
//指定のテクスチャ情報を取得
//in	使用したいテクスチャハンドル
//out	テクスチャ情報のポインタの入ったポインタ変数のポインタ
//=======================================================
ID3D11ShaderResourceView**	GetTexture(int	index)
{
	//	エラーチェック
	if (index < 0)
	{
		return	NULL;	// 0未満
	}
	if (index >= g_TextureIndex)
	{
		return	NULL;	// ロード数オーバー
	}

	//	インデックスが示す場所の配列のポインタを返す
	return	&g_pTexture[index];

}


//===================================================================
//テクスチャのロード
//in	テクスチャファイル名の先頭ポインタ
//
int		LoadTexture(char*	filename)
{
	//すでに読み込まれたテクスチャ名を調べて同名の
	//テクスチャ名が存在した場合は、テクスチャ名の
	//格納された配列の番号を返す。

	for (int i = 0; i < g_TextureIndex; i++)
	{	//テクスチャ名を比較
		if (strcmp(g_TextureName[i], filename) == 0)
		//if (strcmp(&g_TextureName[i][0], filename) == 0)
		{
			return	i;
		}
	}
	//	読み込み数が限界を超えていないか？
	if (g_TextureIndex == MAX_TEXTURE_NUM)
	{
		return	-1;//	読み込めないのでエラーコードを返す
	}

	//	テクスチャのロード
	HRESULT		hr = D3DX11CreateShaderResourceViewFromFile(
		GetDevice(),
		filename,
		NULL,
		NULL,
		&g_pTexture[g_TextureIndex],
		NULL
	);
	if (hr != S_OK)
	{
		return	-1;//	読み込み失敗
	}

	//	ロードしたテクスチャ名の登録
	strcpy_s(g_TextureName[g_TextureIndex], 256, filename);
	//strcpy_s(&g_TextureName[g_TextureIndex][0], 256, filename);

	int		retIndex = g_TextureIndex;	//現在の数を一時退避
	g_TextureIndex++;					//現在の数を増やしておく

	return	retIndex;					//退避していた値を返す

}






