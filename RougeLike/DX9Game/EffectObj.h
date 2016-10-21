#pragma once

//3Dエフェクトを管理するクラス
#include "MeshObj.h"

#define OBJ_LIFE 30	//オブジェクトの生存時間

//クラス定義
class CGameScene;

class CEffectObj :
	public CMeshObj
{
protected:
	int m_nLifeTime;	//生存時間
public:
	CEffectObj(CGameScene *pScene);				//コンストラクタ
	~CEffectObj(void);								//デストラクタ

	void Update();									//更新
	void Fin();										//終了処理
};

