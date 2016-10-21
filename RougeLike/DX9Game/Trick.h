#pragma once

//技クラス

#include <Windows.h>
#include <tchar.h>

//技の文字数
#define TRICK_FONT_NUM_MAX 256

class CTrick
{
protected:
	int		m_ID;					//技種類個別のID
	_TCHAR	m_szName[TRICK_FONT_NUM_MAX];	//技の名前
	int		m_nEffectValue;			//技の効果の数値
	int		m_nEffectType;			//技効果の種類
	int		m_nEffectRange;			//技の効果範囲
public:
	CTrick(void);
	~CTrick(void);
	
	_TCHAR* GetName()	{return m_szName;}				//名前を取得
	int	GetID()			{return m_ID;}					//IDを取得
	int	GetValue()		{return m_nEffectValue;}		//効果の数値を渡す
	int GetType()		{return m_nEffectType;}			//効果の種類を返す
	int GetRange()		{return m_nEffectRange;}		//技の効果範囲

	//名前を設定
	void SetName(_TCHAR Name[]);

	//IDの設定
	void SetID(int nID)		{m_ID = nID;}

	//技の効能設定
	void SetValue(int nValue)			{m_nEffectValue = nValue;}

	//IDから技名の判別
	void FindName	(int nID);

	//IDから効果の種類の設定
	void EffectSetting(int nID);

	//IDから、技範囲の設定
	void SetRange(int nID);
};

