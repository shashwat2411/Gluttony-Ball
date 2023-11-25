#include	"znoTouch_sprite.h"

#define		NUM_VERTEX	(4)

static	ID3D11Buffer*	g_VertexBuffer = NULL;

//=================================================
//�X�v���C�g�`�揈��
//in
//	�\�����WX, �\�����WY, ���T�C�Y, �c�T�C�Y, ��]�p�x, �J���[
//=================================================
void DrawSpriteColorRotate(float posx, float posy, int size_w, int size_h, float kakudo, D3DXCOLOR col,
	float	PaternNo, float	uv_w, float uv_h, int NumPatern)
{
	// �\���������|���S���̒��_�o�b�t�@��ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);
	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	D3D11_MAPPED_SUBRESOURCE msr;
	//���_�o�b�t�@�ւ̏������݋������炤
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//���_�\���̂̌^�Ƀ|�C���^�[�^��ϊ�������
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	//���_ V0���Z�b�g
	vertex[0].Position = D3DXVECTOR3(-size_w / 2, -size_h / 2, 0.0f);
	vertex[0].Diffuse = col;	// D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(PaternNo * uv_w, NumPatern * uv_h);
	//���_ V1���Z�b�g
	vertex[1].Position = D3DXVECTOR3(+size_w / 2, -size_h / 2, 0.0f);
	vertex[1].Diffuse = col;	// D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2((PaternNo + 1) * uv_w, NumPatern * uv_h);
	//���_ V2���Z�b�g
	vertex[2].Position = D3DXVECTOR3(-size_w / 2, +size_h / 2, 0.0f);
	vertex[2].Diffuse = col;	// D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(PaternNo * uv_w, (NumPatern + 1) * uv_h);
	//���_ V3���Z�b�g
	vertex[3].Position = D3DXVECTOR3(+size_w / 2, +size_h / 2, 0.0f);
	vertex[3].Diffuse = col;	// D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2((PaternNo + 1) * uv_w, (NumPatern + 1) * uv_h);

	//�x�����W�A���֕ϊ�
	float	rad = D3DXToRadian(kakudo);
	float	x, y;

	for (int i = 0; i < 4; i++)
	{
		x = vertex[i].Position.x * cosf(rad) - vertex[i].Position.y * sinf(rad);
		y = vertex[i].Position.y * cosf(rad) + vertex[i].Position.x * sinf(rad);

		vertex[i].Position.x = x + posx;
		vertex[i].Position.y = y + posy;
	}

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);//�������ݏI��

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);

	// �e�N�X�`���̃Z�b�g
	//GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture);
}

void	InitSprite()
{
	ID3D11Device *pDevice = GetDevice();

	{//�O�p�`�p�̒��_����������
		// ���_�o�b�t�@����
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;//���_1�����_���̃T�C�Y�ō��
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);
		//�O�p�`�p���_�i�[����
		D3DXCOLOR	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	////���p�`������
	//InitLineCircle();

	// �e�N�X�`���̃��[�h
	//D3DX11CreateShaderResourceViewFromFile(
	//	pDevice,
	//	g_TextureName,	//	�e�N�X�`���摜�̃t�@�C����
	//	NULL,
	//	NULL,
	//	&g_Texture,		//	�ǂݍ��񂾃e�N�X�`���̏�񂪓���ϐ��̃|�C���^
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
