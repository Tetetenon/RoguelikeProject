#include "TextureManager.h"
#include "Graphics.h"

#include <tchar.h>


LPDIRECT3DTEXTURE9	CTextureManager::m_TextureData[TEXTURE_MAX];			//テクスチャデータ格納用
bool				CTextureManager::m_TextureLoad[TEXTURE_MAX] = {false};	//テクスチャ読み込みフラグ


//使用テクスチャ
#define TEXTURE_PATH_WINDOW			_T("../data/texture/Window.png")		//ウィンドウ
#define TEXTURE_PATH_WINDOW_ALPHA	_T("../data/texture/Window_A.png")		//半透明ウィンドウ
#define TEXTURE_PATH_SELECT_WINDOW	_T("../data/texture/Window2.png")		//選択中ウィンドウ
#define TEXTURE_PATH_FLOOR			_T("../data/Texture/Floor.png")			//床
#define TEXTURE_PATH_WALL			_T("../data/Texture/Wall.png")			//カベ

#define TEXTURE_PATH_TITLE			_T("../data/texture/Title.png")			//タイトル
#define TEXTURE_PATH_RESULT			_T("../data/texture/Result.png")		//リザルト
#define TEXTURE_PATH_GAMECLEAR		_T("../data/texture/GameClear.png")		//ゲームクリア

#define TEXTURE_PATH_PRESS_SPACE	_T("../data/texture/PressSpace.png")	//プレススペース
#define TEXTURE_PATH_CIRCLE_P		_T("../data/texture/Circle_P.png")		//プレイヤーユニットサークル
#define TEXTURE_PATH_CIRCLE_E		_T("../data/texture/Circle_E.png")		//エネミーユニットサークル
#define TEXTURE_PATH_CIRCLE_F		_T("../data/texture/Circle_F.png")		//友軍ユニットサークル
#define TEXTURE_PATH_CIRCLE_I		_T("../data/texture/Circle_I.png")		//アイテムサークル
#define TEXTURE_PATH_MENIUWINDOW	_T("../data/texture/Menu_Window.png")	//メニューウィンドウ
#define TEXTURE_PATH_OPERATION		_T("../data/texture/Operation.png")		//操作説明テクスチャ
#define TEXTURE_PATH_RED_TEXTURE	_T("../data/texture/RedTexture.png")	//赤色テクスチャ
#define TEXTURE_PATH_WHITE_TEXTURE	_T("../data/texture/WhiteTexture.png")	//白色テクスチャ

#define TEXTURE_PATH_HP				_T("../data/texture/GreenTexture.png")	//緑色テクスチャ
#define TEXTURE_PATH_PURPLE_TEXTURE	_T("../data/texture/PurpleTexture.png")	//紫色テクスチャ
#define TEXTURE_PATH_BLUE_TEXTURE	_T("../data/texture/BlueTexture.png")	//青色テクスチャ
#define TEXTURE_PATH_ORANGE_TEXTURE	_T("../data/texture/OrangeTexture.png")	//橙色テクスチャ

#define TEXTURE_PATH_PARTICLE		_T("../data/texture/ParticleWhite.png")	//パーティクルテクスチャ１
#define TEXTURE_PATH_PARTICLE2		_T("../data/texture/flare07.bmp")		//パーティクルテクスチャ２
#define TEXTURE_PATH_LEVELUP		_T("../data/texture/LevelUp.png")		//パーティクルテクスチャ２

#define TEXTURE_PATH_RED_HOOD		_T("../data/texture/RedHood.png")		//ステータス画面用赤ずきん
#define TEXTURE_PATH_RED_HOOD_PO	_T("../data/texture/Poison.png")		//ステータス用毒状態
#define TEXTURE_PATH_RED_HOOD_PA	_T("../data/texture/Paralysis.png")		//ステータス用麻痺
#define TEXTURE_PATH_RED_HOOD_SL	_T("../data/texture/Sleep.png")			//ステータス用睡眠
#define TEXTURE_PATH_RED_HOOD_CO	_T("../data/texture/Confusion.png")		//ステータス用混乱
#define TEXTURE_PATH_ATTACK			_T("../data/texture/Attack.png")		//ステータス用攻撃力テクスチャ
#define TEXTURE_PATH_DEFENCE		_T("../data/texture/Defence.png")		//ステータス用防御力テクスチャ
#define TEXTURE_PATH_EXP			_T("../data/texture/Exp.png")			//ステータス用経験値テクスチャ


