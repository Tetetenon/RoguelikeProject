#pragma once

#include "2DWindow.h"
#include "EquipmentWindow.h"
#include "EquipmentCommandWindow.h"

class CEquipmentInventoryCursor:
	public C2DWindow
{
private:
	static int			m_Number;				//現在選択しているアイテムが何番目の物かを管理する
public:
	CEquipmentInventoryCursor(void);		//コンストラクタ
	~CEquipmentInventoryCursor(void);	//デストラクタ

	void Init();				//初期化
	void Fin();					//終了処理

	void Draw();				//描画
	void Update();				//更新

	void SetVertex ();			//ポリゴン情報を埋める

	void SetPos();				//ポリゴンの位置情報を設定する

	static int GetItemNum();			//選択しているアイテムの情報を返却する。
};

