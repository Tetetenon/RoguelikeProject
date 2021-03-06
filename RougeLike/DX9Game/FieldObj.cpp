#include "FieldObj.h"
#include "MapData.h"

#include "ModelManager.h"
#include "GameScene.h"
#include"MapObjManager.h"
//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CFieldObj::CFieldObj(CGameScene* Scene):
CMeshObj(Scene)
{
	//ポインタを取得
	m_pMapObjManager = CMapObjManager::GetPointer();
	m_pMapData = CMapData::GetPointer();
	m_pUnitManager = CUnitManager::GetPointer();

	//描画フラグ初期化
	m_bDrawFlg = true;

	//IDの設定
	m_uID = ID_MESHOOBJ;

	//自身の番号の設定
	m_ObjNumber = m_pMapObjManager->GetNextNumber();
	//次の番号を設定
	m_pMapObjManager->SetNextNumber(m_ObjNumber + 1);

	//オブジェクトをリストに追加
	m_pMapObjManager->Add(m_ObjNumber,this);
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CFieldObj::~CFieldObj(void)
{
}


//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CFieldObj::Update()
{
	//自身とプレイヤーの位置が離れていたら描画ふらぐを下げる
	m_bDrawFlg = true;
	int DistanceX = abs(m_nUnit_Pos_X - m_pUnitManager->GetPlayerPosX());
	int DistanceZ = abs(m_nUnit_Pos_Z - m_pUnitManager->GetPlayerPosZ());

	if ((DistanceZ > 8) || (DistanceX > 6))
	{
		m_bDrawFlg = false;
	}

	//マップ上で一番上のオブジェクトの場合、上にユニットがいるか確認する必要がないため、スル―
	if (m_nUnit_Pos_Z <= 0)
		return;

	//自身の上にユニットが存在するかどうかを確認する
	if ((0 != m_pMapData->Get_UnitMapSituation(m_nUnit_Pos_X,m_nUnit_Pos_Z - 1)) || (0 != m_pMapData->Get_ItemMapSituation(m_nUnit_Pos_X, m_nUnit_Pos_Z - 1)))
	{
		//ユニットが存在する場合、フラグを立てて、半透明描画に切り替える
		m_bNearUnitFlg = true;
	}
	else
	{
		//存在しない場合、不透明描画にする
		m_bNearUnitFlg = false;
	}
}
//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CFieldObj::Draw()
{
	if (m_bDrawFlg)
	{
		m_pMesh->MaterialNoAlpha();
		CMeshObj::Draw();
	}
}
//---------------------------------------------------------------------------------------
//半透明描画
//---------------------------------------------------------------------------------------
void CFieldObj::DrawAlpha()
{
	if (m_bDrawFlg)
	{
		m_pMesh->MaterialAlpha();
		CMeshObj::DrawAlpha();
	}
}

//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void CFieldObj::Fin()
{
	CMeshObj::Fin();
}
//---------------------------------------------------------------------------------------
//オブジェクトの生成
//---------------------------------------------------------------------------------------
void CFieldObj::SetObject(CMeshObj *pSetter,int SetNumber,int PosX,int PosY)
{
	//呼び出した相手のポインタがある
	if(!pSetter)
		return;

	//オブジェクトを追加
	CFieldObj *pFieldObj = new CFieldObj(pSetter ->GetScene());

	//メッシュの設定
	pFieldObj ->SetMesh(CModelManager::GetMesh(SetNumber));

	//ワールドを取得
	D3DXMATRIX world = pSetter->GetWorld();

	//モデルの角度を変更する
	D3DXMatrixRotationY(&world,90.0f);
	
	//モデルのスケールを変更する
	D3DXMatrixScaling(&world,0.3f,0.3f,0.3f);

	//自身のマップ配列状での位置を設定する
	pFieldObj->m_nUnit_Pos_X = PosX;
	pFieldObj->m_nUnit_Pos_Z = PosY;

	//自身の上にオブジェクトが存在するかのフラグを初期化する
	pFieldObj->m_bNearUnitFlg = false;

	//位置情報を設定
	world._41 = (PosX - (MAP_SIZE / 2)) * GRIDSIZE + GRIDSIZE / 2;
	world._42 = 0.0f;
	world._43 = -((PosY) - (MAP_SIZE / 2)) * GRIDSIZE - GRIDSIZE / 2;

	//ワールドマトリックスを設定
	pFieldObj ->SetWorld(world);
}