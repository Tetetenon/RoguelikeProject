#include "DamageNotation.h"
#include "Graphics.h"
#include "Camera.h"
#include "TextureManager.h"
#include "define.h"
#include <math.h>
#include "DamageBillBoardManager.h"

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CDamageNotation::CDamageNotation(int Damage,D3DXVECTOR3 Pos)
{
	//�g�p���Ȃ�����ݒ�
	for (int i = 0; i < DrawDigit; i++)
	{
		int Digit = pow((float)10,(DrawDigit - i) - 1);
		if (Damage - Digit < 0)
			m_NumPolygon[i].m_bDrawFlg = false;

	}
	//�e�N�X�`����ID��ݒ肷��
	for (int i = 0; i < DrawDigit; i++)
	{
		//�g�p���Ȃ��|���S���̓X���\
		if (!m_NumPolygon[i].m_bDrawFlg)
			continue;
		//�`�悷�鐔�l��ݒ�
		int Digit = pow((float)10, (DrawDigit - i) - 1);
		int nTextureNumber = (Damage / Digit) % 10;

		//�`�悷�鐔�l����A�e�N�X�`�����w��
		m_NumPolygon[i].m_nTextureNumber = TEXTURE_0 + nTextureNumber;
	}

	//���_���̍쐬
	MakeVertex();

	//���l��������
	m_nAlpha = 0.0f;

	//�ړ�������ݒ�
	m_MoveVector.x = MoveVecX;
	m_MoveVector.y = MoveVecY;
	m_MoveVector.z = MoveVecZ;

	//���ړ��ʂ�������
	m_AmountMovement = D3DXVECTOR3(0.0f,0.0f,0.0f);

	//�S�Ẵ|���S��������
	for (int i = 0; i < DrawDigit; i++)
	{
		//�ʒu����ݒ�
		m_NumPolygon[i].m_Pos = Pos;

		m_NumPolygon[i].m_Pos.x += (POLYGON_SIZE_X * (i - 1));

		//������ɂ�����
		m_NumPolygon[i].m_Pos.y += 2.0f;

		//������O��
		m_NumPolygon[i].m_Pos.z -= 1.0f;

		//�X�P�[���̏�����
		m_NumPolygon[i].m_Scl = D3DXVECTOR3(1,1,1);
	}

	//�}�l�[�W���[�̃|�C���^�̎擾
	m_pManager = CDamageBillBoardManager::GetPointer();

	//�������Ԃ̐ݒ�
	m_LifeTime = LifeTime;
	//�ŗLID�̎擾
	m_nID = m_pManager->GetNextNumber();
	//���̔ԍ���ݒ肷��
	m_pManager->SetNextNumber(m_nID + 1);

	//�}�l�[�W���[�Ɏ��g�̒ǉ�����
	m_pManager->Add(m_nID, this);
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CDamageNotation::~CDamageNotation()
{
	//�S�Ẵ|���S���f�[�^������
	for (int i = 0; i < DrawDigit; i++)
	{
		if (m_NumPolygon[i].m_pD3DVtxBuff != NULL)
		{
			//���_�o�b�t�@�̊J��
			m_NumPolygon[i].m_pD3DVtxBuff->Release();
			m_NumPolygon[i].m_pD3DVtxBuff = NULL;
		}
	}
}

//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CDamageNotation::Draw()
{
	D3DXMATRIX mtxView, mtxScale, mtxTranslate, mtxRot, mtxOffset;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �r���[�}�g���b�N�X���擾
	mtxView = CCamera::GetMtxView();

	//�S�Ẵ|���S�����`�揈�����s��
	for (int i = 0; i < DrawDigit; i++)
	{
		//�`��t���O�������Ă��Ȃ��ꍇ�A�������X�L�b�v
		if (!m_NumPolygon[i].m_bDrawFlg)
			continue;
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_NumPolygon[i].m_mtxWorld);

		// �]�u�s������߂�	
		m_NumPolygon[i].m_mtxWorld._11 = mtxView._11;
		m_NumPolygon[i].m_mtxWorld._12 = mtxView._21;
		m_NumPolygon[i].m_mtxWorld._13 = mtxView._31;

		m_NumPolygon[i].m_mtxWorld._21 = mtxView._12;
		m_NumPolygon[i].m_mtxWorld._22 = mtxView._22;
		m_NumPolygon[i].m_mtxWorld._23 = mtxView._32;

		m_NumPolygon[i].m_mtxWorld._31 = mtxView._13;
		m_NumPolygon[i].m_mtxWorld._32 = mtxView._23;
		m_NumPolygon[i].m_mtxWorld._33 = mtxView._33;

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScale, m_NumPolygon[i].m_Scl.x, m_NumPolygon[i].m_Scl.y, m_NumPolygon[i].m_Scl.z);
		D3DXMatrixMultiply(&m_NumPolygon[i].m_mtxWorld, &m_NumPolygon[i].m_mtxWorld, &mtxScale);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, m_NumPolygon[i].m_Pos.x, m_NumPolygon[i].m_Pos.y, m_NumPolygon[i].m_Pos.z);
		D3DXMatrixMultiply(&m_NumPolygon[i].m_mtxWorld, &m_NumPolygon[i].m_mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_NumPolygon[i].m_mtxWorld);

		// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetStreamSource(0, m_NumPolygon[i].m_pD3DVtxBuff, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̃Z�b�g
		pDevice->SetTexture(0, *CTextureManager::GetTexture(m_NumPolygon[i].m_nTextureNumber));

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CDamageNotation::Update()
{
	//�ړ�
	m_AmountMovement += m_MoveVector;

	//�������Ԃ����炷
	m_LifeTime--;

	//�����x��ύX����
	m_nAlpha = (m_LifeTime / LifeTime) * 255;

	//�S�Ẵ|���S�����X�V
	for (int i = 0; i < DrawDigit; i++)
	{

		//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_NumPolygon[i].m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �㏸���Ă����قǔ������ɂ���
		pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nAlpha);
		pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nAlpha);
		pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nAlpha);
		pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nAlpha);

		// ���_�f�[�^���A�����b�N����
		m_NumPolygon[i].m_pD3DVtxBuff->Unlock();
		//�r���{�[�h�̈ړ�
		m_NumPolygon[i].m_Pos += m_MoveVector;
	}
}
//---------------------------------------------------------------------------------------
// ���_���̍쐬
//---------------------------------------------------------------------------------------
HRESULT CDamageNotation::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//�S�Ẵ|���S��������
	for (int i = 0; i < DrawDigit; i++)
	{
		// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&m_NumPolygon[i].m_pD3DVtxBuff,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))						// NULL�ɐݒ�
		{
			return E_FAIL;
		}

		{
			//���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_3D *pVtx;

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			m_NumPolygon[i].m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3((-POLYGON_SIZE_X / 2.0f),-POLYGON_SIZE_Y / 2.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3((-POLYGON_SIZE_X / 2.0f), POLYGON_SIZE_Y / 2.0f, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(( POLYGON_SIZE_X / 2.0f),-POLYGON_SIZE_Y / 2.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(( POLYGON_SIZE_X / 2.0f), POLYGON_SIZE_Y / 2.0f, 0.0f);


			// �@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

			// ���_�f�[�^���A�����b�N����
			m_NumPolygon[i].m_pD3DVtxBuff->Unlock();
		}
	}

	return S_OK;
}