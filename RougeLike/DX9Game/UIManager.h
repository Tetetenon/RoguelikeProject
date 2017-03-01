#pragma once

//全てのUIの描画、更新などの管理を行う

//クラスの定義
class CItemWindow;					//アイテムウィンドウ
class CItemWindowCursor;			//アイテムカーソル
class CItemCommandWindow;			//アイテムコマンドウィンドウ
class CItemCommandCursor;			//コマンド選択カーソル

class CHPDraw;						//HPの描画

class CMenuWindow;					//メニューウィンドウ
class CMenuSelect;					//メニューセレクトカーソル
class CMenuWindow_Back;				//メニューウィンドウの背景

class CMenuStatesWindow;			//メニューステータスウィンドウ

class CStatesWindow;				//ステータスウィンドウ
class CStatesCharacter;				//キャラクター画像
class CStatesFont;					//キャラクターステータスの文字
class CStatesValue;					//キャラクターステータス数値

class CEquipmentWindow;				//装備ウィンドウ
class CEquipmentWindowCursor;		//装備選択カーソル
class CEquipmentCommandWindow;		//装備コマンドウィンドウ
class CEquipmentCommandCursor;		//装備コマンドカーソル

class CTrickWindow;					//技ウィンドウ
class CTrickWindowCursor;			//技カーソル

class COperation;					//操作説明
class CMiniMap;						//ミニマップ
class CMessageWindow;				//メッセージウィンドウ

class CUIManager
{
private:
	//シングルトンにすることで、UIの多重作成を防止し、ユニーク性を確保
	static CUIManager* m_pUIManager;

	//各管理クラスのポインタ
	CItemWindow*				m_pItemWindow;
	CItemWindowCursor*			m_pItemWindowCursor;
	CItemCommandWindow*			m_pItemCommandWindow;
	CItemCommandCursor*			m_pItemCommandCursor;

	CHPDraw*					m_pHPDraw;

	CMenuWindow*				m_pMenuWindow;
	CMenuSelect*				m_pMenuSelect;
	CMenuWindow_Back*			m_pMenuBack;

	CMenuStatesWindow*			m_pMenuStatesWindow;

	CStatesWindow*				m_pStatesWindow;
	CStatesCharacter*			m_pStatesCharcter;
	CStatesFont*				m_pStatesFont;
	CStatesValue*				m_pStatesValue;

	CEquipmentWindow*			m_pEquipmentWindow;
	CEquipmentWindowCursor*		m_pEquipmentWindowCursor;
	CEquipmentCommandWindow*	m_pEquipmentCommandWindow;
	CEquipmentCommandCursor*	m_pEquipmentCommandCursor;

	CTrickWindow*				m_pTrickWindow;
	CTrickWindowCursor*			m_pTrickWindowCursor;

	COperation*					m_pOperation;
	CMiniMap*					m_pMiniMap;
	CMessageWindow*				m_pMessageWindow;

	CUIManager();						//コンストラクタ
	~CUIManager();						//デストラクタ
public:
	static void Create();				//マネージャーの作成
	static void Delete();				//マネージャーの削除

	static CUIManager* GetPointer();	//マネジャーポインタの取得

	void ManageUIInit();				//各UIの初期化
	void ManageUIUpdate();				//各UIの更新
	void ManageUIDraw();				//各UIの描画	

	void ItemWindowUpdate();			//アイテムウィンドウの更新
	void ItemWindowDraw();				//アイテムウィンドウの描画

	void ManageUISetPointer();			//各UIメンバ変数のポインタを設定する
};