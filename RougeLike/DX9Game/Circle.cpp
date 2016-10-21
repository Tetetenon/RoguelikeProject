#include "Circle.h"
#include "Graphics.h"
#include "define.h"
#include "TextureManager.h"
#include <tchar.h>

#define MAP_SIZE 1

//---------------------------------------------------------------------------------------
//�@�R���X�g���N�^
//---------------------------------------------------------------------------------------
CCircle::CCircle(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//���_���ݒ�(�k�ރ|���S���l��)
	m_NumVertex = (MAP_SIZE + 1) * MAP_SIZE * 2 + (MAP_SIZE - 1) * 2;

	//�C���f�b�N�X���̐ݒ�(�k�ރ|���S�����l��)
	m_NumVertexIndex = (MAP_SIZE + 1) * 2 * MAP_SIZE + (MAP_SIZE - 1) * 2;

	//�|���S����(�k�ރ|���S���l��)
	m_NumPolygon = MAP_SIZE * MAP_SIZE * 2 + (MAP_SIZE - 1) * 4;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if( FAILED( pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_NumVertex,
		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,	// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_3D,	// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pD3DVtxBuff,
		// ���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
		NULL )))
	{
		LPCTSTR szMsg = _T("����s��!");
		MessageBox(NULL, szMsg, NULL, MB_OK);
	}

	if( FAILED( pDevice->CreateIndexBuffer( sizeof( WORD ) * m_NumVertexIndex,
	// �C���f�b�N�X�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y�i�o�C�g�j
		D3DUSAGE_WRITEONLY,		// �g�p�@
		D3DFMT_INDEX16,			// �t�H�[�}�b�g
		D3DPOOL_MANAGED,		// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pD3DIdxBuff,	//
		NULL )))
	{
		LPCTSTR szMsg = _T("���s!");
		MessageBox(NULL, szMsg, NULL, MB_OK);
	}

	// 1���̎l�p�`�|���S���ɒ���t����e�N�X�`���̃T�C�Y
	const float fSizeTexX = 1.0f;
	const float fSizeTexZ = 1.0f;

	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N��
	// ���_�o�b�t�@�ւ̃|�C���^���擾
	m_pD3DVtxBuff->Lock( 0, 0,(void**)&pVtx, 0 );

	//���_���̐ݒ�
	for( int nCntZ = 0; nCntZ < MAP_SIZE + 1; nCntZ ++ )
	{
		for( int nCntX = 0; nCntX < MAP_SIZE + 1; nCntX ++ )
		{
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].vtx.x = -MAP_SIZE / 2.0f * MASS_SIZE + nCntX * MASS_SIZE;
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].vtx.y = 0.1f;
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].vtx.z = MAP_SIZE / 2.0f * MASS_SIZE - nCntZ * MASS_SIZE;
			// �@��
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
			// ���ˌ�
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// �e�N�X�`�����W
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].tex.x = (float)MASS_SIZE * nCntX / 3;
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].tex.y = (float)MASS_SIZE * nCntZ / 3;
		}
	}

	// ���_�f�[�^���A�����b�N����
	m_pD3DVtxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
	WORD *pIdx;
	
	// �C���f�b�N�X�f�[�^�͈̔͂����b�N�����_�o�b�t�@�ւ̃|�C���^���擾
	m_pD3DIdxBuff->Lock( 0, 0, (void**)&pIdx, 0 );
	
	int nCntIdx = 0;

	for( int nCntZ = 0; nCntZ < MAP_SIZE; nCntZ ++ )
	{
		if( nCntZ > 0 )
		{	
			// �k�ރ|���S���̂��߂̃_�u���ݒ�
			pIdx[nCntIdx] = ( nCntZ + 1 ) * ( MAP_SIZE + 1 );
			nCntIdx ++;
		}
		for( int nCntX = 0; nCntX < MAP_SIZE + 1; nCntX ++ )
		{
			pIdx[nCntIdx] = ( nCntZ + 1 ) * ( MAP_SIZE + 1 ) + nCntX;
			nCntIdx ++;
			pIdx[nCntIdx] = nCntZ * ( MAP_SIZE + 1 ) + nCntX;
			nCntIdx ++;
		}
	
		if( nCntZ < MAP_SIZE - 1 )
		{	
			// �k�ރ|���S���̂��߂̃_�u���ݒ�
			pIdx[nCntIdx] = nCntZ * ( MAP_SIZE + 1 ) + MAP_SIZE;
			nCntIdx ++;
		}
	}

	// ���_�f�[�^���A�����b�N����
	m_pD3DIdxBuff->Unlock();
}


