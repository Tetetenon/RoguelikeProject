#include "Item.h"
#include "define.h"
#include <string>

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CItem::CItem(void)
{
	//文字列初期化
	for(int i = 0;i < ITEM_FONT_NUM_MAX;i++)
	{
		lstrcpyn(m_szName,_T("無し"),sizeof(_TCHAR) * ITEM_FONT_NUM_MAX / 2);
	}
	//IDの初期化
	m_ID = 0;
	//効能値の初期化
	m_nEffectValue = 0;
	//効能の種類の初期化
	m_nEffectType = -99;
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CItem::~CItem(void)
{
}
//---------------------------------------------------------------------------------------
//名前を設定
//---------------------------------------------------------------------------------------
void CItem::SetName(_TCHAR Name[])
{
	lstrcpyn(m_szName,Name,sizeof(_TCHAR) * ITEM_FONT_NUM_MAX / 2);
}

//---------------------------------------------------------------------------------------
//IDから名前を検索、名前を格納
//---------------------------------------------------------------------------------------
void CItem::FindName	(int nID)
{
	switch(nID)
	{
	case ITEM_APPLE:
		SetName(_T("林檎"));
		break;
	case ITEM_HERB:
		SetName(_T("薬草"));
		break;
	case ITEM_SWORD:
		SetName(_T("けん"));
		break;
	case ITEM_SHIELD:
		SetName(_T("たて"));
		break;
	default:
		break;
	}
}
void CItem::EffectSetting(int nID)
{
	//アイテムのIDによって効果を変更する
	switch(nID)
	{
		//林檎
	case ITEM_APPLE:
		//特に効果なし
		m_nEffectType = EFFECT_NON;
		break;
		//薬草
	case ITEM_HERB:
		//体力の回復
		m_nEffectType =  EFFECT_RECOVERY;
		break;
		//剣
	case ITEM_SWORD:
		//攻撃力アップ
		m_nEffectType =  EFFECT_EQUIPMENT_ATTACK;
		break;
		//盾
	case ITEM_SHIELD:
		//防御力アップ
		m_nEffectType =  EFFECT_EQUIPMENT_DEFENCE;
		break;
		//バグ検査用
	default:
		//効果なし
		m_nEffectType =  EFFECT_NON;
		break;
	}
}