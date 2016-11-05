#include "GameClearScene.h"
#include "Input.h"
#include "GameState.h"
#include "define.h"

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CGameClearScene::CGameClearScene(void):
m_pGraphics(NULL)
{
	//ゲームクリアクラスの実態生成
	m_GameClear = new CGameClear();
	//プレススペース作成
	m_pPress = new CPressSpace();
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CGameClearScene::~CGameClearScene(void)
{
	//リザルトクラスの実態削除
	delete m_GameClear;
	//プレススペースクラスの中身の開放
	delete m_pPress;
}

//---------------------------------------------------------------------------------------
//リザルトシーンの生成
//---------------------------------------------------------------------------------------
CGameClearScene* CGameClearScene::Create(CGraphics* pGraph)
{
	//リザルトクラスの実態生成
	CGameClearScene* pResualtScene = new CGameClearScene();

	//生成が成功したかどうか
	if (pResualtScene) 
	{
		if (!pResualtScene->Initialize(pGraph))
		{
			//失敗したら解放して安全に処理
			SAFE_DELETE(pResualtScene);
		}
	}
	//リザルトクラスが生成できたか返す
	return pResualtScene;
}

//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void CGameClearScene::Release()
{
	//自身の終了処理
	Finalize();
	//自身の削除
	delete this;
}

//---------------------------------------------------------------------------------------
//レンダリング
//---------------------------------------------------------------------------------------
void CGameClearScene::Render()
{
	if (m_pGraphics->Begin()) 
	{	// 描画開始

		Draw();					// 描画処理

		m_pGraphics->End();		// 描画終了
	}
	m_pGraphics->SwapBuffer();		// バックバッファ入替
}
//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CGameClearScene::UpDate()
{
	//入力情報の更新
	CInput::Update();

	//プレススペース更新
	m_pPress ->Update();

	//もしSPACEが押されていればタイトルシーンへ移行
	if(CInput::GetKeyTrigger(DIK_SPACE))
	{
		CGameState::StateUpdate(STATE_TITLE);
	}
}
//---------------------------------------------------------------------------------------
//初期化処理
//---------------------------------------------------------------------------------------
bool CGameClearScene::Initialize(CGraphics* pGraph)
{
	//デバイスのポインタを設定する
	m_pGraphics = pGraph;

	//成功したことを返す
	return true;
}


//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void CGameClearScene::Finalize()
{

}

//---------------------------------------------------------------------------------------
//描画処理
//---------------------------------------------------------------------------------------
void CGameClearScene::Draw()
{
	// 半透明部分描画
	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//リザルトテクスチャ描画
	m_GameClear->Draw();

	//プレススペース描画
	m_pPress ->Draw();
	
	pD->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}