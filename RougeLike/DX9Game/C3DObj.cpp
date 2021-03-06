//3Dオブジェクトクラス実装
#include "C3DObj.h"
#include "GameScene.h"

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
C3DObj::C3DObj(CGameScene* pScene):
	m_uID(ID_3DOBJ)
{
	//ワールド座標の初期化
	D3DXMatrixIdentity(&m_world);

	//シーンクラスのポインタを取得
	m_pScene = pScene;

	//リストデータの初期化
	m_pNext = m_pBack = NULL;

	//シーンにオブジェクトを追加する
	//thisポインタ:自分自身を表す
	//m_pScene -> Add(this);
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
C3DObj::~C3DObj(void)
{
	//シーンオブジェクトの削除
	//m_pScene ->Del(this);
}

//---------------------------------------------------------------------------------------
//初期化
//---------------------------------------------------------------------------------------
void C3DObj::Init()
{
}
//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void C3DObj::Fin()
{

}
//---------------------------------------------------------------------------------------
//更新処理
//---------------------------------------------------------------------------------------
void C3DObj::Update()
{
}
//---------------------------------------------------------------------------------------
//描画処理
//---------------------------------------------------------------------------------------
void C3DObj::Draw()
{

}

//---------------------------------------------------------------------------------------
//半透明処理
//---------------------------------------------------------------------------------------
void C3DObj::DrawAlpha()
{

}

//---------------------------------------------------------------------------------------
//位置情報取得
//---------------------------------------------------------------------------------------
D3DXVECTOR3 C3DObj::GetPos()
{
	D3DXVECTOR3 pos(m_world._41,m_world._42,m_world._43);
	return pos;
}
//---------------------------------------------------------------------------------------
//上方向ベクトルの取得
//---------------------------------------------------------------------------------------
D3DXVECTOR3 C3DObj::GetUp()
{
	
	D3DXVECTOR3 Up(m_world._21,m_world._22,m_world._23);
	return Up;
}
//---------------------------------------------------------------------------------------
//前方ベクトルの取得
//---------------------------------------------------------------------------------------
D3DXVECTOR3 C3DObj::GetForward()
{
	D3DXVECTOR3 Forward(m_world._31,m_world._32,m_world._33);
	return Forward;
}
//---------------------------------------------------------------------------------------
//X右ベクトルの取得
//---------------------------------------------------------------------------------------
D3DXVECTOR3 C3DObj::GetRight()
{
	D3DXVECTOR3 Right(m_world._31,m_world._32,m_world._33);
	return Right;
}
//---------------------------------------------------------------------------------------
//オブジェクトの検索
//---------------------------------------------------------------------------------------
//C3DObj* C3DObj::Find(UINT uID,C3DObj* p)
//{
//	//シーンオブジェクトが存在しなければ、ほかのオブジェクトも存在しないため
//	//ここで最初に判定をする
//	if(m_pScene)
//		return m_pScene ->Find(uID,p);
//	return NULL;
//}

//---------------------------------------------------------------------------------------
//配列位置情報取得(X)
//---------------------------------------------------------------------------------------
int C3DObj::GetPosX ()
{
	return m_nUnit_Pos_X;
}

//---------------------------------------------------------------------------------------
//配列位置情報取得(Z)
//---------------------------------------------------------------------------------------
int C3DObj::GetPosZ ()
{
	return m_nUnit_Pos_Z;
}