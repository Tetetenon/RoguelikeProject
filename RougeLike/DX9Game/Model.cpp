//モデルデータ管理クラス　実装
#include "Model.h"


//モデルの数を規定
CMesh CModel::m_Mesh[MODEL_NUM];

#define PLAYER_MODEL	_T("../data/model/model/Zak.x")
#define ENEMY_MODEL		_T("../data/model/model/Zak.x")


//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CModel::CModel()
{

}