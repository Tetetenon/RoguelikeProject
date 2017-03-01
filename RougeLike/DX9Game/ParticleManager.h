#pragma once

//パーティクルの管理を行う

//インクルード
#include<map>
#include<list>
#include<vector>

class CParticle;

typedef std::vector<CParticle*>			PARTICLE_LIST;
typedef std::map<int, PARTICLE_LIST>	PARTICLE_MAP;
typedef std::pair<int, PARTICLE_LIST>	PARTICLE_PAIR;

class CParticleManager
{
private:
	//変数
	//マネージャーポインタ
	static CParticleManager* m_pParticleManager;
	PARTICLE_MAP*	m_pParticleMap;
	int				m_nNextID;

	//関数
	CParticleManager();			//コンストラクタ
	~CParticleManager();		//デストラクタ

public:
	void Init();				//初期化
	void Fin();				//終了処理
	void Update();			//更新処理
	void Draw();				//描画

	static void Create();			//マネージャーの作成
	static void Delete();			//マネージャーの削除
	static CParticleManager* GetPointer();	//マネージャーのポインタを渡す

	//次に作成するパーティクルの番号を渡す
	int GetNextID() { return m_nNextID; }
	//次に作成するオブジェクト番号を設定
	void SetNextID(int SetID) { m_nNextID = SetID; }

	//-----パーティクルの管理-----
	//リストへ追加
	void Add(int ID, CParticle* pObj);
	//リストから削除
	void Del(int ID);
	//リストから検索
	CParticle* Find(int ID);
};