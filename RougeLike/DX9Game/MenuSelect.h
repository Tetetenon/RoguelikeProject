#pragma once
#include "C2DTexture.h"

//ステータスウィンドウクラスの定義
class CStatesWindow;
class CItemWindow;
class CTrickWindow;
class CEquipmentWindow;

//メニュー項目
enum MENUTAG
{
	MENU_ITEM = 0,		//アイテム
	MENU_TRICK,			//ワザ
	MENU_MAX
};

class CMenuSelect :
	public C2DTexture
{
private:
	//シングルトン
	static CMenuSelect* m_pMenuSelect;

	int	m_nSelectNumber;		//現在選択しているメニュー番号格納用変数
	bool m_bOperationFlg;		//操作可能フラグ
	int	m_nInterval;			//ボタン入力のインターバル

	CStatesWindow*		m_pStatesWindow;		//ステータスウィンドウのポインタ
	CItemWindow*		m_pItemWindow;
	CTrickWindow*		m_pTrickWindow;
	CEquipmentWindow*	m_pEquipmentWindow;

	CMenuSelect(void);					//コンストラクタ
	~CMenuSelect(void);					//デストラクタ
public:
	//実体の作成
	static void Create();
	//実体の削除
	static void Delete();
	//実体のポインタを渡す
	static CMenuSelect* GetPointer();

	void Update();						//更新
	//現在の操作フラグ状態を取得
	bool GetOperationFlg()		{return m_bOperationFlg;}
	//メンバ変数のポインタを設定する
	void SetPointer();
};