//-----数字-----
#define TEXTURE_PATH_0	_T("../data/texture/0.png")							//数字テクスチャ
#define TEXTURE_PATH_1	_T("../data/texture/1.png")							//数字テクスチャ
#define TEXTURE_PATH_2	_T("../data/texture/2.png")							//数字テクスチャ
#define TEXTURE_PATH_3	_T("../data/texture/3.png")							//数字テクスチャ
#define TEXTURE_PATH_4	_T("../data/texture/4.png")							//数字テクスチャ
#define TEXTURE_PATH_5	_T("../data/texture/5.png")							//数字テクスチャ
#define TEXTURE_PATH_6	_T("../data/texture/6.png")							//数字テクスチャ
#define TEXTURE_PATH_7	_T("../data/texture/7.png")							//数字テクスチャ
#define TEXTURE_PATH_8	_T("../data/texture/8.png")							//数字テクスチャ
#define TEXTURE_PATH_9	_T("../data/texture/9.png")							//数字テクスチャ

//-----アルファベット-----
#define TEXTURE_PATH_F	_T("../data/texture/F.png")							//アルファベットテクスチャ


//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CTextureManager::CTextureManager(void)
{
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CTextureManager::~CTextureManager(void)
{
}


//---------------------------------------------------------------------------------------
//テクスチャデータの読み込み
//---------------------------------------------------------------------------------------
void CTextureManager::LoadTexture()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//モデルデータの初期化
	ReleaseTexture();

	
	//ウインドウ
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_WINDOW])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_WINDOW,&m_TextureData[TEXTURE_WINDOW]);
	}

	//ウインドウ(半透明)
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_WINDOW_ALPHA])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_WINDOW_ALPHA,&m_TextureData[TEXTURE_WINDOW_ALPHA]);
	}

	//セレクトウインドウ
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_SELECT_WINDOW])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_SELECT_WINDOW,&m_TextureData[TEXTURE_SELECT_WINDOW]);
	}

	//床
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_FLOOR])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_FLOOR,&m_TextureData[TEXTURE_FLOOR]);
	}

	//壁
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_WALL])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_WALL,&m_TextureData[TEXTURE_WALL]);
	}

	//タイトル
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_TITLE])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_TITLE,&m_TextureData[TEXTURE_TITLE]);
	}

	//リザルト
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_RESULT])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_RESULT,&m_TextureData[TEXTURE_RESULT]);
	}

	//ゲームクリア
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_GAMECLEAR])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_GAMECLEAR,&m_TextureData[TEXTURE_GAMECLEAR]);
	}

	//プレススペース
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_PRESS_SPACE])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_PRESS_SPACE,&m_TextureData[TEXTURE_PRESS_SPACE]);
	}

	//プレイヤーサークル
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_CIRCLE_P])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_CIRCLE_P,&m_TextureData[TEXTURE_CIRCLE_P]);
	}

	//エネミーサークル
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_CIRCLE_E])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_CIRCLE_E,&m_TextureData[TEXTURE_CIRCLE_E]);
	}

	//友軍サークル
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_CIRCLE_F])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_CIRCLE_F,&m_TextureData[TEXTURE_CIRCLE_F]);
	}
	
	//アイテムサークル
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_CIRCLE_I])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_CIRCLE_I,&m_TextureData[TEXTURE_CIRCLE_I]);
	}

	//メニューウィンドウ
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_MENU_WINDOW])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_MENIUWINDOW,&m_TextureData[TEXTURE_MENU_WINDOW]);
	}

	//操作説明
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_OPERATION])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_OPERATION,&m_TextureData[TEXTURE_OPERATION]);
	}

	//赤いテクスチャ
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_RED_TEXTURE])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_RED_TEXTURE,&m_TextureData[TEXTURE_RED_TEXTURE]);
	}
	
	//白いテクスチャ
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_WHITE_TEXTURE])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_WHITE_TEXTURE,&m_TextureData[TEXTURE_WHITE_TEXTURE]);
	}
	//青いテクスチャ
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_BLUE_TEXTURE])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_BLUE_TEXTURE,&m_TextureData[TEXTURE_BLUE_TEXTURE]);
	}
	//橙テクスチャ
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_ORANGE_TEXTURE])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_ORANGE_TEXTURE,&m_TextureData[TEXTURE_ORANGE_TEXTURE]);
	}
	//紫テクスチャ
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_PURPLE_TEXTURE])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_PURPLE_TEXTURE,&m_TextureData[TEXTURE_PURPLE_TEXTURE]);
	}

	//パーティクルテクスチャ
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_PARTICLE1])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_PARTICLE,&m_TextureData[TEXTURE_PARTICLE1]);
	}

	//パーティクルテクスチャ２
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_PARTICLE2])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_PARTICLE2,&m_TextureData[TEXTURE_PARTICLE2]);
	}

	//レベルアップテクスチャ
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_LEVELUP])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_LEVELUP,&m_TextureData[TEXTURE_LEVELUP]);
	}

	//赤ずきん
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_RED_HOOD])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_RED_HOOD,&m_TextureData[TEXTURE_RED_HOOD]);
	}

	//赤ずきん(毒)
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_RED_HOOD_POISON])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_RED_HOOD_PO,&m_TextureData[TEXTURE_RED_HOOD_POISON]);
	}

	//赤ずきん(麻痺)
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_RED_HOOD_PARALYSIS])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_RED_HOOD_PA,&m_TextureData[TEXTURE_RED_HOOD_PARALYSIS]);
	}

	//赤ずきん(睡眠)
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_RED_HOOD_SLEEP])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_RED_HOOD_SL,&m_TextureData[TEXTURE_RED_HOOD_SLEEP]);
	}

	//赤ずきん(混乱)
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_RED_HOOD_CONFUSION])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_RED_HOOD_CO,&m_TextureData[TEXTURE_RED_HOOD_CONFUSION]);
	}

	//HPバー
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_HP_BAR])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_HP,&m_TextureData[TEXTURE_HP_BAR]);
	}

	//こうげき
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_ATTACK])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_ATTACK,&m_TextureData[TEXTURE_ATTACK]);
	}

	//ぼうぎょ
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_DEFENCE])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_DEFENCE,&m_TextureData[TEXTURE_DEFENCE]);
	}

	//けいけんち
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_EXP])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_EXP,&m_TextureData[TEXTURE_EXP]);
	}

	//数値
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_0])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_0,&m_TextureData[TEXTURE_0]);
	}

	//数値
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_1])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_1,&m_TextureData[TEXTURE_1]);
	}

	//数値
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_2])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_2,&m_TextureData[TEXTURE_2]);
	}

	//数値
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_3])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_3,&m_TextureData[TEXTURE_3]);
	}

	//数値
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_4])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_4,&m_TextureData[TEXTURE_4]);
	}

	//数値
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_5])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_5,&m_TextureData[TEXTURE_5]);
	}

	//数値
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_6])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_6,&m_TextureData[TEXTURE_6]);
	}

	//数値
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_7])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_7,&m_TextureData[TEXTURE_7]);
	}

	//数値
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_8])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_8,&m_TextureData[TEXTURE_8]);
	}

	//数値
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_9])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_9,&m_TextureData[TEXTURE_9]);
	}

	//アルファベット
	//テクスチャの読み込みが完了していなければ読み込む
	if(!m_TextureLoad[TEXTURE_F])
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_F,&m_TextureData[TEXTURE_F]);
	}
	
}

//---------------------------------------------------------------------------------------
//全てのメッシュデータを削除する
//---------------------------------------------------------------------------------------
void CTextureManager::ReleaseTexture()
{
	//テクスチャデータが存在すれば、削除を行う
	for(int i = 0;i < TEXTURE_MAX;i++)
	{
		//テクスチャデータが読み込まれている
		if(m_TextureLoad[i])
		{
			//テクスチャの開放
			SAFE_RELEASE(m_TextureData[i]);

			//テクスチャ読み込みフラグ倒す
			m_TextureLoad[i] = false;
		}
	}
}
//---------------------------------------------------------------------------------------
//指定されたテクスチャデータを渡す
//---------------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9* CTextureManager::GetTexture(int nNumber)
{
	return &m_TextureData[nNumber];
}