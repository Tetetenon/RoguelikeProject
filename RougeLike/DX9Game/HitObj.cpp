#include "HitObj.h"
#include "ModelManager.h"
#include "GameScene.h"


//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CHitObj::CHitObj(CGameScene *pScene):
CEffectObj(pScene)
{
	//使用するモデルの番号を設定
	m_nMeshNumber = MODEL_HIT;
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CHitObj::~CHitObj(void)
{
}
//---------------------------------------------------------------------------------------
//生成
//---------------------------------------------------------------------------------------
void CHitObj::Generation(CMeshObj *pGenerator)
{
	//呼び出し相手のポインタが存在する
	if(!pGenerator)
		return;

	//消滅オブジェクトを追加する
	CHitObj* pEffect = new CHitObj(pGenerator -> GetScene());

	//メッシュの設定
	pEffect ->SetMesh(CModelManager::GetMesh(pEffect -> m_nMeshNumber));

	//生存時間を設定
	pEffect ->m_nLifeTime = OBJ_LIFE;

	//ワールドマトリックスからローカル軸を抽出し、座標を抽出
	D3DXMATRIX world = pGenerator ->GetWorld();

	//自身のワールドマトリックスを設定
	pEffect -> SetWorld(world);
}