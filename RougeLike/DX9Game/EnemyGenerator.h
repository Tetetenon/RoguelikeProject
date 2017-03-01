#pragma once
#include "meshobj.h"

class CMapData;
class CUnit;

class CEnemyGenerator :
	public CMeshObj
{
private:
	//シングルトン
	static CEnemyGenerator* m_pEnemyGenerator;

	CMapData*	m_pMapData;
	CUnit*		m_pPlayer;

	int m_FieldEnemyCounter;			//フィールド上のエネミーの数をカウントする
	int m_MaxFieldEnemy;				//フィールド上に生成する最大数を設定
	bool m_bMakeFlg;					//そのターンでの生成フラグ

	CEnemyGenerator(CGameScene* pScene);	//コンストラクタ
	~CEnemyGenerator(void);				//デストラクタ
public:

	static void Create(CGameScene *pScene);
	static void Delete();
	static CEnemyGenerator* GetPointer();

	//メンバ変数のポインタを設定する
	void SetPointer();

	void Update();						//更新

	//フィールド上に生成できる最大数を設定
	void SetMaxGenerator (int nMaxCount);

	//エネミー生成数を減算
	void SumMakeEnemyNum();

	//フィールド上にランダムに敵を配置する
	void MakeEnemy();

	//エネミーの生成数をリセット
	void  ResetMakeEnemyNum();
};