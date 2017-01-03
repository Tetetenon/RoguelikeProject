#pragma once

//フィールド上のオブジェクトの管理を行う。


//インクルード
#include<map>
#include<list>
#include<vector>

class CFieldObj;
class CUnit;


typedef std::vector<CFieldObj*>					FIELDOBJ_LIST;	//フィールドオブジェクトのリスト
typedef std::map<int, FIELDOBJ_LIST>			FIELDOBJ_MAP;	//リストとID
typedef std::pair<int, FIELDOBJ_LIST>			FIELDOBJ_PAIR;

class CMapObjManager
{
private:

	//変数

	//マネージャークラス
	static FIELDOBJ_MAP*	m_pMapObjManager;

	static CUnit*			m_pPlayer;			//プレイヤーの位置取得用
	static bool				m_bDeleteFlg;		//全オブジェクト削除フラグ
	static int				m_nNextObjNumber;	//次に生成されたオブジェクトにつける番号

	//関数
	CMapObjManager();							//コンストラクタ
	~CMapObjManager();							//デストラクタ
public:

	static void Init();							//初期化
	static void Fin();							//終了処理
	static void Update();						//更新
	static void Draw(bool Alpha);				//描画

	static void Create();						//フィールドオブジェマネージャーの作成
	static void Delete();						//フィールドオブジェマネージャーの削除

	static void ChangeDeleteFlg(bool ChangeFlg);//フィールドオブジェクトの削除フラグを変更する

	//次のオブジェクトの番号を渡す
	static int	GetNextNumber() { return m_nNextObjNumber; }
	//次のオブジェクト番号を設定
	static void SetNextNumber(int Number) { m_nNextObjNumber = Number; }

	static FIELDOBJ_MAP* GetPointer();		//マネージャーデバイスのポインタを渡す

	static void PlayerSet();				//プレイヤーのポインタを設定する

	//-----フィールドオブジェの操作-----
	//フィールドオブジェクトのリストへの追加
	static void Add(int ObjID,CFieldObj* pObj);
	//フィールドオブジェクトのリスからの削除
	static void Del(int ObjID);
	//リスト上から特定のオブジェクトを探索する
	static CFieldObj* Find(int ObjID);
};

