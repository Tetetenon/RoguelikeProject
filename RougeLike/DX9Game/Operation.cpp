#include "Operation.h"
#include "TextureManager.h"


//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
COperation::COperation(void)
{
	//使用するテクスチャIDの設定
	m_nTextureID = TEXTURE_OPERATION;

	//位置情報の設定
	m_aVertex[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 240.0f , 365.0f ,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(SCREEN_WIDTH -  10.0f , 365.0f ,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 240.0f ,SCREEN_HEIGHT - 5.0f ,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(SCREEN_WIDTH -  10.0f ,SCREEN_HEIGHT - 5.0f ,0.0f);
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
COperation::~COperation(void)
{
}
