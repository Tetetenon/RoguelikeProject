#include "MapObjManager.h"

#include"FieldObj.h"

FIELDOBJ_MAP* CMapObjManager::m_pMapObjManager = NULL;

bool			CMapObjManager::m_bDeleteFlg = false;		//全オブジェクト削除フラグ
int				CMapObjManager::m_nNextObjNumber = 0;	//次に生成されたオブジェクトにつける番号

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CMapObjManager::CMapObjManager()
{
	//初期化
	m_pMapObjManager->clear();
	m_bDeleteFlg = false;
	m_nNextObjNumber = 0;
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CMapObjManager::~CMapObjManager()
{
	//変数の初期化
	m_bDeleteFlg = false;

	//プレイヤーポインタの開放
	m_nNextObjNumber = 0;

	//中身の掃除
	m_pMapObjManager->clear();
}

//---------------------------------------------------------------------------------------
//マネージャーの作成
//---------------------------------------------------------------------------------------
void CMapObjManager::Create()
{
	//マネージャーが作成されてなければ作成
	if (!m_pMapObjManager)
	{
		m_pMapObjManager = new FIELDOBJ_MAP();
	}
}

//---------------------------------------------------------------------------------------
//マネージャーの削除
//---------------------------------------------------------------------------------------
void CMapObjManager::Delete()
{
	//NULLチェック
	if (m_pMapObjManager)
	{
		//終了処理
		Fin();
		//削除
		delete m_pMapObjManager;
		//中身の掃除
		m_pMapObjManager = NULL;
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの追加
//---------------------------------------------------------------------------------------
void CMapObjManager::Add(int ObjID,CFieldObj* pAddObj)
{
	//IDでオブジェクトの検索
	auto ObjIterator = m_pMapObjManager->find(ObjID);

	//そのIDのオブジェクトが既に登録されているか確認する
	if (ObjIterator != m_pMapObjManager->end())
	{
		//登録されているため、オブジェデータのみ挿入
		ObjIterator->second.push_back(pAddObj);
	}
	else
	{
		//IDも登録されていないため、ID,オブジェデータともに登録する
		FIELDOBJ_LIST NewObjList;
		NewObjList.push_back(pAddObj);


		FIELDOBJ_PAIR NewObjPair(ObjID,NewObjList);
		m_pMapObjManager->insert(NewObjPair);
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの削除
//---------------------------------------------------------------------------------------
void CMapObjManager::Del(int ObjID)
{
	//IDでオブジェクトの検索
	auto ObjIterator = m_pMapObjManager->find(ObjID);

	//そのオブジェクトのIDが存在してる場合、削除
	if (ObjIterator != m_pMapObjManager->end())
	{
		auto ListIterator = ObjIterator->second.begin();
		(*ListIterator)->Fin();
		delete (*ListIterator);
		ObjIterator->second.erase(ListIterator);
		//m_pMapObjManager->erase(ObjIterator);
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの中から、指定されたIDのオブジェクトを返す
//---------------------------------------------------------------------------------------
CFieldObj* CMapObjManager::Find(int ObjID)
{
	//IDでオブジェクトの検索
	auto ObjIterator = m_pMapObjManager->find(ObjID);

	//そのオブジェクトのIDが存在してる場合、データを返す
	if (ObjIterator != m_pMapObjManager->end())
	{
		return ObjIterator->second[0];
	}
	else
	{
		return NULL;
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの初期化
//---------------------------------------------------------------------------------------
void CMapObjManager::Init()
{
	//リストの先頭を取得
	auto MapIterator = m_pMapObjManager->begin();

	for (; MapIterator != m_pMapObjManager->end(); ++MapIterator)
	{
		for (auto ListIterator = MapIterator->second.begin(); ListIterator != MapIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Init();
		}
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの更新
//---------------------------------------------------------------------------------------
void CMapObjManager::Update()
{
	//リストの先頭を取得
	auto MapIterator = m_pMapObjManager->begin();

	for (; MapIterator != m_pMapObjManager->end(); ++MapIterator)
	{
		for (auto ListIterator = MapIterator->second.begin(); ListIterator != MapIterator->second.end();)
		{
			//削除フラグが立っていた場合、削除処理を行う
			if (m_bDeleteFlg)
			{
				//削除処理
				(*ListIterator)->Fin();
				delete (*ListIterator);
				ListIterator = MapIterator->second.erase(ListIterator);
			}
			else
			{
				//更新
				(*ListIterator)->Update();
				 ListIterator++;
			}
		}
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの描画
//---------------------------------------------------------------------------------------
void CMapObjManager::Draw(bool Alpha)//Alpha:半透明描画をするか
{
	//リストの先頭を取得する
	auto MapIterator = m_pMapObjManager->begin();

	//リスト上のフィールドオブジェクト全ての描画処理を行う
	for (; MapIterator != m_pMapObjManager->end(); ++MapIterator)
	{
		for (auto ListIterator = MapIterator->second.begin(); ListIterator != MapIterator->second.end(); ++ListIterator)
		{
			//描画するオブジェクトの上にユニットが存在するかどうかで、描画を切り替える
			if ((*ListIterator)->GetNearUnitFlg())
			{
				if (Alpha)
					(*ListIterator)->DrawAlpha();
			}
			else
			{
				if (!Alpha)
					(*ListIterator)->Draw();
			}
			
		}
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの終了処理
//---------------------------------------------------------------------------------------
void CMapObjManager::Fin()
{
	//リストの先頭を取得
	auto MapIterator = m_pMapObjManager->begin();

	for (; MapIterator != m_pMapObjManager->end();++MapIterator)
	{
		for (auto ListIterator = MapIterator->second.begin(); ListIterator != MapIterator->second.end();)
		{
			//終了処理
			(*ListIterator)->Fin();
			delete(*ListIterator);
			(*ListIterator) = NULL;
			ListIterator = MapIterator->second.erase(ListIterator);
		}
	}

	//リストを掃除
	m_pMapObjManager->clear();
}
//---------------------------------------------------------------------------------------
//マネージャーのデバイスを渡す
//---------------------------------------------------------------------------------------
FIELDOBJ_MAP* CMapObjManager::GetPointer()
{
	return m_pMapObjManager;
}
//---------------------------------------------------------------------------------------
//フィールドオブジェクトの削除フラグを変更する
//---------------------------------------------------------------------------------------
void CMapObjManager::ChangeDeleteFlg(bool ChangeFlg)
{
	m_bDeleteFlg = ChangeFlg;
}