#pragma once

#include "define.h"
#include "Mesh.h"

//使用するモデル一覧
enum MODELNUM
{
	MODEL_PLAYER = 0,		//プレイヤー(赤ずきん)
	MODEL_BEE,				//エネミー(蜂)
	MODEL_BEAR,				//エネミー(クマ)
	MODEL_WOLF,				//エネミー(狼)
	MODEL_TREE,				//フィールドオブジェ(木)
	MODEL_WALL,				//フィールドオブジェ(壁)
	MODEL_TREASUREBOX,		//フィールドオブジェ(宝箱)
	MODEL_STAIRS,			//フィールドオブジェ(階段)
	MODEL_HIT,				//戦闘時ヒットオブジェト
	MODEL_DELETE,			//戦闘時消滅
	MODEL_MAX
};

class CModelManager
{
private:
	static CMesh	m_MeshData[MODEL_MAX];		//メッシュデータ保存用
	static bool		m_MeshLoadFlg[MODEL_MAX];	//モデルデータ読み込みフラグ
public:
	CModelManager(void);						//コンストラクタ
	~CModelManager(void);						//デストラクタ

	static void		LoadMesh();					//メッシュデータをロードする

	static void		ReleaseMesh();				//全てのメッシュデータを削除する

	static CMesh*	GetMesh(int nNumber);		//指定されたメッシュデータを渡す
};

