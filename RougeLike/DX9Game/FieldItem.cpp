#include "FieldItem.h"
#include "GameScene.h"
#include "define.h"
#include "MapData.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "MiniMap.h"
#include"ItemManager.h"

int CFieldItem::n_Debug = 0;

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CFieldItem::CFieldItem(CGameScene *pScene):
CMeshObj(pScene)
{
	//ポインタの取得
	m_pItemManager = CItemManager::GetPointer();
	m_pMapData = CMapData::GetPointer();

	m_uID = ID_ITEM;

	//使用するモデルの番号
	m_nMeshNumber = MODEL_TREASUREBOX;
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CFieldItem::~CFieldItem(void)
{
}

//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CFieldItem::Update		()
{
	if(!m_ItemDelete)
		Delete();
}
//---------------------------------------------------------------------------------------
//描画処理
//---------------------------------------------------------------------------------------
void CFieldItem::Draw	()
{
	//親の描画処理を行う
	CMeshObj::Draw();
	//サークルの描画を行う
	m_Circle.Draw(OBJ_NUM_ITEM);
}
//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void CFieldItem::Fin		()
{
	CMeshObj::Fin();
}
//---------------------------------------------------------------------------------------
//自身の削除
//---------------------------------------------------------------------------------------
void CFieldItem::Delete		()
{
	m_ItemDelete = false;
	CMeshObj::Fin();
	//マネージャー上から自身を削除する
	m_pItemManager->Del(m_FieldID);
}

//---------------------------------------------------------------------------------------
//アイテムの生成
//---------------------------------------------------------------------------------------
void CFieldItem::Generation(CMeshObj *pGeneration)
{
	//メッシュ情報あり&呼び出しのポインタ情報がある
	if(!pGeneration)
		return;

	//アイテムを追加
	CFieldItem* pFieldItem = new CFieldItem(pGeneration ->GetScene());

	//アイテムの番号を設定する
	pFieldItem ->m_FieldID = pFieldItem->m_pItemManager->GetNextItemID();

	//アイテムの生成カウントを加算
	pFieldItem->m_pItemManager->NextItemID(pFieldItem->m_FieldID + 1);

	//IDの設定
	pFieldItem ->m_Item.SetID(1 + rand()%ITEM_SHIELD);

	//アイテムIDから、名前を設定する
	pFieldItem ->m_Item.FindName(pFieldItem ->m_Item.GetID());

	//アイテムIDから、アイテムの効能の種類を設定する
	pFieldItem ->m_Item.EffectSetting(pFieldItem ->m_Item.GetID());

	//アイテムの効能を設定する
	pFieldItem ->m_Item.SetValue(10);

	//メッシュの設定
	switch (pFieldItem->m_Item.GetID())
	{
	case ITEM_APPLE:
		pFieldItem->SetMesh(CModelManager::GetMesh(MODEL_APPLE));
		break;
	case ITEM_HERB:
		pFieldItem->SetMesh(CModelManager::GetMesh(MODEL_HERB));
		break;
	case ITEM_SWORD:
		pFieldItem->SetMesh(CModelManager::GetMesh(MODEL_SWORD));
		break;
	case ITEM_SHIELD:
		pFieldItem->SetMesh(CModelManager::GetMesh(MODEL_SHIELD));
		break;
	default:
		pFieldItem->SetMesh(CModelManager::GetMesh(MODEL_WALL));
		break;
	}

	//生存フラグ
	pFieldItem ->m_ItemDelete = true;


	//-----位置情報の設定-----
	int RoomNumber = rand() % pFieldItem->m_pMapData->GetMakeRoomNum();

	//部屋の間取りの取得
	RECT Pos = pFieldItem->m_pMapData->GetRoomFloorPlan(RoomNumber);

	//アイテムの位置情報の設定
	pFieldItem ->m_Pos.x = (float)(rand()%(Pos.right - Pos.left) + Pos.left);
	pFieldItem ->m_Pos.y = (float)(rand()%(Pos.bottom - Pos.top) + Pos.top);

	//アイテム設置予定場所が部屋の中かつ階段の上以外、アイテムがおいていない
	while(!pFieldItem ->m_pMapData->CheckInTheRoom((int)pFieldItem ->m_Pos.x,(int)pFieldItem ->m_Pos.y)
		|| pFieldItem ->m_pMapData->CheckStairs((int)pFieldItem ->m_Pos.x,(int)pFieldItem ->m_Pos.y)
		|| pFieldItem ->m_pMapData->Get_ItemMapSituation((int)pFieldItem ->m_Pos.x,(int)pFieldItem ->m_Pos.y) != 0
		|| pFieldItem ->m_pMapData->Get_TerrainMapSituation((int)pFieldItem->m_Pos.x, (int)pFieldItem->m_Pos.y) != FLOOR)
	{

		//アイテムの位置情報の再設定
		pFieldItem->m_Pos.x = (float)(rand() % (Pos.right - Pos.left) + Pos.left);
		pFieldItem->m_Pos.y = (float)(rand() % (Pos.bottom - Pos.top) + Pos.top);
	}

	//マップデータ上に自身の存在を設定
	pFieldItem->m_pMapData->Set_ItemMap((int)pFieldItem ->m_Pos.x,(int)pFieldItem ->m_Pos.y,pFieldItem ->m_FieldID);

	//ワールドマトリックスからローカル座標抽出
	D3DXMATRIX world = pGeneration ->GetWorld();

	//モデルのスケールを変更する
	D3DXMatrixScaling(&world,0.1f,0.1f,0.1f);
	

	//それぞれの軸の値を格納する
	D3DXVECTOR3 vX,vY,vZ,vP;
	
	vX = D3DXVECTOR3(world._11,world._12,world._13);	//vX:X軸回転
	vY = D3DXVECTOR3(world._21,world._22,world._23);	//vY:Y軸回転
	vZ = D3DXVECTOR3(world._31,world._32,world._33);	//vZ:Z軸回転
	vP = D3DXVECTOR3(world._41,world._42,world._43);	//位置情報
	
	//回転行列の作成
	D3DXMATRIX rot_X,rot_Y,rot_Z;
	D3DXMatrixRotationAxis(&rot_X,&vX,0);		//&rot_YにvYとangle.yの値を掛け合わせた行列を格納する
	D3DXMatrixRotationAxis(&rot_Y,&vY,PI + PI / 2);		//&rot_Zに現在の角度(vY)に回転度数(angle.y)をかけた値の行列を格納
	D3DXMatrixRotationAxis(&rot_Z,&vZ,0);		//&rot_Zに現在の角度(vZ)に回転度数(angle.z)をかけた値の行列を格納

	//計算結果の行列をワールド行列に反映させる
	world *= (rot_Z *rot_Y * rot_X);

	//ワールド座標上の位置情報の設定
	world._41 = (pFieldItem ->m_Pos.x - (MAP_SIZE / 2)) * GRIDSIZE + GRIDSIZE / 2;
	world._42 = 0.0f;
	world._43 = -((pFieldItem ->m_Pos.y) - (MAP_SIZE / 2)) * GRIDSIZE - GRIDSIZE / 2;


	//ワールドマトリックスを設定
	pFieldItem ->SetWorld(world);

	//アイテムサークルの位置を指定
	pFieldItem ->m_Circle.SetPos(D3DXVECTOR3(world._41,world._42,world._43));

	//マネージャーにオブジェクトを追加する
	pFieldItem->m_pItemManager->Add(pFieldItem->m_FieldID, pFieldItem);
}