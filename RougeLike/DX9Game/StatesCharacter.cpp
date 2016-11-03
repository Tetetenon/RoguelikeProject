#include "StatesCharacter.h"
#include "TextureManager.h"
#include "Unit.h"

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CStatesCharacter::CStatesCharacter(void)
{
	//使用するテクスチャIDの設定
	m_nTextureID = TEXTURE_RED_HOOD;

	//位置情報の設定
	m_aVertex[0].pos = D3DXVECTOR3( 10.0f, 50.0f,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(125.0f, 50.0f,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3( 10.0f,165.0f,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(125.0f,165.0f,0.0f);
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CStatesCharacter::~CStatesCharacter(void)
{
}

//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CStatesCharacter::Update(int nState)
{
	//もらった状態ステートの値に応じ、テクスチャを変更する
	switch(nState)
	{
		//麻痺
	case UNIT_STATE_PARALYSIS:
		//使用するテクスチャIDの設定
		m_nTextureID = TEXTURE_RED_HOOD_PARALYSIS;
		break;
		//混乱
	case UNIT_STATE_CONFUSION:
		//使用するテクスチャIDの設定
		m_nTextureID = TEXTURE_RED_HOOD_CONFUSION;
		break;
		//毒
	case UNIT_STATE_POISON:
		//使用するテクスチャIDの設定
		m_nTextureID = TEXTURE_RED_HOOD_POISON;
		break;
		//睡眠
	case UNIT_STATE_SLEEP:
		//使用するテクスチャIDの設定
		m_nTextureID = TEXTURE_RED_HOOD_SLEEP;
		break;
	default:
		//使用するテクスチャIDの設定
		m_nTextureID = TEXTURE_RED_HOOD;
		break;
	}
}
