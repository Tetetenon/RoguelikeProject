#pragma once

//ユニットが消滅したときのエフェクトクラス
#include "EffectObj.h"

class CGameScene;

class CDeleteObj:
	public CEffectObj
{
public:
	CDeleteObj(CGameScene *pScene);		//コンストラクタ
	~CDeleteObj(void);					//デストラクタ

	static void Generation(CMeshObj* pGenerator);	//エフェクトの生成
};

