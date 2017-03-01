//自機クラス　定義
#pragma once

#include "Unit.h"

class CItemWindowCursor;
class CItemCommandCursor;
class CHPDraw;
class CEquipmentCommandWindow;
class CEquipmentWindowCursor;
class CStatesValue;
class CFade;
class CMenuWindow;


class CPlayer :
	public CUnit 
{
private:
	CItemWindowCursor*			m_pInventoryCursor;				//アイテムウインドウのカーソルの位置を特定する
	CItemCommandCursor*			m_pCommandCursor;				//コマンドカーソルの位置を特定する
	CHPDraw*					m_pHPDraw;						//HPバーへのポインタ
	CEquipmentCommandWindow*	m_pEquipmentCommandWindow;		//装備コマンドへのポインタ
	CEquipmentWindowCursor*	m_pEquipmentInventoryCursor;	//装備アイテムカーソルのポインタ
	CStatesValue*				m_pStatesValue;					//ステータス数値描画へのポインタ
	CFade*						m_pFade;						//フェードへのポインタ
	CMenuWindow*				m_pMenuWindow;					//メニューウィンドウへのポインタ
	int							m_nEquipmentInterval;			//装備コマンドを描画してから、何秒立ったか
	LPD3DXFONT					m_pFont;						//描画フォントの設定
	RECT						m_FontDrawPos;					//フォントの描画位置を設定する
	int							m_nRecoveryInterval;			//回復する間隔数値
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

	void SetPos();					//位置情報を再設定する

	//プレイヤーの技の描画フラグを確認
	bool GetPlayerTrickWindowFlg(){return m_pTrickWindow->GetDrawFlg();}

	//現在のレベルを描画する
	void DrawLevel();

	//メンバ変数のポインタを取得する
	void MemberPointerGet();
};

