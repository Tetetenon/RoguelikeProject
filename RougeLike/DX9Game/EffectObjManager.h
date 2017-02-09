#pragma once

//攻撃ヒット時のエフェクトオブジェクトの管理を行う

//インクルード
#include <map>
#include<list>
#include<vector>

class CEffectObj;

typedef std::vector<CEffectObj*>	EFFECTOBJ_LIST;
typedef std::map<int, EFFECTOBJ_LIST>	EFFECTOBJ_MAP;
typedef std::pair<int, EFFECTOBJ_LIST>	EFFECTOBJ_PAIR;

class CEffectObjManager
{
private:
	//変数

	//シングルトン
	static EFFECTOBJ_MAP*	m_pEffectManager;

	//次のエフェクトの番号
	static int				m_nEffectNumber;

	//関数

	CEffectObjManager();					//コンストラクタ
	~CEffectObjManager();					//デストラクタ
public:
	//関数
	static void Init();						//初期化
	static void Fin();						//終了処理
	static void Update();					//更新
	static void Draw();						//描画

	static void Create();					//マネージャーの作成
	static void Delete();					//マネージャーの削除

	//エフェクトの番号の取得
	static int GetEffectNumber() { return m_nEffectNumber; }
	//エフェクト番号の設定
	static void SetEffectNumber(int nNumber) { m_nEffectNumber = nNumber; }

	//-----リストの操作-----
	//オブジェクトの追加
	static void Add(int ID, CEffectObj* pAdd);
	//オブジェクトの削除
	static void Del(int ID);
	//オブジェクトの探索
	static CEffectObj* Find(int ID);
};

