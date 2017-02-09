#pragma once

#include "MeshObj.h"
#include "Unit.h"

class CGameScene;
class CFieldObj :
	public CMeshObj
{
private:
	int m_ObjNumber;				//オブジェクトを一意に定める番号
	bool m_bNearUnitFlg;			//自身の配列上での上にユニットが存在するか
public:
	CFieldObj(CGameScene* pScene);		//コンストラクタ
	virtual ~CFieldObj(void);		//デストラクタ

	void Draw();					//描画
	void DrawAlpha();				//描画(半透明)
	void Update();					//更新(削除フラグの確認用)
	void Fin();						//終了処理

	//自身の上にユニットが存在するか
	bool GetNearUnitFlg()
	{
		return m_bNearUnitFlg;
	}

	//フィールド上にオブジェクトを設置する
	static void SetObject(CMeshObj *pSetter,int nSetNumber,int PosX,int PosY);
};