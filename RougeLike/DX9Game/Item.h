#pragma once

//アイテムクラス

#include <Windows.h>
#include <tchar.h>

//アイテムの文字数
#define ITEM_FONT_NUM_MAX 10

//アイテムの名前
enum ITEMNAME
{
	ITEM_APPLE	= 1,	//林檎
	ITEM_HERB,			//薬草
	ITEM_SWORD,			//剣
	ITEM_SHIELD,		//盾
	ITEM_MAX
};

class CItem
{
protected:
	int		m_ID;		//アイテム種類個別のID
	_TCHAR	m_szName[ITEM_FONT_NUM_MAX];		//アイテムの名前
	int		m_nEffectValue;				//アイテムの効果の数値
	int		m_nEffectType;				//アイテム効果の種類
public:
	CItem(void);
	~CItem(void);
	
	_TCHAR* GetName()	
	{
		return m_szName;
	}				//名前を取得
	int	GetID()	
	{
		return m_ID;
	}							//IDを取得
	int	GetValue()
	{
		return m_nEffectValue;
	}				//効果の数値を渡す
	int GetType()	
	{
		return m_nEffectType;
	}				//アイテム効果の種類を返す

	//名前を設定
	void SetName(_TCHAR Name[]);
	//IDの設定
	void SetID(int nID)		{m_ID = nID;}
	//アイテムの効能設定
	void SetValue(int nValue)			{m_nEffectValue = nValue;}
	//タイプの初期化
	void SetType(int nType) { m_nEffectType = nType; }

	//IDからアイテム名の判別
	void FindName	(int nID);

	//IDからアイテム効果の種類の設定
	void EffectSetting(int nID);
};

