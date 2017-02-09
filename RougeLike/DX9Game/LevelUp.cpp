#include "LevelUp.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Graphics.h"
#include "define.h"

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CLevelUp::CLevelUp(D3DXVECTOR3 Pos)
{
	//�e�N�X�`��ID�̐ݒ�
	m_nTextureID = TEXTURE_LEVELUP;

	//���_���̍쐬
	MakeVertex();
	//�ʒu����ݒ�
	m_Pos = Pos;

	//������ɂ�����
	m_Pos.y += 20;

	//���_���̐ݒ�
	SetVertex();

	//������㏸�l��������
	m_UpPos = 0;

	//�X�P�[���̏�����
	m_Scl= D3DXVECTOR3(POLYGON_SIZE_X,POLYGON_SIZE_Y,POLYGON_SIZE_Z);
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CLevelUp::~CLevelUp(void)
{
	if(m_pD3DVtxBuff != NULL)
	{
		// ���_�o�b�t�@�̊J��
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff = NULL;
	}
}
//---------------------------------------------------------------------------------------
//�`�揈��
//---------------------------------------------------------------------------------------
void CLevelUp::Draw()
{
	D3DXMATRIX mtxView, mtxScale, mtxTranslate,mtxRot,mtxOffset;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �r���[�}�g���b�N�X���擾
	mtxView = CCamera::GetMtxView();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity( &m_mtxWorld);
	
	// �|���S���𐳖ʂɌ�����
#if 0
	D3DXVECTOR3 TargetPos = D3DXVECTOR3(mtxView._41,mtxView._42,mtxView._43);
	
	D3DXMatrixIdentity( &mtxRot);
	D3DXMatrixIdentity( &mtxOffset);

	D3DXMatrixLookAtLH(&mtxRot,&TargetPos,&m_Pos,&D3DXVECTOR3(0,1,0));

	// �t�s������߂�
	//D3DXMatrixInverse(&m_mtxWorld,NULL,&mtxView);
	D3DXMatrixInverse(&mtxRot,NULL,&mtxRot);
	mtxRot._41 = 0.0f;
	mtxRot._42 = 0.0f;
	mtxRot._43 = 0.0f;
    D3DXMatrixTranslation( &mtxOffset, m_Pos.x, m_Pos.y, m_Pos.z);                        // �I�t�Z�b�g�s�������Ă����āA

    D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxRot );                             // �܂��^�[�Q�b�g�����Ɏ���]������
    //D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxOffset );         
#else
	// �]�u�s������߂�	
	m_mtxWorld._11 = mtxView._11;	
	m_mtxWorld._12 = mtxView._21;	
	m_mtxWorld._13 = mtxView._31;

	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;

	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

#endif
		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScale, m_Scl.x,m_Scl.y,m_Scl.z);
		D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld, &mtxScale);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);
		D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetStreamSource(0, m_pD3DVtxBuff, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̃Z�b�g
		pDevice ->SetTexture(0,*CTextureManager::GetTexture(m_nTextureID));

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, NUM_POLYGON);

		// ���C�e�B���O��L���ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//---------------------------------------------------------------------------------------
//�X�V����
//---------------------------------------------------------------------------------------
void CLevelUp::Update(D3DXVECTOR3 Pos)
{	
	//������㏸�l�����Z
	m_UpPos += 3;

	if(m_UpPos > 255)
	{
		m_UpPos = 255;
	}
	
	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �㏸���Ă����قǔ������ɂ���
	pVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,255 - m_UpPos);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,255 - m_UpPos);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,255 - m_UpPos);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,255 - m_UpPos);

	// ���_�f�[�^���A�����b�N����
	m_pD3DVtxBuff->Unlock();
	//�r���{�[�h�̈ړ�
	m_Pos.x = Pos.x;
	m_Pos.y = (Pos.y + m_UpPos / 51.0f);
	m_Pos.z = Pos.z;

	//���_���̐ݒ�
	SetVertex();
}

//---------------------------------------------------------------------------------------
//���_���̐ݒ�
//---------------------------------------------------------------------------------------
void CLevelUp::SetVertex()
{
	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].vtx = D3DXVECTOR3(-POLYGON_SIZE_X / 2.0f,-POLYGON_SIZE_Y/2.0f,0.0f);
	pVtx[1].vtx = D3DXVECTOR3( POLYGON_SIZE_X / 2.0f,-POLYGON_SIZE_Y/2.0f,0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-POLYGON_SIZE_X / 2.0f, POLYGON_SIZE_Y/2.0f,0.0f);
	pVtx[3].vtx = D3DXVECTOR3( POLYGON_SIZE_X / 2.0f, POLYGON_SIZE_Y/2.0f,0.0f);

	// ���_�f�[�^���A�����b�N����
	m_pD3DVtxBuff->Unlock();
}
//---------------------------------------------------------------------------------------
// ���_���̍쐬
//---------------------------------------------------------------------------------------
HRESULT CLevelUp::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&m_pD3DVtxBuff,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))						// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{
		//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-POLYGON_SIZE_X / 2.0f,-POLYGON_SIZE_Y / 2.0f,0.0f);
		pVtx[1].vtx = D3DXVECTOR3( POLYGON_SIZE_X / 2.0f,-POLYGON_SIZE_Y / 2.0f,0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-POLYGON_SIZE_X / 2.0f, POLYGON_SIZE_Y / 2.0f,0.0f);
		pVtx[3].vtx = D3DXVECTOR3( POLYGON_SIZE_X / 2.0f, POLYGON_SIZE_Y / 2.0f,0.0f);

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		
		// ���_�f�[�^���A�����b�N����
		m_pD3DVtxBuff->Unlock();
	}

	return S_OK;
}