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
#include "ItemGenerator.h"		//アイテム生成クラス

//-----オブジェクト-----
#include "FieldObjMaker.h"		//フィールドオブジェクラス
#include "Camera.h"				//カメラクラス
#include "Turn.h"				//ターン管理クラス
#include "MapData.h"			//マップ実装
#include "DeleteObj.h"			//消滅エフェクトクラス
#include "HitObj.h"				//ヒットエフェクトクラス
#include "Sky.h"				//スカイドーム

#define GAME_CLEAR	(1)
#define GAME_OVER	(2)

class CFade;					//フェード
class CHierarchieNum;			//階層数表示
class CUnitManager;				//ユニットマネージャー
class CEffectObjManager;		//エフェクトオブジェ
class CDamageBillBoardManager;	//ダメージビルボード
class CItemManager;				//フィールドアイテム
class CMapObjManager;			//マップオブジェ
class CParticleManager;			//パーティクル
class CUIManager;				//UIマネージャ
class CPlayer;					//プレイヤー
class CEnemyGenerator;

class CGameScene
{
private:
	CGraphics*					m_pGraph;					//グラフィックデバイス	
	TCHAR						m_szDebug[1024];			// デバッグ用文字列
	int							m_FPS;						// フレーム数カウント用

	//-------- ゲーム用オブジェクト -----
	CPlayer*					m_pPlayer;					//プレイヤー
	CEnemyGenerator*			m_pEnemyGenerator;			//エネミー生成
	CItemGenerator*				m_pFieldGenerator;			//アイテム生成
	CFieldObjMaker*				m_pFieldObjMaker;			//フィールドオブジェ生成
	CCamera*					m_pCamera;					//カメラ

	CFade*						m_pFade;					//フェード
	CHierarchieNum*				m_pHierarchieNum;			//階層数表示

	//マネージャーポインタ
	CDamageBillBoardManager*	m_pDamageManager;			//ダメージ表記マネージャー
	CUnitManager*				m_pUnitManager;				//ユニットマネージャー			
	CEffectObjManager*			m_pEffectManager;			//エフェクトオブジェマネージャー
	CItemManager*				m_pFieldItemManager;		//フィールドアイテム
	CMapObjManager*				m_pMapObjManager;			//マップオブジェ
	CParticleManager*			m_pParticleManager;			//パーティクル
	CUIManager*					m_pUIManager;				//UIマネージャー

	CMapData*					m_pMap;						//マップ
	CTurn*						m_pTurn;					//ターンクラス
	CSky*						m_pSky;						//スカイドーム
	static bool					m_MapMake;					//マップデータを再生成する
	static bool					m_OldMapMake;				//前フレームのマップ再生成フラグを保持

	static int					m_nPlayerLevel;				//階層を下りた時点のプレイヤーのレベル

	static int					m_nGameClaer;				//ゲームをクリアしたか、ゲームオーバーになったか
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