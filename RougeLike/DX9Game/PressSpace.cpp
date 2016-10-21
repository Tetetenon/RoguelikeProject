#include "PressSpace.h"
#include "TextureManager.h"

//点滅時間
#define FLASHTIME 30

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CPressSpace::CPressSpace(void)
{
	//使用するテクスチャIDの設定
	m_nTextureID = TEXTURE_PRESS_SPACE;

	//描画フラグの初期化
	m_bAlphaSwitch = true;

	//描画時間の初期化
	m_nFlashTimer = 0;
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CPressSpace::~CPressSpace(void)
{
}


//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CPressSpace::Update()
{
	//テクスチャのアルファ値をフラグの状態から、加算減算分岐
	if(m_bAlphaSwitch)
	{
		//現在の点滅時間を加算
		m_nFlashTimer += 3;

		//限界値調整
		if(m_nFlashTimer >= 255)
			m_nFlashTimer = 255;
	}
	else
	{
		m_nFlashTimer -= 3;

		//限界値調整
		if(m_nFlashTimer <= 0)
			m_nFlashTimer = 0;
	}

	//頂点カラーの設定
	m_aVertex[0].col = D3DCOLOR_RGBA(255,255,255,m_nFlashTimer);
	m_aVertex[1].col = D3DCOLOR_RGBA(255,255,255,m_nFlashTimer);
	m_aVertex[2].col = D3DCOLOR_RGBA(255,255,255,m_nFlashTimer);
	m_aVertex[3].col = D3DCOLOR_RGBA(255,255,255,m_nFlashTimer);

	//限界値になった場合、フラグを反転
	if(m_nFlashTimer >= 255 || m_nFlashTimer <= 0)
	{
		//フラグを反転させ、限界値を超えないようにする
		m_bAlphaSwitch = !m_bAlphaSwitch;
	}
}