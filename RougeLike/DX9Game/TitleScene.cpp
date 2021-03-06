#include "TitleScene.h"
#include "define.h"
#include "Input.h"
#include "GameState.h"
#include "Fade.h"

bool CTitleScene::m_bCreate = false;		//生成成功フラグ

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CTitleScene::CTitleScene(void):
m_pGraphics(NULL)
{
	//フェードの実態を作成
	CFade::Create();

	//タイトルテクスチャ描画クラスの実体を作成
	m_pTitle = new CTitle();
	//フェードインクラス作成
	m_pFade = CFade::GetPointer();
	//プレススペース作成
	m_pPress = new CPressSpace();
	//生成成功
	m_bCreate = true;
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CTitleScene::~CTitleScene(void)
{
	//生成に成功していたら削除開放
	if(m_bCreate)
	{
		//フェードの実態を削除
		CFade::Delete();

		//タイトルポインタの中身削除、解放
		delete m_pTitle;
		//プレススペースクラスの中身の開放
		delete m_pPress;

		//生成状態偽
		m_bCreate = false;
	}
}

//---------------------------------------------------------------------------------------
//タイトルシーンの作成
//---------------------------------------------------------------------------------------
CTitleScene* CTitleScene::Create(CGraphics* pGraph)
{
	//自身の作成
	CTitleScene* pTitleScene = new CTitleScene();

	//作成できたか確認
	if (pTitleScene) 
	{
		//初期化を行う
		if (!pTitleScene->Initialize(pGraph))
		{
			//初期化処理に失敗したら削除する
			SAFE_DELETE(pTitleScene);
		}
	}

	//成功したらタイトルシーンのポインタ、失敗時はNULL
	return pTitleScene;
}

//---------------------------------------------------------------------------------------
//タイトルシーンの開放
//---------------------------------------------------------------------------------------
void CTitleScene::Release()
{
	//終了処理
	Finalize();

	if(m_bCreate)
	{
		//自身の削除
		delete this;
	}
}

//---------------------------------------------------------------------------------------
//レンダリング処理
//---------------------------------------------------------------------------------------
void CTitleScene::Render()
{
	//描画開始
	if (m_pGraphics->Begin()) 
	{
		Draw();					// 描画処理

		m_pGraphics->End();		// 描画終了
	}
	m_pGraphics->SwapBuffer();		// バックバッファ入替
}
//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CTitleScene::Update()
{
	//入力更新
	CInput::Update();

	//プレススペース更新
	m_pPress ->Update();

	//SPACEを押されていたら、ゲームシーンへ移行
	if(CInput::GetKeyTrigger(DIK_SPACE) || CInput::GetJoyTrigger(0,3))
	{
		//フェードイン開始フラグを立てる
		m_pFade->ChangeState(FADEMODE_OUT);
	}
	//フェードインの更新
	m_pFade ->Update();
	//フェードインが完了したら、ステートを変更する
	if(m_pFade ->GetFadeAlpha() >= 255)
	{
		CGameState::StateUpdate(STATE_GAME);
	}
}

//---------------------------------------------------------------------------------------
//初期化処理
//---------------------------------------------------------------------------------------
bool CTitleScene::Initialize(CGraphics* pGraph)
{
	//グラフィックデバイスのポインタ取得
	m_pGraphics = pGraph;

	//成功
	return true;
}
//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void CTitleScene::Finalize()
{
	
}
//---------------------------------------------------------------------------------------
//描画処理
//---------------------------------------------------------------------------------------
void CTitleScene::Draw()
{
	// 半透明部分描画
	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();

	//半透明描画設定
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//タイトルテクスチャの描画
	m_pTitle->Draw();

	//プレススペース描画
	m_pPress ->Draw();
	
	//フェード描画
	m_pFade ->Draw();
	
	//描画設定を元に戻す(不透明)
	pD->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}