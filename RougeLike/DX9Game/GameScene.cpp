//=======================================================================================
//
//	  ゲームシーン クラス
//
//=======================================================================================

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include "define.h"
#include "GameScene.h"
#include "Input.h"

#include "Enemy.h"
#include "Item.h"
#include "FieldObj.h"
#include "ModelManager.h"
#include "Turn.h"
#include "Player.h"
#include "GameState.h"

#include"UnitManager.h"
#include "EnemyGenerator.h"
#include"ItemManager.h"
#include"MapObjManager.h"
#include"ParticleManager.h"
#include"EffectObjManager.h"
#include"EnemyManager.h"
#include "UIManager.h"
#include "Fade.h"					//フェードアウト
#include "HierarchieNum.h"			//階層数表示
#include "DamageBillBoardManager.h"

bool	CGameScene::m_MapMake = false;
bool	CGameScene::m_OldMapMake = false;
int		CGameScene::m_nPlayerLevel = 0;

int	CGameScene::m_nGameClaer = 0;	//ゲームをクリアできたか

//---------------------------------------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------------------------------------
CGameScene::CGameScene():
	m_pGraph(NULL),
	m_FPS()
{
	//デバッグ文字の初期化
	m_szDebug[0] = _T('\0');

	//ゲームのクリア状態の初期化
	m_nGameClaer = 0;

	srand((unsigned int)time(NULL));			//時間で乱数の初期化を行う


	//シングルトンの作成
	CCamera::Create(this);
	CSky::Create(this);
	CUnitManager::Create();
	CItemManager::Create();
	CMapObjManager::Create();
	CParticleManager::Create();
	CEffectObjManager::Create();
	CDamageBillBoardManager::Create();
	CEnemyGenerator::Create(this);
	CFade::Create();
	CHierarchieNum::Create();
	CUIManager::Create();
	CMapData::Create();


	//シングルトンのポインタの取得
	m_pCamera			= CCamera::GetPointer();					//カメラ
	m_pSky				= CSky::GetPointer();						//スカイドーム
	m_pUnitManager		= CUnitManager::GetPointer();
	m_pFieldItemManager = CItemManager::GetPointer();
	m_pMapObjManager	= CMapObjManager::GetPointer();
	m_pParticleManager	= CParticleManager::GetPointer();
	m_pEffectManager	= CEffectObjManager::GetPointer();
	m_pDamageManager	= CDamageBillBoardManager::GetPointer();	//ダメージ表記マネージャー
	m_pEnemyGenerator	= CEnemyGenerator::GetPointer();	//エネミージェネレーター
	m_pFade				= CFade::GetPointer();						//フェードアウト
	m_pHierarchieNum	= CHierarchieNum::GetPointer();				//階層数表示
	m_pUIManager		= CUIManager::GetPointer();
	m_pMap				= CMapData::GetPointer();				//マップデータ


	//メンバクラスのコンストラクタを起動
	m_pFieldObjMaker	= new CFieldObjMaker(this);		//フィールドオブジェクト
	m_pTurn				= new CTurn();					//ターン
	m_pFieldGenerator	= new CItemGenerator(this);		//フィールドアイテム生成
	m_pPlayer			= new CPlayer(this);			//プレイヤー

	//各クラスのメンバのポインタをセットする
	m_pUIManager			->ManageUISetPointer();
	m_pEnemyGenerator		->SetPointer();
	m_pHierarchieNum		->SetPointer();
	m_pMap					->SetPointer();

	//マップの生成
	m_pMap->MapGeneration();
	//プレイヤーの位置を設定する
	m_pPlayer->SetPos();
}

