#pragma once

//技クラス

#include <Windows.h>
#include <tchar.h>

//技の文字数
#define TRICK_FONT_NUM_MAX 256

//技の名前
enum TRICKNAME
{
	TRICK_NAME_1 = 0,	//技１
	TRICK_NAME_2,
	TRICK_NAME_3,
	TRICK_NAME_4,
	TRICK_NAME_MAX
};

//技の効果ジャンル
enum TRICKEFFECT
{
	TRICK_EFFECT_ATTACK = 0,	//攻撃
	TRICK_EFFECT_STATES_UP,		//ステータスの強化、弱化
	TRICK_EFFECT_RECOVERY,		//回復
	TRICK_EFFECT_MAX
};


//技の効果範囲
enum TRICKRANGE
{
	TRICK_RANGE_FRONT = 0,	//前方に攻撃
	TRICK_RANGE_ME,			//自身
	TRICK_RANGE_ALL,		//部屋全体
	TRICK_RANGE_WIDE,		//前方３マス
	TRICK_RANGE_MAX			//
};

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

