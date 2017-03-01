#include "MenuSelect.h"
#include "TextureManager.h"
#include "Input.h"
#include "ItemWindow.h"
#include "StatesWindow.h"
#include "EquipmentWindow.h"
#include "TrickWindow.h"

//---------------------------------------------------------------------------------------
//静的メンバ変数
//---------------------------------------------------------------------------------------
CMenuSelect* CMenuSelect::m_pMenuSelect = NULL;

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CMenuSelect::CMenuSelect(void)
{
	//使用するテクスチャIDの設定
	m_nTextureID = TEXTURE_RED_TEXTURE;

	//選択中コマンドの設定
	m_nSelectNumber = 0;

	//ボタン入力経過時間を初期化
	m_nInterval = 0;

	//操作フラグの初期化
	m_bOperationFlg = false;

	//位置情報の設定
	m_aVertex[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 240.0f , 50.0f ,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(SCREEN_WIDTH -  10.0f , 50.0f ,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 240.0f ,205.0f ,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(SCREEN_WIDTH -  10.0f ,205.0f ,0.0f);
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CMenuSelect::~CMenuSelect(void)
{
	//操作フラグの初期化
	m_bOperationFlg = false;

	//ボタン入力経過時間を初期化
	m_nInterval = 0;
}
//---------------------------------------------------------------------------------------
//実体の生成
//---------------------------------------------------------------------------------------
void CMenuSelect::Create()
{
	//中身がなければ作成
	if (!m_pMenuSelect)
	{
		m_pMenuSelect = new CMenuSelect;
	}
}
//---------------------------------------------------------------------------------------
//実体の削除
//---------------------------------------------------------------------------------------
void CMenuSelect::Delete()
{
	//実体があれば削除
	if (m_pMenuSelect)
	{
		delete m_pMenuSelect;
		m_pMenuSelect = NULL;
	}
}
//---------------------------------------------------------------------------------------
//実体のポインタを渡す
//---------------------------------------------------------------------------------------
CMenuSelect* CMenuSelect::GetPointer()
{
	//念のため作成関数を呼び出す
	Create();
	return m_pMenuSelect;
}
//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CMenuSelect::Update(void)
{
	m_nInterval ++;
	if(!m_pItemWindow->GetDrawFlg() && !m_pEquipmentWindow->GetDrawFlg() && !m_pTrickWindow->GetDrawFlg())
	{
		//上キーを押している
		if((CInput::GetKeyTrigger(DIK_W) || CInput::GetJoyAxis(0,JOY_Y) <= -JoyMoveCap) && m_nInterval >= ButtonIntervalTime)
		{
			//選択中コマンドを上に
			m_nSelectNumber --;

			//ループ
			if (m_nSelectNumber < 0)
				m_nSelectNumber = MENU_MAX - 1;

			//ボタン入力インターバルを0にする
			m_nInterval = 0;
		}
		//下キーを押している
		if((CInput::GetKeyTrigger(DIK_S) || CInput::GetJoyAxis(0, JOY_Y) >= JoyMoveCap) && m_nInterval >= ButtonIntervalTime)
		{
			//選択中コマンドを下に
			m_nSelectNumber ++;

			//ループ
			m_nSelectNumber %= MENU_MAX;

			//ボタン入力インターバルを0にする
			m_nInterval = 0;
		}

		//L(決定)ボタンを押した
		if((CInput::GetKeyTrigger(DIK_L) || CInput::GetJoyTrigger(0,3)) && m_nInterval >= ButtonIntervalTime)
		{
			//現在選択しているメニューに応じ、出力するウィンドウを設定する
			switch(m_nSelectNumber)
			{
				//アイテム
			case MENU_ITEM:
				//アイテムウインドウを描画するフラグを立てる
				m_pItemWindow->DrawFlgChange(true);
				break;
			case MENU_TRICK:
				//技ウィンドウの描画フラグを立てる
				m_pTrickWindow->DrawFlgChange();
				break;
			}

			//ボタン入力インターバルを0にする
			m_nInterval = 0;
		}
	}

	//位置情報の設定
	m_aVertex[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 235.0f , 50.0f + (m_nSelectNumber * 155.0f) ,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(SCREEN_WIDTH -  20.0f , 50.0f + (m_nSelectNumber * 155.0f) ,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 235.0f ,205.0f + (m_nSelectNumber * 155.0f) ,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(SCREEN_WIDTH -  20.0f ,205.0f + (m_nSelectNumber * 155.0f) ,0.0f);
}
//---------------------------------------------------------------------------------------
//メンバ変数のポインタを設定
//---------------------------------------------------------------------------------------
void CMenuSelect::SetPointer()
{
	//ステータスウィンドウのポインタを取得
	m_pStatesWindow = CStatesWindow::GetPointer();
	m_pItemWindow = CItemWindow::GetPointer();
	m_pTrickWindow = CTrickWindow::GetPointer();
	m_pEquipmentWindow = CEquipmentWindow::GetPointer();
}
