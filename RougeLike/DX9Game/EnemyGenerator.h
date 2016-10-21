#pragma once
#include "meshobj.h"

class CEnemyGenerator :
	public CMeshObj
{
private:
	static int m_FieldEnemyCounter;			//フィールド上のエネミーの数をカウントする

	static int m_MaxFieldEnemy;				//フィールド上に生成する最大数を設定

	static bool m_bMakeFlg;					//そのターンでの生成フラグ
public:
	CEnemyGenerator(CGameScene* pScene);	//コンストラクタ
	~CEnemyGenerator(void);				//デストラクタ

	void Init();						//初期化
	void Fin();							//終了処理

	void Update();						//更新

	//フィールド上に生成できる最大数を設定
	static void SetMaxGenerator (int nMaxCount);

	//エネミー生成数を減算
	static void SumMakeEnemyNum();

	//フィールド上にランダムに敵を配置する
	void MakeEnemy();

	//エネミーの生成数をリセット
	static void  ResetMakeEnemyNum();
};