#pragma once

#include "2DWindow.h"
class CEquipmentWindow;
class CEquipmentCommandWindow;
class CItemWindow;

class CEquipmentWindowCursor:
	public C2DWindow
{
private:
	//シングルトン
	static CEquipmentWindowCursor* m_pEquiomentInventoryCursor;
	int			m_Number;				//現在選択しているアイテムが何番目の物かを管理する
	int			m_nInterval;			//ボタン入力を行ってからのインターバルタイム

	CEquipmentWindow*			m_pEquipmentWindow;			//装備ウィンドウへのポインタ
	CEquipmentCommandWindow*	m_pEquipmentCommandWindow;	//装備コマンドウィンドウへのポインタ
	CItemWindow*				m_pItemWindow;				//アイテムウィンドウへのポインタ

	CEquipmentWindowCursor(void);		//コンストラクタ 
	~CEquipmentWindowCursor(void);	//デストラクタ
public:
	static void Create();							//実体の生成
	static void Delete();							//実体の削除
	static CEquipmentWindowCursor* GetPointer();	//実体のポインターを渡す

	void Draw();				//描画
	void Update();				//更新

	void SetVertex ();			//ポリゴン情報を埋める

	void SetPos();				//ポリゴンの位置情報を設定する

	int GetItemNum();			//選択しているアイテムの情報を返却する。

	//メンバ変数のポインタの設定
	void SetPointer();
};