//---------------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------------
CGameScene::~CGameScene()
{
	//シングルトンの削除
	CCamera::Delete();
	CSky::Delete();
	CUnitManager::Delete();
	CItemManager::Delete();
	CMapObjManager::Delete();
	CParticleManager::Delete();
	CEffectObjManager::Delete();
	CDamageBillBoardManager::Delete();
	CFade::Delete();
	CHierarchieNum::Delete();
	CFade::Delete();
	CHierarchieNum::Delete();
	CMapData::Delete();
	CEnemyGenerator::Delete();
	CUIManager::Delete();
	//シングルトンのポインタの中身をきれいに
	m_pCamera	= NULL;			//カメラ
	m_pSky		= NULL;			//スカイドーム
	m_pDamageManager = NULL;	//ダメージ表記

	//メンバクラスのポインタを消去
	delete m_pFieldObjMaker;	//フィールドオブジェ生成
	delete m_pTurn;				//ターン
	delete m_pFieldGenerator;	//フィールドアイテム

	m_nGameClaer = 0;

	//プレイヤーのポインタを解放
	if (m_pPlayer)
	{
		m_pPlayer = NULL;
	}
}

//---------------------------------------------------------------------------------------
// シーン生成
//---------------------------------------------------------------------------------------
CGameScene* CGameScene::Create(CGraphics* pGraph)
{
	//シーンのメモリを確保する
	CGameScene* pGameScene = new CGameScene();
	//シーンメモリ確保に成功したら、初期化を行う
	if (pGameScene) {
		if (!pGameScene->Initialize(pGraph)) {
			SAFE_DELETE(pGameScene);
		}
	}
	return pGameScene;
}

//---------------------------------------------------------------------------------------
// デバイス、リソース初期化
//---------------------------------------------------------------------------------------
bool CGameScene::Initialize(CGraphics* pGraph)
{
	m_pGraph = pGraph;

	//-------- ゲーム用オブジェクトの初期化

	//モデルデータの読み込み
	CModelManager::LoadMesh();

	//各種オブジェクトの初期化
	InitObj();
	return true;
}

//---------------------------------------------------------------------------------------
// デバイス、リソース解放
//---------------------------------------------------------------------------------------
void CGameScene::Finalize()
{
	//-------- ゲーム用オブジェクトの後始末

	//モデルデータの開放
	CModelManager::ReleaseMesh();

	//オブジェクトの終了処理
	FinObj();
}

//---------------------------------------------------------------------------------------
// シーン解放
//---------------------------------------------------------------------------------------
void CGameScene::Release()
{
	//使用しているクラスの終了処理を行う
	Finalize();
	//シーンクラスの削除を行う
	delete this;
}

//---------------------------------------------------------------------------------------
// ゲーム描画処理（メインループからコールされる）
//---------------------------------------------------------------------------------------
void CGameScene::Render()
{
	if (m_pGraph->Begin())
	{
		// 描画開始

		Draw();					// 描画処理

		m_pGraph->End();		// 描画終了
	}
	m_pGraph->SwapBuffer();		// バックバッファ入替
}

//---------------------------------------------------------------------------------------
// ゲームメイン処理（メインループからコールされる）
//---------------------------------------------------------------------------------------
void CGameScene::Update()
{
	// 入力更新
	CInput::Update();

	//----- ここにゲーム本体処理
	UpdateObj();
}

