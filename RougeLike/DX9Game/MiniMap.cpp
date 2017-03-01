#include <Windows.h>
#include "MiniMap.h"
#include "TextureManager.h"
#include "EditTexture.h"
#include "MapData.h"
#include "Input.h"

//---------------------------------------------------------------------------------------
//�ÓI�����o�ϐ��錾
//---------------------------------------------------------------------------------------
CMiniMap* CMiniMap::m_pMinimap = NULL;

namespace
{
	enum GRID_TYPE
	{
		TYPE_PLAYER = 0,
		TYPE_ENEMY,
		TYPE_ITEM,
		TYPE_FLOOR,
		TYPE_STAIRS,
		TYPE_WALL,
		TYPE_LINE,
		TYPE_SENTINEL,
	};
}

static DWORD GRID_COLOR[TYPE_SENTINEL] = {
	D3DCOLOR_RGBA(  0,213,255,CMiniMap::MINIMAP_ALPHA),	// PLAYER
	D3DCOLOR_RGBA(255,  0,  0,CMiniMap::MINIMAP_ALPHA),	// ENEMY
	D3DCOLOR_RGBA(255,120,  0,CMiniMap::MINIMAP_ALPHA),	// ITEM
	D3DCOLOR_RGBA(255,255,255,CMiniMap::MINIMAP_ALPHA),	// FLOOR
	D3DCOLOR_RGBA(  0,255,  0,CMiniMap::MINIMAP_ALPHA),	// STAIRS
	D3DCOLOR_RGBA(  0,  0,  0,CMiniMap::MINIMAP_ALPHA),	// WALL
	D3DCOLOR_RGBA(  0,  0,  0,CMiniMap::MINIMAP_ALPHA),	// LINE

};

static void WriteGridForTexture(int x, int y, DWORD col, CEditTexture* pTex)
{
	const int _x = x * CMiniMap::GRID_SIZE + x * CMiniMap::LINE_SPACE;
	const int _y = y * CMiniMap::GRID_SIZE + y * CMiniMap::LINE_SPACE;
	pTex->FillColor(_x,_y,CMiniMap::GRID_SIZE,CMiniMap::GRID_SIZE,col);
}

static GRID_TYPE GetUnitType(const Map& map_data)
{
	if (map_data.m_isVisible == FALSE) return TYPE_WALL;
	if (map_data.m_unit == OBJ_NUM_PLAYER)
		return TYPE_PLAYER;
	return TYPE_ENEMY;
}

static GRID_TYPE GetTerrainType(const Map& map_data)
{
	switch (map_data.m_terrain)
	{
	case FLOOR:
	case ROOT:
	case ROOT_ENTRANCE:
		if (map_data.m_isVisible == FALSE) return TYPE_WALL;
		return TYPE_FLOOR;
	case STAIRS:
		return TYPE_STAIRS;
	default:
		return TYPE_WALL;
	}
}

static GRID_TYPE GetItemType(const Map& map_data)
{
	if (map_data.m_isVisible == FALSE) return TYPE_WALL;
	return  TYPE_ITEM;
}

static bool IsUnitExist(const Map& map_data)
{
	return map_data.m_unit >= 1 ? true : false;
}

static bool IsItemIExit(const Map& map_data)
{
	return map_data.m_item >= 1 ? true : false;
}

static GRID_TYPE GetGridTypeByMapData(const Map& map_data)
{
	if (IsUnitExist(map_data)) 
		return GetUnitType(map_data);
	else if (IsItemIExit(map_data)) 
		return GetItemType(map_data);
	return GetTerrainType(map_data);
}

static DWORD GetGridColorByMapData(const Map& map_data)
{
	return GRID_COLOR[GetGridTypeByMapData(map_data)];
}

static void WriteGrid(int x, int y, CEditTexture* pMiniMap,CMapData* pMapData)
{
	const DWORD col = GetGridColorByMapData(pMapData->Get_MapData(x,y));
	WriteGridForTexture(x,y,col, pMiniMap);
}


