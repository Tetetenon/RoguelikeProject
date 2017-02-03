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
#include"ItemManager.h"
#include"MapObjManager.h"
#include"ParticleManager.h"
#include"EffectObjManager.h"
#include"EnemyManager.h"

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

	//シングルトンのポインタの取得
	m_pCamera	= CCamera::GetPointer();			//カメラ
	m_pSky		= CSky::GetPointer();				//スカイドーム

	
	//メンバクラスのコンストラクタを起動
	m_pFieldObjMaker	= new CFieldObjMaker(this);		//フィールドオブジェクト

	m_pFade				= new CFade();					//フェードアウト
	
	m_pMessageWindow		= new MessageWindow();		//メッセージウインドウ
	m_pHPDraw			= new CHPDraw();				//ステータスウインドウ

	//アイテムウィンドウ
	m_pInventoryCursor	= new CInventoryCursor();		//アイテムカーソル
	m_pCommandWindow	= new CCommandWindow();			//コマンドウインドウ
	m_pCommandCursor	= new CCommandCursor();			//コマンドカーソル
	//装備ウィンドウ
	m_pEquipmentInventoryCursor = new CEquipmentInventoryCursor();	//装備ウィンドウカーソル
	m_pEquipmentCommandWindow = new CEquipmentCommandWindow();	//装備コマンドウィンドウ
	m_pEquipmentCommandCursor = new CEquipmentCommandCursor();	//装備コマンドカーソル

	m_pMap				= new CMapData();				//マップデータ
	m_pTurn				= new CTurn();					//ターン

	m_pFieldGenerator	= new CItemGenerator(this);		//フィールドアイテム生成
	m_pEnemyGenerator	= new CEnemyGenerator(this);	//エネミージェネレーター

	//メニューウィンドウ
	m_pMenuWindow		= new CMenuWindow();			//メニューウインドウ
	m_pMenuSelect		= new CMenuSelect();			//メニューセレクト
	m_pMenuWindowBack	= new CMenuWindow_Back();		//メニューの背景

	//ステータスウィンドウ
	m_pStatesWindow		= new CStatesWindow();			//ステータスウィンドウ
	m_pStatesCharacter	= new CStatesCharacter();		//キャラクターウィンドウ
	m_pStatesFont		= new CStatesFont();			//ステータスフォント
	m_pStatesValue		= new CStatesValue();			//ステータス数値

	m_pOperation = new COperation();					//操作説明

	m_pTrickWindowCursor = new CTrickWindowCursor();	//ワザウィンドウカーソル

	m_pMiniMap = new CMiniMap();						//ミニマップ
	m_pHierarchiNum = new CHierarchieNum();				//現在の階層数をフェードイン中に表示する

	m_pPlayer			= new CPlayer(this);			//プレイヤー
}

