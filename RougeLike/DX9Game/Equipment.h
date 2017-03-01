#pragma once
#include "Item.h"

//所持できる最大アイテム量
#define EQUIPMENT_NUM_MAX 5

class CEquipment:
	public CItem
{
private:
	CItem	m_Item[EQUIPMENT_NUM_MAX];	//アイテムデータ(アイテムの持てる数)
public:
	CEquipment();						//コンストラクタ
	~CEquipment();						//デストラクタ

	bool SetItem(CItem Item);	//ストレージにアイテムをセット
								//指定されたアイテムの名前を返す
	_TCHAR* GetInventoryItemName(int Coefficient) { return m_Item[Coefficient].GetName(); }

	//指定されたアイテムを渡す
	CItem GetItem(int Coefficient) { return m_Item[Coefficient]; }

	void DelInventory(int Receipt);				//指定した番号のアイテムを消去

	int GetEffect(int Receipt);					//指定されたアイテムの効果ジャンルを返却

	int GetEffectValue(int Receipt);			//指定されたアイテムの効能を返却する

	void FindName(int nID, int Receipt);		//IDから名前を検索する

	int GetAttackTotalValue();					//インベントリに存在するすべての攻撃強化アイテムの合計値を算出し、渡す
	int GetDefenceTotalValue();					//インベントリに存在するすべての防御強化アイテムの合計値を算出し、渡す	

};

