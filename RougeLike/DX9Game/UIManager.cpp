#include "UIManager.h"
//-----アイテムウインドウ-----
#include "ItemWindow.h"
#include "ItemWindowCursor.h"		//アイテムカーソル
#include "ItemCommandWindow.h"		//コマンドウインドウ
#include "ItemCommandCursor.h"		//コマンド選択カーソル
#include "ItemDescriptionFrame.h"	//アイテム説明
//-----ステータス描画-----
#include "HPDraw.h"
//-----メニューウインドウ-----
#include "MenuWindow.h"				//メニューウインドウテクスチャ描画
#include "MenuSelect.h"				//メニューウィンドウのセレクト用ポリゴン
#include "MenuWindow_Back.h"		//メニューウィンドウの背景
#include "MenuStatesWindow.h"
//-----ステータスウィンドウ-----
#include "StatesWindow.h"			//ステータスのウィンドウのみ
#include "StatesCharacter.h"		//キャラクターウィンドウ
#include "StatesFont.h"				//キャラクターステータスの文字
#include "StatesValue.h"			//キャラクターのステータス
//-----装備ウィンドウ-----
#include "EquipmentWindow.h"		//装備ウィンドウ
#include "EquipmentWindowCursor.h"	//装備選択カーソル
#include "EquipmentCommandWindow.h"	//装備コマンドウィンドウ
#include "EquipmentCommandCursor.h"	//装備コマンドカーソル
//-----技ウィンドウ-----
#include "TrickWindow.h"			//技ウィンドウ
#include "TrickWindowCursor.h"		//技カーソル
//-----その他-----
#include "Operation.h"				//操作説明
#include "MiniMap.h"				//ミニマップ処理
#include "HierarchieNum.h"			//現在の階層数を、フェードイン中に表示する
#include "MessageWindow.h"			//メッセージウィンドウ
//---------------------------------------------------------------------------------------
//静的メンバ変数宣言
//---------------------------------------------------------------------------------------
CUIManager* CUIManager::m_pUIManager = NULL;
//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CUIManager::CUIManager()
{
	//シングルトンの作成
	CItemWindow::Create();
	CItemWindowCursor::Create();
	CItemCommandWindow::Create();
	CItemCommandCursor::Create();
	CItemDescriptionFrame::Create();

	CHPDraw::Create();

	CMenuSelect::Create();
	CMenuWindow_Back::Create();

	CMenuStatesWindow::Create();

	CStatesWindow::Create();
	CStatesCharacter::Create();
	CStatesFont::Create();
	CStatesValue::Create();

	CEquipmentWindow::Create();
	CEquipmentWindowCursor::Create();
	CEquipmentCommandWindow::Create();
	CEquipmentCommandCursor::Create();

	CTrickWindowCursor::Create();
	CTrickWindow::Create();

	COperation::Create();
	CMiniMap::Create();
	CHierarchieNum::Create();
	CMessageWindow::Create();
	CMenuWindow::Create();

	//-----各ポインタの取得-----
	m_pItemWindow				= CItemWindow::GetPointer();
	m_pItemWindowCursor			= CItemWindowCursor::GetPointer();
	m_pItemCommandWindow		= CItemCommandWindow::GetPointer();
	m_pItemCommandCursor		= CItemCommandCursor::GetPointer();

	m_pHPDraw					= CHPDraw::GetPointer();

	m_pMenuSelect				= CMenuSelect::GetPointer();
	m_pMenuBack					= CMenuWindow_Back::GetPointer();

	m_pMenuStatesWindow			= CMenuStatesWindow::GetPointer();

	m_pStatesWindow				= CStatesWindow::GetPointer();
	m_pStatesCharcter			= CStatesCharacter::GetPointer();
	m_pStatesFont				= CStatesFont::GetPointer();
	m_pStatesValue				= CStatesValue::GetPointer();

	m_pEquipmentWindow			= CEquipmentWindow::GetPointer();
	m_pEquipmentWindowCursor	= CEquipmentWindowCursor::GetPointer();
	m_pEquipmentCommandWindow	= CEquipmentCommandWindow::GetPointer();
	m_pEquipmentCommandCursor	= CEquipmentCommandCursor::GetPointer();

	m_pTrickWindow				= CTrickWindow::GetPointer();
	m_pTrickWindowCursor		= CTrickWindowCursor::GetPointer();

	m_pOperation				= COperation::GetPoiner();
	m_pMiniMap					= CMiniMap::GetPointer();
	m_pMessageWindow			= CMessageWindow::GetPointer();
	m_pMenuWindow				= CMenuWindow::GetPointer();
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CUIManager::~CUIManager()
{
	//シングルトンの削除
	CItemWindow::Delete();
	CItemWindowCursor::Delete();
	CItemCommandWindow::Delete();
	CItemCommandCursor::Delete();
	CItemDescriptionFrame::Delete();

	CHPDraw::Delete();

	CMenuWindow::Delete();
	CMenuSelect::Delete();
	CMenuWindow_Back::Delete();

	CMenuStatesWindow::Delete();

	CStatesWindow::Delete();
	CStatesCharacter::Delete();
	CStatesFont::Delete();
	CStatesValue::Delete();

	CEquipmentWindow::Delete();
	CEquipmentWindowCursor::Delete();
	CEquipmentCommandWindow::Delete();
	CEquipmentCommandCursor::Delete();

	CTrickWindow::Delete();
	CTrickWindowCursor::Delete();

	COperation::Delete();
	CMiniMap::Delete();
	CHierarchieNum::Delete();
	CMessageWindow::Delete();
}
//---------------------------------------------------------------------------------------
//マネージャーの実体の作成
//---------------------------------------------------------------------------------------
void CUIManager::Create()
{
	//実体がなければ作成
	if (!m_pUIManager)
	{
		m_pUIManager = new CUIManager;
	}
}
//---------------------------------------------------------------------------------------
//マネージャーの実体を削除
//---------------------------------------------------------------------------------------
void CUIManager::Delete()
{
	//実体があれば削除
	if (m_pUIManager)
	{
		delete m_pUIManager;
		m_pUIManager = NULL;
	}
}
//---------------------------------------------------------------------------------------
//マネージャーのポインタを渡す
//---------------------------------------------------------------------------------------
CUIManager* CUIManager::GetPointer()
{
	//念のため作成関数を呼ぶ
	Create();
	return m_pUIManager;
}
//---------------------------------------------------------------------------------------
//各UIの更新
//---------------------------------------------------------------------------------------
void CUIManager::ManageUIUpdate()
{
	m_pMessageWindow->Update();	//メッセージウインドウ更新
	m_pHPDraw->Update();			//HP更新

	//メニューウィンドウの描画が行われているか？
	if(m_pMenuWindow->GetDrawFlg())
	{
		//ステータスウィンドウの描画が行われているか？
		if (!m_pStatesWindow->GetDrawFlg())
		{
			//メニューウィンドウのセレクトを更新
			m_pMenuSelect->Update();
			//メニューウィンドウの入力更新
			m_pMenuWindow->Update();
			//メニューステータスウィンドウの更新
			m_pMenuStatesWindow->Update();
		}
	}
	//ステータスウィンドウの更新(キー入力の更新)
	m_pStatesWindow->Update();

	//アイテムウィンドウの更新
	ItemWindowUpdate();

	//プレイヤーの技ウィンドウの描画フラグを確認
	if (m_pTrickWindow->GetDrawFlg())
	{
		//技ウィンドウの更新
		m_pTrickWindow->UpDate();
		//技ウィンドウのカーソルを更新
		m_pTrickWindowCursor->Update();
	}
	//ステータスウィンドウのサイズの更新
	m_pStatesWindow->WindowSizeUpdate();

	// ミニマップの更新
	m_pMiniMap->Update();

}
//---------------------------------------------------------------------------------------
//各UIの描画
//---------------------------------------------------------------------------------------
void CUIManager::ManageUIDraw()
{
	//メッセージウインドウ描画
	m_pMessageWindow->Draw();
	//操作説明描画
	m_pOperation->Draw();
	//ステータスのウィンドウを描画する
	m_pStatesWindow->Draw();
	//HP描画
	m_pHPDraw->Draw();
	//キャラクターウィンドウの描画
	m_pStatesCharcter->Draw();

	//メニューウィンドウの描画フラグが立っているか確認
	if (m_pMenuWindow->GetDrawFlg())
	{
		//メニューウィンドウの背景描画
		m_pMenuBack->Draw();
		//セレクトメニューテクスチャ描画
		m_pMenuSelect->Draw();
		//メニューウィンドウテクスチャ描画
		m_pMenuWindow->Draw();

		//メニューステータスウィンドウの描画
		m_pMenuStatesWindow->Draw();
		//ステータスの文字を描画する
		m_pStatesFont->Draw();
		//ステータスの数値を描画する
		m_pStatesValue->Draw();
	}

	//アイテムウィンドウの描画
	ItemWindowDraw();

	//プレイヤーの技ウィンドウの描画フラグを確認
	if (m_pTrickWindow->GetDrawFlg())
	{
		//技ウィンドウを描画
		m_pTrickWindow->Draw();
		//技ウィンドウのカーソルを描画
		m_pTrickWindowCursor->Draw();
	}

	//メニューウィンドウの描画してなければ描画
	if (!m_pMenuWindow->GetDrawFlg())
	{
		//ミニマップの描画
		m_pMiniMap->Draw();
	}
}
//---------------------------------------------------------------------------------------
//アイテムウィンドウの更新
//---------------------------------------------------------------------------------------
void CUIManager::ItemWindowUpdate()
{
	//アイテムウィンドウの描画が行われていない場合、処理を行わない
	if (!m_pItemWindow->GetDrawFlg())
		return;

	//アイテムウィンドウの更新フラグが立っていればアイテムウィンドウを更新する
	if (m_pItemWindow->GetUpdateFlg())
	{
		//コマンドウインドウが描画されているか判別を行う
		if (m_pItemCommandWindow->GetDrawFlg())
		{
			//コマンドウインドウの更新
			m_pItemCommandWindow->UpDate();
			//コマンドカーソルの更新
			m_pItemCommandCursor->Update();
		}
		else
		{
			//アイテムウィンドウの更新
			m_pItemWindow->UpDate();
			//ウインドウカーソルの更新
			m_pItemWindowCursor->Update();
		}
	}
	else
	{
		//装備コマンドウインドウが描画されているか判別を行う
		if (m_pEquipmentCommandWindow->GetDrawFlg())
		{
			//装備ウインドウの更新
			m_pEquipmentCommandWindow->UpDate();
			//装備カーソルの更新
			m_pEquipmentCommandCursor->Update();
		}
		else
		{
			//装備ウィンドウの更新
			m_pEquipmentWindow->UpDate();
			//装備ウインドウカーソルの更新
			m_pEquipmentWindowCursor->Update();
		}
	}
}


//---------------------------------------------------------------------------------------
//アイテムウィンドウの描画
//---------------------------------------------------------------------------------------
void CUIManager::ItemWindowDraw()
{
	//アイテムウィンドウの描画をしていない場合処理を行わない
	if (!m_pItemWindow->GetDrawFlg())
		return;
	//アイテムウインドウの描画
	m_pItemWindow->Draw();

	//装備ウインドウの描画
	m_pEquipmentWindow->Draw();

	//コマンドカーソルが描画処理を行うか判別を行う
	if (m_pItemCommandWindow->GetDrawFlg())
	{
		//コマンドウインドウ描画
		m_pItemCommandWindow->Draw();
		//コマンドカーソルの描画
		m_pItemCommandCursor->Draw();
	}

	//アイテムウィンドウ側の更新を行う場合
	if (m_pItemWindow->GetUpdateFlg())
	{
		//アイテムウィンドウカーソルを描画
		m_pItemWindowCursor->Draw();
	}
	else if (m_pItemWindow->GetDrawFlg())
	{
		//装備カーソルの描画
		m_pEquipmentWindowCursor->Draw();
	}
	//コマンドカーソルが描画処理を行うか判別を行う
	if (m_pEquipmentCommandWindow->GetDrawFlg())
	{
		//装備コマンドウインドウ描画
		m_pEquipmentCommandWindow->Draw();
		//装備コマンドカーソルの描画
		m_pEquipmentCommandCursor->Draw();
	}
}
//---------------------------------------------------------------------------------------
//各UIのメンバ変数のポインタをセットする
//---------------------------------------------------------------------------------------
void CUIManager::ManageUISetPointer()
{
	m_pItemWindow				->SetPoiner();
	m_pItemWindowCursor			->SetPointer();
	m_pItemCommandWindow		->SetPointer();
	m_pItemCommandCursor		->SetPointer();
	m_pMenuSelect				->SetPointer();
	m_pStatesWindow				->SetPointer();
	m_pEquipmentWindow			->SetPointer();
	m_pEquipmentWindowCursor	->SetPointer();
	m_pEquipmentCommandWindow	->SetPointer();
	m_pEquipmentCommandCursor	->SetPointer();
	m_pTrickWindow				->SetPointer();
	m_pTrickWindowCursor		->SetPointer();
	m_pMiniMap					->SetPointer();
}
//---------------------------------------------------------------------------------------
//各UIの初期化
//---------------------------------------------------------------------------------------
void CUIManager::ManageUIInit()
{
	m_pMessageWindow->InitFontData();
}