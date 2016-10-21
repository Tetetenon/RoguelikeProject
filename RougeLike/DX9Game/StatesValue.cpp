#include "StatesValue.h"
#include "Graphics.h"
#include "TextureManager.h"


//各ステータスデータの格納
int CStatesValue::m_nStatesValue[STATES_FONT_MAX];
//ポリゴン情報
VERTEX_2D	CStatesValue::m_aVertex[STATES_FONT_MAX * 2][NUM_VERTEX];

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CStatesValue::CStatesValue(void)
{
	//ポリゴン情報設定
	SetVertex();
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CStatesValue::~CStatesValue(void)
{
}
//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CStatesValue::Draw ()
{
	int nParNum;	//ステータス数値格納

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	
	// アルファ・ブレンディングを行う
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// 透過処理を行う
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//頂点フォーマットの設定
	pDevice ->SetFVF(FVF_VERTEX_2D);

	//アイテムウインドウ分描画
	for(int i = 0;i < STATES_FONT_MAX * 2;i++)
	{
		//配列係数によってステータス数値を変更する
		nParNum = m_nStatesValue[(int)i / (int)2];
		int j = (1 + (9 * ((1 - (i % 2)) % 2)));
		//表示する桁数値をだす
		nParNum = nParNum / j;

		nParNum %= 10;

		//表示する数値に応じてテクスチャを変更する
		switch(nParNum)
		{
		case 0:
			//テクスチャセット
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_0));
			break;
		case 1:
			//テクスチャセット
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_1));
			break;
		case 2:
			//テクスチャセット
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_2));
			break;
		case 3:
			//テクスチャセット
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_3));
			break;
		case 4:
			//テクスチャセット
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_4));
			break;
		case 5:
			//テクスチャセット
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_5));
			break;
		case 6:
			//テクスチャセット
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_6));
			break;
		case 7:
			//テクスチャセット
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_7));
			break;
		case 8:
			//テクスチャセット
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_8));
			break;
		case 9:
			//テクスチャセット
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_9));
			break;
		}

		//ポリゴンの描画
		//頂点情報を外部が持っている場合Up
		//そのほかはprimitive
		pDevice -> DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP,          //プリミティブの種類List（三角形描く）Strip(つなげて作る)
			NUM_POLYGON,                 //ポリゴン数
			m_aVertex[i],            //配列の先頭アドレス
			sizeof(VERTEX_2D)            //データの大きさ
			);
	}

}

//---------------------------------------------------------------------------------------
//ポリゴン情報の設定
//---------------------------------------------------------------------------------------
void CStatesValue::SetVertex()
{
	for(int i = 0;i < STATES_FONT_MAX * 2;i += 2)
	{
		//位置情報設定
		m_aVertex[i][0].pos		= D3DXVECTOR3((float)130.0f,(float)185.0f + FontScale * (i / 2) + (FontClearance),0.0f);
		m_aVertex[i][1].pos		= D3DXVECTOR3((float)180.0f,(float)185.0f + FontScale * (i / 2) + (FontClearance),0.0f);
		m_aVertex[i][2].pos		= D3DXVECTOR3((float)130.0f,(float)185.0f + FontScale * (i / 2) + (FontClearance) + FontScale,0.0f);
		m_aVertex[i][3].pos		= D3DXVECTOR3((float)180.0f,(float)185.0f + FontScale * (i / 2) + (FontClearance) + FontScale,0.0f);
		//位置情報設定
		m_aVertex[i + 1][0].pos = D3DXVECTOR3((float)180.0f,(float)185.0f + FontScale * (i / 2) + (FontClearance),0.0f);
		m_aVertex[i + 1][1].pos = D3DXVECTOR3((float)230.0f,(float)185.0f + FontScale * (i / 2) + (FontClearance),0.0f);
		m_aVertex[i + 1][2].pos = D3DXVECTOR3((float)180.0f,(float)185.0f + FontScale * (i / 2) + (FontClearance) + FontScale,0.0f);
		m_aVertex[i + 1][3].pos = D3DXVECTOR3((float)230.0f,(float)185.0f + FontScale * (i / 2) + (FontClearance) + FontScale,0.0f);
		
		//パースペクティブ設定?
		m_aVertex[i][0].rhw = 1.0f;
		m_aVertex[i][1].rhw = 1.0f;
		m_aVertex[i][2].rhw = 1.0f;
		m_aVertex[i][3].rhw = 1.0f;

		//パースペクティブ設定?
		m_aVertex[i + 1][0].rhw = 1.0f;
		m_aVertex[i + 1][1].rhw = 1.0f;
		m_aVertex[i + 1][2].rhw = 1.0f;
		m_aVertex[i + 1][3].rhw = 1.0f;

		//頂点カラーの設定
		m_aVertex[i][0].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i][1].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i][2].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i][3].col = D3DCOLOR_RGBA(255,255,255,255);

		//頂点カラーの設定
		m_aVertex[i + 1][0].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i + 1][1].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i + 1][2].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i + 1][3].col = D3DCOLOR_RGBA(255,255,255,255);

		//ポリゴンとテクスチャの頂点を対応させる
		m_aVertex[i][0].tex = D3DXVECTOR2(0.0f,0.0f);
		m_aVertex[i][1].tex = D3DXVECTOR2(1.0f,0.0f);
		m_aVertex[i][2].tex = D3DXVECTOR2(0.0f,1.0f);
		m_aVertex[i][3].tex = D3DXVECTOR2(1.0f,1.0f);

		//ポリゴンとテクスチャの頂点を対応させる
		m_aVertex[i + 1][0].tex = D3DXVECTOR2(0.0f,0.0f);
		m_aVertex[i + 1][1].tex = D3DXVECTOR2(1.0f,0.0f);
		m_aVertex[i + 1][2].tex = D3DXVECTOR2(0.0f,1.0f);
		m_aVertex[i + 1][3].tex = D3DXVECTOR2(1.0f,1.0f);
	}

}