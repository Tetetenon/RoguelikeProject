#pragma once

#include "MeshObj.h"

class CFieldObjMaker:
	public CMeshObj
{
private:
public:
	CFieldObjMaker(CGameScene* pScene);		//コンストラクタ
	~CFieldObjMaker(void);		//デストラクタ

	//フィールドオブジェ設置関数
	void PutObj(int SetNumber,int PosX,int PosY);
};

