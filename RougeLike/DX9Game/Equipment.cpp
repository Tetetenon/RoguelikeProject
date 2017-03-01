#include "Equipment.h"
#include "define.h"

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CEquipment::CEquipment()
{
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CEquipment::~CEquipment()
{
}

//---------------------------------------------------------------------------------------
//ストレージにアイテムをセット
//---------------------------------------------------------------------------------------
bool CEquipment::SetItem(CItem Item)
{
	for (int i = 0; i < EQUIPMENT_NUM_MAX; i++)
	{
		//ストレージが空白の部分を探す
		if (m_Item[i].GetID() == 0)
		{
			//アイテムの格納
			m_Item[i] = Item;

			//効能の設定がされていなければ、自動的に設定する
			if (m_Item[i].GetValue() == 0)
			{
				//効能を設定
				m_Item[i].SetValue(rand() % 10 + 5);
			}
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------------
//IDから名前を検索、名前を格納
//---------------------------------------------------------------------------------------
void CEquipment::FindName(int nID, int Receipt)
{
	switch (nID)
	{
	case ITEM_APPLE:
		m_Item[Receipt].SetName(_T("林檎"));
		break;
	case ITEM_HERB:
		m_Item[Receipt].SetName(_T("薬草"));
		break;
	case ITEM_SWORD:
		m_Item[Receipt].SetName(_T("けん"));
		break;
	case ITEM_SHIELD:
		m_Item[Receipt].SetName(_T("たて"));
		break;
	default:
		break;
	}
}

//---------------------------------------------------------------------------------------
//指定されたアイテムを消去
//---------------------------------------------------------------------------------------
void CEquipment::DelInventory(int Receipt)
{
	//中身を初期化し、消去
	//IDの初期化
	m_Item[Receipt].SetID(0);
	//名前の初期化
	m_Item[Receipt].SetName(_T("0"));
	//タイプの初期化
	m_Item[Receipt].SetValue(0);
	//効果値の初期化
	m_Item[Receipt].SetType(-99);

}
//---------------------------------------------------------------------------------------
//指定されたアイテムの効果ジャンルを返却する
//---------------------------------------------------------------------------------------
int CEquipment::GetEffect(int Receipt)
{
	//アイテムのIDによって効果を変更する
	switch (m_Item[Receipt].GetID())
	{
		//林檎
	case ITEM_APPLE:
		//特に効果なし
		return EFFECT_NON;
		break;
		//薬草
	case ITEM_HERB:
		//体力の回復
		return EFFECT_RECOVERY;
		break;
		//剣
	case ITEM_SWORD:
		//攻撃力アップ
		return EFFECT_EQUIPMENT_ATTACK;
		break;
		//盾
	case ITEM_SHIELD:
		//防御力アップ
		return EFFECT_EQUIPMENT_DEFENCE;
		break;
		//バグ検査用
	default:
		//効果なし
		return EFFECT_NON;
		break;
	}
}
//---------------------------------------------------------------------------------------
//指定されたアイテムの効能?を返却する
//---------------------------------------------------------------------------------------
int CEquipment::GetEffectValue(int Receipt)
{
	//アイテムのIDによって効果を変更する
	switch (m_Item[Receipt].GetID())
	{
		//林檎
	case ITEM_APPLE:
		//特に効果なし
		return EFFECT_NON;
		break;
		//薬草
	case ITEM_HERB:
		//体力の回復
		return m_Item[Receipt].GetValue();
		break;
		//剣
	case ITEM_SWORD:
		//攻撃力アップ
		return m_Item[Receipt].GetValue();
		break;
		//盾
	case ITEM_SHIELD:
		//防御力アップ
		return m_Item[Receipt].GetValue();
		break;

		//バグ検査用
	default:
		//効果なし
		return EFFECT_NON;
		break;
	}
}
//---------------------------------------------------------------------------------------
//インベントリに存在するすべての攻撃強化アイテムの合計値を算出し、渡す
//---------------------------------------------------------------------------------------
int CEquipment::GetAttackTotalValue()
{
	//合計値格納用変数
	int nTotalNum = 0;

	//全てのアイテム欄を確認する
	for (int i = 0; i < EQUIPMENT_NUM_MAX; i++)
	{
		//効果が攻撃補助か確認する
		if (m_Item[i].GetType() == EFFECT_EQUIPMENT_ATTACK)
		{
			//攻撃補助型なら、その値を取り出し、加算
			nTotalNum += m_Item[i].GetValue();
		}
	}
	return nTotalNum;
}
//---------------------------------------------------------------------------------------
//インベントリに存在するすべての防御強化アイテムの合計値を算出し、渡す
//---------------------------------------------------------------------------------------
int CEquipment::GetDefenceTotalValue()
{
	//合計値格納用変数
	int nTotalNum = 0;
	//全てのアイテム欄を確認する
	for (int i = 0; i < EQUIPMENT_NUM_MAX; i++)
	{
		//効果が防御補助か確認する
		if (m_Item[i].GetType() == EFFECT_EQUIPMENT_DEFENCE)
		{
			//防御補助型なら、その値を取り出し、加算
			nTotalNum += m_Item[i].GetValue();
		}
	}
	return nTotalNum;
}