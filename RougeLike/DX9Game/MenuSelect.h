#pragma once
#include "C2DTexture.h"

//メニュー項目
enum MENUTAG
{
	MENU_ITEM = 0,		//アイテム
	MENU_TRICK,			//ワザ
	MENU_EQUIPMENT,		//装備確認
	MENU_STATES,		//ステータス
	MENU_MAX
};

class CMenuSelect :
	public C2DTexture
{
private:
	static int	m_nSelectNumber;		//現在選択しているメニュー番号格納用変数
	static bool m_bOperationFlg;		//操作可能フラグ
	static int	m_nInterval;			//ボタン入力のインターバル		
public:
	CMenuSelect(void);					//コンストラクタ
	~CMenuSelect(void);					//デストラクタ

	void Update();						//更新

	//現在の操作フラグ状態を取得
	static bool GetOperationFlg()		{return m_bOperationFlg;}
	//操作フラグの反転
	static void ChangeDrawFlg();
};