//---------------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------------
CGameScene::~CGameScene()
{
	//シングルトンの削除
	CCamera::Delete();
	CSky::Delete();
	//シングルトンのポインタの中身をきれいに
	m_pCamera	= NULL;			//カメラ
	m_pSky		= NULL;			//スカイドーム

	//メンバクラスのポインタを消去
	delete m_pEnemyGenerator;	//エネミージェネレーター

	delete m_pFieldObjMaker;	//フィールドオブジェ生成

	delete m_pFade;				//フェードアウト

	delete m_pMessageWindow;	//メッセージウインドウ

	delete m_pHPDraw;			//ステータスウインドウ

	//アイテムウィンドウ
	//delete m_pInventory;		//インベントリ破棄
	delete m_pInventoryCursor;	//アイテムカーソル破棄
	delete m_pCommandWindow;	//コマンドウインドウ破棄
	delete m_pCommandCursor;	//コマンドカーソル破棄

	//装備ウィンドウ
	delete m_pEquipmentInventoryCursor;	//装備ウィンドウカーソル
	delete m_pEquipmentCommandWindow;	//装備コマンドウィンドウ
	delete m_pEquipmentCommandCursor;	//装備コマンドカーソル

	delete m_pMap;				//マップデータ
	delete m_pTurn;				//ターン

	delete m_pFieldGenerator;	//フィールドアイテム

	//メニューウィンドウ
	delete m_pMenuWindow;		//メニューウインドウ
	delete m_pMenuSelect;		//メニューセレクト
	delete m_pMenuWindowBack;	//メニューウィンドウの背景

	//ステータスウィンドウ
	delete m_pStatesWindow;		//ステータスウィンドウ
	delete m_pStatesCharacter;	//キャラクターウィンドウ
	delete m_pStatesFont;		//ステータス文字
	delete m_pStatesValue;		//ステータス数値

	delete m_pOperation;		//操作説明

	delete m_pTrickWindowCursor;	//技ウィンドウカーソル

	delete m_pMiniMap;				//ミニマップ
	delete m_pHierarchiNum;			//フェードイン中に表示する階層数

	m_nGameClaer = 0;

	//マネージャーの削除
	CUnitManager::Destroy();
	CItemManager::Delete();
	CMapObjManager::Delete();
	CParticleManager::Delete();
	CEffectObjManager::Delete();

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
	CItemManager::Init();		//アイテムマネージャーの管理オブジェクトの初期化
	CUnitManager::Init();		//ユニットマネージャーの管理オブジェクトの初期化
	CMapObjManager::Init();		//フィールドオブジェマネージャーの管理オブジェクトの初期化
	CParticleManager::Init();	//パーティクルマネージャーの初期化
	CEffectObjManager::Init();	//エフェクトマネージャーの初期化
	//プレイヤーのポインタを取得する
	CMapObjManager::PlayerSet();

	//カメラの初期化
	m_pCamera->Init();
	//スカイドームの初期化
	m_pSky->Init();

	//この時点のプレイヤーのレベルを取得する
	m_nPlayerLevel = m_pPlayer->GetLevel();

	//メッセージウインドウの初期化
	m_pMessageWindow ->Init();


	//-----アイテムウィンドウ-----
	//アイテムカーソルの初期化
	m_pInventoryCursor->Init();
	//コマンドウインドウの初期化
	m_pCommandWindow ->Init();
	//コマンドカーソルの初期化
	m_pCommandCursor ->Init();

	//-----装備ウィンドウ-----
	//装備カーソル
	m_pEquipmentInventoryCursor ->Init();
	//装備コマンドウィンドウ
	m_pEquipmentCommandWindow ->Init();
	//装備コマンドカーソル
	m_pEquipmentCommandCursor ->Init();

	//ワザウィンドウカーソル初期化
	m_pTrickWindowCursor ->Init();

	//初期配置エネミーの設定
	m_pEnemyGenerator ->MakeEnemy();

	//初期配置アイテムの設定
	m_pFieldGenerator->MakeItem();

	//配列情報から、オブジェクトを置くべき位置にオブジェクトを設置
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
		{

			if(CMapData::Get_TerrainMapSituation(i,j) == IN_THE_WALL)
				m_pFieldObjMaker->PutObj(MODEL_TREE,i,j);

			if(CMapData::Get_TerrainMapSituation(i,j) == STAIRS)
				m_pFieldObjMaker->PutObj(MODEL_STAIRS,i,j);
		}
	}

	//フェードの状態をフェードインに設定
	CFade::ChangeState(FADEMODE_IN);
	//ユニットを一時行動不能状態に設定
	CUnitManager::ChangeMoveCanFlg(false);
}
//---------------------------------------------------------------------------------------
//全オブジェクト破棄
//---------------------------------------------------------------------------------------
void CGameScene::FinObj()
{
	//途中でリストが変わる可能性を考慮し、退避用ポインタを持つ

	//各マネージャーで管理するオブジェクトの終了処理を行う
	CUnitManager::Fin();
	CItemManager::Fin();
	CMapObjManager::Fin();
	CParticleManager::Fin();
	CEffectObjManager::Fin();

	//メッセージウインドウの終了処理
	m_pMessageWindow ->Fin();

	//マップデータの終了処理
	m_pMap ->Fin();


	//-----アイテムウィンドウ-----
	//インベントリ終了
	//m_pInventory ->Fin();
	//アイテムカーソルの終了
	m_pInventoryCursor ->Fin();
	//コマンドウインドウの終了処理
	m_pCommandWindow ->Fin();
	//コマンドカーソルの終了処理
	m_pCommandCursor ->Fin();

	//-----装備ウィンドウ-----
	//装備ウィンドウ終了処理
	//m_pEquipmentInventory ->Fin();
	//装備カーソル終了処理
	m_pEquipmentInventoryCursor->Fin();
	//装備コマンドウィンドウ終了処理
	m_pEquipmentCommandWindow ->Fin();
	//装備コマンドカーソル終了処理
	m_pEquipmentCommandCursor ->Fin();

	//-----技ウィンドウカーソル-----
	m_pTrickWindowCursor ->Fin();
}
//---------------------------------------------------------------------------------------
//全オブジェクト更新
//---------------------------------------------------------------------------------------
void CGameScene::UpdateObj()
{
	//マップの再生成フラグが立っていたら処理
	if(m_MapMake && m_OldMapMake)
	{
		//フェードアウトフラグを立てる
		m_pFade->ChangeState(FADEMODE_OUT);

		//マップデータの再生成
		CMapData::MapGeneration();

		//フィールドオブジェクト削除
		CMapObjManager::Fin();
		//エネミーオブジェクト削除
		CEnemyManager::Fin();
		//アイテムオブジェクトの削除
		CItemManager::Fin();
		//パーティクルオブジェクトの削除
		CParticleManager::Fin();
		//エフェクトオブジェクトの削除
		CEffectObjManager::Fin();
		
		//配列情報から、オブジェクトを置くべき位置にオブジェクトを設置
		for(int i = 0;i < MAP_SIZE;i++)
		{
			for(int j = 0;j < MAP_SIZE;j++)
			{

				if(CMapData::Get_TerrainMapSituation(i,j) == IN_THE_WALL)
					m_pFieldObjMaker->PutObj(MODEL_TREE,i,j);

				if(CMapData::Get_TerrainMapSituation(i,j) == STAIRS)
					m_pFieldObjMaker->PutObj(MODEL_STAIRS,i,j);
			}
		}

		//ターンステート初期化
		CTurn::Init();

		//エネミー生成数をリセット
		CEnemyGenerator::ResetMakeEnemyNum();

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
	CUnitManager::Update();
	CItemManager::Update();
	CMapObjManager::Update();
	CParticleManager::Update();
	CEffectObjManager::Update();

	//ジェネレーターの更新
	m_pEnemyGenerator->Update();
	m_pFieldGenerator->Update();

	m_pCamera->Update();
	m_pCamera -> PostUpdate();		//カメラ更新
	m_pMessageWindow ->Update();	//メッセージウインドウ更新
	m_pHPDraw ->Update();			//HP更新
	m_pMap ->UpDate();				//マップデータ更新

	//メニューウィンドウの描画が行われているか？
	if(CMenuWindow::GetDrawFlg())
	{
		//ステータスウィンドウの描画が行われているか？
		if(!CStatesWindow::GetDrawFlg())
		{
			//メニューウィンドウのセレクトを更新
			m_pMenuSelect ->Update();
			//メニューウィンドウの入力更新
			m_pMenuWindow ->Update();
		}
	}
	//ステータスウィンドウの更新(キー入力の更新)
	m_pStatesWindow ->Update();

	//-----アイテムウィンドウ-----
	//アイテムウインドウの描画処理がされているか判別を行う
	if(CInventory::GetDrawFlg())
	{
		//ウインドウカーソルの更新
		m_pInventoryCursor->Update();
	}

	//コマンドウインドウが描画されているか判別を行う
	if(m_pCommandWindow ->GetDrawFlg())
	{
		//コマンドウインドウの更新
		m_pCommandWindow->UpDate();
		//コマンドカーソルの更新
		m_pCommandCursor->Update();
	}

	//-----装備ウィンドウ-----
	
	//装備ウインドウの描画処理がされているか判別を行う
	if(CEquipmentInventory::GetDrawFlg())
	{
		//装備ウインドウカーソルの更新
		m_pEquipmentInventoryCursor->Update();
	}

	//装備コマンドウインドウが描画されているか判別を行う
	if(m_pEquipmentCommandWindow ->GetDrawFlg())
	{
		//装備ウインドウの更新
		m_pEquipmentCommandWindow->UpDate();
		//装備カーソルの更新
		m_pEquipmentCommandCursor->Update();
	}

	//プレイヤーの技ウィンドウの描画フラグを確認
	if(m_pPlayer ->GetPlayerTrickWindowFlg())
	{
		//技ウィンドウのカーソルを更新
		m_pTrickWindowCursor->Update();
	}

	//ステータス画像の更新
	m_pStatesCharacter->Update(m_pPlayer ->GetStatesMode());

	//ステータスウィンドウのサイズの更新
	m_pStatesWindow->WindowSizeUpdate();

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
			CUnitManager::ChangeMoveCanFlg(true);
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
		CFade::ChangeState(FADEMODE_NON);
	}

	// ミニマップの更新
	m_pMiniMap->Update();
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
	CMapObjManager::Draw(false);
	CItemManager::Draw();
	CUnitManager::Draw();
	CEffectObjManager::Draw();
	
	pD ->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);

	pD ->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);

	pD ->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//Zバッファレンダリング計算無効化
	pD ->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	//透明描画
	//フィールド上のオブジェクトの半透明のオブジェクトのみ描画する
	CMapObjManager::Draw(true);
	CParticleManager::Draw();

	pD ->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);

	
	//Zバッファレンダリング計算有効化
	pD ->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	
	//Zバッファの無効
	pD->SetRenderState( D3DRS_ZENABLE , FALSE );

	//メッセージウインドウ描画
	m_pMessageWindow -> Draw();

	//ミニマップの描画
	m_pMiniMap->Draw();

	//メニューウィンドウの描画フラグが立っているか確認
	if(CMenuWindow::GetDrawFlg())
	{
		//メニューウィンドウの背景描画
		m_pMenuWindowBack -> Draw();
		//セレクトメニューテクスチャ描画
		m_pMenuSelect ->Draw();
		//メニューウィンドウテクスチャ描画
		m_pMenuWindow ->Draw();
	}

	//操作説明描画
	m_pOperation ->Draw();

	//-----アイテムウィンドウ-----

	//アイテムウインドウが描画処理を行うか判別する
	if(CInventory::GetDrawFlg())
	{
		//インベントリ(アイテムウインドウ)の描画
		m_pPlayer ->DrawInventory();
		//アイテムカーソルの描画
		m_pInventoryCursor->Draw();
	}
	//コマンドカーソルが描画処理を行うか判別を行う
	if(m_pCommandWindow ->GetDrawFlg())
	{
		//コマンドウインドウ描画
		m_pCommandWindow ->Draw();
		//コマンドカーソルの描画
		m_pCommandCursor ->Draw();
	}

	//-----装備ウィンドウ-----

	//装備ウインドウが描画処理を行うか判別する
	if(CEquipmentInventory::GetDrawFlg())
	{
		//装備ウインドウの描画
		m_pPlayer ->DrawEquipment();
		//装備カーソルの描画
		m_pEquipmentInventoryCursor->Draw();
	}
	//コマンドカーソルが描画処理を行うか判別を行う
	if(m_pEquipmentCommandWindow ->GetDrawFlg())
	{
		//装備コマンドウインドウ描画
		m_pEquipmentCommandWindow ->Draw();
		//装備コマンドカーソルの描画
		m_pEquipmentCommandCursor ->Draw();
	}
	//ステータスのウィンドウを描画する
	m_pStatesWindow -> Draw();
	//HP描画
	m_pHPDraw ->Draw();
	//キャラクターウィンドウの描画
	m_pStatesCharacter ->Draw();

	//階層数の描画
	CMapData::DrawHierarchyNum();
	//プレイヤーレベルの表示
	m_pPlayer->DrawLevel();

	//ステータスウィンドウの描画フラグが立っていたら描画
	if(m_pStatesWindow->GetDrawFlg())
	{
		//ステータスの文字を描画する
		m_pStatesFont ->Draw();
		//ステータスの数値を描画する
		m_pStatesValue ->Draw();
	}

	//プレイヤーの技ウィンドウの描画フラグを確認
	if(m_pPlayer ->GetPlayerTrickWindowFlg())
	{
		//技ウィンドウを描画
		m_pPlayer ->DrawTrick();
		//技ウィンドウのカーソルを描画
		m_pTrickWindowCursor->Draw();
	}
	//フェードの描画
	m_pFade ->Draw();
	//フェードの状態を格納
	int FadeMode = m_pFade->GetFadeState();
	//フェードの状態が、フェードインの場合、階層数を表示
	if(FadeMode == FADEMODE_IN)
		m_pHierarchiNum->Draw();
}
//ゲームのクリア状況を変更する
void CGameScene::GameClearStateChange(int Change)
{
	m_nGameClaer = Change;
}

//=======================================================================================
//	End of File
//=======================================================================================