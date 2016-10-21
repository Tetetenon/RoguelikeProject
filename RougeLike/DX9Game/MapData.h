#pragma once

#include "EnemyGenerator.h"
#include "ItemGenerator.h"

#include "Structure.h"

//区画のサイズ
#define SECTION_MIN_SIZE 8
#define SECTION_MAX_SIZE 10

//マップサイズ
#define MAP_SIZE 30

//生成できる部屋の最大数
#define ROOM_MAX_NUM	(MAP_SIZE / SECTION_MIN_SIZE) * (MAP_SIZE / SECTION_MIN_SIZE)


//マップ情報を格納する構造体
typedef struct
{
	int m_Map_Situation;		//マップ状況(壁、床、壁の中、プレイヤーがいる、エネミーがいる…ect)
}Map;

//マップの状況
enum Situation
{
	IN_THE_WALL = -1,	//壁の中
	WALL_UP  = 1,	//壁(上向き)
	WALL_DOWN,		//壁(下向き)
	WALL_RIGH,		//壁(右向き)
	WALL_LEFT,		//壁(左向き)
	FLOOR,			//床
	STAIRS,			//階段
	etc
};

//マップ情報の管理
class CMapData
{
private:

	//-----マップデータ-----
	static Map						m_TerrainMap[MAP_SIZE][MAP_SIZE];			//マップ情報
	static Map						m_ItemMap[MAP_SIZE][MAP_SIZE];				//マップ上のアイテム情報格納
	static Map						m_UnitMap[MAP_SIZE][MAP_SIZE];				//マップ上のユニット情報格納


	static LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;								//頂点バッファインタフェースへのポインタ
	static LPDIRECT3DINDEXBUFFER9	m_pD3DIdxBuff;								//インデックスバッファ
	static D3DXMATRIX				m_mtxWorld;									//ワールドマトリックス

	static int						m_NumVertexIndex;							//インデックス数
	static int						m_NumVertex;								//総頂点数
	static int						m_NumPolygon;								//ポリゴン数

	static RECT						m_Section[ROOM_MAX_NUM];					//区画
	static RECT						m_Room[ROOM_MAX_NUM];						//部屋の大きさ(間取り?)

	static int						m_CountMakeRoom;							//実際に生成した部屋の数

	static int						m_nHierarchyNum;							//階層数を保持する

	static LPD3DXFONT				m_pFont;									//描画フォントの設定
	static RECT						m_FontDrawPos;								//フォントの描画位置を設定する
	static int						m_nDividPattern;							//生成するマップパターン
public:
	CMapData(void);										//コンストラクタ
	~CMapData(void);									//デストラクタ

	void Init();										//初期化
	void UpDate();										//更新
	void Draw();										//描画
	void Fin();											//終了処理
	
	void SetFontPos();									//文字描画位置を設定


	//-----地形マップ状態取得-----
	static int Get_TerrainMapSituation (int,int);				//地形配列の位置を指定し状態を返す

	//-----ユニットマップ状態取得-----
	static int Get_UnitMapSituation (int,int);					//ユニット配列の位置を指定し、状態を返す

	//-----アイテムマップ状態取得-----
	static int Get_ItemMapSituation (int,int);					//アイテム配列の位置を取得し、状態を返す

	//-----ユニットマップ操作-----
	static void Back_UnitMap	(int,int);				//指定した位置情報を元に戻す。
	static void Set_UnitMap		(int,int,int);			//指定した位置情報を指定した値に変更する。

	//-----アイテムマップ操作-----
	static void Back_ItemMap	(int,int);				//指定した位置情報を元に戻す。
	static void Set_ItemMap		(int,int,int);				//指定した位置情報を指定した値に変更する。

	//-----マップをすべて初期化する-----
	static void AllInitMapData();

	//-----マップを生成する-----
	static void MapGeneration();

	//マップを区画で分離する
	static void DivideMap();

	//部屋を作成する
	static void MakeRoom();

	//通路を作成する
	static void MakeRoot();

	//階段の位置を決定する
	static void StairsSet();

	//指定された位置が、部屋の中か判定する
	static bool CheckInTheRoom(int,int);

	//指定された位置に階段があるか判断する
	static bool CheckStairs(int,int);

	//指定された位置が、どの部屋か、判別し、部屋番号を返す(部屋にいなければ、最大部屋番号を渡す)
	static int GetRoomNumber(int,int);

	//指定された部屋番号の間取りを取得する
	static RECT GetRoomFloorPlan(int);

	//現在の階層数を描画する
	static void DrawHierarchyNum();
};

