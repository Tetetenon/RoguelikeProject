#include "EffectObj.h"
#include "ModelManager.h"
#include "GameScene.h"
#include"EffectObjManager.h"

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CEffectObj::CEffectObj(CGameScene *pScene):
CMeshObj(pScene),
m_nLifeTime(OBJ_LIFE)
{
	//ポインタを取得
	m_pEffectObjManager = CEffectObjManager::GetPointer();

	//自身の番号を設定
	m_nEffectID = m_pEffectObjManager->GetEffectNumber();

	//次のエフェクト番号の設定
	m_pEffectObjManager->SetEffectNumber(m_nEffectID + 1);

	//マネージャーに追加
	m_pEffectObjManager->Add(m_nEffectID,this);
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CEffectObj::~CEffectObj(void)
{
}

//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CEffectObj::Update()
{
	//生存時間を減算
	m_nLifeTime --;

	//親関数の更新
	CMeshObj::Update();
}
//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void CEffectObj::Fin()
{
	//親の終了処理
	CMeshObj::Fin();
}