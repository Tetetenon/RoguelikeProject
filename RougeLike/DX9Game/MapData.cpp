#include "MapData.h"
#include "Graphics.h"
#include "TextureManager.h"
#include "GameScene.h"

#include <stdlib.h>
#include <tchar.h>

#include<fstream>
#include<iostream>
#include<string>
#include<sstream> //�����X�g���[��


//�ÓI�����o���̒�`
Map						CMapData::m_TerrainMap[MAP_SIZE][MAP_SIZE];				//�n�`�}�b�v���
Map						CMapData::m_UnitMap[MAP_SIZE][MAP_SIZE];				//���j�b�g�}�b�v
Map						CMapData::m_ItemMap[MAP_SIZE][MAP_SIZE];				//�A�C�e���}�b�v

LPDIRECT3DVERTEXBUFFER9 CMapData::m_pD3DVtxBuff;								//���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	CMapData::m_pD3DIdxBuff;								//�C���f�b�N�X�o�b�t�@
D3DXMATRIX				CMapData::m_mtxWorld;									//���[���h�}�g���b�N�X

int						CMapData::m_NumVertexIndex;								//�C���f�b�N�X��
int						CMapData::m_NumVertex;									//�����_��
int						CMapData::m_NumPolygon;									//�|���S����
RECT					CMapData::m_Section[ROOM_MAX_NUM];						//���
RECT					CMapData::m_Room[ROOM_MAX_NUM];							//����

int						CMapData::m_CountMakeRoom;								//���ۂɐ������������̐�
int						CMapData::m_nHierarchyNum;								//�K�w��


LPD3DXFONT				CMapData::m_pFont;										//�`��t�H���g�̐ݒ�
RECT					CMapData::m_FontDrawPos;								//�t�H���g�̕`��ʒu��ݒ肷��
int						CMapData::m_nDividPattern;								//��������}�b�v�p�^�[��

AStar					CMapData::m_AStarData[MAP_SIZE][MAP_SIZE];				//A*�A���S���Y���Ɏg�p����\����
AStarList*				CMapData::m_pAstarList;									//A*�A���S���Y���Ŏ��̒T�����̃f�[�^��ۑ�����
//---------------------------------------------------------------------------------------
//�@�R���X�g���N�^
//---------------------------------------------------------------------------------------
CMapData::CMapData(void)
{
	int nFloorCounter = 0;

	//�}�b�v�𐶐�
	MapGeneration();

	//�}�b�v�̏����𐔂���
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
		{
			//�}�b�v��񂪏��Ȃ���Z
			if(CMapData::Get_TerrainMapSituation(i,j) == FLOOR)
				nFloorCounter ++;
		}
	}

	//���j�b�g�̍ő�ݒu�\����ݒ�
	CEnemyGenerator::SetMaxGenerator((int)nFloorCounter / 5);

	//�A�C�e���̍ő吶������ݒ�
	CItemGenerator::SetMaxItem(10 + rand()%10);

	//�A�C�e���}�b�v������
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
			m_ItemMap[i][j].m_Map_Situation = 0;
	}

	//���j�b�g�}�b�v������
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
			m_UnitMap[i][j].m_Map_Situation = 0;
	}

	//�f�o�C�X�i�[
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//-----���_�̍쐬-----

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
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].vtx.y = 0.0f;
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].vtx.z = MAP_SIZE / 2.0f * MASS_SIZE - nCntZ * MASS_SIZE;
			// �@��
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
			// ���ˌ�
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
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

	//�K�w����������
	m_nHierarchyNum = 1;
	
	//�t�H���g�ւ̃|�C���^���擾����
	D3DXCreateFont(pDevice,24,0,1,0,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,NULL,&m_pFont);
	//�t�H���g�`��ʒu��ݒ�
	SetFontPos();
}

//---------------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------------
CMapData::~CMapData(void)
{
	//A*�ŗp�����f�[�^�̏�����
	InitAStarData();
	//���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_pD3DVtxBuff);
	//�C���f�b�N�X�o�b�t�@�̊J��
	SAFE_RELEASE(m_pD3DIdxBuff);
}

