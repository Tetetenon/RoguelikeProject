#include "HierarchieNum.h"
#include "Graphics.h"
#include "MapData.h"
#include "TextureManager.h"

#include "Fade.h"

#define NUM_FONT_SIZE (180)

VERTEX_2D	CHierarchieNum::m_aVertex[HIERARCHIENUM][NUM_VERTEX];
//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CHierarchieNum::CHierarchieNum(void)
{
	//ポリゴン情報設定
	SetVertex();
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CHierarchieNum::~CHierarchieNum(void)
{

}

//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CHierarchieNum::Draw()
{
	//階層数を保存
	int HierarchieNum = CMapData::GetHierarchieNum();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	
	// アルファ・ブレンディングを行う
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// 透過処理を行う
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//頂点フォーマットの設定
	pDevice ->SetFVF(FVF_VERTEX_2D);

	for(int i =0 ;i < HIERARCHIENUM;i++)
	{
		if(i == HIERARCHIENUM - 1)
		{
			//テクスチャセット
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_F));
		}
		else
		{
			int nNumTexture = HierarchieNum / (9 * i + 1) % 10;

			//表示する数値に応じてテクスチャを変更する
			switch(nNumTexture)
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
		}
		//アルファ値を設定
		int AlphaNum = 255 - CFade::GetFadeAlpha();
		for(int j = 0;j < HIERARCHIENUM;j++)
		{
			//頂点カラーの設定
			m_aVertex[j][0].col = D3DCOLOR_RGBA(255,255,255,AlphaNum);
			m_aVertex[j][1].col = D3DCOLOR_RGBA(255,255,255,AlphaNum);
			m_aVertex[j][2].col = D3DCOLOR_RGBA(255,255,255,AlphaNum);
			m_aVertex[j][3].col = D3DCOLOR_RGBA(255,255,255,AlphaNum);
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
void CHierarchieNum::SetVertex()
{
	for(int i = 0;i < HIERARCHIENUM;i++)
	{
		//位置情報設定
		m_aVertex[i][0].pos		= D3DXVECTOR3((float)(SCREEN_WIDTH / 2) + (NUM_FONT_SIZE - NUM_FONT_SIZE / 2) - (NUM_FONT_SIZE * i),(float)(SCREEN_HEIGHT / 2) - NUM_FONT_SIZE,0.0f);
		m_aVertex[i][1].pos		= D3DXVECTOR3((float)(SCREEN_WIDTH / 2)	+ (NUM_FONT_SIZE + NUM_FONT_SIZE / 2) - (NUM_FONT_SIZE * i),(float)(SCREEN_HEIGHT / 2) - NUM_FONT_SIZE,0.0f);
		m_aVertex[i][2].pos		= D3DXVECTOR3((float)(SCREEN_WIDTH / 2) + (NUM_FONT_SIZE - NUM_FONT_SIZE / 2) - (NUM_FONT_SIZE * i),(float)(SCREEN_HEIGHT / 2) + NUM_FONT_SIZE,0.0f);
		m_aVertex[i][3].pos		= D3DXVECTOR3((float)(SCREEN_WIDTH / 2)	+ (NUM_FONT_SIZE + NUM_FONT_SIZE / 2) - (NUM_FONT_SIZE * i),(float)(SCREEN_HEIGHT / 2) + NUM_FONT_SIZE,0.0f);
		
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