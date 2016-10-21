#pragma once

class CUnit;

class CBattle
{
public:
	CBattle(void);										//コンストラクタ
	~CBattle(void);										//デストラクタ

	static int DamageCalculation(int Attack,int Defence);		//ダメージ計算
};