//---------------------------------------------------------------------------------------
// ������
//---------------------------------------------------------------------------------------
void CMapData::Init()
{
}
//---------------------------------------------------------------------------------------
//�����`��ʒu��ݒ�
//---------------------------------------------------------------------------------------
void CMapData::SetFontPos()
{
	m_FontDrawPos.left		= (LONG)125.0f;
	m_FontDrawPos.top		= (LONG)100.0f;
	m_FontDrawPos.right		= (LONG)230.0f;
	m_FontDrawPos.bottom	= (LONG)120.0f;
}
//---------------------------------------------------------------------------------------
// �X�V
//---------------------------------------------------------------------------------------
void CMapData::UpDate()
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
void CMapData:: Draw()
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
			switch(m_TerrainMap[i][j].m_Map_Situation)
			{
				//��
				case FLOOR:
					pDevice->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_FLOOR));
				break;
				//��
				case WALL_UP:
				case WALL_DOWN:
				case WALL_RIGH:
				case WALL_LEFT:
					pDevice->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_WALL));
				break;
				//�ǒ�
				case IN_THE_WALL:
					pDevice->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_IN_THE_WALL));
				break;
				//�f�t�H���g�͏�
				default:
					pDevice->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_IN_THE_WALL));
				break;
			}
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
void CMapData:: Fin()
{
}
//---------------------------------------------------------------------------------------
// �w�肵���n�`�̏�Ԃ�Ԃ�
//---------------------------------------------------------------------------------------
int CMapData::Get_TerrainMapSituation (int PosX,int PosY)
{
	//�͈͊O��ǂݍ��񂾏ꍇ�A�G���[�l��Ԃ�
	if(PosX < 0 || PosX > MAP_SIZE || PosY < 0 || PosY > MAP_SIZE)
		return ERROR_NUM;
	return m_TerrainMap[PosY][PosX].m_Map_Situation;
}
//---------------------------------------------------------------------------------------
// �w�肵���ʒu�̃��j�b�g������Ԃ�Ԃ�
//---------------------------------------------------------------------------------------
int CMapData::Get_UnitMapSituation(int PosX,int PosY)
{
	//�͈͊O��ǂݍ��񂾏ꍇ�A�G���[�l��Ԃ�
	if(PosX < 0 || PosX > MAP_SIZE || PosY < 0 || PosY > MAP_SIZE)
		return ERROR_NUM;
	return m_UnitMap[PosY][PosX].m_Map_Situation;
}
//---------------------------------------------------------------------------------------
// �w�肵���ʒu�̃A�C�e����Ԃ�Ԃ�
//---------------------------------------------------------------------------------------
int CMapData::Get_ItemMapSituation(int PosX,int PosY)
{
	//�͈͊O��ǂݍ��񂾏ꍇ�A�G���[�l��Ԃ�
	if(PosX < 0 || PosX > MAP_SIZE || PosY < 0 || PosY > MAP_SIZE)
		return ERROR_NUM;
	return m_ItemMap[PosY][PosX].m_Map_Situation;
}


//---------------------------------------------------------------------------------------
// �w�肵���ʒu�������Ƃɖ߂�
//---------------------------------------------------------------------------------------
void CMapData:: Back_UnitMap(int PosX,int PosY)
{
	m_UnitMap[PosY][PosX].m_Map_Situation = 0;
}
//---------------------------------------------------------------------------------------
// �w�肵���ʒu����ύX����
//---------------------------------------------------------------------------------------
void CMapData:: Set_UnitMap(int PosX,int PosY,int Change)
{
	m_UnitMap[PosY][PosX].m_Map_Situation = Change;
}
//---------------------------------------------------------------------------------------
// �w�肵���ʒu�������Ƃɖ߂�
//---------------------------------------------------------------------------------------
void CMapData:: Back_ItemMap(int PosX,int PosY)
{
	m_ItemMap[PosY][PosX].m_Map_Situation = 0;
}
//---------------------------------------------------------------------------------------
// �w�肵���ʒu����ύX����
//---------------------------------------------------------------------------------------
void CMapData:: Set_ItemMap(int PosX,int PosY,int Change)
{
	m_ItemMap[PosY][PosX].m_Map_Situation = Change;
}
//---------------------------------------------------------------------------------------
// �}�b�v�����ׂď���������
//---------------------------------------------------------------------------------------
void CMapData::AllInitMapData()
{
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
		{
			m_TerrainMap[j][i].m_Map_Situation = IN_THE_WALL;
			m_UnitMap[j][i].m_Map_Situation = 0;
			m_ItemMap[j][i].m_Map_Situation = 0;
		}
	}

	for(int i = 0;i < ROOM_MAX_NUM;i++)
	{
		m_Section[i].top    = 0;
		m_Section[i].bottom = 0;
		m_Section[i].right	= 0;
		m_Section[i].left	= 0;
		
		m_Room[i].top		= 0;
		m_Room[i].bottom	= 0;
		m_Room[i].right		= 0;
		m_Room[i].left		= 0;
	}
}

