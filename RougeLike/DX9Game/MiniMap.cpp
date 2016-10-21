#include "MiniMap.h"
#include "TextureManager.h"


C2DTexture	CMiniMap::m_MapPolygon[MAP_SIZE][MAP_SIZE];	//マップデータを格納する
bool		CMiniMap::m_DrawFlg[MAP_SIZE][MAP_SIZE];		//マップデータの描画フラグを立てる
//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CMiniMap::CMiniMap(void)
{
	//全ての描画フラグを初期化する
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
		{
			m_DrawFlg[i][j] = false;
		}
	}

	//全てのマップデータを設定
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
		{
			//位置情報の設定
			m_MapPolygon[i][j].SetPos(SCREEN_WIDTH - 215.0f + i * POLYGON_SIZE + POLYGON_HALF_SIZE, 50 + j * POLYGON_SIZE + POLYGON_HALF_SIZE,POLYGON_SIZE,POLYGON_SIZE);

			//アルファ値を設定する
			m_MapPolygon[i][j].SetAlpha(255 * 0.8);
		}
	}
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CMiniMap::~CMiniMap(void)
{
}


//---------------------------------------------------------------------------------------
//初期化
//---------------------------------------------------------------------------------------
void CMiniMap::Init(void)
{
	//全ての描画フラグを初期化する
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
		{
			m_DrawFlg[i][j] = false;
			m_DrawFlg[i][j] = true;
		}
	}

	//全てのマップデータを設定
	for(int i = 0;i < MAP_SIZE;i++)
	{
		//地形確認
		for(int j = 0;j < MAP_SIZE;j++)
		{
			int k = 0;
			switch(CMapData::Get_TerrainMapSituation(i,j))
			{
			case STAIRS:
				k = TEXTURE_PURPLE_TEXTURE;
				break;
			case FLOOR:
				k = TEXTURE_FLOOR;
				break;
			default:
				k = TEXTURE_WALL;
				break;
			}
			//使用テクスチャの設定
			m_MapPolygon[i][j].SetTextureID(k);
		}
	}
}
//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void CMiniMap::Fin(void)
{
}

//---------------------------------------------------------------------------------------
//ミニマップ上の指定された位置にアイコンを設置する
//---------------------------------------------------------------------------------------
void CMiniMap::SetIcon(int nX,int nY,int nNumber)
{
	m_MapPolygon[nX][nY].SetTextureID(nNumber);
}

//---------------------------------------------------------------------------------------
//ミニマップ上の指定された位置を地形情報にする
//---------------------------------------------------------------------------------------
void CMiniMap::Delete(int nX,int nY)
{

	int nTextureNumber = 0;
	switch(CMapData::Get_TerrainMapSituation(nX,nY))
	{
	case STAIRS:
		nTextureNumber = TEXTURE_RED_TEXTURE;
		break;
	case FLOOR:
		nTextureNumber = TEXTURE_FLOOR;
		break;
	default:
		nTextureNumber = TEXTURE_WALL;
		break;
	}
	//使用テクスチャの設定
	m_MapPolygon[nX][nY].SetTextureID(nTextureNumber);
}



//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CMiniMap::Draw()
{
	//全てのポリゴンに対し処理を行う
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE; j++)
		{
			//描画フラグが立っていた場合、描画を行う
			if(m_DrawFlg[i][j])
				m_MapPolygon[i][j].Draw();
		}
	}
}
//---------------------------------------------------------------------------------------
//更新処理
//---------------------------------------------------------------------------------------
void CMiniMap::Update(void)
{
}
//---------------------------------------------------------------------------------------
//指定された位置の描画フラグを立てる
//---------------------------------------------------------------------------------------
void CMiniMap::DrawFlgUp (int nX,int nZ)
{
	m_DrawFlg[nX][nZ] = true;
}
//---------------------------------------------------------------------------------------
//指定された位置の描画フラグを返す
//---------------------------------------------------------------------------------------
bool CMiniMap::GetDrawFlg(int nX,int nZ)
{
	return m_DrawFlg[nX][nZ];
}