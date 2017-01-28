#include "TrickWindow.h"
#include "Graphics.h"
#include "Input.h"
#include <tchar.h>
#include "Turn.h"
#include "TextureManager.h"
#include "TrickWindowCursor.h"
#include "Player.h"
#include "MenuWindow.h"
//---------------------------------------------------------------------------------------
//マクロ定義
//---------------------------------------------------------------------------------------

//ウインドウサイズ
#define WINDOW_WIDHT 300
#define WINDOW_HEIGHT 30

//---------------------------------------------------------------------------------------
//静的メンバ定義
//---------------------------------------------------------------------------------------
bool				CTrickWindow::m_bDrawFlg;				//描画フラグ
CTrickWindowCursor	CTrickWindow::m_TrickCursor;			//選択しているアイテムウインドウの取得
//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CTrickWindow::CTrickWindow(void)
{
	//メンバ初期化
	m_bDrawFlg = false;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//情報格納用フォントを設定
	//フォントへのポインタを初期化
	m_Font = NULL;

	//フォントの設定
	D3DXCreateFont(pDevice, 12, 12, 1, 0, FALSE, SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL,&m_Font);

	//ポリゴン情報の設定
	SetVertex();

	//フォント表示位置の設定
	SetFontPos();

	//IDの設定m_Trick
	for(int i = 0;i < TRICK_NAME_MAX;i++)
	{
		//IDの設定
		m_Trick[i].SetID(i);
		//名前の設定
		m_Trick[i].FindName(i);
		//効果の種類の設定
		m_Trick[i].EffectSetting(i);
		//技範囲の設定
		m_Trick[i].SetRange(i);
	}
	//技の効果の設定
	m_Trick[TRICK_NAME_1].SetValue(5);
	m_Trick[TRICK_NAME_2].SetValue(5);
	m_Trick[TRICK_NAME_3].SetValue(5);
	m_Trick[TRICK_NAME_4].SetValue(5);
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CTrickWindow::~CTrickWindow(void)
{
}

//---------------------------------------------------------------------------------------
//初期化
//---------------------------------------------------------------------------------------
void CTrickWindow::Init()
{
}
//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void CTrickWindow::Fin()
{

}
//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CTrickWindow::UpDate()
{
	//技選択中のみ操作可能
	if(m_bDrawFlg)
	{
		//Lで決定
		if(CInput::GetKeyTrigger(DIK_L))
		{
			//ここで戦闘ステートへ移動

			//技を使用
			CPlayer::SetState(CTurn::GAME_STATE_ATTACK);
			
			//自身のフラグを倒す
			m_bDrawFlg = false;

			//メニューの描画フラグを倒す
			CMenuWindow::ChangDrawFlg();
		}

		//KとIキーで戻る
		if(CInput::GetKeyTrigger(DIK_K))
		{
			//自身のフラグを倒す
			m_bDrawFlg = false;
		}
	}
}
//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CTrickWindow::Draw()
{
		_TCHAR* TrickName;		//描画用に文字を格納する
		int		TrickID;			//描画の可否をIDで判別する

		//デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
		
		// アルファ・ブレンディングを行う
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		// 透過処理を行う
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//頂点フォーマットの設定
		pDevice ->SetFVF(FVF_VERTEX_2D);

		//技ウインドウ分描画
		for(int i = 0;i < ITEM_NUM_MAX;i++)
		{
			TrickName = m_Trick[i].GetName();
			TrickID	= m_Trick[i].GetID();

			//テクスチャセット
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_WINDOW));

			//ポリゴンの描画
			//頂点情報を外部が持っている場合Up
			//そのほかはprimitive
			pDevice -> DrawPrimitiveUP(
				D3DPT_TRIANGLESTRIP,          //プリミティブの種類List（三角形描く）Strip(つなげて作る)
				NUM_POLYGON,                 //ポリゴン数
				m_aVertex[i],            //配列の先頭アドレス
				sizeof(VERTEX_2D)            //データの大きさ
				);

			// テキスト描画
			m_Font->DrawText(NULL,TrickName,-1, &m_Pos[i], DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0x00, 0xff));
		}

}
//---------------------------------------------------------------------------------------
//ポリゴン情報を埋める
//---------------------------------------------------------------------------------------
void CTrickWindow::SetVertex()
{
	for(int i = 0;i < TRICK_NUM_MAX;i++)
	{
		//位置情報設定
		m_aVertex[i][0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (i + 1)					,0.0f);
		m_aVertex[i][1].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (i + 1)					,0.0f);
		m_aVertex[i][2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	,0.0f);
		m_aVertex[i][3].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	,0.0f);

		//パースペクティブ設定?
		m_aVertex[i][0].rhw = 1.0f;
		m_aVertex[i][1].rhw = 1.0f;
		m_aVertex[i][2].rhw = 1.0f;
		m_aVertex[i][3].rhw = 1.0f;

		//頂点カラーの設定
		m_aVertex[i][0].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i][1].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i][2].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i][3].col = D3DCOLOR_RGBA(255,255,255,255);

		//ポリゴンとテクスチャの頂点を対応させる
		m_aVertex[i][0].tex = D3DXVECTOR2(0.0f,0.0f);
		m_aVertex[i][1].tex = D3DXVECTOR2(1.0f,0.0f);
		m_aVertex[i][2].tex = D3DXVECTOR2(0.0f,1.0f);
		m_aVertex[i][3].tex = D3DXVECTOR2(1.0f,1.0f);
	}
}
//---------------------------------------------------------------------------------------
//フォント情報の設定
//---------------------------------------------------------------------------------------
void CTrickWindow::SetFontPos()
{
	for(int i = 0;i < TRICK_NUM_MAX;i++)
	{
		m_Pos[i].left	= (LONG)(m_aVertex[i][0].pos.x + 50.0f);
		m_Pos[i].top	= (LONG)(m_aVertex[i][1].pos.y + 10.0f);
		m_Pos[i].right	= (LONG)m_aVertex[i][3].pos.x;
		m_Pos[i].bottom	= (LONG)m_aVertex[i][2].pos.y;
	}
}
//---------------------------------------------------------------------------------------
//描画フラグを外部からON/OFFする
//---------------------------------------------------------------------------------------
void CTrickWindow::DrawFlgChange()
{
	m_bDrawFlg = !m_bDrawFlg;
}
//---------------------------------------------------------------------------------------
//指定された技の効果ジャンルを返却する
//---------------------------------------------------------------------------------------
int CTrickWindow::GetEffect(int Receipt)
{
	return m_Trick[Receipt].GetType();
}
//---------------------------------------------------------------------------------------
//指定された技の効能を返却する
//---------------------------------------------------------------------------------------
int CTrickWindow::GetEffectValue(int Receipt)
{
	//技のIDによって効果を変更する
	switch(m_Trick[Receipt].GetID())
	{
		//1
	case TRICK_NAME_1:
		return EFFECT_NON;
		break;
		//2
	case TRICK_NAME_2:
		return m_Trick[Receipt].GetValue();
		break;
		//3
	case TRICK_NAME_3:
		return m_Trick[Receipt].GetValue();
		break;
		//4
	case TRICK_NAME_4:
		return m_Trick[Receipt].GetValue();
		break;

		//バグ検査用
	default:
		//効果なし
		return -99;
		break;
	}
}

//---------------------------------------------------------------------------------------
//指定された技の範囲を返す
//---------------------------------------------------------------------------------------
int CTrickWindow::GetRange(int Receipt)
{
	//指定された係数が、配列内か確認する
	if(Receipt < TRICK_NAME_MAX)
		//配列内であれば、正規の値を取得し、渡す
		return m_Trick[Receipt].GetRange();
	else
		//配列内でなければ、正面の値を渡す。
		return TRICK_RANGE_FRONT;
}