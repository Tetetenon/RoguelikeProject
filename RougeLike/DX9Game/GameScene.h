//=======================================================================================
//
//	  ゲームシーン クラス定義
//
//=======================================================================================
#pragma once

#include "Graphics.h"
#include "C3DObj.h"
#include "Mesh.h"

//-----プレイヤー、エネミー(ユニット)-----
#include "EnemyGenerator.h"		//エネミー生成クラス
#include "ItemGenerator.h"		//アイテム生成クラス

//-----オブジェクト-----
#include "FieldObjMaker.h"		//フィールドオブジェクラス
#include "Camera.h"				//カメラクラス
#include "Turn.h"				//ターン管理クラス
#include "MessageWindow.h"		//メッセージウインドウ実装
#include "MapData.h"			//マップ実装
#include "DeleteObj.h"			//消滅エフェクトクラス
#include "HitObj.h"				//ヒットエフェクトクラス
#include "Sky.h"				//スカイドーム

//-----アイテムウインドウ-----
#include "ItemWindowCursor.h"		//アイテムカーソル
#include "ItemCommandWindow.h"		//コマンドウインドウ
#include "ItemCommandCursor.h"		//コマンド選択カーソル

//-----ステータス描画-----
#include "HPDraw.h"

//-----メニューウインドウ-----
#include "MenuWindow.h"				//メニューウインドウテクスチャ描画
#include "MenuSelect.h"				//メニューウィンドウのセレクト用ポリゴン
#include "MenuWindow_Back.h"		//メニューウィンドウの背景

//-----ステータスウィンドウ-----
#include "StatesWindow.h"			//ステータスのウィンドウのみ
#include "StatesCharacter.h"		//キャラクターウィンドウ
#include "StatesFont.h"				//キャラクターステータスの文字
#include "StatesValue.h"			//キャラクターのステータス

//-----装備ウィンドウ-----
#include "EquipmentWindowCursor.h"	//装備選択カーソル
#include "EquipmentCommandWindow.h"	//装備コマンドウィンドウ
#include "EquipmentCommandCursor.h"	//装備コマンドカーソル

//-----技ウィンドウ-----
#include "TrickWindowCursor.h"		//技カーソル

#include "Fade.h"					//フェードアウト
#include "Operation.h"				//操作説明

#include "MiniMap.h"				//ミニマップ処理

#include "HierarchieNum.h"			//現在の階層数を、フェードイン中に表示する

#include "DamageBillBoardManager.h"	//ダメージ表記マネージャー

#define GAME_CLEAR	(1)
#define GAME_OVER	(2)

class CGameScene
{
private:
	CGraphics*					m_pGraph;					//グラフィックデバイス

	CFade*						m_pFade;					//フェードアウト
		
	TCHAR						m_szDebug[1024];			// デバッグ用文字列
	int							m_FPS;						// フレーム数カウント用

	//-------- ゲーム用オブジェクト -----
	CPlayer*					m_pPlayer;					//プレイヤー
	CEnemyGenerator*			m_pEnemyGenerator;			//エネミー生成
	CItemGenerator*				m_pFieldGenerator;			//アイテム生成
	CFieldObjMaker*				m_pFieldObjMaker;			//フィールドオブジェ生成
	CCamera*					m_pCamera;					//カメラ
	MessageWindow*				m_pMessageWindow;			//ウインドウ
	CHPDraw*					m_pHPDraw;					//ステータス描画
	CMapData*					m_pMap;						//マップ
	CTurn*						m_pTurn;					//ターンクラス
	COperation*					m_pOperation;				//操作説明

	//アイテムウィンドウ
	CInventoryCursor*			m_pInventoryCursor;			//アイテムカーソル
	CCommandWindow*				m_pCommandWindow;			//コマンドウインドウ
	CCommandCursor*				m_pCommandCursor;			//コマンドカーソル

	//装備ウィンドウ
	CEquipmentInventoryCursor*	m_pEquipmentInventoryCursor;//装備カーソル
	CEquipmentCommandWindow*	m_pEquipmentCommandWindow;	//装備ウィンドウコマンドウィンドウ
	CEquipmentCommandCursor*	m_pEquipmentCommandCursor;	//装備ウィンドウコマンド選択
	//-----メニューウィンドウ-----
	CMenuWindow*				m_pMenuWindow;				//メニューウインドウ
	CMenuSelect*				m_pMenuSelect;				//メニューセレクト
	CMenuWindow_Back*			m_pMenuWindowBack;			//メニューウィンドウの背景

	//-----ステータスウィンドウ-----
	CStatesWindow*				m_pStatesWindow;			//ウィンドウ
	CStatesCharacter*			m_pStatesCharacter;			//キャラクターウィンドウ
	CStatesFont*				m_pStatesFont;				//ステータス項目文字
	CStatesValue*				m_pStatesValue;				//ステータス数値

	CDamageBillBoardManager*	m_pDamageManager;			//ダメージ表記マネージャー

	//-----技ウィンドウ-----
	CTrickWindowCursor*			m_pTrickWindowCursor;		//技ウィンドウカーソル

	CSky*						m_pSky;						//スカイドーム

	CMiniMap*					m_pMiniMap;					//ミニマップ

	static bool					m_MapMake;					//マップデータを再生成する
	static bool					m_OldMapMake;				//前フレームのマップ再生成フラグを保持

	static int					m_nPlayerLevel;				//階層を下りた時点のプレイヤーのレベル

	static int					m_nGameClaer;				//ゲームをクリアしたか、ゲームオーバーになったか

	CHierarchieNum*				m_pHierarchiNum;			//フェードイン中に階層数を表示する
public:
	CGameScene();
	virtual ~CGameScene();
	//シーンの作成
	static CGameScene* Create(CGraphics* pGraph);
	//シーンの削除
	void Release();
	//描画
	void Render();
	//更新
	void Update();
	//FPS情報を取得
	void SetFPS(int nFPS){m_FPS = nFPS;}
	//
	void AddDebugStr(LPCTSTR psz)
	{
		lstrcat(m_szDebug, psz);
	}
	//マップの再生成フラグを立てる
	static void MapReMake ()	{m_MapMake = true;}	

	//プレイヤーのレベルを取得
	//static int GetPlayerLevel()	{return m_nPlayerLevel;}

	//ゲームのクリア状況を変更する
	static void GameClearStateChange(int Change);
private:
	//初期化
	bool Initialize(CGraphics* pGraph);
	//終了処理
	void Finalize();
	//描画
	void Draw();

	//-----オブジェクトの処理-----
	//初期化
	void InitObj();
	//終了処理
	void FinObj();
	//更新
	void UpdateObj();
	//描画
	void DrawObj();
};

//=======================================================================================
//	End of File
//=======================================================================================