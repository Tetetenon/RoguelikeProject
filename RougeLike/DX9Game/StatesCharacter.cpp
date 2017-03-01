#include "StatesCharacter.h"
#include "TextureManager.h"
#include "Unit.h"

//---------------------------------------------------------------------------------------
//静的メンバ変数
//---------------------------------------------------------------------------------------
CStatesCharacter* CStatesCharacter::m_pStatesCharacter = NULL;

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CStatesCharacter::CStatesCharacter(void)
{
	//使用するテクスチャIDの設定
	m_nTextureID = TEXTURE_RED_HOOD;

	//位置情報の設定
	m_aVertex[0].pos = D3DXVECTOR3( 10.0f, 10.0f,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3( 90.0f, 10.0f,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3( 10.0f, 90.0f,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3( 90.0f, 90.0f,0.0f);
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CStatesCharacter::~CStatesCharacter(void)
{
}

//---------------------------------------------------------------------------------------
//実体の生成
//---------------------------------------------------------------------------------------
void CStatesCharacter::Create()
{
	//中身の確認
	if (!m_pStatesCharacter)
	{
		//中身がなければ作成
		m_pStatesCharacter = new CStatesCharacter;
	}
}
//---------------------------------------------------------------------------------------
//実体の削除
//---------------------------------------------------------------------------------------
void CStatesCharacter::Delete()
{
	//中身の確認
	if (m_pStatesCharacter)
	{
		//中身があれば削除
		delete m_pStatesCharacter;
		m_pStatesCharacter = NULL;
	}
}
//---------------------------------------------------------------------------------------
//実体のポインタを渡す
//---------------------------------------------------------------------------------------
CStatesCharacter* CStatesCharacter::GetPointer()
{
	//念のため作成
	Create();
	return m_pStatesCharacter;
}
//---------------------------------------------------------------------------------------
//使用するテクスチャを交換する
//---------------------------------------------------------------------------------------
void CStatesCharacter::ChangeTexture(int nState)
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
