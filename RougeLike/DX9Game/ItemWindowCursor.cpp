#include "ItemWindowCursor.h"
#include "Graphics.h"
#include "Input.h"
#include "ItemWindow.h"
#include "ItemCommandWindow.h"

#include "TextureManager.h"
//---------------------------------------------------------------------------------------
//マクロ定義
//---------------------------------------------------------------------------------------


//ウインドウサイズ
#define WINDOW_WIDHT  300
#define WINDOW_HEIGHT  30

CItemWindowCursor* CItemWindowCursor::m_pItemWindowCursor = NULL;

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CItemWindowCursor::CItemWindowCursor(void)
{
	//ボタン入力経過時間を初期化する
	m_nInterval = 0;
	//選択中のカーソル番号を初期化する
	m_nNumber = 0;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//ポリゴン情報の設定
	SetVertex();

	//ポリゴン位置情報の設定
	SetPos();
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CItemWindowCursor::~CItemWindowCursor(void)
{
	//ボタン入力経過時間を初期化する
	m_nInterval =  0;
	//選択中のカーソル番号を初期化する
	m_nNumber = 0;
}
//---------------------------------------------------------------------------------------
//自身の実態の作成
//---------------------------------------------------------------------------------------
void CItemWindowCursor::Create()
{
	//実体がまだ存在していない場合、作成を行う
	if (!m_pItemWindowCursor)
	{
		m_pItemWindowCursor = new CItemWindowCursor;
	}
}//---------------------------------------------------------------------------------------
//自身の実態の削除
//---------------------------------------------------------------------------------------
void CItemWindowCursor::Delete()
{
	//自身の実態の確認
	if (m_pItemWindowCursor)
	{
		//実体があれば、削除
		delete m_pItemWindowCursor;
		//中身をきれいに
		m_pItemWindowCursor = NULL;
	}
}//---------------------------------------------------------------------------------------
//自身のポインタを渡す
//---------------------------------------------------------------------------------------
CItemWindowCursor* CItemWindowCursor::GetPointer()
{
	//念のためポインタを作成
	Create();
	return m_pItemWindowCursor;
}

//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CItemWindowCursor::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
		
	// アルファ・ブレンディングを行う
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// 透過処理を行う
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//頂点フォーマットの設定
	pDevice ->SetFVF(FVF_VERTEX_2D);

	//テクスチャセット
	pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_SELECT_WINDOW));
	//ポリゴンの描画
	//頂点情報を外部が持っている場合Up
	//そのほかはprimitive
	pDevice -> DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,          //プリミティブの種類List（三角形描く）Strip(つなげて作る)
		NUM_POLYGON,                 //ポリゴン数
		m_aVertex,            //配列の先頭アドレス
		sizeof(VERTEX_2D)            //データの大きさ
		);
}

//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CItemWindowCursor::Update()
{
	//ボタン入力からの経過時間を加算
	m_nInterval++;
	if((CInput::GetKeyTrigger(DIK_W) || (CInput::GetJoyAxis(0, JOY_Y) <= -JoyMoveCap)) && m_nInterval >= ButtonIntervalTime)
	{
		//上に移動
		m_nNumber --;

		//ループ
		if(m_nNumber < 0)
			m_nNumber = ITEM_NUM_MAX - 1;
		//位置情報再設定
		SetPos();

		//ボタン入力経過時間を0に
		m_nInterval = 0;
	}

	if((CInput::GetKeyTrigger(DIK_S) || (CInput::GetJoyAxis(0,JOY_Y) >= JoyMoveCap)) && m_nInterval >= ButtonIntervalTime)
	{
		//下に移動
		m_nNumber ++;

		//ループ
		m_nNumber%= ITEM_NUM_MAX;

		//位置情報を再設定
		SetPos();

		//ボタン入力経過時間を0に
		m_nInterval = 0;
	}
	//横を選択した場合、アイテムウィンドウのほうへカーソル更新を移す
	if((CInput::GetKeyTrigger(DIK_D) || CInput::GetKeyTrigger(DIK_A) || abs((long)CInput::GetJoyAxis(0, JOY_X)) >= JoyMoveCap) && m_nInterval >= ButtonIntervalTime)
	{
		//装備アイテムウィンドウの更新
		m_pItemWindow->UpdateFlgChange(false);
		//ボタン入力経過時間を0に
		m_nInterval = 0;
	}
	
}

//---------------------------------------------------------------------------------------
//ポリゴン情報設定
//---------------------------------------------------------------------------------------
void CItemWindowCursor::SetVertex ()
{	
	//位置情報設定
	m_aVertex[0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (m_nNumber + 1)				+ WINDOW_HEIGHT,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH				 ,(float)WINDOW_HEIGHT * (m_nNumber + 1)					+ WINDOW_HEIGHT,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (m_nNumber + 1) + WINDOW_HEIGHT+ WINDOW_HEIGHT,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH				 ,(float)WINDOW_HEIGHT * (m_nNumber + 1) + WINDOW_HEIGHT	+ WINDOW_HEIGHT,0.0f);

	//パースペクティブ設定?
	m_aVertex[0].rhw = 1.0f;
	m_aVertex[1].rhw = 1.0f;
	m_aVertex[2].rhw = 1.0f;
	m_aVertex[3].rhw = 1.0f;

	//頂点カラーの設定
	m_aVertex[0].col = D3DCOLOR_RGBA(255,255,255,255);
	m_aVertex[1].col = D3DCOLOR_RGBA(255,255,255,255);
	m_aVertex[2].col = D3DCOLOR_RGBA(255,255,255,255);
	m_aVertex[3].col = D3DCOLOR_RGBA(255,255,255,255);

	//ポリゴンとテクスチャの頂点を対応させる
	m_aVertex[0].tex = D3DXVECTOR2(0.0f,0.0f);
	m_aVertex[1].tex = D3DXVECTOR2(1.0f,0.0f);
	m_aVertex[2].tex = D3DXVECTOR2(0.0f,1.0f);
	m_aVertex[3].tex = D3DXVECTOR2(1.0f,1.0f);
}

//---------------------------------------------------------------------------------------
//ポリゴン位置設定
//---------------------------------------------------------------------------------------
void CItemWindowCursor::SetPos()
{
	//位置情報設定
	m_aVertex[0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (m_nNumber + 1)				 + WINDOW_HEIGHT,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (m_nNumber + 1)					 + WINDOW_HEIGHT,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (m_nNumber + 1) + WINDOW_HEIGHT + WINDOW_HEIGHT,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (m_nNumber + 1) + WINDOW_HEIGHT	 + WINDOW_HEIGHT,0.0f);
}
//---------------------------------------------------------------------------------------
//選択中のアイテム番号を返す
//---------------------------------------------------------------------------------------
int CItemWindowCursor::GetItemNum()
{
	return m_nNumber;
}

//---------------------------------------------------------------------------------------
//メンバ変数のポインタを設定する
//---------------------------------------------------------------------------------------
void CItemWindowCursor::SetPointer()
{
	//ポインタの取得
	m_pItemCommandWindow = CItemCommandWindow::GetPointer();
	m_pItemWindow = CItemWindow::GetPointer();
}
