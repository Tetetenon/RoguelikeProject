#pragma once
#include "MapData.h"
#include "C2DTexture.h"

class CEditTexture;
class CMapData;

class CMiniMap : public C2DTexture
{
public:
	enum
	{
		GRID_SIZE = 3,
		LINE_SPACE = 1,
		GRID_NUM = MAP_SIZE,
		POLYGON_WIDTH = GRID_SIZE * GRID_NUM + (GRID_NUM - 1) * LINE_SPACE,
		POLYGON_HEIGHT = GRID_SIZE * GRID_NUM + (GRID_NUM - 1) * LINE_SPACE,
		POLYGON_ORIGIN_X = 600,
		POLYGON_ORIGIN_Y = 10,
		MINIMAP_ALPHA = 180,
	};
	enum
	{
		NORMAL_MAP_MODE = 0,
		BIG_MAP_MODE,
		DELETE_MAP_MODE,
		MAX_MAP_MODE
	};

private:
	static CMiniMap* m_pMinimap;
	CEditTexture*		m_pEditTexture;						//ミニマップテクスチャ生成
	CMapData*			m_pMapData;

	int m_nMapMode;								//マップのポリゴンサイズ
	int	m_nInterval;

	CMiniMap(void);								//コンストラクタ
	~CMiniMap(void);							//デストラクタ
public:
	static void Create();						//実体の作成
	static void Delete();						//実体の削除
	static CMiniMap* GetPointer();				//実体のポインタを渡す

	void Update();								// 更新
	void Draw () override;						//描画

	//メンバ変数のポインタを渡す
	void SetPointer();

	//ポリゴンのサイズを変更する
	void SizeChange();
};