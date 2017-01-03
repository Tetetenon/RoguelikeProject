#include "FieldObj.h"
#include "MapData.h"

#include "ModelManager.h"
#include "GameScene.h"
#include"MapObjManager.h"
int CFieldObj::m_nMakeNum_Debug = 0;
//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CFieldObj::CFieldObj(CGameScene* Scene):
CMeshObj(Scene)
{
	//IDの設定
	m_uID = ID_MESHOOBJ;

	//自身の番号の設定
	m_ObjNumber = CMapObjManager::GetNextNumber();
	//次の番号を設定
	CMapObjManager::SetNextNumber(m_ObjNumber + 1);

	//オブジェクトをリストに追加
	CMapObjManager::Add(m_ObjNumber,this);
	m_nMakeNum_Debug++;
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CFieldObj::~CFieldObj(void)
{
	m_nMakeNum_Debug--;
	if (m_nMakeNum_Debug == 0)
	{
		int a = 0;
	}
}


//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CFieldObj::Update()
{
}
//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CFieldObj::Draw()
{
	m_pMesh->MaterialNoAlpha();
	CMeshObj::Draw();
}
//---------------------------------------------------------------------------------------
//半透明描画
//---------------------------------------------------------------------------------------
void CFieldObj::DrawAlpha()
{
	m_pMesh->MaterialAlpha();
	CMeshObj::DrawAlpha();
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


	//位置情報を設定
	world._41 = (PosX - (MAP_SIZE / 2)) * GRIDSIZE + GRIDSIZE / 2;
	world._42 = 0.0f;
	world._43 = -((PosY) - (MAP_SIZE / 2)) * GRIDSIZE - GRIDSIZE / 2;

	//ワールドマトリックスを設定
	pFieldObj ->SetWorld(world);
}