#pragma once
#include"Item.h"
#include<tchar.h>
//所持できる最大アイテム量
#define ITEM_NUM_MAX 10

class CInventory:
	public CItem
{
private:
	CItem	m_Item[ITEM_NUM_MAX];	//アイテムデータ(アイテムの持てる数)
public:
	CInventory();							//コンストラクタ
	~CInventory();							//デストラクタ

	//指定されたアイテムデータを渡す
	CItem GetItem(int Coefficient) 
	{
		return m_Item[Coefficient]; 
	}

	//指定されたアイテムの名前を返す
	_TCHAR* GetInventoryItemName(int Coefficient) { return m_Item[Coefficient].GetName(); }

	bool SetItem(CItem Item);		//ストレージにアイテムをセット

	void DelInventory(int Receipt);				//指定した番号のアイテムを消去

	int GetEffect(int Receipt);					//指定されたアイテムの効果ジャンルを返却

	int GetEffectValue(int Receipt);			//指定されたアイテムの効能を返却する

};

