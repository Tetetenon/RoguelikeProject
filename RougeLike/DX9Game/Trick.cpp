#include "Trick.h"
#include "define.h"
#include <string>

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CTrick::CTrick(void)
{
	//文字列初期化
	for(int i = 0;i < TRICK_FONT_NUM_MAX;i++)
	{
		lstrcpyn(m_szName,_T("無し"),sizeof(_TCHAR) * TRICK_FONT_NUM_MAX / 2);
	}
	//IDの初期化
	m_ID = 0;
	//効能値の初期化
	m_nEffectValue = 0;
	//効能の種類の初期化
	m_nEffectType = -99;
	//技範囲の初期化
	m_nEffectRange = 0;
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CTrick::~CTrick(void)
{
}
//---------------------------------------------------------------------------------------
//名前を設定
//---------------------------------------------------------------------------------------
void CTrick::SetName(_TCHAR Name[])
{
	lstrcpyn(m_szName,Name,sizeof(_TCHAR) * TRICK_FONT_NUM_MAX / 2);
}

//---------------------------------------------------------------------------------------
//IDから名前を検索、名前を格納
//---------------------------------------------------------------------------------------
void CTrick::FindName	(int nID)
{
	switch(nID)
	{
	case TRICK_NAME_1:
		SetName(_T("前方３マスに攻撃"));
		break;
	case TRICK_NAME_2:
		SetName(_T("部屋全体攻撃"));
		break;
	case TRICK_NAME_3:
		SetName(_T("回復"));
		break;
	case TRICK_NAME_4:
		SetName(_T("攻守１アップ"));
		break;
	default:
		break;
	}
}
//---------------------------------------------------------------------------------------
//IDから効果を検索、設定
//---------------------------------------------------------------------------------------
void CTrick::EffectSetting(int nID)
{
	//技のIDによって効果を変更する
	switch(nID)
	{
		//1
	case TRICK_NAME_1:
		//前方３マスに攻撃
		m_nEffectType = TRICK_EFFECT_ATTACK;
		break;
		//2
	case TRICK_NAME_2:
		//部屋全体に攻撃
		m_nEffectType =  TRICK_EFFECT_ATTACK;
		break;
		//回復
	case TRICK_NAME_3:
		//4
		m_nEffectType =  TRICK_EFFECT_RECOVERY;
		break;
		//ステータス強化
	case TRICK_NAME_4:
		//防御力アップ
		m_nEffectType =  TRICK_EFFECT_STATES_UP;
		break;
		//バグ検査用
	default:
		//効果なし
		m_nEffectType =  TRICK_EFFECT_MAX;
		break;
	}
}
//---------------------------------------------------------------------------------------
//IDから技の範囲を設定
//---------------------------------------------------------------------------------------
void CTrick::SetRange(int nID)
{
	//技のIDによって範囲を変更する
	switch(nID)
	{
		//1
	case TRICK_NAME_1:
		//前方３マスに攻撃
		m_nEffectRange = TRICK_RANGE_WIDE;
		break;
		//2
	case TRICK_NAME_2:
		//部屋全体に攻撃
		m_nEffectRange =  TRICK_RANGE_ALL;
		break;
		//回復
	case TRICK_NAME_3:
		//自分
		m_nEffectRange =  TRICK_RANGE_ME;
		break;
		//ステータス強化
	case TRICK_NAME_4:
		//自分
		m_nEffectRange =  TRICK_RANGE_ME;
		break;
		//バグ検査用
	default:
		//効果なし
		m_nEffectRange =  TRICK_RANGE_MAX;
		break;
	}
}