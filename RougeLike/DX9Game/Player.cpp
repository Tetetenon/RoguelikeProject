//自機クラス　実装
#include "Player.h"
#include "Input.h"
#include "Enemy.h"
#include "ItemCommandCursor.h"
#include "ItemWindowCursor.h"
#include "EquipmentCommandWindow.h"
#include "EnemyGenerator.h"
#include "MessageWindow.h"
#include "ModelManager.h"
#include "Turn.h"
#include "GameScene.h"
#include "HPDraw.h"
#include "MenuWindow.h"
#include "EquipmentWindowCursor.h"
#include "TextureManager.h"
#include "MiniMap.h"

CInventoryCursor	CPlayer::m_InventoryCursor;	//アイテムウインドウのカーソルの位置を特定する
CCommandCursor		CPlayer::m_CommandCursor;	//コマンドカーソルの位置を特定する

LPD3DXFONT			CPlayer::m_pFont;			//描画フォントの設定
RECT				CPlayer::m_FontDrawPos;		//フォントの描画位置を設定する
int					CPlayer::m_nDividPattern;	//生成するマップパターン

int		CPlayer::m_State_Cpy;					//外部からステートの変更を掛ける
bool	CPlayer::m_bState_Change_Flg = false;;	//外部からのステート変更がかかったか

#define PATH_DATA_PLAYER		("../data/txt/Player.txt")
#define PATH_LEVEL_UP_PLAYER	("../data/txt/LevelUp_Player.txt")
#define SPEED 0.0f