//---------------------------------------------------------------------------------------
//�@�f�X�g���N�^
//---------------------------------------------------------------------------------------
CCircle::~CCircle(void)
{
	//���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_pD3DVtxBuff);
	//�C���f�b�N�X�o�b�t�@�̊J��
	SAFE_RELEASE(m_pD3DIdxBuff);
}


//---------------------------------------------------------------------------------------
// ������
//---------------------------------------------------------------------------------------
void CCircle::Init()
{
}
//---------------------------------------------------------------------------------------
// �X�V
//---------------------------------------------------------------------------------------
void CCircle::Update()
{
	
	VERTEX_3D *pVtx;

	// ���_�G�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pD3DVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);

	// ���_�f�[�^���A�����b�N����
	m_pD3DVtxBuff->Unlock();
}
//---------------------------------------------------------------------------------------
// �`��
//---------------------------------------------------------------------------------------
void CCircle:: Draw(int UnitNumber)
{
	///�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	
	//���C�e�B���O���ꎞ�I�ɐ؂�
	pDevice->SetRenderState(D3DRS_LIGHTING,false);
	// ���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity( &m_mtxWorld );
		
	// ���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform( D3DTS_WORLD, &m_mtxWorld );

	// ���̌�ɕ`��
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource( 0,
		m_pD3DVtxBuff, 0,
		sizeof(VERTEX_3D) );

	// �C���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetIndices( m_pD3DIdxBuff );

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF( FVF_VERTEX_3D );

	//�t�B�[���h�̈ʒu�}�X���Ƃɔz���Ԃ��m�F���A�o�͓��e��ύX����
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j<MAP_SIZE;j++)
		{

			//���j�b�g�̎��ʔԍ��ɂ��A�g�p����e�N�X�`����ݒ�

			//�v���C���[�̏ꍇ
			if(UnitNumber == OBJ_NUM_PLAYER)
				pDevice->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_CIRCLE_P));
			
			//�p�[�e�B�[�����o�[�̏ꍇ
			if(UnitNumber >= OBJ_NUM_PARTY)
				pDevice->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_CIRCLE_F));

			//�G�l�~�[�̏ꍇ
			if(UnitNumber >= OBJ_NUM_ENEMY)
				pDevice->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_CIRCLE_E));

			//�A�C�e���̏ꍇ
			if(UnitNumber == OBJ_NUM_ITEM)
				pDevice->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_CIRCLE_I));

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLESTRIP,
				i * (MAP_SIZE + 1) + j,	// ���_�o�b�t�@�̃x�[�X�ʒu
				0,	// ���_�o�b�t�@�̎g�p�J�n�ʒu
				3,
				0,	// �C���f�b�N�X�o�b�t�@�̊J�n�ʒu
				2);
		}
	}
	
	//���C�e�B���O��߂�
	pDevice->SetRenderState(D3DRS_LIGHTING,true);
}
//---------------------------------------------------------------------------------------
// �I������
//---------------------------------------------------------------------------------------
void CCircle:: Fin()
{
}

//---------------------------------------------------------------------------------------
//�@�ʒu���̐ݒ�
//---------------------------------------------------------------------------------------
void CCircle::SetPos(D3DXVECTOR3 Pos)
{
	
	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N��
	// ���_�o�b�t�@�ւ̃|�C���^���擾
	m_pD3DVtxBuff->Lock( 0, 0,(void**)&pVtx, 0 );

	//���_���̐ݒ�
	for( int nCntZ = 0; nCntZ < MAP_SIZE + 1; nCntZ ++ )
	{
		for( int nCntX = 0; nCntX < MAP_SIZE + 1; nCntX ++ )
		{
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].vtx.x = Pos.x + (-MAP_SIZE / 2.0f * MASS_SIZE + nCntX * MASS_SIZE);
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].vtx.y = 0.1f;
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].vtx.z = Pos.z + (MAP_SIZE / 2.0f * MASS_SIZE - nCntZ * MASS_SIZE);

			// �@��
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

			// ���ˌ�
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].tex.x = (float)MASS_SIZE * nCntX / 3;
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].tex.y = (float)MASS_SIZE * nCntZ / 3;
		}
	}

	// ���_�f�[�^���A�����b�N����
	m_pD3DVtxBuff->Unlock();
}