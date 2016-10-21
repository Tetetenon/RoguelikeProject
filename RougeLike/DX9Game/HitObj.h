#pragma once

//ユニットに攻撃がヒットしたときのエフェクトクラス

#include "EffectObj.h"

class CGameScene;

class CHitObj:
	public CEffectObj
{
private:
	static bool		m_bDrawFlg;			//描画フラグ

	static int		m_PosX;				//オブジェクトの横軸位置
	static int		m_PosY;				//オブジェクトの縦軸位置
public:
	CHitObj(CGameScene *pScene);		//コンストラクタ
	~CHitObj(void);						//デストラクタ
	static void Generation(CMeshObj* pGenerator);	//生成
};

