#pragma once

//攻撃ヒット時のビルボードの管理を行う

//インクルード
#include <map>
#include<list>
#include<vector>

//ダメージ表示を行うクラス
class CDamageNotation;

//型の定義
typedef std::vector<CDamageNotation*>			DAMAGE_NOTATION_LIST;
typedef std::map <int, DAMAGE_NOTATION_LIST>	DAMAGE_NOTATION_MAP;
typedef std::pair<int, DAMAGE_NOTATION_LIST>		DAMAGE_NOTATION_PAIR;

class CDamageBillBoardManager
{
private:
	//変数
	//シングルトン
	static CDamageBillBoardManager* m_pManager;


	DAMAGE_NOTATION_MAP* m_pDamageBillBoardMap;
	//次のビルボードの番号
	int m_nNextBillBoardNumber;

	//関数
	CDamageBillBoardManager();		//コンストラクタ
	~CDamageBillBoardManager();		//デストラクタ
public:
	//関数
	void ManagerObjFin();			//管理オブジェクトの終了処理
	void ManagerObjUpdate();		//管理オブジェクトの更新
	void ManagerObjDraw();			//管理オブジェクトの更新

	//マネージャーの作成、削除
	static void Create();
	static void Delete();

	//ポインタを渡す
	static CDamageBillBoardManager* GetPointer();

	//次に割り振る番号の取得
	int GetNextNumber()
	{
		return m_nNextBillBoardNumber;
	}

	//次に割り振る番号の設定
	void SetNextNumber(int nNumber)
	{
		m_nNextBillBoardNumber = nNumber;
	}

	//-----リストの操作-----
	void Add(int ID, CDamageNotation* pAddObj);	//オブジェクトの追加
	void Del(int ID);							//オブジェクトの削除
	CDamageNotation* Find(int ID);				//オブジェクトの検索

};