//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CMiniMap::CMiniMap(void)
	: m_pEditTexture(NULL)
{
	m_nMapMode = 0;
	m_nInterval = 0;

	SizeChange();

	m_pEditTexture = new CEditTexture(POLYGON_WIDTH,POLYGON_HEIGHT,CGraphics::GetDevice());
	//
	m_pEditTexture->FillColor(D3DCOLOR_RGBA(0,0,0,0));
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CMiniMap::~CMiniMap(void)
{
	delete m_pEditTexture;
}
//---------------------------------------------------------------------------------------
//���̂̍쐬
//---------------------------------------------------------------------------------------
void CMiniMap::Create()
{
	//���g���Ȃ���΍쐬
	if (!m_pMinimap)
	{
		m_pMinimap = new CMiniMap;
	}
}
//---------------------------------------------------------------------------------------
//���̂̍폜
//---------------------------------------------------------------------------------------
void CMiniMap::Delete()
{
	//���g������΍폜
	if (m_pMinimap)
	{
		delete m_pMinimap;
		m_pMinimap = NULL;
	}
}
//---------------------------------------------------------------------------------------
//���̂̃|�C���^��n��
//---------------------------------------------------------------------------------------
CMiniMap* CMiniMap::GetPointer()
{
	//�O�̂��ߍ쐬�֐����Ă�
	Create();
	return m_pMinimap;
}
//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CMiniMap::Update()
{
	m_nInterval++;

	// �~�j�}�b�v�̃N���A
	m_pEditTexture->FillColor(GRID_COLOR[TYPE_LINE]);
	// �e�O���b�h�̍X�V
	for (int y = 0; y < MAP_SIZE; ++y)
		for (int x = 0; x < MAP_SIZE; ++x)
			WriteGrid(x,y,m_pEditTexture,m_pMapData);


	//M�������ƃ}�b�v�T�C�Y��ύX
	if (m_nInterval < ButtonIntervalTime)
		return;
	if (CInput::GetKeyTrigger(DIK_M) || CInput::GetJoyTrigger(0, 11))
	{
		m_nMapMode++;
		m_nMapMode %= MAX_MAP_MODE;

		//�T�C�Y�̕ύX
		SizeChange();

		m_nInterval = 0;
	}
	if (CInput::GetKeyTrigger(DIK_N) || CInput::GetJoyTrigger(0, 10))
	{
		m_nMapMode++;
		m_nMapMode %= MAX_MAP_MODE;

		//�T�C�Y�̕ύX
		SizeChange();

		m_nInterval = 0;
	}
}

//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CMiniMap::Draw()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//���u�����f�B���O���s��
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// ���ߏ������s��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice ->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̃Z�b�g
	pDevice ->SetTexture(0,*m_pEditTexture);

	
	//�|���S���̕`��
	pDevice -> DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,          //�v���~�e�B�u�̎��List�i�O�p�`�`���jStrip(�Ȃ��č��)
		NUM_POLYGON,                 //�|���S����
		m_aVertex,					//�z��̐擪�A�h���X
		sizeof(VERTEX_2D)            //�f�[�^�̑傫��
		);


}

//---------------------------------------------------------------------------------------
//�|�C���^�̐ݒ�
//---------------------------------------------------------------------------------------
void CMiniMap::SetPointer()
{
	//�|�C���^�̎擾
	m_pMapData = CMapData::GetPointer();
}

//---------------------------------------------------------------------------------------
//�|���S���̃T�C�Y��ύX����
//---------------------------------------------------------------------------------------
void CMiniMap::SizeChange()
{
	//���݂̃��[�h�Ń|���S���T�C�Y��ύX����
	switch (m_nMapMode)
	{
		//�m�[�}���T�C�Y
	case 0:
		SetPosLeftUpOrigin(POLYGON_ORIGIN_X, POLYGON_ORIGIN_Y, POLYGON_WIDTH, POLYGON_HEIGHT);
		break;
		//�ő�T�C�Y
	case 1:
		SetPosLeftUpOrigin(0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
		break;
		//����
	case 2:
		SetPosLeftUpOrigin(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,0,0);
		break;

	}
}
