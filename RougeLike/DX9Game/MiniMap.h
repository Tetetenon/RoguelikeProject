#pragma once
#include "C2DTexture.h"
#include "MapData.h"

//ミニマップの１ポリゴンのサイズ
#define POLYGON_SIZE		(200 / MAP_SIZE)
#define POLYGON_HALF_SIZE	(POLYGON_SIZE / 2)

class CMiniMap
{
private:
	static C2DTexture	m_MapPolygon[MAP_SIZE][MAP_SIZE];	//マップデータを格納する
	static bool			m_DrawFlg[MAP_SIZE][MAP_SIZE];		//マップデータの描画フラグを立てる
public:
	CMiniMap(void);								//コンストラクタ
	~CMiniMap(void);							//デストラクタ

	void Init();								//初期化
	void Fin();									//終了処理

	void Draw ();								//描画
	void Update();								//更新

	static void DrawFlgUp(int nX,int nZ);				//到達した部分の描画フラグを立てる
	static bool GetDrawFlg(int nX,int nZ);				//指定された位置の描画フラグを返す

	static void SetIcon(int nX,int nZ,int nNumber);		//指定された位置に指定されたアイコンを設置する
	static void Delete(int nX,int nZ);					//指定された位置の情報を地形情報に戻す

	static void MiniMapBack(int nX,int nZ);				//指定した位置のマップ状態をもとに戻す
};

