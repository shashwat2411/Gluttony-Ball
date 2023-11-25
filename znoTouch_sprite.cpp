#include	"znoTouch_sprite.h"

#define		NUM_VERTEX	(4)

static	ID3D11Buffer*	g_VertexBuffer = NULL;

//=================================================
//スプライト描画処理
//in
//	表示座標X, 表示座標Y, 横サイズ, 縦サイズ, 回転角度, カラー
//=================================================
void DrawSpriteColorRotate(float posx, float posy, int size_w, int size_h, float kakudo, D3DXCOLOR col,
	float	PaternNo, float	uv_w, float uv_h, int NumPatern)
{
	// 表示したいポリゴンの頂点バッファを設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);
	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	D3D11_MAPPED_SUBRESOURCE msr;
	//頂点バッファへの書き込み許可をもらう
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//頂点構造体の型にポインター型を変換をする
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	//頂点 V0をセット
	vertex[0].Position = D3DXVECTOR3(-size_w / 2, -size_h / 2, 0.0f);
	vertex[0].Diffuse = col;	// D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(PaternNo * uv_w, NumPatern * uv_h);
	//頂点 V1をセット
	vertex[1].Position = D3DXVECTOR3(+size_w / 2, -size_h / 2, 0.0f);
	vertex[1].Diffuse = col;	// D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2((PaternNo + 1) * uv_w, NumPatern * uv_h);
	//頂点 V2をセット
	vertex[2].Position = D3DXVECTOR3(-size_w / 2, +size_h / 2, 0.0f);
	vertex[2].Diffuse = col;	// D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(PaternNo * uv_w, (NumPatern + 1) * uv_h);
	//頂点 V3をセット
	vertex[3].Position = D3DXVECTOR3(+size_w / 2, +size_h / 2, 0.0f);
	vertex[3].Diffuse = col;	// D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2((PaternNo + 1) * uv_w, (NumPatern + 1) * uv_h);

	//度をラジアンへ変換
	float	rad = D3DXToRadian(kakudo);
	float	x, y;

	for (int i = 0; i < 4; i++)
	{
		x = vertex[i].Position.x * cosf(rad) - vertex[i].Position.y * sinf(rad);
		y = vertex[i].Position.y * cosf(rad) + vertex[i].Position.x * sinf(rad);

		vertex[i].Position.x = x + posx;
		vertex[i].Position.y = y + posy;
	}

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);//書き込み終了

	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_VERTEX, 0);

	// テクスチャのセット
	//GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);
}

void	InitSprite()
{
	ID3D11Device *pDevice = GetDevice();

	{//三角形用の頂点初期化処理
		// 頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;//頂点1個＊頂点数のサイズで作る
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);
		//三角形用頂点格納処理
		D3DXCOLOR	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	////多角形初期化
	//InitLineCircle();

	// テクスチャのロード
	//D3DX11CreateShaderResourceViewFromFile(
	//	pDevice,
	//	g_TextureName,	//	テクスチャ画像のファイル名
	//	NULL,
	//	NULL,
	//	&g_Texture,		//	読み込んだテクスチャの情報が入る変数のポインタ
	//	NULL
	//);

}

void	UninitSprite()
{
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}
