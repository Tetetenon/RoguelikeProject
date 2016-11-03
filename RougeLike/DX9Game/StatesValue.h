#pragma once
//ユニットのステータス値を出力する
#include "C2DTexture.h"
#include "StatesDefine.h"

class CStatesValue :
	public C2DTexture
{
private:
	//各ステータスデータの格納
	static int m_nStatesValue[STATES_FONT_MAX];
	//ポリゴン情報
	static VERTEX_2D	m_aVertex[STATES_FONT_MAX * 2][NUM_VERTEX];
public:
	CStatesValue(void);			//コンストラクタ
	~CStatesValue(void);		//デストラクタ

	void Draw ();				//描画

	void SetVertex();			//ポリゴン情報の設定
	
	//描画する攻撃の値を設定する
	static void SetNumAttack(int nAttack)	{m_nStatesValue[STATES_FONT_ATTACK] = nAttack;}

	//描画する防御の値を設定する
	static void SetNumDefence(int nDefence)	{m_nStatesValue[STATES_FONT_DEFENCE] = nDefence;}

	//描画する経験値の値を設定する
	static void SetNumExp(int nExp)	{m_nStatesValue[STATES_FONT_EXP] = nExp;}

};

