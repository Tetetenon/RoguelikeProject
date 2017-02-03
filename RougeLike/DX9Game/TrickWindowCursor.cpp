#include "TrickWindowCursor.h"
#include "Graphics.h"
#include "Input.h"

#include "TextureManager.h"
//---------------------------------------------------------------------------------------
//マクロ定義
//---------------------------------------------------------------------------------------



//ウインドウサイズ
#define WINDOW_WIDHT  300
#define WINDOW_HEIGHT  30

int		CTrickWindowCursor::m_Number = 0;				//現在選択しているアイテムが何番目の物かを管理する


//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CTrickWindowCursor::CTrickWindowCursor(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//ポリゴン情報の設定
	SetVertex();

	//ポリゴン位置情報の設定
	SetPos();

	//ボタン入力経過時間を0にする
	m_nInterval = 0;
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CTrickWindowCursor::~CTrickWindowCursor(void)
{
	//ボタン入力経過時間を0にする
	m_nInterval = 0;
}

//---------------------------------------------------------------------------------------
//初期化
//---------------------------------------------------------------------------------------
void CTrickWindowCursor::Init()
{

}
//---------------------------------------------------------------------------------------
//終了
//---------------------------------------------------------------------------------------
void CTrickWindowCursor::Fin()
{

}

//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CTrickWindowCursor::Draw()
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
void CTrickWindowCursor::Update()
{
	//ボタン入力経過時間を加算
	m_nInterval ++;

	//アイテム選択中のみ操作可能
	if(CTrickWindow::GetDrawFlg())
	{
		if((CInput::GetKeyTrigger(DIK_W) || (CInput::GetJoyAxis(0,JOY_Y) <= -JoyMoveCap)) && m_nInterval >= ButtonIntervalTime)
		{
			//上に移動
			m_Number --;

			//ループ
			if (m_Number < 0)
				m_Number = TRICK_NUM_MAX - 1;
			//位置情報再設定
			SetPos();

			//ボタン入力からの経過時間を0にする
			m_nInterval = 0;
		}

		if((CInput::GetKeyTrigger(DIK_S) || (CInput::GetJoyAxis(0,JOY_Y) >= JoyMoveCap)) && m_nInterval >= ButtonIntervalTime)
		{
			//下に移動
			m_Number ++;
			//ループ
			m_Number %= TRICK_NUM_MAX;

			//位置情報を再設定
			SetPos();

			//ボタン入力からの経過時間を0にする
			m_nInterval = 0;
		}
	}
}

//---------------------------------------------------------------------------------------
//ポリゴン情報設定
//---------------------------------------------------------------------------------------
void CTrickWindowCursor::SetVertex ()
{	
	//位置情報設定
	m_aVertex[0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (m_Number + 1)					,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (m_Number + 1)					,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (m_Number + 1) + WINDOW_HEIGHT	,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (m_Number + 1) + WINDOW_HEIGHT	,0.0f);

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
void CTrickWindowCursor::SetPos()
{
	//位置情報設定
	m_aVertex[0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (m_Number + 1)					,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (m_Number + 1)					,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (m_Number + 1) + WINDOW_HEIGHT	,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (m_Number + 1) + WINDOW_HEIGHT	,0.0f);
}
//---------------------------------------------------------------------------------------
//選択中の技番号を返す
//---------------------------------------------------------------------------------------
int CTrickWindowCursor::GetTrickNum()
{
	return m_Number;
}