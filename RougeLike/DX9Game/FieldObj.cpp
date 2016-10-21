#include "FieldObj.h"
#include "MapData.h"

#include "ModelManager.h"
#include "GameScene.h"

CMeshObj*	CFieldObj::m_pPlayer = NULL;
bool		CFieldObj::m_bDeleteObj = false;
int			CFieldObj::m_Counter = 0;
//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CFieldObj::CFieldObj(CGameScene* Scene):
CMeshObj(Scene)
{
	//IDの設定
	m_uID = ID_MESHOOBJ;
	//全オブジェクト削除フラグを倒す
	m_bDeleteObj = false;

	//プレイヤーへのポインタを取得
	m_pPlayer = (CMeshObj*)Find(ID_PLAYER);
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CFieldObj::~CFieldObj(void)
{
	m_Counter = 0;
	m_bDeleteObj = true;

	//プレイヤーポインタを削除
	m_pPlayer = NULL;
}


//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CFieldObj::Update()
{
	//全オブジェクト削除フラグが立っていた場合、削除を行う
	if(m_bDeleteObj)
	{
		Fin();
	}
}
//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CFieldObj::Draw()
{
	//プレイヤーの近くのモデルは、半透明にして描画を行う
	if(m_pPlayer)
	{
		//プレイヤーの位置を取得する
		D3DXVECTOR3 PlayerPos = m_pPlayer ->GetPos();
		
		//自身の位置とプレイヤーの位置の比較
		float DistanceX = abs(m_world._41 - PlayerPos.x);
		float DistanceZ = m_world._43 - PlayerPos.z;
		
		//自身の位置と、プレイヤーの位置が近ければ、モデルを半透明の物に変更する
		if(DistanceX <= GRIDSIZE)
		{
			if(DistanceZ < 0 && DistanceZ > - GRIDSIZE * 1.5)
			{
				return;
			}
			else
			{
				m_pMesh->MaterialNoAlpha();
				CMeshObj::Draw();
			}
		}
		else
		{
			m_pMesh->MaterialNoAlpha();
			CMeshObj::Draw();
		}
	}
}
//---------------------------------------------------------------------------------------
//半透明描画
//---------------------------------------------------------------------------------------
void CFieldObj::DrawAlpha()
{
	//プレイヤーの近くのモデルは、半透明にして描画を行う
	if(m_pPlayer)
	{
		//プレイヤーの位置を取得する
		D3DXVECTOR3 PlayerPos = m_pPlayer ->GetPos();
		
		//自身の位置とプレイヤーの位置の比較
		float DistanceX = abs(m_world._41 - PlayerPos.x);
		float DistanceZ = m_world._43 - PlayerPos.z;
		
		//自身の位置と、プレイヤーの位置が近ければ、モデルを半透明の物に変更する
		if(DistanceX <= GRIDSIZE)
		{
			if(DistanceZ < 0 && DistanceZ > -GRIDSIZE * 2)
			{
				m_pMesh->MaterialAlpha();
				CMeshObj::DrawAlpha();
			}
			else
			{
				return;
			}
		}
		else
		{
			return;
		}
	}
}

//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void CFieldObj::Fin()
{
	CMeshObj::Fin();

	delete this;
}
//---------------------------------------------------------------------------------------
//オブジェクトの生成
//---------------------------------------------------------------------------------------
void CFieldObj::SetObject(CMeshObj *pSetter,int SetNumber,int PosX,int PosY)
{
	//呼び出した相手のポインタがある
	if(!pSetter)
		return;

	//作った数加算
	m_Counter++;

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