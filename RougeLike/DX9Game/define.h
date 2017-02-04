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


//装備コマンド
enum
{
	EQUIPMENT_COMMAD_BACK = 0,
	EQUIPMENT_COMMAND_MAX
};

//所持できる最大技数
#define TRICK_NUM_MAX 4

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

//アイテムコマンド
enum
{
	COMMAND_USE = 0,	//使う
	COMMAND_EQUIPMENT,	//装備
	COMMAND_RELINQUISH,	//捨てる
	COMMAND_MAX
};
//文字と文字の隙間
#define FontClearance	10.0f

//文字サイズ
#define FontScale		45.0f

//
#define RIKU_TAKAHASHI	(0)

//ジョイスティックの左スティックが入力されたとはんだんする値
const float JoyMoveCap = 0.5f;
//ボタンの入力のインターバールタイム
const float ButtonIntervalTime = 10.0f;

#define DebugMode (false)

#endif

//=======================================================================================
//	End of File
//=======================================================================================