#pragma once
#include "MeshObj.h"

class CItemGenerator:
	public CMeshObj
{
private:
	static int m_FieldItemCounter;		//フィールド上のアイテムの数をカウントする

	static int m_MaxFieldItem;			//フィールド上に生成する最大数を設定する
public:
	CItemGenerator(CGameScene* pScene);				//コンストラクタ
	~CItemGenerator(void);				//デストラクタ

	void Init();						//初期化
	void Fin();							//終了処理

	void Update();						//更新

	//フィールド上に生成するアイテムの最大数を設定する
	static void SetMaxItem(int MaxItemNum);

	//フィールド上にアイテムを生成する
	 void MakeItem();

	 //アイテム再生数をリセット
	 static void ResetMakeItemNum();
};

