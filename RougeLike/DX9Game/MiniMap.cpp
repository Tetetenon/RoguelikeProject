#include <Windows.h>
#include "MiniMap.h"
#include "TextureManager.h"
#include "EditTexture.h"
#include "MapData.h"

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
	if (map_data.m_isVisible == FALSE) return GRID_TYPE::TYPE_WALL;
	if (map_data.m_unit == OBJ_NUM_PLAYER)
		return GRID_TYPE::TYPE_PLAYER;
	return GRID_TYPE::TYPE_ENEMY;
}

static GRID_TYPE GetTerrainType(const Map& map_data)
{
	switch (map_data.m_terrain)
	{
	case Situation::FLOOR:
		if (map_data.m_isVisible == FALSE) return GRID_TYPE::TYPE_WALL;
		return GRID_TYPE::TYPE_FLOOR;
	case Situation::STAIRS:
		return GRID_TYPE::TYPE_STAIRS;
	default:
		return GRID_TYPE::TYPE_WALL;
	}
}

static GRID_TYPE GetItemType(const Map& map_data)
{
	if (map_data.m_isVisible == FALSE) return GRID_TYPE::TYPE_WALL;
	return  GRID_TYPE::TYPE_ITEM;
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

static void WriteGrid(int x, int y, CEditTexture* pMiniMap)
{
	const DWORD col = GetGridColorByMapData(CMapData::Get_MapData(x,y));
	WriteGridForTexture(x,y,col, pMiniMap);
}


//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CMiniMap::CMiniMap(void)
	: m_pEditTexture(NULL)
{
	m_pEditTexture = new CEditTexture(POLYGON_WIDTH,POLYGON_HEIGHT,CGraphics::GetDevice());
	//
	m_pEditTexture->FillColor(D3DCOLOR_RGBA(0,0,0,0));	
	SetPosLeftUpOrigin(POLYGON_ORIGIN_X,POLYGON_ORIGIN_Y,POLYGON_WIDTH,POLYGON_HEIGHT);
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CMiniMap::~CMiniMap(void)
{
	delete m_pEditTexture;
}

//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CMiniMap::Update()
{
	// ミニマップのクリア
	m_pEditTexture->FillColor(GRID_COLOR[GRID_TYPE::TYPE_LINE]);
	// 各グリッドの更新
	for (int y = 0; y < MAP_SIZE; ++y)
		for (int x = 0; x < MAP_SIZE; ++x)
			WriteGrid(x,y,m_pEditTexture);
}

//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CMiniMap::Draw()
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//αブレンディングを行う
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// 透過処理を行う
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//頂点フォーマットの設定
	pDevice ->SetFVF(FVF_VERTEX_2D);

	//テクスチャのセット
	pDevice ->SetTexture(0,*m_pEditTexture);

	
	//ポリゴンの描画
	pDevice -> DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,          //プリミティブの種類List（三角形描く）Strip(つなげて作る)
		NUM_POLYGON,                 //ポリゴン数
		m_aVertex,            //配列の先頭アドレス
		sizeof(VERTEX_2D)            //データの大きさ
		);


}
