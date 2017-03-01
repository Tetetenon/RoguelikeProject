#pragma once

#include "2DWindow.h"
#include "Item.h"
#include "Equipment.h"

class CEquipmentCommandWindow;
class CEquipmentWindowCursor;
class CMenuWindow;
class CItemWindow;

class CEquipmentWindow:
	public CItem,
	public C2DWindow
{
private:
	//シングルトン
	static CEquipmentWindow* m_pEquipmentWindow;

	LPD3DXFONT			m_Font;					//描画用フォント
	RECT				m_Pos[EQUIPMENT_NUM_MAX];	//ウィンドウ表示位置
	bool				m_bDrawFlg;				//描画フラグ
	VERTEX_2D			m_aVertex[EQUIPMENT_NUM_MAX][NUM_VERTEX];	//ポリゴン頂点情報格納用

	int					m_nInterval;

	CEquipmentCommandWindow*		m_pCommandWindow;		//コマンドウインドウの描画フラグ変更用
	CEquipmentWindowCursor*			m_pInventoryCursor;		//選択しているアイテムウインドウの取得
	CEquipment*						m_pPlayerEquipment;		//プレイヤーの装備アイテムへのポインタ
	CMenuWindow*					m_pMenuWindow;			//メニューウィンドウへのポインタ
	CItemWindow*					m_pItemWindow;			//アイテムウィンドウポインタ
	CEquipmentWindow(void);							//コンストラクタ
	~CEquipmentWindow(void);							//デストラクタ
public:
	static void Create();						//実体の作成
	static void Delete();						//実体の削除
	static CEquipmentWindow* GetPointer();	//実体のポインタを渡す

	void UpDate();								//更新部
	void Draw();								//描画

	void DrawFlgChange();				//描画フラグをON/OFFする

	void SetVertex();							//ポリゴン情報を埋める
	void SetFontPos();							//フォント描画位置設定

	//描画のフラグ状況を取得
	bool GetDrawFlg()	{return m_bDrawFlg;}

	//メンバ変数のポインタを設定する
	void SetPointer();
};