//---------------------------------------------------------------------------------------
// �}�b�v�𐶐�����
//---------------------------------------------------------------------------------------
void CMapData::MapGeneration()
{
	//�}�b�v�f�[�^�̏�����
	AllInitMapData();

	//�}�b�v�̋�敪��
	DivideMap();

	//�����ɕ��������
	MakeRoom();

	//�������畔���ւ̒ʘH���쐬����
	MakeRoot();

	//�K�i���ǂ����̕����̒��ɐݒ肷��
	StairsSet();

	//�K�w�����Z
	m_nHierarchyNum ++;

	
	//10�K�w�ړ�������A�V�[�����Q�[���N���A�ɑJ�ڂ�����
	if(m_nHierarchyNum > 10)
	{
		//�Q�[���̃N���A�󋵂��N���A�ɕύX����
		CGameScene::GameClearFlgChange(true);

		//�Q�[�����C�����I��
		CGameScene::FadeOutStart();

		//�G�l�~�[�̐������̃��Z�b�g
		CEnemyGenerator::ResetMakeEnemyNum();
		//�t�B�[���h�A�C�e���������̃��Z�b�g
		CItemGenerator::ResetMakeItemNum();
	}

}
//---------------------------------------------------------------------------------------
// �}�b�v�̋�敪��
//---------------------------------------------------------------------------------------
void CMapData::DivideMap()
{
	//�c�������
	int RemainingZone_X = MAP_SIZE;
	int RemainingZone_Z = MAP_SIZE;


	//���E�������肷��Ƃ��Ɏg�p
	int BorderLineX = 0;
	int BorderLineZ = 0;

	//�l��擖����̃T�C�Y
	int OneRoomX = 0;
	int OneRoomZ = 0;

	//�R�p�^�[���̒�����A�����_���ɑI�����A���𕪂���
	m_nDividPattern = rand()%4;
	//m_nDividPattern = 3;

	switch(m_nDividPattern)
	{
		//���悸������
	case 0:
		//-----���E��������& �������-----
		for(m_CountMakeRoom = 0;m_CountMakeRoom < ROOM_MAX_NUM;m_CountMakeRoom ++)
		{
			//�܂��������邾���̗̈悪���邩�m�F
			if(RemainingZone_X < SECTION_MAX_SIZE || RemainingZone_Z < SECTION_MAX_SIZE)
				break;

			//��̋��̉�����ݒ肷��
			BorderLineX = rand()%SECTION_MAX_SIZE;

			//�������Œ���̕������Ȃ���Ύ���܂ł���
			while(BorderLineX < SECTION_MIN_SIZE)
			{
				//�ŏ��̋��̉�����ݒ肷��
				BorderLineX = rand()%SECTION_MAX_SIZE;
			}

			//���T�C�Y������
			m_Section[m_CountMakeRoom].top	= 0;
			m_Section[m_CountMakeRoom].bottom = RemainingZone_Z;

			m_Section[m_CountMakeRoom].right	= RemainingZone_X;
			m_Section[m_CountMakeRoom].left	= RemainingZone_X - BorderLineX;

			//�c��̕������炷
			RemainingZone_X -= BorderLineX;
			
			//���̋������肵�ɍs��!
			m_CountMakeRoom ++;
			
			//�܂��������邾���̗̈悪���邩�m�F
			if(RemainingZone_X < SECTION_MAX_SIZE || RemainingZone_Z < SECTION_MAX_SIZE)
				break;

			//�����̋��̏c����ݒ�
			BorderLineZ = rand()%SECTION_MAX_SIZE;

			//�c�����Œ���̕������Ă��Ȃ���΁A����܂Ń��[�v
			while(BorderLineZ < SECTION_MIN_SIZE)
			{
				BorderLineZ = rand()%SECTION_MAX_SIZE;
			}

			//���T�C�Y������
			m_Section[m_CountMakeRoom].top	= RemainingZone_Z - BorderLineZ;
			m_Section[m_CountMakeRoom].bottom = RemainingZone_Z;

			m_Section[m_CountMakeRoom].right	= RemainingZone_X;
			m_Section[m_CountMakeRoom].left	= 0;

			//�c��̍��������炷
			RemainingZone_Z -= BorderLineZ;
		}
		break;

		//�S���ϓ��ɓ���
	case 1:
		{
			int RoomNumX = (RemainingZone_X / SECTION_MIN_SIZE);
			int RoomNumZ = (RemainingZone_Z / SECTION_MIN_SIZE);

			//�}�b�v��ɍ��鐔���v�Z
			OneRoomX = RemainingZone_X / RoomNumX;
			OneRoomZ = RemainingZone_Z / RoomNumZ;

			//���ʒu��ݒ�
			for(m_CountMakeRoom= 0;m_CountMakeRoom < RoomNumX * RoomNumZ;m_CountMakeRoom++)
			{
				m_Section[m_CountMakeRoom].left = (m_CountMakeRoom % RoomNumX) * OneRoomX;
				m_Section[m_CountMakeRoom].right = (m_CountMakeRoom % RoomNumX) * OneRoomX + OneRoomX;

				m_Section[m_CountMakeRoom].top = (m_CountMakeRoom / RoomNumZ) * OneRoomZ;
				m_Section[m_CountMakeRoom].bottom = (m_CountMakeRoom / RoomNumZ) * OneRoomX + OneRoomZ;
			}
		}
		break;

		//4����
	case 2:
		{
			int RoomNumX = (RemainingZone_X / SECTION_MAX_SIZE);
			int RoomNumZ = (RemainingZone_Z / SECTION_MAX_SIZE);

			//�}�b�v��ɍ��鐔���v�Z
			OneRoomX = RemainingZone_X / RoomNumX;
			OneRoomZ = RemainingZone_Z / RoomNumZ;

			//���ʒu��ݒ�
			for(m_CountMakeRoom= 0;m_CountMakeRoom < RoomNumX * RoomNumZ;m_CountMakeRoom++)
			{
				m_Section[m_CountMakeRoom].left = (m_CountMakeRoom % RoomNumX) * OneRoomX;
				m_Section[m_CountMakeRoom].right = (m_CountMakeRoom % RoomNumX) * OneRoomX + OneRoomX;

				m_Section[m_CountMakeRoom].top = (m_CountMakeRoom / RoomNumZ) * OneRoomZ;
				m_Section[m_CountMakeRoom].bottom = (m_CountMakeRoom / RoomNumZ) * OneRoomX + OneRoomZ;
			}
		}
		break;
	case 3:
		{
			m_Section[0].left		= 0;
			m_Section[0].right	= MAP_SIZE;

			m_Section[0].top		= 0;
			m_Section[0].bottom	= MAP_SIZE;
		}
		break;
	}
}
//---------------------------------------------------------------------------------------
// �����̍쐬
//---------------------------------------------------------------------------------------
void CMapData::MakeRoom()
{
	//��镔���̃T�C�Y
	int nRoomSize_X;
	int nRoomSize_Y;

	//���̃T�C�Y
	int nSectionSize_X;
	int nSectionSize_Y;

	//���������ꏊ�̒��S�ʒu
	int nMakeRoomPos_X;
	int nMakeRoomPos_Y;

	//����������̂��������ݒ菈�����s��
	for(int i = 0;i <= m_CountMakeRoom;i++)
	{
		//���̃T�C�Y���v�Z����
		nSectionSize_X = m_Section[i].right - m_Section[i].left;	//���̉���
		nSectionSize_Y = m_Section[i].bottom - m_Section[i].top;	//���̏c��

		//���̃T�C�Y�����ȉ��Ȃ�΁A���[�v���甲����
		if(nSectionSize_X < SECTION_MIN_SIZE || nSectionSize_Y < SECTION_MIN_SIZE )
			break;
		//---�����̃T�C�Y��ݒ�----

		//�����̕�
		nRoomSize_X = rand()%(nSectionSize_X - 3);

		//���T�C�Y�ȉ��ɂȂ�Ȃ��悤����
		while(nRoomSize_X < (nSectionSize_X / 2))
			nRoomSize_X = rand()%(nSectionSize_X - 3);

		//�����̉��s
		nRoomSize_Y = rand()%(nSectionSize_Y - 3);

		//���T�C�Y�ȉ��ɂȂ�Ȃ��l�ɒ���
		while(nRoomSize_Y < (nSectionSize_Y / 2))
			nRoomSize_Y = rand()%(nSectionSize_Y - 3);

		//-----�����̈ʒu��ݒ肷��-----
		//��
		nMakeRoomPos_X = rand()%(m_Section[i].right - nRoomSize_X / 2);

		//���l�ȉ��ɂȂ�Ȃ��l�ɒ���
		//while(nMakeRoomPos_X <= m_Section[i].left + 2)
		//	nMakeRoomPos_X = rand()%(m_Section[i].right - nRoomSize_X / 2 - 2);
		while(m_Section[i].left >= nMakeRoomPos_X - nRoomSize_X / 2 || m_Section[i].right <= nMakeRoomPos_X + nRoomSize_X / 2 || nMakeRoomPos_X <= m_Section[i].left)
			nMakeRoomPos_X = rand()%(m_Section[i].right - nRoomSize_X / 2 - 1);


		//�c
		nMakeRoomPos_Y = rand()%(m_Section[i].bottom - nRoomSize_Y / 2);

		//���l�ȉ��ɂȂ�Ȃ��l�ɒ���
		//while(nMakeRoomPos_Y <= m_Section[i].top + 2)
		//	nMakeRoomPos_Y = rand()%(m_Section[i].bottom - nRoomSize_Y / 2 - 2);
		
		while(m_Section[i].top >= nMakeRoomPos_Y - nRoomSize_Y / 2 || m_Section[i].bottom <= nMakeRoomPos_Y + nRoomSize_Y / 2 || nMakeRoomPos_Y <= m_Section[i].top)
			nMakeRoomPos_Y = rand()%(m_Section[i].bottom - nRoomSize_Y / 2);

		//�����̐ݒ�
		m_Room[i].top		= nMakeRoomPos_Y - (nRoomSize_Y / 2);
		m_Room[i].bottom	= nMakeRoomPos_Y + (nRoomSize_Y / 2);
		m_Room[i].left		= nMakeRoomPos_X - (nRoomSize_X / 2);
		m_Room[i].right		= nMakeRoomPos_X + (nRoomSize_X / 2);

		//���������ۂɃ}�b�v��ɍ쐬����
		for(int j = m_Room[i].top;j < m_Room[i].bottom;j++)
		{
			for(int k = m_Room[i].left;k < m_Room[i].right;k++)
			{
				m_TerrainMap[j][k].m_Map_Situation = FLOOR;
			}
		}
	}

}
//---------------------------------------------------------------------------------------
// �ʘH�̍쐬
//---------------------------------------------------------------------------------------
void CMapData::MakeRoot()
{
	
	bool bNeighbor_LeftAndRight;		//�������אڂ��Ă���(���E��)
	bool bNeighbor_UpAndDown;			//�������אڂ��Ă���(�㉺��)
	
	int nBorderLine;					//���E��
	
	//�אڂ��Ă������T��
	for(int i = 0;i <= m_CountMakeRoom;i++)
	{	
		if(m_Room[i].bottom - m_Room[i].top <= 0)
			break;

		if(m_Room[i].right - m_Room[i].left <= 0)
			break;
		for(int j = 0;j < m_CountMakeRoom;j++)
		{
			//�t���O������������
			bNeighbor_LeftAndRight = false;
			bNeighbor_UpAndDown = false;
			
			if(m_Room[j].bottom - m_Room[j].top <= 0)
				break;

			if(m_Room[j].right - m_Room[j].left <= 0)
				break;
	
			//���g�̉E�[�ƌ������Ă��镔���̍��[����������΁A�אڂ��Ă���
			if(m_Section[i].right == m_Section[j].left)
			{
				bNeighbor_LeftAndRight = true;
			}
	
			//���g�̏�[�ƌ������Ă��镔���̉��[����������΁A�אڂ��Ă���
			if(m_Section[i].top == m_Section[j].bottom)
			{
				bNeighbor_UpAndDown = true;
			}
	
			//�אڃt���O�������Ă���΁A�ʘH���쐬����
	
			//���E�ŗא�(i:�E�̕���	j:���̕���)
			if(bNeighbor_LeftAndRight)
			{
				//�E�̕����̒ʘH�̃X�^�[�g�ʒu
				int RightRootStertPoint;

				//���̕����̒ʘH�̃X�^�[�g�ʒu
				int LeftRootStertPoint;
	
				//���E���ʒu��ݒ�
				nBorderLine = m_Section[i].right;
	
				//�ʘH�̃X�^�[�g�ʒu���E�̕����̉E�[����ݒ�
				RightRootStertPoint = rand()%(m_Room[i].top - m_Room[i].bottom) + m_Room[i].top;
	
				//�ʘH�̃X�^�[�g�ʒu�����̕����̍�������ݒ�
				LeftRootStertPoint = rand()%(m_Room[j].top - m_Room[j].bottom) + m_Room[j].top;

				//�E�̕������狫�E���܂ŒʘH���쐬
				for(int k = m_Room[i].right;k <= nBorderLine;k++)
				{
					m_TerrainMap[RightRootStertPoint][k].m_Map_Situation = FLOOR;
				}
				
				//���̕������狫�E���܂ŒʘH���쐬
				for(int k = m_Room[j].left;k >= nBorderLine;k--)
				{
					m_TerrainMap[LeftRootStertPoint][k].m_Map_Situation = FLOOR;
				}
				
	
				//���E���𖄂߂ĒʘH�쐬
				for(int k = RightRootStertPoint;k != LeftRootStertPoint;)
				{
					m_TerrainMap[k][nBorderLine].m_Map_Situation = FLOOR;
				
					//���̒ʘH�ʒu����ƈʒu��������Ή����Ă���
					if(k > LeftRootStertPoint)
						k--;
				
					//���̒ʘH�ʒu����ƈʒu���Ⴏ��΂����Ă���
					if(k < LeftRootStertPoint)
						k++;	
				}
			}
		}
	}

}
//---------------------------------------------------------------------------------------
// �K�i�̍쐬
//---------------------------------------------------------------------------------------
void CMapData::StairsSet()
{
	int StairsPos_X;		//�K�i���ݗ\��n
	int StairsPos_Y;		//�K�i���ݗ\��n


	//�K�i�̈ʒu�������_���ɐݒ�
	StairsPos_X = rand()%MAP_SIZE;
	StairsPos_Y = rand()%MAP_SIZE;

	//���ɐݒ肵���ʒu�������̒��Ȃ�΁A�ݒu
	while(!CheckInTheRoom(StairsPos_X,StairsPos_Y))
	{
		//�����̒��łȂ���΍Đݒ���s��
		StairsPos_X = rand()%MAP_SIZE;
		StairsPos_Y = rand()%MAP_SIZE;
	}

	//�K�i��ݒu����!
	m_TerrainMap[StairsPos_Y][StairsPos_X].m_Map_Situation = STAIRS;
}

