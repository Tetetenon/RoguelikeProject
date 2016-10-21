#pragma once

//‹ZƒNƒ‰ƒX

#include <Windows.h>
#include <tchar.h>

//‹Z‚Ì•¶š”
#define TRICK_FONT_NUM_MAX 256

class CTrick
{
protected:
	int		m_ID;					//‹Zí—ŞŒÂ•Ê‚ÌID
	_TCHAR	m_szName[TRICK_FONT_NUM_MAX];	//‹Z‚Ì–¼‘O
	int		m_nEffectValue;			//‹Z‚ÌŒø‰Ê‚Ì”’l
	int		m_nEffectType;			//‹ZŒø‰Ê‚Ìí—Ş
	int		m_nEffectRange;			//‹Z‚ÌŒø‰Ê”ÍˆÍ
public:
	CTrick(void);
	~CTrick(void);
	
	_TCHAR* GetName()	{return m_szName;}				//–¼‘O‚ğæ“¾
	int	GetID()			{return m_ID;}					//ID‚ğæ“¾
	int	GetValue()		{return m_nEffectValue;}		//Œø‰Ê‚Ì”’l‚ğ“n‚·
	int GetType()		{return m_nEffectType;}			//Œø‰Ê‚Ìí—Ş‚ğ•Ô‚·
	int GetRange()		{return m_nEffectRange;}		//‹Z‚ÌŒø‰Ê”ÍˆÍ

	//–¼‘O‚ğİ’è
	void SetName(_TCHAR Name[]);

	//ID‚Ìİ’è
	void SetID(int nID)		{m_ID = nID;}

	//‹Z‚ÌŒø”\İ’è
	void SetValue(int nValue)			{m_nEffectValue = nValue;}

	//ID‚©‚ç‹Z–¼‚Ì”»•Ê
	void FindName	(int nID);

	//ID‚©‚çŒø‰Ê‚Ìí—Ş‚Ìİ’è
	void EffectSetting(int nID);

	//ID‚©‚çA‹Z”ÍˆÍ‚Ìİ’è
	void SetRange(int nID);
};

