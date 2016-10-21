#include "MenuSelect.h"
#include "TextureManager.h"
#include "Input.h"
#include "ItemWindow.h"
#include "StatesWindow.h"
#include "EquipmentWindow.h"
#include "TrickWindow.h"

int	 CMenuSelect::m_nSelectNumber = 0;		//現在選択しているメニュー番号格納用変数
bool CMenuSelect::m_bOperationFlg = false;	//メニューウィンドウ操作フラグ
int	 CMenuSelect::m_nInterval = 0;			//ボタン入力のインターバル	


//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CMenuSelect::CMenuSelect(void)
{
	//使用するテクスチャIDの設定
	m_nTextureID = TEXTURE_RED_TEXTURE;

	//選択中コマンドの設定
	m_nSelectNumber = 0;

	//操作フラグの初期化
	m_bOperationFlg = false;

	//位置情報の設定
	m_aVertex[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 240.0f , 50.0f ,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(SCREEN_WIDTH -  10.0f , 50.0f ,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 240.0f ,127.5f ,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(SCREEN_WIDTH -  10.0f ,127.5f ,0.0f);
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CMenuSelect::~CMenuSelect(void)
{
	//操作フラグの初期化
	m_bOperationFlg = false;
}


//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CMenuSelect::Update(void)
{
	m_nInterval ++;
	//アイテムウィンドウも、装備ウィンドウも、技ウィンドウも描画していない
	if(!CInventory::GetDrawFlg() && !CEquipmentInventory::GetDrawFlg()&&!CTrickWindow::GetDrawFlg())
	{
		//上キーを押している
		if(CInput::GetKeyTrigger(DIK_W))
		{
			//選択中コマンドを上に
			m_nSelectNumber --;
		}
		//下キーを押している
		if(CInput::GetKeyTrigger(DIK_S))
		{
			//選択中コマンドを下に
			m_nSelectNumber ++;
		}

		//L(決定)ボタンを押した
		if(CInput::GetKeyTrigger(DIK_L) && m_nInterval >= 10)
		{
			//現在選択しているメニューに応じ、出力するウィンドウを設定する
			switch(m_nSelectNumber)
			{
				//アイテム
			case MENU_ITEM:
				//アイテムウインドウを描画するフラグを立てる
				CInventory::DrawFlgChange();
				break;
				//装備
			case MENU_EQUIPMENT:
				//装備ウィンドウを描画するフラグを立てる
				CEquipmentInventory::DrawFlgChange();
				break;
				//ステータス
			case MENU_STATES:
				//ステータスウィンドウの描画フラグを立てる
				CStatesWindow::ChangeDrawFlg();
				break;
			case MENU_TRICK:
				//技ウィンドウの描画フラグを立てる
				CTrickWindow::DrawFlgChange();
				break;
			}
		}
	}
	//-----許容領域範囲内に居るか確認-----
	if(m_nSelectNumber < 0)
	{
		m_nSelectNumber = 0;
	}
	if(m_nSelectNumber >= MENU_MAX)
	{
		m_nSelectNumber = MENU_MAX - 1;
	}

	//位置情報の設定
	m_aVertex[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 235.0f , 50.0f + (m_nSelectNumber * 77.5f) ,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(SCREEN_WIDTH -  20.0f , 50.0f + (m_nSelectNumber * 77.5f) ,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 235.0f ,127.5f + (m_nSelectNumber * 77.5f) ,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(SCREEN_WIDTH -  20.0f ,127.5f + (m_nSelectNumber * 77.5f) ,0.0f);
}