using namespace std;
//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CPlayer::CPlayer(CGameScene* pScene):
CUnit(pScene)
{
	//オブジェクトのIDを設定
	m_uID = ID_PLAYER;

	//ユニットのステートを設定
	m_nStateNumber = GAME_STATE_STAND_BY_PLAYER;

	//使用するモデル番号を設定
	m_nMeshNumber = MODEL_PLAYER;
	
	//デバイス格納
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//フォントへのポインタを取得する
	D3DXCreateFont(pDevice,24,0,1,0,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,NULL,&m_pFont);
	//フォント描画位置を設定
	SetFontPos();
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CPlayer::~CPlayer(void)
{
}

//---------------------------------------------------------------------------------------
//初期化
//---------------------------------------------------------------------------------------
void CPlayer::Init()
{
	//ユニットの番号を設定
	m_nUnitNumber = OBJ_NUM_PLAYER;

	//ユニット生成数をカウント
	m_nMakeNumber ++;

	//メッシュオブジェクトとして初期化
	CMeshObj::Init();

	//ユニットとして初期化
	CUnit::Init();

	//オブジェクトのIDを設定
	m_uID = ID_PLAYER;

	//メッシュデータの設定
	SetMesh(CModelManager::GetMesh(m_nMeshNumber));
	
	//-----ステータスデータの読み込み-----
    //ファイルの読み込み
    ifstream ifs(PATH_DATA_PLAYER);

    if(!ifs)
	{
		LPCTSTR szMsg = _T("読み込み失敗!");
   		 MessageBox(NULL, szMsg, NULL, MB_OK);
	}
    //txtファイルを1行ずつ読み込む
    string str;
	int i = 0;	//格納配列係数
	int PlayerData[STATES_MAX];	//ステータス値

    while(getline(ifs,str))
	{
        string token;
        istringstream stream(str);

        //1行のうち、文字列とコンマを分割する(コンマが出てくるまで読み込む)
        while(getline(stream,token,','))
		{
			PlayerData[i] = (int)stof(token);
			i++;
        }
    }
	//ファイルを閉じる
	ifs.close();

	//-----レベルアップデータの読み込み-----
    //ファイルの読み込み
	ifstream ifsLevel(PATH_LEVEL_UP_PLAYER);

    if(!ifsLevel)
	{
		LPCTSTR szMsg = _T("読み込み失敗!");
   		 MessageBox(NULL, szMsg, NULL, MB_OK);
	}
    //txtファイルを1行ずつ読み込む
	int PlayerUpData[UPSTATES_MAX];	//レベルアップ時上昇値格納
	i = 0;
    while(getline(ifsLevel,str))
	{
        string token;
        istringstream stream(str);

        //1行のうち、文字列とコンマを分割する(コンマが出てくるまで読み込む)
        while(getline(stream,token,','))
		{
			PlayerUpData[i] = (int)stof(token);
			i++;
        }
    }
	//ファイルを閉じる
	ifs.close();

	//-----ステータスの設定-----

	//名前の設定
	_stprintf(m_szName, _T("赤ずきん"));

	//HPを設定
	m_nMaxHP = PlayerData[STATES_MAX_HP];
	m_nHP = PlayerData[STATES_HP];

	//攻撃力を設定
	m_nAttack = PlayerData[STATES_AT];

	//防御力を設定
	m_nDefence = PlayerData[STATES_DF];

	//経験値蓄積値を設定
	m_nExp = PlayerData[STATES_EXP];

	//倒して得られる経験値を設定
	m_nXp = PlayerData[STATES_XP];

	//-----レベルアップ時の上昇値を設定-----
	//最大HP
	m_nHPUpNum = PlayerUpData[UPSTATES_MAX_HP];
	//攻撃力
	m_nAttackUpNum = PlayerUpData[UPSTATES_AT];
	//防御力
	m_nDefenceUpNum = PlayerUpData[UPSTATES_DF];

	//生きている
	m_bSurvival = true;

	//位置情報の設定
	SetPos();

	//画面に描画してもらう最大HPを渡す
	CHPDraw::SetMaxHP(m_nMaxHP);

	//画面に描画してもらうHPの数値を渡す
	CHPDraw::SetHP(m_nHP);

	//ステートの設定
	m_nStateNumber = m_State_Cpy = GAME_STATE_STAND_BY_PLAYER;

	//外部からのステート変更なし
	m_bState_Change_Flg = false;

	//入力待ちに存在するユニット数+1
	CTurn::AddCount(m_nStateNumber);

	//装備コマンドウィンドウ描画時間を初期化
	m_nEquipmentInterval = 0;

	m_bDirectionFlg[Forword] = true;
}
//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void CPlayer::Fin()
{
	//メッシュオブジェクトとしての終了処理
	CMeshObj::Fin();
	//アイテムインベントリの終了処理
	m_pInventory ->Fin();

	//装備インベントリの終了処理
	m_pEquipment ->Fin();
}
//---------------------------------------------------------------------------------------
//文字描画位置を設定
//---------------------------------------------------------------------------------------
void CPlayer::SetFontPos()
{
	m_FontDrawPos.left		= (LONG)125.0f;
	m_FontDrawPos.top		= (LONG) 70.0f;
	m_FontDrawPos.right		= (LONG)230.0f;
	m_FontDrawPos.bottom	= (LONG) 90.0f;
}

//---------------------------------------------------------------------------------------
//更新処理
//---------------------------------------------------------------------------------------
void CPlayer::Update()
{

	//外部から変更したステートを確認し、違えば本来のステートも変更をかける
	if(m_bState_Change_Flg)
	{
		m_nStateNumber = m_State_Cpy;
		m_bState_Change_Flg = false;
	}

	//コピーを設定
	m_State_Cpy = m_nStateNumber;
	//ユニット本来の更新をかける
	CUnit::Update();

	//装備画面のコマンドを描画していて、決定ボタンを押していれば、装備アイテムをアイテム欄に戻す
	if(CEquipmentCommandWindow::GetDrawFlg())
	{
		//装備コマンドウィンドウの描画時間を加算
		m_nEquipmentInterval++;

		if(CInput::GetKeyTrigger(DIK_L) && m_nEquipmentInterval > 30)
		{
			if(m_pInventory->SetItem(m_pEquipment->GetItem(CEquipmentInventoryCursor::GetItemNum())))
			{
				//メッセージ表記
				TCHAR	str[256];
				_stprintf(str, _T("%sを戻した"),m_pEquipment->GetInventoryItemName(CEquipmentInventoryCursor::GetItemNum()));
	
				//メッセージテスト
				MessageWindow::SetMassege(str);

				//装備インベントリ側のアイテムの破棄
				m_pEquipment->DelInventory(CEquipmentInventoryCursor::GetItemNum());

				//コマンドウィンドウ描画時間を初期化
				m_nEquipmentInterval= 0;
			}
			else
			{
	
				//メッセージテスト
				MessageWindow::SetMassege(_T("アイテムがいっぱいだった!"));

				//コマンドウィンドウ描画時間を初期化
				m_nEquipmentInterval= 0;
			}
		}
	}

	//-----ステータス描画のため、プレイヤーのステータスデータを渡す-----
	//攻撃力(装備加算の分も描画)
	CStatesValue::SetNumAttack(m_nAttack + m_pEquipment -> GetAttackTotalValue());
	//防御力(装備加算分も描画)
	CStatesValue::SetNumDefence(m_nDefence + m_pEquipment ->GetDefenceTotalValue());
	//経験値
	CStatesValue::SetNumExp(m_nExp);
}

//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CPlayer::Draw()
{
	//ユニットとしての描画処理
	CUnit::Draw();
}
//---------------------------------------------------------------------------------------
//外部からステートの変更をかける
//---------------------------------------------------------------------------------------
void CPlayer::SetState(int nState)
{
	m_State_Cpy = nState;
	m_bState_Change_Flg = true;
}

//---------------------------------------------------------------------------------------
//現在のステート情報を渡す
//---------------------------------------------------------------------------------------
int CPlayer::GetState()	
{
	return m_State_Cpy;
}
//---------------------------------------------------------------------------------------
//入力更新
//---------------------------------------------------------------------------------------
void CPlayer::InputUpdate()
{
	//アイテムウインドウを描画していなければ更新
	if(!m_pInventory->GetDrawFlg() && m_nStateNumber == CTurn::GetState())
	{
		//回転度数初期化
		m_Angle = D3DXVECTOR3(0.0f,0.0f,0.0f);

		//移動フラグ
		bool bMoveSuccess = false;

		//-----方向キー入力をした-----
		if(CInput::GetKeyPress(DIK_W) || CInput::GetKeyPress(DIK_S) || CInput::GetKeyPress(DIK_A) || CInput::GetKeyPress(DIK_D))
		{
			//メニューウィンドウが出ていなければ攻撃
			if(!CMenuWindow::GetDrawFlg())
			{
				//向きフラグ初期化
				for(int i = 0;i < MaxDirection;i++)
					m_bDirectionFlg[i] = false;
		
				//移動予定の位置
				int PosX = m_nUnit_Pos_X;
				int PosZ = m_nUnit_Pos_Z;
				//-----上移動-----
				if(CInput::GetKeyPress(DIK_W))
				{	
					//向きフラグ上
					m_bDirectionFlg[Forword] = true;

					//スペースキーを押していなかった場合、移動する
					if(!CInput::GetKeyPress(DIK_Q))
					{
						//行き先設定
						PosZ --;

						//移動フラグ　真
						bMoveSuccess = true;
					}
				}
				//-----下移動-----
				if(CInput::GetKeyPress(DIK_S))
				{
					//向きフラグ下
					m_bDirectionFlg[Back] = true;

					//スペースキーを押していなかった場合、移動する
					if(!CInput::GetKeyPress(DIK_Q))
					{
						//行き先設定
						PosZ ++;

						//移動フラグ　真
						bMoveSuccess = true;
					}
				}
				//-----右移動-----
				if(CInput::GetKeyPress(DIK_D))
				{
					//向きフラグ右
					m_bDirectionFlg[Right] = true;

					//スペースキーを押していなかった場合、移動
					if(!CInput::GetKeyPress(DIK_Q))
					{
						//行き先設定
						PosX ++;

						//移動フラグ　真
						bMoveSuccess = true;
					}
				}
				//-----左移動-----
				if(CInput::GetKeyPress(DIK_A))
				{
					//向きフラグ左
					m_bDirectionFlg[Left] = true;

					//スペースを押していなかった場合、移動する
					if(!CInput::GetKeyPress(DIK_Q))
					{
						//行き先設定
						PosX --;

						//移動フラグ　真
						bMoveSuccess = true;
					}
				}
				
				//混乱状態の場合、移動方向をランダムに変更する
				if(m_nState == UNIT_STATE_CONFUSION && bMoveSuccess)
				{
					//向きフラグ初期化
					for(int i = 0;i < MaxDirection;i++)
						m_bDirectionFlg[i] = false;
		
					//移動予定の位置初期化
					PosX = m_nUnit_Pos_X;
					PosZ = m_nUnit_Pos_Z;

					//移動方向を四方からランダムに設定
					switch(rand()%2)
					{
					case 0:
						//行先設定
						PosZ--;
						//向きフラグ上
						m_bDirectionFlg[Forword] = true;
						break;
					case 1:
						//行先設定
						PosZ ++;
						//向きフラグ下
						m_bDirectionFlg[Back] = true;
						break;
					}
					switch(rand()%3)
					{
					case 0:
						//行先設定
						PosX--;
						//向きフラグ左
						m_bDirectionFlg[Left] = true;
						break;
					case 1:
						//行先設定
						PosX ++;
						//向きフラグ右
						m_bDirectionFlg[Right] = true;
						break;
					default:
						//移動しない
						break;
					}
				}

				//移動フラグが立っていた場合
				if(bMoveSuccess)
				{

					//移動先のマップ状況を取得する
					int Situation = CMapData::Get_TerrainMapSituation(PosX,PosZ);

					//移動先にエネミーがほかのユニットがいないか確認する
					int EnemySearch = CMapData::Get_UnitMapSituation(PosX,PosZ);

					//移動先が床(又は階段)ならば移動可能
					if((FLOOR == Situation || STAIRS == Situation) && EnemySearch == 0)
					{
						//マーキング消去
						CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);

						//ミニマップ上の位置情報を削除
						CMiniMap::Delete(m_nUnit_Pos_X,m_nUnit_Pos_Z);

						//目的地に到達していない
						m_bDestination = false;
						m_fTimer = 0.0f;
						
						//移動先を本来の位置に設定
						m_nUnit_Pos_X = PosX;
						m_nUnit_Pos_Z = PosZ;

						//マーキング
						CMapData::Set_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z,m_nUnitNumber);

						//ミニマップ上に位置情報をセット
						CMiniMap::SetIcon(m_nUnit_Pos_X,m_nUnit_Pos_Z,TEXTURE_BLUE_TEXTURE);

						//入力待ちに存在するユニットの数-1
						CTurn::SumCount(m_nStateNumber);

						//ステートの遷移
						m_nStateNumber =  m_State_Cpy = GAME_STATE_MOVE;

						//移動ステートに存在するユニット数+1
						CTurn::AddCount(m_nStateNumber);


						//足元が階段であれば上る
						if(Situation == STAIRS)
						{
							//シーンのマップ再生成フラグを立てる
							CGameScene::MapReMake();
						}
					}
				}

				//回頭
				int nAngle = 0;		//ユニットの回転させる角度

				//フラグの状況から角度を設定する
				if(m_bDirectionFlg[0])
				{
					if(m_bDirectionFlg[1])
						nAngle = 45;
					else if(m_bDirectionFlg[3])
						nAngle = 315;
					else
						nAngle = 0;
				}

				else if(m_bDirectionFlg[2])
				{
					if(m_bDirectionFlg[1])
						nAngle = 135;
					else if(m_bDirectionFlg[3])
						nAngle = 225;
					else
						nAngle = 180;
				}
				else if(m_bDirectionFlg[1])
					nAngle = 90;
				else if(m_bDirectionFlg[3])
					nAngle = 270;

				int OldAngle = (int)(m_fOldAngle * 180 / PI );
				float RotateAngle = (float)(nAngle * PI / 180);

				m_Angle.y = RotateAngle - m_fOldAngle;

				m_fOldAngle = RotateAngle;
			}
		}
		//-----攻撃-----
		if(CInput::GetKeyTrigger(DIK_L))
		{
			//メニューウィンドウが出ていなければ攻撃
			if(!CMenuWindow::GetDrawFlg())
			{
				//入力待ちに存在するユニットの数-1
				CTurn::SumCount(m_nStateNumber);

				//ステートの遷移
				m_nStateNumber =  m_State_Cpy = GAME_STATE_ATTACK;

				//攻撃ステートに存在するユニット数+1
				CTurn::AddCount(m_nStateNumber);

				//繰り出す技の番号を指定
				m_nTrickNumber = TRICK_RANGE_FRONT;
			}
		}

		//-----足踏み-----
		if(CInput::GetKeyTrigger(DIK_E))
		{
			//ターンスキップ
			
			//入力待ちに存在するユニットの数-1
			CTurn::SumCount(m_nStateNumber);

			//自身のステートの設定
			m_nStateNumber = GAME_STATE_TURN_END;

			//ターン終了に存在するユニットの数+1
			CTurn::AddCount(m_nStateNumber);
		}
		
		//テスト(毒)
		if(CInput::GetKeyTrigger(DIK_UP))
		{
			SetStateAbnormal(UNIT_STATE_POISON);
		}
		//テスト(混乱)
		if(CInput::GetKeyTrigger(DIK_DOWN))
		{
			SetStateAbnormal(UNIT_STATE_CONFUSION);
		}
		//テスト(麻痺)
		if(CInput::GetKeyTrigger(DIK_RIGHT))
		{
			SetStateAbnormal(UNIT_STATE_PARALYSIS);
		}
		//テスト(睡眠)
		if(CInput::GetKeyTrigger(DIK_LEFT))
		{
			SetStateAbnormal(UNIT_STATE_SLEEP);
		}
		//テスト
		if(CInput::GetKeyPress(DIK_V))
		{
			//シーンのマップ再生成フラグを立てる
			CGameScene::MapReMake();
		}

		//-----メニューウィンドウ-----
		if(CInput::GetKeyTrigger(DIK_I))
		{
			//メニューウインドウ描画フラグを立てる
			CMenuWindow::ChangDrawFlg();
		}

		//ワールドマトリックスからローカル軸抽出、座標抽出
		D3DXMATRIX world = GetWorld();

		//それぞれの軸の値を格納する
		D3DXVECTOR3 vX,vY,vZ,vP;
		
		vX = D3DXVECTOR3(world._11,world._12,world._13);	//vX:X軸回転
		vY = D3DXVECTOR3(world._21,world._22,world._23);	//vY:Y軸回転
		vZ = D3DXVECTOR3(world._31,world._32,world._33);	//vZ:Z軸回転
		vP = D3DXVECTOR3(world._41,world._42,world._43);	//位置情報

		
		//回転行列の作成
		D3DXMATRIX rot_X,rot_Y,rot_Z;
		D3DXMatrixRotationAxis(&rot_X,&vX,m_Angle.x);		//&rot_YにvYとangle.yの値を掛け合わせた行列を格納する
		D3DXMatrixRotationAxis(&rot_Y,&vY,m_Angle.y);		//&rot_Zに現在の角度(vY)に回転度数(angle.y)をかけた値の行列を格納
		D3DXMatrixRotationAxis(&rot_Z,&vZ,m_Angle.z);		//&rot_Zに現在の角度(vZ)に回転度数(angle.z)をかけた値の行列を格納
		

		//回転度数初期化
		m_Angle = D3DXVECTOR3(0.0f,0.0f,0.0f);	

		//計算結果の行列をワールド行列に反映させる
		world *= (rot_Z *rot_Y * rot_X);

		world._41 = vP.x;
		world._42 = vP.y;
		world._43 = vP.z;

		//ワールドマトリックスを設定
		SetWorld(world);
	}
}
//---------------------------------------------------------------------------------------
//移動更新
//---------------------------------------------------------------------------------------
void CPlayer::MoveUpdate()
{
	//目的地に到達していない場合、ボタン入力経過時間を加算
	if(!m_bDestination)
	{
		//入力からの経過を計算
		m_fTimer += 0.1f;
		//移動完了
		if(m_fTimer >= ACTION_TIME)
		{
			//入力からの経過をリセット
			m_fTimer = 0.0f;

			//足元のアイテムのチェック
			ChackFeetItem();

			//移動ステートに存在するユニットの数-1
			CTurn::SumCount(m_nStateNumber);
			
			//ステートの遷移(ターンの終了)
			m_nStateNumber =  m_State_Cpy = GAME_STATE_STAND_BY_PLAYER;
			
			//入力待ちステートに存在するユニット数+1
			CTurn::AddCount(m_nStateNumber);
		}
	}

	//ワールドマトリックスからローカル軸抽出、座標抽出
	D3DXMATRIX world = GetWorld();

	//それぞれの軸の値を格納する
	D3DXVECTOR3 vX,vY,vZ,vP;
	
	vX = D3DXVECTOR3(world._11,world._12,world._13);	//vX:X軸回転
	vY = D3DXVECTOR3(world._21,world._22,world._23);	//vY:Y軸回転
	vZ = D3DXVECTOR3(world._31,world._32,world._33);	//vZ:Z軸回転
	vP = D3DXVECTOR3(world._41,world._42,world._43);	//位置情報

	world._41 = world._43 = 0.0f;	//原点へ移動させる
	
	m_Pos.x = (m_nUnit_Pos_X - (MAP_SIZE / 2)) * GRIDSIZE + GRIDSIZE / 2;
	m_Pos.z = -((m_nUnit_Pos_Z) - (MAP_SIZE / 2)) * GRIDSIZE - GRIDSIZE / 2;

	vP = vP + (m_Pos - vP) * (m_fTimer / ACTION_TIME);

	//移動完了
	if(vP == m_Pos)
	{
		m_bDestination = true;
	}

	//回転行列の作成
	D3DXMATRIX rot_X,rot_Y,rot_Z;
	D3DXMatrixRotationAxis(&rot_X,&vX,m_Angle.x);		//&rot_YにvYとangle.yの値を掛け合わせた行列を格納する
	D3DXMatrixRotationAxis(&rot_Y,&vY,m_Angle.y);		//&rot_Zに現在の角度(vY)に回転度数(angle.y)をかけた値の行列を格納
	D3DXMatrixRotationAxis(&rot_Z,&vZ,m_Angle.z);		//&rot_Zに現在の角度(vZ)に回転度数(angle.z)をかけた値の行列を格納

	//回転度数初期化
	m_Angle = D3DXVECTOR3(0.0f,0.0f,0.0f);	

	//計算結果の行列をワールド行列に反映させる
	world *= (rot_Z *rot_Y * rot_X);

	world._41 = vP.x;
	world._42 = vP.y;
	world._43 = vP.z;

	//ワールドマトリックスを設定
	SetWorld(world);

}
//---------------------------------------------------------------------------------------
//アクション更新
//---------------------------------------------------------------------------------------
void CPlayer::ActUpdate()
{
	//アクションステートに存在するユニットの数-1
	CTurn::SumCount(m_nStateNumber);

	//ステートの遷移(ターンの終了)
	m_nStateNumber =  m_State_Cpy = GAME_STATE_STAND_BY_PLAYER;

	//入力待ちに存在するユニットの数+1
	CTurn::AddCount(m_nStateNumber);

	//メッセージテスト
	MessageWindow::SetMassege(_T("行動した"));
}
//---------------------------------------------------------------------------------------
//ターン終了更新
//---------------------------------------------------------------------------------------
void CPlayer::TurnEndUpdate()
{
	//ターン終了ステートに存在するユニットの数-1
	CTurn::SumCount(m_nStateNumber);

	//ステートの遷移(ターンの終了)
	m_nStateNumber =  m_State_Cpy = GAME_STATE_STAND_BY_PLAYER;

	//入力待ちステートに存在するユニットの数+1
	CTurn::AddCount(m_nStateNumber);
}
//---------------------------------------------------------------------------------------
//アイテム更新
//---------------------------------------------------------------------------------------
void CPlayer::ItemUpdate()
{
	//選択されたコマンドによって処理を分岐させる
	switch(m_CommandCursor.GetCommand())
	{
		//アイテムを使用した
	case COMMAND_USE:

		//メッセージテスト
		MessageWindow::SetMassege(_T("アイテムを使った"));

		//アイテムの効果によって取得する値を変更する
		switch(m_pInventory->GetEffect(m_InventoryCursor.GetItemNum()))
		{
			//効果なし
		case EFFECT_NON:
		case EFFECT_EQUIPMENT_ATTACK:
		case EFFECT_EQUIPMENT_DEFENCE:
			//メッセージテスト
			MessageWindow::SetMassege(_T("…が、何も起こらなかった"));
			break;
			//回復効果
		case EFFECT_RECOVERY:

			//アイテムの回復効果の回復量を取得する
			RecoveryHP(m_pInventory->GetEffectValue(m_InventoryCursor.GetItemNum()));

			//メッセージテスト
			MessageWindow::SetMassege(_T("体力を回復した!"));
		//画面に描画してもらうHPの数値を渡す
		CHPDraw::SetHP(m_nHP);
			
			break;

			//デバッグ用
		default:
			//メッセージテスト
			MessageWindow::SetMassege(_T("なんか間違ってね?"));
			break;
		}

		//使用アイテムの破棄
		m_pInventory->DelInventory(m_InventoryCursor.GetItemNum());

		break;
		//アイテムを装備した
	case COMMAND_EQUIPMENT:

		//装備インベントリから、装備できるスペースがあるか探し、あれば装備インベントリに格納する
		if(m_pEquipment->SetItem(m_pInventory->GetItem(m_InventoryCursor.GetItemNum())))
		{
			//メッセージ表記
			TCHAR	str[256];
			_stprintf(str, _T("%sは%sを装備した"),m_szName,m_pInventory->GetInventoryItemName(m_InventoryCursor.GetItemNum()));
	
			//メッセージテスト
			MessageWindow::SetMassege(str);

			//アイテムインベントリ側のアイテムの破棄
			m_pInventory->DelInventory(m_InventoryCursor.GetItemNum());
		}
		else
		{
			//メッセージ表記
			TCHAR	str[256];
			_stprintf(str, _T("装備がいっぱいだった!"));
	
			//メッセージテスト
			MessageWindow::SetMassege(_T("装備がいっぱいだった"));
		}
		break;
		//アイテムを捨てた
	case COMMAND_RELINQUISH:

		//アイテムの破棄
		m_pInventory->DelInventory(m_InventoryCursor.GetItemNum());

		//メッセージテスト
		MessageWindow::SetMassege(_T("アイテムを捨てた"));

		break;
	}

	//アイテム使用ステートに存在するユニット-1
	CTurn::SumCount(m_nStateNumber);

	//ステートの遷移(ターンの終了)
	m_nStateNumber =  m_State_Cpy = GAME_STATE_TURN_END;

	//入力待ちステートに存在するユニット数+1
	CTurn::AddCount(m_nStateNumber);
}