//---------------------------------------------------------------------------------------
// �w�肳�ꂽ�ʒu�������̒����m�F����
//---------------------------------------------------------------------------------------
bool CMapData::CheckInTheRoom(int PosX,int PosY)
{
	bool InFlg = false;	//�����̒��ɋ���

	//�����̃f�[�^���m�F���A���ɋ��邩�m�F����
	for(int i = 0;i <= m_CountMakeRoom;i ++)
	{
		//�����̍�������m�F����
		if(m_Room[i].top < (PosY) && m_Room[i].bottom > (PosY))
		{
			//�����̉����m�F
			if(m_Room[i].right > (PosX) && m_Room[i].left < (PosX))
			{
				//�����̏����𖞂����Ε����ɂ��邱�ƂɂȂ�B
				InFlg = true;
				break;
			}
		}
	}

	return InFlg;
}

//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�ʒu�ɊK�i�����邩���f����
//---------------------------------------------------------------------------------------
bool CMapData::CheckStairs(int PosX,int PosY)
{
	//�w��ʒu�ɊK�i������ΐ�
	if(m_TerrainMap[PosY][PosX].m_Map_Situation == STAIRS)
	{
		return true;
	}

	//������Ε�
	return false;
}
//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�ʒu���A�ǂ̕������A���ʂ��A�����ԍ���Ԃ�(�����ɂ��Ȃ���΁A�ő啔���ԍ���n��)
//---------------------------------------------------------------------------------------
int CMapData::GetRoomNumber(int nPosX,int nPosZ)
{
	//�S�Ă̕������`�F�b�N
	for(int i = 0;i <= m_CountMakeRoom;i++)
	{
		//�����̉������ɑ��݂��邩�m�F
		if(nPosX >= m_Room[i].left && nPosX <= m_Room[i].right)
		{
			//�����̏c�����ɑ��݂��邩�m�F
			if(nPosZ >= m_Room[i].top && nPosZ <= m_Room[i].bottom)
			{
				return i;
			}
		}
	}

	return ROOM_MAX_NUM;
}
//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�����ԍ��̊Ԏ���Ԃ�(�����ԍ����쐬�������������傫����΁A0,0,0,0�̒l��Ԃ�)
//---------------------------------------------------------------------------------------
RECT CMapData::GetRoomFloorPlan(int nRoomNumber)
{
	//�w�肳�ꂽ�������A����������̐����Ȃ����m�F����
	if(m_CountMakeRoom >= nRoomNumber)
	{
		return m_Room[nRoomNumber];
	}

	//�͈͊O�̐��l���n���ꂽ
	RECT ReturnNum;
	ReturnNum.top		= 0.0f;
	ReturnNum.bottom	= 0.0f;
	ReturnNum.right		= 0.0f;
	ReturnNum.left		= 0.0f;

	return ReturnNum;
}
//---------------------------------------------------------------------------------------
//�K�w���̕`��
//---------------------------------------------------------------------------------------
void CMapData::DrawHierarchyNum()
{
	char Hierarchy[256];
	_stprintf(Hierarchy, _T("%d�K"), m_nHierarchyNum);
	//���l(����)�`��
	m_pFont ->DrawText(NULL,Hierarchy,-1,&m_FontDrawPos,DT_LEFT,D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
}



//---------------------------------------------------------------------------------------
//A*�A���S���Y���̏���ݒ肷��
//---------------------------------------------------------------------------------------
void CMapData::ASarSetData(int NowPosX,int NowPosZ,int EnemyPosX,int EnemyPosZ,int PlayerPosX,int PlayerPosZ)
{
	//���g�̈ʒu���\���̔z��̒��Ɋi�[����

	//�ʒu����ۑ�
	m_AStarData[NowPosZ][NowPosX].m_nPosX = NowPosX;
	m_AStarData[NowPosZ][NowPosX].m_nPosZ = NowPosZ;
	//�R�X�g����͂���
	m_AStarData[NowPosZ][NowPosX].m_nCost = AStarCalculator(NowPosX,NowPosZ,EnemyPosX,EnemyPosZ);
	//�q���[���X�e�b�N�l����͂���
	m_AStarData[NowPosZ][NowPosX].m_nHeuristic = AStarCalculator(NowPosX,NowPosZ,PlayerPosX,PlayerPosX);
	//�X�R�A����͂���(�R�X�g+�q���[���X�e�B�b�N�l)
	m_AStarData[NowPosZ][NowPosX].m_nScore = m_AStarData[NowPosZ][NowPosX].m_nCost + m_AStarData[NowPosZ][NowPosX].m_nHeuristic;
}

//---------------------------------------------------------------------------------------
//A*�A���S���Y���p�\���̂̏��������s��
//---------------------------------------------------------------------------------------
void CMapData::InitAStarData()
{
	//�f�[�^�̏��������s��
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int k = 0;k < MAP_SIZE;k++)
		{
			//�}�b�v�̃I�[�v���N���[�Y�t���O������
			m_AStarData[i][k].m_nMapStatus = 0;

			//�R�X�g�A�q���[���X�e�B�b�N�l�A�X�R�A������
			m_AStarData[i][k].m_nCost = 0;
			m_AStarData[i][k].m_nHeuristic = 0;
			m_AStarData[i][k].m_nScore = 0;

			//���g�̐e�̃|�C���^������������
			m_AStarData[i][k].m_ParentPos = D3DXVECTOR2(0,0);
		}
	}
	
	//���ꂩ��폜����f�[�^
	AStarList* DeleteAstarData = m_pAstarList;


	//���X�g�̍Ō�܂ňړ�����
	while(DeleteAstarData!= NULL)
	{
		//���ꂩ��폜����f�[�^�̎��̃f�[�^
		AStarList* NextDeleteData = DeleteAstarData->NextData;

		//�f�[�^�̍폜
		delete DeleteAstarData;
		DeleteAstarData = NULL;

		//���̃f�[�^�̍폜�Ɉڂ�
		DeleteAstarData = NextDeleteData;
	}

	m_pAstarList = NULL;
}


