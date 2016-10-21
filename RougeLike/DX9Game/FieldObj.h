#pragma once

#include "MeshObj.h"
#include "Unit.h"

class CGameScene;
class CFieldObj :
	public CMeshObj
{
private:
	static CMeshObj*	m_pPlayer;	//プレイヤーの位置情報取得用
	static bool m_bDeleteObj;		//全フィールドオブジェ削除フラグ
	static int	m_Counter;			//作った数	
public:
	CFieldObj(CGameScene* pScene);		//コンストラクタ
	virtual ~CFieldObj(void);		//デストラクタ

	void Draw();					//描画
	void DrawAlpha();				//描画(半透明)
	void Update();					//更新(削除フラグの確認用)
	void Fin();						//終了処理

	//フィールド上にオブジェクトを設置する
	static void SetObject(CMeshObj *pSetter,int nSetNumber,int PosX,int PosY);

	//削除フラグを上げる
	static void DeleteObjFlgUp(){m_bDeleteObj = true;}

	//削除フラグを下げる
	static void DeleteObjFlgDown(){m_bDeleteObj = false;}
};

