//自機クラス　定義
#pragma once

#include "Unit.h"

class CInventoryCursor;
class CCommandCursor;


class CPlayer :
	public CUnit 
{
private:
	static CInventoryCursor m_InventoryCursor;		//アイテムウインドウのカーソルの位置を特定する
	static CCommandCursor	m_CommandCursor;		//コマンドカーソルの位置を特定する

	static CTurn::GameState	m_State_Cpy;			//ステートを外部から変更をかける際に使用する
	static bool				m_bState_Change_Flg;	//ステートに変更がかかったか

	int						m_nEquipmentInterval;	//装備コマンドを描画してから、何秒立ったか

	static LPD3DXFONT		m_pFont;				//描画フォントの設定
	static RECT				m_FontDrawPos;			//フォントの描画位置を設定する
	static int				m_nDividPattern;		//生成するマップパターン
public:
	CPlayer(CGameScene* pScene);					//コンストラクタ
	~CPlayer(void);								//デストラクタ

	void Update();						//更新処理
	void Draw();						//描画
	
	void SetFontPos();					//文字描画位置を設定

	//ステート別更新
	void InputUpdate();					//入力更新

	void MoveUpdate();					//移動更新

	void ActUpdate();					//アクション更新

	void ItemUpdate();					//アイテム使用更新
	void TurnEndUpdate();				//ターン終了更新

	static void SetState(CTurn::GameState nState);//外部からステートの状態を変更させる

	//現在のステート情報を渡す
	static int GetState();

	void	SetPos();					//位置情報を再設定する

	void DrawInventory();				//自身のアイテムを描画させる
	void DrawEquipment();				//自身の装備を描画させる
	void DrawTrick();					//自身の技を描画させる

	//プレイヤーの技の描画フラグを確認
	bool GetPlayerTrickWindowFlg(){return m_pTrickWindow->GetDrawFlg();}

	//現在のレベルを描画する
	void DrawLevel();
};

