#pragma once

#include "define.h"

enum TEXTURENUM
{
	TEXTURE_WINDOW	= 0,		//ウインドウ
	TEXTURE_WINDOW_ALPHA,		//ウィンドウ(半透明)
	TEXTURE_SELECT_WINDOW,		//選択中ウインドウ
	TEXTURE_FLOOR,				//床
	TEXTURE_WALL,				//壁
	TEXTURE_IN_THE_WALL,		//壁の中
	TEXTURE_TITLE,				//タイトル
	TEXTURE_RESULT,				//リザルト
	TEXTURE_PRESS_SPACE,		//プレススペース
	TEXTURE_CIRCLE_P,			//プレイヤーサークル
	TEXTURE_CIRCLE_E,			//エネミーサークル
	TEXTURE_CIRCLE_F,			//パーティー(友軍)サークル
	TEXTURE_CIRCLE_I,			//アイテムサークル
	TEXTURE_MENU_WINDOW,		//メニューウィンドウ
	TEXTURE_OPERATION,			//操作説明テクスチャ
	TEXTURE_RED_TEXTURE,		//赤いテクスチャ
	TEXTURE_WHITE_TEXTURE,		//白いテクスチャ

	TEXTURE_BLUE_TEXTURE,		//青いテクスチャ
	TEXTURE_ORANGE_TEXTURE,		//オレンジテクスチャ
	TEXTURE_PURPLE_TEXTURE,		//紫テクスチャ

	TEXTURE_PARTICLE1,			//パーティクルテクスチャ
	TEXTURE_PARTICLE2,			//パーティクルテクスチャ
	TEXTURE_LEVELUP,			//レベルアップテクスチャ
	
	//-----ステータス関連-----
	TEXTURE_HP_BAR,				//HPバー用テクスチャ
	TEXTURE_RED_HOOD,			//ステータス用赤ずきん画像
	TEXTURE_RED_HOOD_PARALYSIS,	//ステータス用赤ずきん画像(麻痺)
	TEXTURE_RED_HOOD_SLEEP,		//ステータス用赤ずきん画像(睡眠)
	TEXTURE_RED_HOOD_POISON,	//ステータス用赤ずきん画像(毒)
	TEXTURE_RED_HOOD_CONFUSION,	//ステータス用赤ずきん画像(混乱)
	TEXTURE_ATTACK,				//こうげき
	TEXTURE_DEFENCE,			//ぼうぎょ
	TEXTURE_EXP,				//けいけんち

	//-----数値-----
	TEXTURE_0,		//0
	TEXTURE_1,		//1
	TEXTURE_2,		//2
	TEXTURE_3,		//3
	TEXTURE_4,		//4
	TEXTURE_5,		//5
	TEXTURE_6,		//6
	TEXTURE_7,		//7
	TEXTURE_8,		//8
	TEXTURE_9,		//9
	TEXTURE_MAX
};

class CTextureManager
{
private:
	static LPDIRECT3DTEXTURE9	m_TextureData[TEXTURE_MAX];	//全テクスチャデータ保存用
	static bool					m_TextureLoad[TEXTURE_MAX];	//全テクスチャの読み込み完了フラグ
public:
	CTextureManager(void);									//コンストラクタ
	~CTextureManager(void);									//デストラクタ

	static void LoadTexture(void);							//テクスチャのロード

	static void ReleaseTexture(void);						//テクスチャデータの開放

	static LPDIRECT3DTEXTURE9*	GetTexture(int nNumber);	//指定されたテクスチャ番号のデータを渡す
};

