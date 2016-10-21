#include "ModelManager.h"

CMesh	CModelManager::m_MeshData[MODEL_MAX];				//メッシュデータ保存用
bool	CModelManager::m_MeshLoadFlg[MODEL_MAX] = {false};	//モデルデータ読み込みフラグ


//-----モデルデータパス-----

#define PATH_MESH_PLAYER		_T("../data/model/model/RedHood.x")			//プレイヤー(赤ずきん)
#define PATH_MESH_BEE			_T("../data/model/model/Bee.x")				//エネミー(蜂)
#define PATH_MESH_BEAR			_T("../data/model/model/Bear.x")			//エネミー(クマ)
#define PATH_MESH_WOLF			_T("../data/model/model/Wolf.x")			//エネミー(狼)
#define PATH_MESH_TREE			_T("../data/model/model/Tree.x")			//フィールドオブジェ(木)
#define PATH_MESH_WALL			_T("../data/model/model/Wall.x")			//フィールドオブジェ(壁)
#define PATH_MESH_ITEM			_T("../data/model/model/TreasureBox.x")		//フィールドオブジェ(宝箱)
#define PATH_MESH_STAIRS		_T("../data/model/model/Stairs.x")			//フィールドオブジェ(階段)
#define PATH_MESH_HIT			_T("../data/model/model/Hit.x")				//戦闘時ヒット
#define PATH_MESH_DELETE		_T("../data/model/model/Delete.x")			//戦闘時消滅




//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CModelManager::CModelManager(void)
{
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CModelManager::~CModelManager(void)
{
}

//---------------------------------------------------------------------------------------
//メッシュデータをロードする
//---------------------------------------------------------------------------------------
void CModelManager::LoadMesh()
{
	//メッシュデータの初期化
	ReleaseMesh();
	
	//-----プレイヤーモデルの読み込み-----
	if(!m_MeshLoadFlg[MODEL_PLAYER])
	{
		//モデルデータのロード
		m_MeshLoadFlg[MODEL_PLAYER] = m_MeshData[MODEL_PLAYER].Initialize(PATH_MESH_PLAYER,true);
	}

	//-----蜂モデルの読み込み-----
	if(!m_MeshLoadFlg[MODEL_BEE])
	{
		//モデルデータのロード
		m_MeshLoadFlg[MODEL_BEE] = m_MeshData[MODEL_BEE].Initialize(PATH_MESH_BEE,true);
	}
	
	//-----クマモデルの読み込み-----
	if(!m_MeshLoadFlg[MODEL_BEAR])
	{
		//モデルデータのロード
		m_MeshLoadFlg[MODEL_BEAR] = m_MeshData[MODEL_BEAR].Initialize(PATH_MESH_BEAR,true);
	}

	//-----狼モデルの読み込み-----
	if(!m_MeshLoadFlg[MODEL_WOLF])
	{
		//モデルデータのロード
		m_MeshLoadFlg[MODEL_WOLF] = m_MeshData[MODEL_WOLF].Initialize(PATH_MESH_WOLF,true);
	}

	//-----木モデルの読み込み-----
	if(!m_MeshLoadFlg[MODEL_TREE])
	{
		//モデルデータのロード
		m_MeshLoadFlg[MODEL_TREE] = m_MeshData[MODEL_TREE].Initialize(PATH_MESH_TREE,true);
	}

	//-----壁モデルの読み込み-----
	if(!m_MeshLoadFlg[MODEL_WALL])
	{
		//モデルデータのロード
		m_MeshLoadFlg[MODEL_WALL] = m_MeshData[MODEL_WALL].Initialize(PATH_MESH_WALL,true);
	}

	//-----宝箱モデルの読み込み-----
	if(!m_MeshLoadFlg[MODEL_TREASUREBOX])
	{
		//モデルデータのロード
		m_MeshLoadFlg[MODEL_TREASUREBOX] = m_MeshData[MODEL_TREASUREBOX].Initialize(PATH_MESH_ITEM,true);
	}

	//-----階段モデルの読み込み-----
	if(!m_MeshLoadFlg[MODEL_STAIRS])
	{
		//モデルデータのロード
		m_MeshLoadFlg[MODEL_STAIRS] = m_MeshData[MODEL_STAIRS].Initialize(PATH_MESH_STAIRS,true);
	}

	//-----戦闘ヒット読み込み-----
	if(!m_MeshLoadFlg[MODEL_HIT])
	{
		//モデルデータのロード
		m_MeshLoadFlg[MODEL_HIT] = m_MeshData[MODEL_HIT].Initialize(PATH_MESH_HIT,true);
	}

	//-----戦闘消滅の読み込み-----
	if(!m_MeshLoadFlg[MODEL_DELETE])
	{
		//モデルデータのロード
		m_MeshLoadFlg[MODEL_DELETE] = m_MeshData[MODEL_DELETE].Initialize(PATH_MESH_DELETE,true);
	}


}

//---------------------------------------------------------------------------------------
//全てのメッシュデータを削除する
//---------------------------------------------------------------------------------------
void CModelManager::ReleaseMesh()
{
	//メッシュデータが存在すれば、削除をすべてのメッシュデータに対し行う
	for(int i = 0;i < MODEL_MAX;i++)
	{
		//メッシュデータが読み込まれている
		if(m_MeshLoadFlg[i])
		{
			//メッシュの終了処理
			m_MeshData[i].Finalize();
			//フラグを倒す
			m_MeshLoadFlg[i] = false;
		}
	}

}

//---------------------------------------------------------------------------------------
//指定されたメッシュデータを渡す
//---------------------------------------------------------------------------------------
CMesh*	CModelManager::GetMesh(int nNumber)
{
	return &m_MeshData[nNumber];
}