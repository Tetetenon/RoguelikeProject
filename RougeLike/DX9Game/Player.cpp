//自機クラス　実装
#include "Player.h"
#include "Input.h"
#include "Enemy.h"

#include "ItemCommandCursor.h"
#include "ItemWindowCursor.h"

#include "EquipmentCommandWindow.h"
#include "EquipmentWindowCursor.h"
#include "EquipmentCommandCursor.h"

#include "StatesValue.h"
#include "Fade.h"
#include "EnemyGenerator.h"
#include "MessageWindow.h"
#include "ModelManager.h"
#include "Turn.h"
#include "GameScene.h"
#include "HPDraw.h"
#include "MenuWindow.h"
#include "TextureManager.h"
#include "MiniMap.h"
#include "UnitManager.h"

//回復する間隔
#define RecoveryIntervalTime 3
#define PATH_DATA_PLAYER		("../data/txt/Player.txt")
#define PATH_LEVEL_UP_PLAYER	("../data/txt/LevelUp_Player.txt")
#define SPEED 0.0f

using namespace std;

#define DEBUG_MODE	(0)

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CPlayer::CPlayer(CGameScene* pScene):
CUnit(pScene),
m_nEquipmentInterval(0)
{
	//使用するモデル番号を設定
	m_nMeshNumber = MODEL_PLAYER;
	
	//デバイス格納
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//フォントへのポインタを取得する
	D3DXCreateFont(pDevice,23,0,1,0,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,NULL,&m_pFont);
	//フォント描画位置を設定
	SetFontPos();

	//ユニットの番号を設定
	m_nUnitNumber = OBJ_NUM_PLAYER;

	//ユニット生成数をカウント
	m_nMakeNumber++;

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

	if (!ifs)
	{
		LPCTSTR szMsg = _T("読み込み失敗!");
		MessageBox(NULL, szMsg, NULL, MB_OK);
	}
	//txtファイルを1行ずつ読み込む
	string str;
	int i = 0;	//格納配列係数
	int PlayerData[STATES_MAX];	//ステータス値

	while (getline(ifs, str))
	{
		string token;
		istringstream stream(str);

		//1行のうち、文字列とコンマを分割する(コンマが出てくるまで読み込む)
		while (getline(stream, token, ','))
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

	if (!ifsLevel)
	{
		LPCTSTR szMsg = _T("読み込み失敗!");
		MessageBox(NULL, szMsg, NULL, MB_OK);
	}
	//txtファイルを1行ずつ読み込む
	int PlayerUpData[UPSTATES_MAX];	//レベルアップ時上昇値格納
	i = 0;
	while (getline(ifsLevel, str))
	{
		string token;
		istringstream stream(str);

		//1行のうち、文字列とコンマを分割する(コンマが出てくるまで読み込む)
		while (getline(stream, token, ','))
		{
			PlayerUpData[i] = (int)stof(token);
			i++;
		}
	}
	//ファイルを閉じる
	ifs.close();

	//-----ステータスの設定-----
	//名前の設定
	sprintf_s(m_szName, _T("赤ずきん"));

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

	//メンバ変数のポインタを取得する
	MemberPointerGet();


	//画面に描画してもらう最大HPを渡す
	m_pHPDraw->SetMaxHP(m_nMaxHP);

	//画面に描画してもらうHPの数値を渡す
	m_pHPDraw->SetHP(m_nHP);

	//ステートの設定
	m_nStateNumber = CTurn::GAME_STATE_STAND_BY;

	//装備コマンドウィンドウ描画時間を初期化
	m_nEquipmentInterval = 0;

	//回復する間隔を初期化
	m_nRecoveryInterval = 0;

	m_bDirectionFlg[Forword] = true;

	//シーン上にオブジェクトの追加
	m_pUnitManager->Add(m_nUnitNumber, this);
	//プレイヤーのポインタをマネージャーに設定させる
	m_pUnitManager->SetPlayerPointer();
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CPlayer::~CPlayer(void)
{
	//メッシュオブジェクトとしての終了処理
	CMeshObj::Fin();

	//回復する間隔を初期化
	m_nRecoveryInterval = 0;
}
//---------------------------------------------------------------------------------------
//文字描画位置を設定
//---------------------------------------------------------------------------------------
void CPlayer::SetFontPos()
{
	m_FontDrawPos.left		= (LONG)140.0f;
	m_FontDrawPos.top		= (LONG) 15.0f;
	m_FontDrawPos.right		= (LONG)240.0f;
	m_FontDrawPos.bottom	= (LONG) 45.0f;
}

//---------------------------------------------------------------------------------------
//更新処理
//---------------------------------------------------------------------------------------
void CPlayer::Update()
{
	//ユニット本来の更新をかける
	CUnit::Update();

	//装備画面のコマンドを描画していて、決定ボタンを押していれば、装備アイテムをアイテム欄に戻す
	if(m_pEquipmentCommandWindow->GetDrawFlg())
	{
		//装備コマンドウィンドウの描画時間を加算
		m_nEquipmentInterval++;

		if((CInput::GetKeyTrigger(DIK_L) || CInput::GetJoyTrigger(0, 3)) && m_nEquipmentInterval > 30)
		{
			if(m_pInventory->SetItem(m_pEquipment->GetItem(m_pEquipmentInventoryCursor->GetItemNum())))
			{
				//メッセージ表記
				TCHAR	str[256];
				sprintf_s(str, _T("%sを戻した"),m_pEquipment->GetInventoryItemName(m_pEquipmentInventoryCursor->GetItemNum()));
	
				//メッセージテスト
				m_pMessageWindow->SetMassege(str);

				//装備インベントリ側のアイテムの破棄
				m_pEquipment->DelInventory(m_pEquipmentInventoryCursor->GetItemNum());

				//コマンドウィンドウ描画時間を初期化
				m_nEquipmentInterval= 0;
			}
			else
			{
				//メッセージテスト
				m_pMessageWindow->SetMassege(_T("アイテムがいっぱいだった!"));

				//コマンドウィンドウ描画時間を初期化
				m_nEquipmentInterval= 0;
			}
		}
	}

	//-----ステータス描画のため、プレイヤーのステータスデータを渡す-----
	//攻撃力(装備加算の分も描画)
	m_pStatesValue->SetNumAttack(m_nAttack + m_pEquipment -> GetAttackTotalValue());
	//防御力(装備加算分も描画)
	m_pStatesValue->SetNumDefence(m_nDefence + m_pEquipment ->GetDefenceTotalValue());
	//経験値
	m_pStatesValue->SetNumExp(m_nExp);
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
//入力更新
//---------------------------------------------------------------------------------------
void CPlayer::InputUpdate()
{
	//状態異常の経過時間を減らす
	//自身のターン処理が一度でも行われたか?
	if (!m_bTurn)
	{
		//自身が状態異常になっているか確認する
		if (m_nState_Turn != 0)
			//状態異常の処理
			TurnStartStateProcessing();
		m_bTurn = true;

		//回復間隔を加算
		m_nRecoveryInterval++;
		//回復する間隔が一定以上を超えたら回復
		if (m_nRecoveryInterval >= RecoveryIntervalTime)
		{
			//HP自動回復
			m_nHP++;
			//最大数値を超えない様に
			if (m_nHP > m_nMaxHP)
				m_nHP = m_nMaxHP;
			//UI側に表記するHPデータに変更をか ける
			m_pHPDraw->SetHP(m_nHP);

			//回復間隔を初期化
			m_nRecoveryInterval = 0;
		}

		//経過ターン数を加算
		CTurn::AddTurnValue();
	}

	//旧ステート情報の確保
	m_nOldStateNumber = m_nStateNumber;

	//メニューウインドウを描画していなければ更新
	if(!m_pMenuWindow->GetDrawFlg() && m_nStateNumber == CTurn::GetState())
	{
		//回転度数初期化
		m_Angle = D3DXVECTOR3(0.0f,0.0f,0.0f);

		//移動フラグ
		bool bMoveSuccess = false;
		//デバッグコマンド(死亡)
		if (CInput::GetKeyTrigger(DIK_G))
		{
			//ゲームメインを終了
			m_pFade->ChangeState(FADEMODE_OUT);

			//ゲームクリア状態をゲームオーバーに
			CGameScene::GameClearStateChange(GAME_OVER);

			//エネミーの生成数のリセット
			m_pEnemyGenerator->ResetMakeEnemyNum();

			//フィールドアイテム生成数のリセット
			CItemGenerator::ResetMakeItemNum();
		}

		//-----足踏み-----
		if (CInput::GetKeyPress(DIK_E) || CInput::GetJoyPress(0, 4))
		{
			//ターンスキップ

			//自身のステートの設定
			m_nStateNumber = CTurn::GAME_STATE_TURN_END;
		}
		else
		{
			//-----方向キー入力をした-----
			if (CInput::GetKeyPress(DIK_W) || CInput::GetKeyPress(DIK_S) || CInput::GetKeyPress(DIK_A) || CInput::GetKeyPress(DIK_D) ||
				abs(CInput::GetJoyAxis(0, JOY_X)) > JoyMoveCap || abs(CInput::GetJoyAxis(0, JOY_Y)) > JoyMoveCap)
			{
				//メニューウィンドウが出ていなければ処理
				if (!m_pMenuWindow->GetDrawFlg())
				{
					//向きフラグ初期化
					for (int i = 0; i < MaxDirection; i++)
						m_bDirectionFlg[i] = false;
					//斜め移動固定化フラグ
					bool bDiagonalMoveFlg = false;
					//斜め移動固定キー入力がされているかどうか確認を行う
					if (CInput::GetKeyPress(DIK_J) || CInput::GetJoyPress(0, 6))
						//押されている
						bDiagonalMoveFlg = true;

					//移動予定の位置
					int PosX = m_nUnit_Pos_X;
					int PosZ = m_nUnit_Pos_Z;
					//-----上移動-----
					if (CInput::GetKeyPress(DIK_W) || CInput::GetJoyAxis(0, JOY_Y) < -JoyMoveCap)
					{
						//向きフラグ上
						m_bDirectionFlg[Forword] = true;

						//スペースキーを押していなかった場合、移動する
						if (!CInput::GetKeyPress(DIK_Q) && !CInput::GetJoyPress(0, 7))
						{
							//行き先設定
							PosZ--;

							//移動フラグ　真
							bMoveSuccess = true;
						}
					}
					//-----下移動-----
					if (CInput::GetKeyPress(DIK_S) || CInput::GetJoyAxis(0, JOY_Y) > JoyMoveCap)
					{
						//向きフラグ下
						m_bDirectionFlg[Back] = true;

						//スペースキーを押していなかった場合、移動する
						if (!CInput::GetKeyPress(DIK_Q) && !CInput::GetJoyPress(0, 7))
						{
							//行き先設定
							PosZ++;

							//移動フラグ　真
							bMoveSuccess = true;
						}
					}
					//-----右移動-----
					if (CInput::GetKeyPress(DIK_D) || CInput::GetJoyAxis(0, JOY_X) > JoyMoveCap)
					{
						//向きフラグ右
						m_bDirectionFlg[Right] = true;

						//スペースキーを押していなかった場合、移動
						if (!CInput::GetKeyPress(DIK_Q) && !CInput::GetJoyPress(0, 7))
						{
							//行き先設定
							PosX++;

							//移動フラグ　真
							bMoveSuccess = true;
						}
					}
					//-----左移動-----
					if (CInput::GetKeyPress(DIK_A) || CInput::GetJoyAxis(0, JOY_X) < -JoyMoveCap)
					{
						//向きフラグ左
						m_bDirectionFlg[Left] = true;

						//スペースを押していなかった場合、移動する
						if (!CInput::GetKeyPress(DIK_Q) && !CInput::GetJoyPress(0, 7))
						{
							//行き先設定
							PosX--;

							//移動フラグ　真
							bMoveSuccess = true;
						}
					}
					//斜め移動固定フラグが立っていた場合、斜め以外の移動の場合、行動をロックする
					if (bDiagonalMoveFlg)
					{
						//上下左右どちらかの入力が入っていない場合、斜め移動ではないため、移動フラグ、行き先を初期化する
						if (PosX == m_nUnit_Pos_X || PosZ == m_nUnit_Pos_Z)
						{
							PosX = m_nUnit_Pos_X;
							PosZ = m_nUnit_Pos_Z;
							bMoveSuccess = false;
						}
					}

					//混乱状態の場合、移動方向をランダムに変更する
					if (m_nState == UNIT_STATE_CONFUSION && bMoveSuccess)
					{
						//向きフラグ初期化
						for (int i = 0; i < MaxDirection; i++)
							m_bDirectionFlg[i] = false;

						//移動予定の位置初期化
						PosX = m_nUnit_Pos_X;
						PosZ = m_nUnit_Pos_Z;

						//移動方向を四方からランダムに設定
						switch (rand() % 2)
						{
						case 0:
							//行先設定
							PosZ--;
							//向きフラグ上
							m_bDirectionFlg[Forword] = true;
							break;
						case 1:
							//行先設定
							PosZ++;
							//向きフラグ下
							m_bDirectionFlg[Back] = true;
							break;
						}
						switch (rand() % 3)
						{
						case 0:
							//行先設定
							PosX--;
							//向きフラグ左
							m_bDirectionFlg[Left] = true;
							break;
						case 1:
							//行先設定
							PosX++;
							//向きフラグ右
							m_bDirectionFlg[Right] = true;
							break;
						default:
							//移動しない
							break;
						}
					}

					//移動フラグが立っていた場合
					if (bMoveSuccess)
					{

						//移動先のマップ状況を取得する
						int Situation = m_pMapData->Get_TerrainMapSituation(PosX, PosZ);

						//移動先にエネミーがほかのユニットがいないか確認する
						int EnemySearch = m_pMapData->Get_UnitMapSituation(PosX, PosZ);

						//移動先が床(又は階段)ならば移動可能
						if ((Situation == FLOOR || Situation == STAIRS || Situation == ROOT || Situation == ROOT_ENTRANCE) && EnemySearch == 0)
						{
							//マーキング消去
							m_pMapData->Back_UnitMap(m_nUnit_Pos_X, m_nUnit_Pos_Z);

							//目的地に到達していない
							m_bDestination = false;
							m_fTimer = 0.0f;

							//移動先を本来の位置に設定
							m_nUnit_Pos_X = PosX;
							m_nUnit_Pos_Z = PosZ;

							//可視化
							m_pMapData->SetVisibleProcess(PosX, PosZ);


							m_pMapData->SetDark(PosX, PosZ, TRUE);

							//マーキング
							m_pMapData->Set_UnitMap(m_nUnit_Pos_X, m_nUnit_Pos_Z, m_nUnitNumber);

							//ステートの遷移
							m_nStateNumber = CTurn::GAME_STATE_MOVE;


							//足元が階段であれば上る
							if (Situation == STAIRS)
							{
								//シーンのマップ再生成フラグを立てる
								CGameScene::MapReMake();
							}
						}
					}

					//回頭
					int nAngle = 0;		//ユニットの回転させる角度

					//フラグの状況から角度を設定する
					if (m_bDirectionFlg[0])
					{
						if (m_bDirectionFlg[1])
							nAngle = 45;
						else if (m_bDirectionFlg[3])
							nAngle = 315;
						else
							nAngle = 0;
					}

					else if (m_bDirectionFlg[2])
					{
						if (m_bDirectionFlg[1])
							nAngle = 135;
						else if (m_bDirectionFlg[3])
							nAngle = 225;
						else
							nAngle = 180;
					}
					else if (m_bDirectionFlg[1])
						nAngle = 90;
					else if (m_bDirectionFlg[3])
						nAngle = 270;

					int OldAngle = (int)(m_fOldAngle * 180 / PI);
					float RotateAngle = (float)(nAngle * PI / 180);

					m_Angle.y = RotateAngle - m_fOldAngle;

					m_fOldAngle = RotateAngle;
				}
			}
			//-----攻撃-----
			if (CInput::GetKeyTrigger(DIK_L) || CInput::GetJoyTrigger(0, 3))
			{
				//メニューウィンドウが出ていなければ攻撃
				if (!m_pMenuWindow->GetDrawFlg())
				{

					//ステートの遷移
					m_nStateNumber = CTurn::GAME_STATE_ATTACK;

					//繰り出す技の番号を指定
					m_nTrickNumber = TRICK_RANGE_FRONT;
				}
			}

			//テスト(毒)
			if (CInput::GetKeyTrigger(DIK_UP))
			{
				SetStateAbnormal(UNIT_STATE_POISON);
			}
			//テスト(混乱)
			if (CInput::GetKeyTrigger(DIK_DOWN))
			{
				SetStateAbnormal(UNIT_STATE_CONFUSION);
			}
			//テスト(麻痺)
			if (CInput::GetKeyTrigger(DIK_RIGHT))
			{
				SetStateAbnormal(UNIT_STATE_PARALYSIS);
			}
			//テスト(睡眠)
			if (CInput::GetKeyTrigger(DIK_LEFT))
			{
				SetStateAbnormal(UNIT_STATE_SLEEP);
			}
			//テスト
			if (CInput::GetKeyTrigger(DIK_V))
			{
				//シーンのマップ再生成フラグを立てる
				CGameScene::MapReMake();
			}

			//-----メニューウィンドウ-----
			if (CInput::GetKeyTrigger(DIK_I) || CInput::GetJoyTrigger(0, 1))
			{
				//メニューウインドウ描画フラグを立てる
				m_pMenuWindow->ChangDrawFlg();
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

			//ステートの遷移(ターンの終了)
			m_nStateNumber = CTurn::GAME_STATE_TURN_END;
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

	//ステートの遷移(ターンの終了)
	m_nStateNumber = CTurn::GAME_STATE_TURN_END;

	//メッセージテスト
	m_pMessageWindow->SetMassege(_T("行動した"));
}
//---------------------------------------------------------------------------------------
//ターン終了更新
//---------------------------------------------------------------------------------------
void CPlayer::TurnEndUpdate()
{
	//ステートの遷移(ターンの終了)
	m_nStateNumber = CTurn::GAME_STATE_STAND_BY;

	//自身のターンが終了した。
	m_bTurnEndFlg = true;

	//ターン初めの処理が完了していない
	m_bTurn = false;

	//次のユニットの更新に移る
	CTurn::ChangeUnitState(CTurn::UNIT_TURN_ENEMY);
}
//---------------------------------------------------------------------------------------
//アイテム更新
//---------------------------------------------------------------------------------------
void CPlayer::ItemUpdate()
{
	//選択されたコマンドによって処理を分岐させる
	switch(m_pCommandCursor->GetCommand())
	{
		//アイテムを使用した
	case COMMAND_USE:

		//メッセージテスト
		m_pMessageWindow->SetMassege(_T("アイテムを使った"));

		//アイテムの効果によって取得する値を変更する
		switch(m_pInventory->GetEffect(m_pInventoryCursor->GetItemNum()))
		{
			//効果なし
		case EFFECT_NON:
		case EFFECT_EQUIPMENT_ATTACK:
		case EFFECT_EQUIPMENT_DEFENCE:
			//メッセージテスト
			m_pMessageWindow->SetMassege(_T("おいしかった。"));
			break;
			//回復効果
		case EFFECT_RECOVERY:

			//アイテムの回復効果の回復量を取得する
			RecoveryHP(m_pInventory->GetEffectValue(m_pInventoryCursor->GetItemNum()));

			//メッセージテスト
			m_pMessageWindow->SetMassege(_T("体力を回復した!"));
		//画面に描画してもらうHPの数値を渡す
		m_pHPDraw->SetHP(m_nHP);
			
			break;

			//デバッグ用
		default:
			//メッセージテスト
			m_pMessageWindow->SetMassege(_T("なんか間違ってね?"));
			break;
		}

		//使用アイテムの破棄
		m_pInventory->DelInventory(m_pInventoryCursor->GetItemNum());

		break;
		//アイテムを装備した
	case COMMAND_EQUIPMENT:

		//装備インベントリから、装備できるスペースがあるか探し、あれば装備インベントリに格納する
		if(m_pEquipment->SetItem(m_pInventory->GetItem(m_pInventoryCursor->GetItemNum())))
		{
			//メッセージ表記
			TCHAR	str[256];
			sprintf_s(str, _T("%sは%sを装備した"),m_szName,m_pInventory->GetInventoryItemName(m_pInventoryCursor->GetItemNum()));
	
			//メッセージテスト
			m_pMessageWindow->SetMassege(str);

			//アイテムインベントリ側のアイテムの破棄
			m_pInventory->DelInventory(m_pInventoryCursor->GetItemNum());
		}
		else
		{
			//メッセージ表記
			m_pMessageWindow->SetMassege(_T("装備がいっぱいだった"));
		}
		break;
		//アイテムを捨てた
	case COMMAND_RELINQUISH:

		//アイテムの破棄
		m_pInventory->DelInventory(m_pInventoryCursor->GetItemNum());

		//メッセージテスト
		m_pMessageWindow->SetMassege(_T("アイテムを捨てた"));

		break;
	}

	//ステートの遷移(ターンの終了)
	m_nStateNumber = CTurn::GAME_STATE_TURN_END;
}

//---------------------------------------------------------------------------------------
//位置の再設定
//---------------------------------------------------------------------------------------
void CPlayer::SetPos()
{
	//配置する部屋の番号を設定
	int SetRoomNumber = rand() % m_pMapData->GetMakeRoomNum();
	//部屋のデータを取得
	RECT RoomPos = m_pMapData->GetRoomFloorPlan(SetRoomNumber);

	//位置情報を設定
	m_nUnit_Pos_X = rand() % (RoomPos.right - RoomPos.left) + RoomPos.left;
	m_nUnit_Pos_Z = rand() % (RoomPos.bottom - RoomPos.top) + RoomPos.top;

	//位置が設置不能ならば、再設定
	while(m_pMapData->Get_TerrainMapSituation(m_nUnit_Pos_X,m_nUnit_Pos_Z) != FLOOR)
	{
		m_nUnit_Pos_X = rand() % (RoomPos.right - RoomPos.left) + RoomPos.left;
		m_nUnit_Pos_Z = rand() % (RoomPos.bottom - RoomPos.top) + RoomPos.top;
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
	m_pMapData->Set_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z,m_nUnitNumber);
	
	//ステートの遷移(ターンの終了)
	m_nStateNumber = CTurn::GAME_STATE_STAND_BY;

	//目的地初期化
	m_Pos = D3DXVECTOR3(world._41,world._42,world._43);
	
	//向きを初期化
	m_fOldAngle = 0;

	//入力時間初期化
	m_fTimer = 0.0f;
	
	// 可視化
	m_pMapData->SetVisibleProcess(m_nUnit_Pos_X,m_nUnit_Pos_Z);

	//目的地に到達している
	m_bDestination = true;
}
//---------------------------------------------------------------------------------------
//レベルの描画
//---------------------------------------------------------------------------------------
void CPlayer::DrawLevel()
{
	char Level[256];
	sprintf_s(Level, _T("Level:%d"), m_nLevel);
	//数値(文字)描画
	m_pFont ->DrawText(NULL,Level,-1,&m_FontDrawPos,DT_LEFT,D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
}
//---------------------------------------------------------------------------------------
//メンバ変数のポインタを取得する
//---------------------------------------------------------------------------------------
void CPlayer::MemberPointerGet()
{
	//HPバーへのポインタを設定する
	m_pHPDraw = CHPDraw::GetPointer();
	//アイテムコマンドカーソルのポインタを取得する
	m_pCommandCursor = CItemCommandCursor::GetPointer();
	//アイテムカーソルのポインタを取得する
	m_pInventoryCursor = CItemWindowCursor::GetPointer();
	//装備コマンドカーソルのポインタを取得
	m_pEquipmentCommandWindow = CEquipmentCommandWindow::GetPointer();
	//装備カーソルへのポインタを取得
	m_pEquipmentInventoryCursor = CEquipmentWindowCursor::GetPointer();
	//ステータス数値へのポインタを取得
	m_pStatesValue = CStatesValue::GetPointer();
	//フェードへのポインタを取得
	m_pFade = CFade::GetPointer();
	//メニューウィンドウへのポインタを取得する
	m_pMenuWindow = CMenuWindow::GetPointer();
}