//---------------------------------------------------------------------------------------
// 描画処理（CGraphics::Render() からコールされる）
//---------------------------------------------------------------------------------------
void CGameScene::Draw()
{
	//デバッグモードのみ描画
	if (DebugMode)
	{
		m_szDebug[0] = _T('\0');	// デバッグ文字列初期化

		// FPS を画面に描画するための文字列を作成
		TCHAR	str[256];
		_stprintf(str, _T("FPS = %d\n"), m_FPS);
		lstrcat(m_szDebug, str);
	}
	//----- ここに描画処理
	DrawObj();

	// デバッグ文字列描画
	m_pGraph->DrawText(0, 0, m_szDebug);
}
//---------------------------------------------------------------------------------------
//全オブジェクト初期化
//---------------------------------------------------------------------------------------
void CGameScene::InitObj()
{
	//マップの初期化
	m_pMap ->Init();

	//全てのオブジェクトの初期化
	m_pFieldItemManager->Init();//アイテムマネージャーの管理オブジェクトの初期化
	m_pUnitManager->Init();		//ユニットマネージャーの管理オブジェクトの初期化
	m_pMapObjManager->Init();	//フィールドオブジェマネージャーの管理オブジェクトの初期化
	m_pParticleManager->Init();	//パーティクルマネージャーの初期化
	m_pEffectManager->Init();	//エフェクトマネージャーの初期化

	//カメラの初期化
	m_pCamera->Init();
	//スカイドームの初期化
	m_pSky->Init();

	//この時点のプレイヤーのレベルを取得する
	m_nPlayerLevel = m_pPlayer->GetLevel();

	//初期配置エネミーの設定
	m_pEnemyGenerator ->MakeEnemy();

	//初期配置アイテムの設定
	m_pFieldGenerator->MakeItem();

	//配列情報から、オブジェクトを置くべき位置にオブジェクトを設置
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
		{
			switch (m_pMap->Get_TerrainMapSituation(i, j))
			{
			case WALL:
				m_pFieldObjMaker->PutObj(MODEL_TREE, i, j);
				break;
			case STAIRS:
				m_pFieldObjMaker->PutObj(MODEL_STAIRS, i, j);
				break;
			case HOME:
				m_pFieldObjMaker->PutObj(MODEL_HOME, i, j);
				break;

			}
		}
	}

	//フェードの状態をフェードインに設定
	m_pFade->ChangeState(FADEMODE_IN);
	//ユニットを一時行動不能状態に設定
	m_pUnitManager->ChangeMoveCanFlg(false);
}
//---------------------------------------------------------------------------------------
//全オブジェクト破棄
//---------------------------------------------------------------------------------------
void CGameScene::FinObj()
{
	//途中でリストが変わる可能性を考慮し、退避用ポインタを持つ

	//各マネージャーで管理するオブジェクトの終了処理を行う
	m_pUnitManager->Fin();
	m_pFieldItemManager->Fin();
	m_pMapObjManager->Fin();
	m_pParticleManager->Fin();
	m_pEffectManager->Fin();

	m_pDamageManager->ManagerObjFin();

	//マップデータの終了処理
	m_pMap->Fin();
}
//---------------------------------------------------------------------------------------
//全オブジェクト更新
//---------------------------------------------------------------------------------------
void CGameScene::UpdateObj()
{
	//マップの再生成フラグが立っていたら処理
	if(m_MapMake && m_OldMapMake)
	{
		//UIのデータを初期化
		m_pUIManager->ManageUIInit();

		//フェードアウトフラグを立てる
		m_pFade->ChangeState(FADEMODE_OUT);

		//マップデータの再生成
		m_pMap->MapGeneration();

		//フィールドオブジェクト削除
		m_pMapObjManager->Fin();
		//エネミーオブジェクト削除
		m_pUnitManager->EnemyDelete();
		//アイテムオブジェクトの削除
		m_pFieldItemManager->Fin();
		//パーティクルオブジェクトの削除
		m_pParticleManager->Fin();
		//エフェクトオブジェクトの削除
		m_pEffectManager->Fin();
		
		//配列情報から、オブジェクトを置くべき位置にオブジェクトを設置
		for(int i = 0;i < MAP_SIZE;i++)
		{
			for(int j = 0;j < MAP_SIZE;j++)
			{
				switch (m_pMap->Get_TerrainMapSituation(i, j))
				{
				case WALL:
					m_pFieldObjMaker->PutObj(MODEL_TREE, i, j);
					break;
				case STAIRS:
					m_pFieldObjMaker->PutObj(MODEL_STAIRS, i, j);
					break;
				case HOME:
					m_pFieldObjMaker->PutObj(MODEL_HOME, i, j);
					break;
				}
			}
		}

		//ターンステート初期化
		CTurn::Init();

		//エネミー生成数をリセット
		m_pEnemyGenerator->ResetMakeEnemyNum();

		//アイテム生成数をリセット
		CItemGenerator::ResetMakeItemNum();

		//プレイヤー位置再設定
		m_pPlayer -> SetPos();

		//マップ再生成フラグを倒す
		m_MapMake = false;

		//初期配置エネミーの設定
		m_pEnemyGenerator ->MakeEnemy();

		//階段到達状態を偽にする
		m_MapMake = false;
	}
	//-----3Dオブジェクトの更新-----

	//マップ再生成フラグ状況を保存しておく
	m_OldMapMake = m_MapMake;

	//各マネージャーの持つオブジェクトの更新
	m_pUnitManager->Update();
	m_pFieldItemManager->Update();
	m_pMapObjManager->Update();
	m_pParticleManager->Update();
	m_pEffectManager->Update();
	m_pUIManager->ManageUIUpdate();

	//ダメージ表記の更新
	m_pDamageManager->ManagerObjUpdate();

	//ジェネレーターの更新
	m_pEnemyGenerator->Update();
	m_pFieldGenerator->Update();

	//カメラの更新
	m_pCamera->Update();
	m_pCamera -> PostUpdate();
	m_pMap ->UpDate();				//マップデータ更新

	//フェードイン開始フラグが立っていた場合、フェードの処理を行う
	//フェードインの更新
	m_pFade ->Update();

	//フェードインが完了したら、ステートを変更する
	if(m_pFade ->GetFadeAlpha() >= 255)
	{
		//フェードの状態を格納
		int FadeMode = m_pFade->GetFadeState();

		//フェードの状態で処理を分岐
		switch(FadeMode)
		{
			//フェード状態がフェードインの状態だった場合
		case FADEMODE_IN:
			//ユニットを一時行動不能状態に設定
			m_pUnitManager->ChangeMoveCanFlg(true);
			break;
			//フェード状態がフェードアウトだった場合
		case FADEMODE_OUT:
			{
				//ゲームクリアできたかによって次に以降するシーンを変更する
				if(m_nGameClaer == GAME_CLEAR)
				{
					CGameState::StateUpdate(STATE_GAMECLEAR);
				}
				else if(m_nGameClaer == GAME_OVER)
				{
					CGameState::StateUpdate(STATE_GAMEOVER);
				}
			}
			break;
		}
		m_pFade->ChangeState(FADEMODE_NON);
	}
}
//---------------------------------------------------------------------------------------
//全オブジェクト描画
//---------------------------------------------------------------------------------------
void CGameScene::DrawObj()
{
	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();

	//Zバッファの適用
	pD->SetRenderState( D3DRS_ZENABLE , TRUE );

	m_pCamera -> PreDraw();	//カメラ反映

	//マップデータ描画
	m_pMap -> Draw();

	//不透明描画
	m_pMapObjManager->Draw(false);
	m_pFieldItemManager->Draw();
	m_pUnitManager->Draw();
	m_pEffectManager->Draw();

	m_pDamageManager->ManagerObjDraw();
	
	pD ->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);

	pD ->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);

	pD ->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//Zバッファレンダリング計算無効化
	pD ->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	//透明描画
	//フィールド上のオブジェクトの半透明のオブジェクトのみ描画する
	m_pMapObjManager->Draw(true);
	m_pParticleManager->Draw();

	pD ->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);

	
	//Zバッファレンダリング計算有効化
	pD ->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	
	//Zバッファの無効
	pD->SetRenderState( D3DRS_ZENABLE , FALSE );

	//UIの描画
	m_pUIManager->ManageUIDraw();

	//階層数の描画
	m_pMap->DrawHierarchyNum();
	//プレイヤーレベルの表示
	m_pPlayer->DrawLevel();
	//フェードの描画
	m_pFade ->Draw();
	//フェードの状態を格納
	int FadeMode = m_pFade->GetFadeState();
	//フェードの状態が、フェードインの場合、階層数を表示
	if(FadeMode == FADEMODE_IN)
		m_pHierarchieNum->Draw();
}
//ゲームのクリア状況を変更する
void CGameScene::GameClearStateChange(int Change)
{
	m_nGameClaer = Change;
}

//=======================================================================================
//	End of File
//=======================================================================================