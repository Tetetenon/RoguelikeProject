//	3Dオブジェクト クラス定義
#pragma once

#include "Graphics.h"

enum OBJID
{
	ID_3DOBJ = 0,
	ID_MESHOOBJ,
	ID_CAMERA,		//カメラ
	ID_PLAYER,		//自機
	ID_SKY,			// スカイドーム
	ID_ENEMY,		//敵機
	ID_ITEM,		//アイテム
	ID_EXPLOSION,	// 爆発
	ID_PARTICLE,	// パーティクル
	MAX_ID
};


// 描画方法
enum ESynthetic {
	eNone = 0,		// 通常描画
	eAdditive,		// 加算合成
	eAlphaBlend,	// 半透明合成
	eSubtractive,	// 減算合成

	eMaxSynthetic
};
class CGameScene;

class C3DObj
{
protected:
	UINT		m_uID;		//オブジェクト種別
	D3DXMATRIX	m_world;	//ワールド変換行列

	CGameScene*		m_pScene;	//所属するシーン
	C3DObj*		m_pNext;	//次オブジェクト
	C3DObj*		m_pBack;	//前オブジェクト
	ESynthetic		m_synthetic;	// 半透明描画フラグ
	
	//配列上の位置情報
	int						m_nUnit_Pos_X;
	int						m_nUnit_Pos_Z;
public:
	C3DObj(CGameScene* pScene);
	virtual ~C3DObj(void);

	virtual void Init();	//初期化
	virtual void Fin();		//終了処理
	virtual void Update();	//更新
	virtual void Draw();	//描画処理
	virtual void DrawAlpha();	//半透明描画処理
	D3DXMATRIX& GetWorld()	{return m_world;}
	void SetWorld(D3DXMATRIX& world){m_world = world;}


	D3DXVECTOR3 GetPos();		//座標取得
	D3DXVECTOR3 GetUp();		//上ベクトル取得
	D3DXVECTOR3 GetForward();	//前方ベクトル取得
	D3DXVECTOR3 GetRight();		//右ベクトル取得
	
	//C3DObj* GetNext () {return m_pNext;}				//次のポインタの取得
	//void	SetNext (C3DObj *pNext) {m_pNext = pNext;}	//次のポインタの設定
	//C3DObj* GetBack () {return m_pBack;}				//前のポインタの取得
	//void	SetBack (C3DObj *pBack) {m_pBack = pBack;}	//前のポインタの設定

	CGameScene* GetScene() {return m_pScene;}				//シーンの取得

	UINT GetID() {return m_uID;}						//IDを取得

	//C3DObj* Find(UINT uID,C3DObj* p = NULL);			//オブジェクトの探索

	void SetPos (D3DXVECTOR3& pos)	{m_world._41 = pos.x,m_world._42 = pos.y;m_world._43 = pos.z;}
	
	int GetPosX ();									//配列位置情報Xを返す
	int GetPosZ ();									//配列位置情報Zを返す
};

