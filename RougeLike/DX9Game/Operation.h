#pragma once
//操作説明テクスチャ
#include "C2DTexture.h"

class COperation :
	public C2DTexture
{
private:
	//シングルトン
	static COperation* m_pOperation;

	COperation(void);		//コンストラクタ
	~COperation(void);		//デストラクタ

public:
	static void Create();			//実体の生成
	static void Delete();			//実体の削除
	static COperation* GetPoiner();	//実体のポインタを渡す
};

