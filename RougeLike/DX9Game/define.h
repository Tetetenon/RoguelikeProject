//=======================================================================================
//
//	  定数定義、マクロ定義
//
//=======================================================================================

#ifndef _H_DEFINE
#define _H_DEFINE

#pragma once

#include <d3d9.h>
#include <d3dx9.h>

//-------- マクロ-----
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)			if(x){ x->Release(); x=NULL; }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(x)			if(x){ delete x; x=NULL; }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if(x){ delete[] x; x=NULL; }
#endif

// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D2 (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX2)

//1グリッドのサイズ
#define GRIDSIZE 3.0f

//画面サイズ
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

//円周率
#define PI 3.14159265359f

//
#define MASS_SIZE 3

//エラー値
#define ERROR_NUM -99

// ３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3	vtx;	//頂点座標
	D3DXVECTOR3	nor;	//法線ベクトル
	D3DCOLOR	diffuse;	//反射光
	D3DXVECTOR2	tex;	//テクスチャ座標
}VERTEX_3D;


//方向
enum Direction
{
	Forword = 0,
	Right,
	Back,
	Left,
	MaxDirection
};

//アイテムコマンド
enum
{
	COMMAND_USE = 0,	//使う
	COMMAND_EQUIPMENT,	//装備
	COMMAND_RELINQUISH,	//捨てる
	COMMAND_MAX
};

//装備コマンド
enum
{
	EQUIPMENT_COMMAD_BACK = 0,
	EQUIPMENT_COMMAND_MAX
};

//アイテムの名前
enum ITEMNAME
{
	ITEM_APPLE	= 1,	//林檎
	ITEM_HERB,			//薬草
	ITEM_SWORD,			//剣
	ITEM_SHIELD,		//盾
	ITEM_MAX
};

//所持できる最大技数
#define TRICK_NUM_MAX 4

//技の名前
enum TRICKNAME
{
	TRICK_NAME_1 = 0,	//技１
	TRICK_NAME_2,
	TRICK_NAME_3,
	TRICK_NAME_4,
	TRICK_NAME_MAX
};

//マップデータ上に示すオブジェクトの通し番号
enum ObjectNumber
{
	OBJ_NUM_ITEM	=	0,			//アイテム
	OBJ_NUM_PLAYER	=   1,			//プレイヤー			:	    0番
	OBJ_NUM_PARTY	=   2,			//パーティー			:  1～  3番
	OBJ_NUM_ENEMY	=   5,			//エネミー				:  4～番
	OBJ_NUM_MAX
};

//アイテムの効果ジャンル
enum ITEMEFFECT
{
	EFFECT_NON = 0,				//何も効果なし
	EFFECT_RECOVERY,			//回復
	EFFECT_EQUIPMENT_ATTACK,	//装備アイテム(攻撃効能)
	EFFECT_EQUIPMENT_DEFENCE,	//装備アイテム(防御効能)
	EFFECT_MAX			
};

//技の効果ジャンル
enum TRICKEFFECT
{
	TRICK_EFFECT_ATTACK = 0,	//攻撃
	TRICK_EFFECT_STATES_UP,		//ステータスの強化、弱化
	TRICK_EFFECT_RECOVERY,		//回復
	TRICK_EFFECT_MAX
};

//技の効果範囲
enum TRICKRANGE
{
	TRICK_RANGE_FRONT = 0,	//前方に攻撃
	TRICK_RANGE_ME,			//自身
	TRICK_RANGE_ALL,		//部屋全体
	TRICK_RANGE_WIDE,		//前方３マス
	TRICK_RANGE_MAX			//
};

//表示するステータス定義
enum STATES
{
	STATES_FONT_ATTACK = 0,	//こうげき
	STATES_FONT_DEFENCE,		//ぼうぎょ
	STATES_FONT_EXP,			//けいけんち
	STATES_FONT_MAX
};

//文字と文字の隙間
#define FontClearance	10.0f

//文字サイズ
#define FontScale		45.0f

//毒ダメージ
#define PoisonDamage 5

//健康状態列挙
enum UNIT_STATE
{
	UNIT_STATE_HEALTH = 0,		//健康そのものである。
	UNIT_STATE_POISON,			//毒
	UNIT_STATE_CONFUSION,		//少し混乱している!
	UNIT_STATE_WINCE,			//ひるみ
	UNIT_STATE_PARALYSIS,		//麻痺
	UNIT_STATE_SLEEP,			//睡眠
	UNIT_STATE_NO_MONEY,		//金欠
	UNIT_STATE_MAX
};


#endif

//=======================================================================================
//	End of File
//=======================================================================================