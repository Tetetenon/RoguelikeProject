#pragma once


#include "EnemyGenerator.h"
#include "ItemGenerator.h"
#include "define.h"

#include "Structure.h"

//区画のサイズ
#define SECTION_MIN_SIZE 8
#define SECTION_MAX_SIZE 10

//移動できる方向の数
#define MOVEVEC 8

//マップサイズ
#define MAP_SIZE 30

//生成できる部屋の最大数
#define ROOM_MAX_NUM	(MAP_SIZE / SECTION_MIN_SIZE) * (MAP_SIZE / SECTION_MIN_SIZE)

//家を建てられる空間のサイズ
#define MakeHomeSize (6)

//マップの状況
enum Situation
{
	//基本系
	WALL,				//カベ
	FLOOR,				//床
	ROOT,				//通路
	ROOT_ENTRANCE,		//通路入口
	STAIRS,				//階段

	BASIC_MAX,

	//オブジェクト系
	LAKE,			//湖
	LAKE_LEFTUP,	//湖左上
	LAKE_LEFTDOWN,	//湖左下
	LAKE_RIGHTUP,	//湖右上
	LAKE_RIGHTDOWN,	//湖右下
	FOUNTAIN,			//噴水
	MUSHROOM,			//キノコ
	HOME,				//家

	OBJ_MAX,

	//罠系
	TRAP_POISON,
	TRAP_NUMBNESS,
	TRAP_SLEEP,
	TRAP_CONFUSION,

	TRAP_MAX,

	etc
};

//マップ情報を格納する構造体
struct Map
{
	Situation m_terrain;
	int m_item;
	ObjectNumber m_unit;
	int m_isVisible;
	int m_roomnumber;
};

//A*アルゴリズムで使用する際に用いる構造体
struct AStar
{
	int			m_nPosX;
	int			m_nPosZ;
	int			m_nMapStatus;		//マップの状態を保存
	float		m_nCost;			//スタート位置から自身の位置までの移動コスト
	float		m_nHeuristic;		//自身の位置から目標地点までのコスト
	float		m_nScore;			//コストとヒューリスティック値の合計値
	D3DXVECTOR2	m_ParentPos;		//自身の親の位置
};

//A*アルゴリズムで用いるリスト
struct AStarList
{
	AStar AstarData;
	AStarList* NextData;
};


//マップ情報の管理
class CMapData
{
private:

	//-----マップデータ-----
	static Map						m_MapData[MAP_SIZE][MAP_SIZE];				// 新しいマップ情報

	static bool						m_bCheckFlg[MAP_SIZE][MAP_SIZE];			//確認が完了したか
	static int						m_nCost[MAP_SIZE][MAP_SIZE];				//現在地からの移動コスト
	static int						m_nScore[MAP_SIZE][MAP_SIZE];				//特定の位置から目標位置までのコスト

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
	

	static AStar		m_AStarData[MAP_SIZE][MAP_SIZE];//A*アルゴリズムに使用する構造体
	static AStarList*	m_pAstarList;
public:
	//方向
	enum VectorFlg
	{
		//縦
		Vectical = 0,
		//横
		Horizon,
		Max
	};

	CMapData(void);										//コンストラクタ
	~CMapData(void);									//デストラクタ

	void Init();										//初期化
	void UpDate();										//更新
	void Draw();										//描画
	void Fin();											//終了処理
	
	void SetFontPos();									//文字描画位置を設定

	//現在の階層数を取得
	static int GetHierarchieNum()	{return m_nHierarchyNum;}

	// ----地形情報の取得
	static const Map& Get_MapData(int,int);

	//-----地形マップ状態取得-----
	static int Get_TerrainMapSituation (int,int);				//地形配列の位置を指定し状態を返す

	//-----ユニットマップ状態取得-----
	static int Get_UnitMapSituation (int,int);					//ユニット配列の位置を指定し、状態を返す

	//-----アイテムマップ状態取得-----
	static int Get_ItemMapSituation (int,int);					//アイテム配列の位置を取得し、状態を返す

	//-----ユニットマップ操作-----
	static void Back_UnitMap	(int,int);				//指定した位置情報を元に戻す。
	static void Set_UnitMap		(int,int,int);			//指定した位置情報を指定した値に変更する。

	//-----可視化-----
	static void SetDark(int,int, BOOL);
	static void SetVisibleProcess(int,int);
	static void SetRoomVisible(int);

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

	//A*アルゴリズム用構造体の初期化を行う
	static void InitAStarData();	

	//A*アルゴリズムの構造体のデータを設定する
	static void ASarSetData(int NowPosX,int NowPosZ,int EnemyPosX,int EnemyPosZ,int PlayerPosX,int PlayerPosZ);

	//指定された位置周囲の移動可能な場所を検索しリストへ追加する
	static void SearchPosition(int SearchPosX,int SearchPosZ,int EnemyPosX,int EnemyPosZ,int PlayerPosX,int PlayerPosZ);

	//A*アルゴリズムにおける、値を計算する
	static float AStarCalculator(int NowPosX,int NowPosZ,int GoalPosX,int GoalPosZ);

	//リスト内の、最もスコアの小さい位置を検索し、渡す
	static void SearchMinScoreData(int *PosX,int *PosZ);

	//セルの状態を遷移させる
	static void CompleteCellCal(int PosX,int PosZ,int State);

	//指定された位置の親の場所を返す
	static void GetParentPos(int ChildPosX,int ChildPosZ,int *ParentPosX,int *ParentPosZ);

	//指定された区画同士が一部でも重なっているか返す
	static bool CheckSectionOverRide(int Section1,int Section2, VectorFlg VectorFlg);

	//フィールド上にオブジェクトを配置する
	static void SetFieldObj();

	//生成した部屋の数を取得する
	static int GetMakeRoomNum()
	{
		return m_CountMakeRoom;
	}
};

