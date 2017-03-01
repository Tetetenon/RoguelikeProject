#pragma once

#include "2DWindow.h"
#include "Turn.h"
#include "EquipmentCommandWindow.h"

//コマンド選択画面のカーソル

class CEquipmentCommandWindow;

class CEquipmentCommandCursor:
	public C2DWindow
{
private:
	//シングルトン
	static CEquipmentCommandCursor* m_pEquipmentCommandCursor;

	int		m_Command;				//何番目のコマンドを選択しているかを格納する
	int		m_nInterval;			//ボタン入力のインターバル
	CEquipmentCommandWindow* m_pEquipmentCommandWindow;

	CEquipmentCommandCursor(void);								//コンストラクタ
	virtual ~CEquipmentCommandCursor(void);						//デストラクタ
public:
	static void Create();								//実体の作成
	static void Delete();								//実体の削除
	static CEquipmentCommandCursor* GetPointer();		//実体のポインタを渡す

	void Draw();										//描画
	void Update();										//更新

	void SetVertex();									//ポリゴン情報を埋める
	void SetPos();										//ポリゴンの位置情報を設定する

	int  GetCommand();									//選択したコマンドを返す 

	//メンバ変数のポインタの設定
	void SetPointer();
};