//---------------------------------------------------------------------------------------
//位置の再設定
//---------------------------------------------------------------------------------------
void CPlayer::SetPos()
{
	//位置情報を設定
	m_nUnit_Pos_X = rand()%MAP_SIZE;
	m_nUnit_Pos_Z = rand()%MAP_SIZE;

	//位置が設置不能ならば、再設定
	while(!CMapData::CheckInTheRoom(m_nUnit_Pos_X,m_nUnit_Pos_Z))
	{
		m_nUnit_Pos_X = rand()%MAP_SIZE;
		m_nUnit_Pos_Z = rand()%MAP_SIZE;
	}

	//ワールドマトリックスからローカル軸抽出、座標抽出
	D3DXMATRIX world = GetWorld();
	
	//モデルのスケールを変更する
	D3DXMatrixScaling(&world,0.2f,0.2f,0.2f);

	//位置情報設定
	world._41 = (m_nUnit_Pos_X - (MAP_SIZE / 2)) * GRIDSIZE + GRIDSIZE / 2;
	world._42 = 0.0f;
	world._43 = -((m_nUnit_Pos_Z) - (MAP_SIZE / 2)) * GRIDSIZE - GRIDSIZE / 2;

	//ワールドマトリックスを設定
	SetWorld(world);

	//マーキング
	CMapData::Set_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z,m_nUnitNumber);

	//ミニマップ上に自身の位置を設定
	CMiniMap::SetIcon(m_nUnit_Pos_X,m_nUnit_Pos_Z,TEXTURE_BLUE_TEXTURE);

	//移動ステートに存在するユニットの数-1
	CTurn::SumCount(m_nStateNumber);
	
	//ステートの遷移(ターンの終了)
	m_nStateNumber =  m_State_Cpy = GAME_STATE_STAND_BY_PLAYER;
	
	//入力待ちステートに存在するユニット数+1
	CTurn::AddCount(m_nStateNumber);

	//目的地初期化
	m_Pos = D3DXVECTOR3(world._41,world._42,world._43);
	
	//向きを初期化
	m_fOldAngle = 0;

	//入力時間初期化
	m_fTimer = 0.0f;

	//目的地に到達している
	m_bDestination = true;
}
//---------------------------------------------------------------------------------------
//アイテムウィンドウの描画
//---------------------------------------------------------------------------------------
void CPlayer::DrawInventory()
{
	m_pInventory ->Draw();
}
//---------------------------------------------------------------------------------------
//装備ウィンドウの描画
//---------------------------------------------------------------------------------------
void CPlayer::DrawEquipment()
{
	m_pEquipment ->Draw();
}
//---------------------------------------------------------------------------------------
//技ウィンドウの描画
//---------------------------------------------------------------------------------------
void CPlayer::DrawTrick()
{
	m_pTrickWindow ->Draw();
}
//---------------------------------------------------------------------------------------
//レベルの描画
//---------------------------------------------------------------------------------------
void CPlayer::DrawLevel()
{
	char Level[256];
	_stprintf(Level, _T("Level:%d"), m_nLevel);
	//数値(文字)描画
	m_pFont ->DrawText(NULL,Level,-1,&m_FontDrawPos,DT_LEFT,D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
}