//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�ʒu���͂̈ړ��\�ȏꏊ�����������X�g�ɒǉ�
//---------------------------------------------------------------------------------------
void CMapData::SearchPosition(int SearchPosX,int SearchPosZ,int EnemyPosX,int EnemyPosZ,int PlayerPosX,int PlayerPosZ)
{
	//�����̕␳�l
	D3DXVECTOR2 CorrectionPos[MOVEVEC] = 
	{
		//			 X, Z
		D3DXVECTOR2(-1,-1),	//����
		D3DXVECTOR2( 0,-1),	//��
		D3DXVECTOR2( 1,-1),	//�E��
		D3DXVECTOR2( 1, 0),	//�E
		D3DXVECTOR2( 1, 1),	//�E��
		D3DXVECTOR2(0 , 1),	//��
		D3DXVECTOR2(-1, 1),	//����
		D3DXVECTOR2(-1, 0)	//��
	};

	//���͂��m�F����
	for(int i = 0;i < MOVEVEC;i++)
	{
		//�q���̈ʒu��ۑ�
		int ChildPosX = (int)(SearchPosX + CorrectionPos[i].x);
		int ChildPosZ = (int)(SearchPosZ + CorrectionPos[i].y);

		int StatusFlg = m_AStarData[ChildPosZ][ChildPosX].m_nMapStatus;

		//�m�F�����ꏊ�̏�Ԃ��v�Z���s���Ă��Ȃ���ԂȂ�Ώ����𑱂���
		if(StatusFlg != 0)
			continue;

		//�m�F�����ʒu����(�ړ��\)���A�N�����Ȃ���Έړ��\���X�g�ɉ�����
		int MapSituNum = Get_TerrainMapSituation(ChildPosX,ChildPosZ);
		int UnitSituNum = Get_UnitMapSituation(ChildPosX,ChildPosZ);

		if(UnitSituNum > 1)
			continue;

		if(MapSituNum != FLOOR && MapSituNum != STAIRS)
			continue;

		//�q���̐e�̈ʒu�����g�ɐݒ肷��
		m_AStarData[ChildPosZ][ChildPosX].m_ParentPos.x = SearchPosX;
		m_AStarData[ChildPosZ][ChildPosX].m_ParentPos.y = SearchPosZ;

		//�X�R�A�̌v�Z���s��
		ASarSetData(ChildPosX,ChildPosZ,EnemyPosX,EnemyPosZ,PlayerPosX,PlayerPosZ);

		//�v�Z���s������ԂɑJ�ڂ���
		CMapData::CompleteCellCal(ChildPosX,ChildPosZ,1);

		//���X�g�ɒǉ�
		//���ꂩ��i�[����f�[�^
		AStarList* NextAStarData = new AStarList;
		//�ʒu���̊i�[
		NextAStarData->AstarData = m_AStarData[ChildPosZ][ChildPosX];
		//���̃f�[�^
		NextAStarData->NextData = NULL;
		//���߂ă��X�g�ɓo�^����
		if(m_pAstarList == NULL)
		{
			m_pAstarList = NextAStarData;
		}
		else
		{
			//���ꂩ��i�[����f�[�^�̑O�̃f�[�^
			AStarList* BackAstarData = m_pAstarList;

			//���X�g�̍Ō�܂ňړ�����
			while(BackAstarData->NextData != NULL)
			{
				BackAstarData = BackAstarData ->NextData;
			}

			//�Ō�܂œ��B������A���̌��Ƀf�[�^��ǉ����A�ڍ�������
			BackAstarData ->NextData = NextAStarData;
		}

	}
}
//---------------------------------------------------------------------------------------
//A*�A���S���Y���ɂ�����A�������v�Z����
//---------------------------------------------------------------------------------------
int CMapData::AStarCalculator(int NowPosX,int NowPosZ,int GoalPosX,int GoalPosZ)
{
	//���݂̈ʒu�ƁA�ڕW�n�_�̈ʒu�̋������v�Z����
	int DistanceX = abs(NowPosX - GoalPosX);
	int DistanceZ = abs(NowPosZ - GoalPosZ);

	//�l���b��I�Ɍv�Z����
	int HeuristicScoreNum = DistanceX + DistanceZ;

	//�΂߈ړ����\�Ȃ��߁A�c�A���̐��l�̒Ⴂ���A�X�R�A�l���猸�Z����
	//�������l
	int SubNum = DistanceX;

	if(DistanceX > DistanceZ)
		SubNum = DistanceZ;

	HeuristicScoreNum -= SubNum;

	//�v�Z�������������l���q���[���X�e�B�b�N�l�Ƃ��ĕԂ�
	return HeuristicScoreNum;
}
//---------------------------------------------------------------------------------------
//���X�g���́A�ł��X�R�A�̏������ʒu���������A�n��
//---------------------------------------------------------------------------------------
void CMapData::SearchMinScoreData(int *PosX,int *PosZ)
{
	//�����A���X�g�ɉ����o�^����Ă��Ȃ���Ώ����𒆒f
	if(m_pAstarList == NULL)
	{
		//���l�����āA�������s��Ԃ�
		*PosX = -99;
		*PosZ = -99;

		return;
	}

	//���ݒT�����̃f�[�^
	AStarList * NowListData = m_pAstarList;

	//�ŏ��X�R�A�̃f�[�^
	AStarList* MinScoreData = m_pAstarList;

	//�S�Ẵf�[�^�̒T�����I������܂ő�����
	while(NowListData)
	{

		//�������݂̍ŏ��X�R�A�����T�����̃f�[�^�̃X�R�A�̂ق�����������΁A����ւ���
		if(MinScoreData->AstarData.m_nScore > NowListData->AstarData.m_nScore)
		{
			MinScoreData = NowListData;
		}

		//���̃f�[�^�̒T���Ɉڂ�
		NowListData = NowListData->NextData;
	}

	//�S�Ẵf�[�^�̒T�����s����

	//�ʒu���̒l��n����悤�Ɋi�[���Ă���
	*PosX = MinScoreData->AstarData.m_nPosX;
	*PosZ = MinScoreData->AstarData.m_nPosZ;

	//���X�g�ォ��ŏ��l�̃f�[�^���폜����

	//�폜����f�[�^���őO�̏ꍇ�A�擪�|�C���^���ړ�������
	if(MinScoreData == m_pAstarList)
	{
		m_pAstarList = m_pAstarList ->NextData;
	}

	//�폜����f�[�^�̑O�Ƀf�[�^�����݂��Ă���ꍇ�A�Ȃ��Ȃ���
	else
	{
		//�폜����f�[�^�̑O�̃f�[�^
		AStarList* BackAstarData = m_pAstarList;

		//���̃|�C���^���폜����f�[�^�ɂȂ�܂ňړ�����
		while(BackAstarData->NextData != MinScoreData)
		{
			BackAstarData = BackAstarData ->NextData;
		}

		//�|�C���^�̐��ύX
		BackAstarData ->NextData = MinScoreData->NextData;
	}

	//��Ԃ�J�ڂ�����
	CompleteCellCal(MinScoreData ->AstarData.m_nPosX,MinScoreData ->AstarData.m_nPosZ,2);

	//�f�[�^�̍폜
	delete MinScoreData;
	MinScoreData = NULL;
}
//---------------------------------------------------------------------------------------
//�w�肵���Z���̏�Ԃ��N���[�Y��(�T������)�ɂ���
//---------------------------------------------------------------------------------------
void CMapData::CompleteCellCal(int PosX,int PosZ,int State)
{
	m_AStarData[PosZ][PosX].m_nMapStatus = State;
}
//---------------------------------------------------------------------------------------
//�w�肵���Z���̐e�̈ʒu��Ԃ�
//---------------------------------------------------------------------------------------
void CMapData::GetParentPos(int ChildPosX,int ChildPosZ,int *ParentPosX,int *ParentPosZ)
{
	*ParentPosX = (int)m_AStarData[ChildPosZ][ChildPosX].m_ParentPos.x;
	*ParentPosZ = (int)m_AStarData[ChildPosZ][ChildPosX].m_ParentPos.y;
}