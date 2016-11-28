//=======================================================================================
//
//	  ゲームシーン クラス定義
//
//=======================================================================================
#pragma once

#include "Graphics.h"
#include "C3DObj.h"
#include "Mesh.h"				// CMeshクラス定義

//-----プレイヤー、エネミー(ユニット)-----
#include "Unit.h"				//ユニット
#include "Player.h"				//プレイヤー
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
//#include "ItemWindow.h"			//インベントリ(アイテムウインドウ)
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
//#include "EquipmentWindow.h"		//装備のウィンドウ
#include "EquipmentWindowCursor.h"	//装備選択カーソル
#include "EquipmentCommandWindow.h"	//装備コマンドウィンドウ
#include "EquipmentCommandCursor.h"	//装備コマンドカーソル

//-----技ウィンドウ-----
#include "TrickWindowCursor.h"		//技カーソル

#include "Fade.h"					//フェードアウト
#include "Operation.h"				//操作説明

#include "MiniMap.h"				//ミニマップ処理

#include "HierarchieNum.h"			//現在の階層数を、フェードイン中に表示する

#define GAME_CLEAR	(1)
#define GAME_OVER	(2)

class CGameScene
{
private:
	CGraphics*					m_pGraph;					//グラフィックデバイス
	C3DObj *					m_pObj;						//オブジェクトデバイス
	CUnit*						m_pUnit;					//ユニットデバイス
	CFieldItem*					m_pItemDevice;				//アイテムデバイス

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

	//-----オブジェクト関連の操作-----
	//シーン上にオブジェクトを追加
	void Add(C3DObj* pObj);
	//シーン上のオブジェクトを削除
	void Del(C3DObj* pObj);
	//シーン上のオブジェクトを探索する
	C3DObj* Find(UINT uID,C3DObj *p);

	
	//-----ユニット関連の操作-----
	//シーン上にユニットを追加する
	void AddUnit(CUnit* pUnit);
	//シーン上のユニットを削除する
	void DelUnit(CUnit* pUnit);
	//シーン上のユニットを探索する
	CUnit*  FindUnit(UINT uID,CUnit *p);


	//-----アイテム関連の操作-----
	//シーン上にアイテムを追加する
	void AddItem(CFieldItem* pItem);
	//シーン上のアイテムを削除する
	void DelItem(CFieldItem* pItem);
	//シーン上のアイテムを探索
	CFieldItem* FindItem(UINT uID,CFieldItem *p);

	//マップの再生成フラグを立てる
	static void MapReMake ()	{m_MapMake = true;}	

	//プレイヤーのレベルを取得
	static int GetPlayerLevel()	{return m_nPlayerLevel;}

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