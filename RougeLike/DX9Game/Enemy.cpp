//敵クラス　実装
#include "Enemy.h"
#include "Input.h"
#include "MessageWindow.h"
#include "ModelManager.h"
#include "Turn.h"
#include "Battle.h"
#include "MiniMap.h"
#include "TextureManager.h"
#include "GameScene.h"
#include "EnemyGenerator.h"
#include <math.h>

#include "MapData.h"



CMeshObj*	CEnemy::m_Player = NULL;				//プレイヤー情報格納
int			CEnemy::m_nEnemyData[STATES_MAX];		//ステータス情報格納
int			CEnemy::m_nLevelUpData[UPSTATES_MAX];	//レベルアップ時上昇ステータス情報格納
bool		CEnemy::m_bStatesLoad = false;			//ステータス情報ファイル読み込みフラグ
bool		CEnemy::m_bLevelUpLoad = false;			//レベルアップ時上昇値ファイル読み込みフラグ
bool		CEnemy::m_bDelete = false;				//全てのエネミーを削除するフラグ
AStar		CEnemy::m_AStarData[MAP_SIZE][MAP_SIZE];		//A*アルゴリズムに使用する構造体

#define PATH_DATA_ENEMY		("../data/txt/Enemy.txt")
#define PATH_LEVEL_UP_ENEMY ("../data/txt/LevelUp_Enemy.txt")

using namespace std;
//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CEnemy::CEnemy(CGameScene* pScene):
CUnit(pScene)
{
	//オブジェクトIDの設定
	m_uID = ID_ENEMY;

	//ユニットのステート状態を設定
	m_nStateNumber = GAME_STATE_STAND_BY_OTHER;
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CEnemy::~CEnemy(void)
{
	//生成が完全に完了したエネミーが消滅する場合、
	if(m_bMakeSuccess)
	{
		//アイテムインベントリの終了処理
		m_pInventory ->Fin();

		//装備インベントリの終了処理
		m_pEquipment ->Fin();

		//マーキング消去
		CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);

		//ミニマップ上の情報を消去
		CMiniMap::Delete(m_nUnit_Pos_X,m_nUnit_Pos_Z);

		//ジェネレーターの生成数を減算
		CEnemyGenerator::SumMakeEnemyNum();
	}
}

//---------------------------------------------------------------------------------------
//プレイヤーポインタ初期化
//---------------------------------------------------------------------------------------
void CEnemy::PlayerPointInit()
{
	m_Player = NULL;
}
//---------------------------------------------------------------------------------------
//エネミーの生成
//---------------------------------------------------------------------------------------
void CEnemy::Generation(CMeshObj *pGenerator)
{
	//メッシュ情報あり&呼び出し相手のポインタあり
	if(!pGenerator)
		return;

	//エネミーを追加
	CEnemy* pEnemy = new CEnemy(pGenerator ->GetScene());

	//ユニットとして親クラスの初期化処理を行う
	pEnemy -> CUnit::Init();

	//エネミーの種類
	int nEnemyType = rand()%3;

	//生成完了状況初期化
	pEnemy ->m_bMakeSuccess = false;

	//エネミーの種別を設定
	switch(nEnemyType)
	{
	case 0:
		//名前の設定
		_stprintf(pEnemy -> m_szName, ("はち"));

		//モデルデータの読み込み
		pEnemy -> m_nMeshNumber = MODEL_BEE;
		break;
	case 1:
		//名前の設定
		_stprintf(pEnemy -> m_szName, ("おおかみ"));

		//モデルデータ読み込み
		pEnemy -> m_nMeshNumber = MODEL_WOLF;
		break;
	case 2:
		//名前の設定
		_stprintf(pEnemy -> m_szName, ("くま"));

		//モデルデータ読み込み
		pEnemy -> m_nMeshNumber = MODEL_BEAR;
		break;

		//デバッグ用処理
	default:
		//名前の設定
		_stprintf(pEnemy -> m_szName, ("かべ"));

		//モデルデータ読み込み
		pEnemy ->m_nMeshNumber = MODEL_WALL;
		break;
	}
	
	//オブジェクトIDの設定
	pEnemy -> m_uID = ID_ENEMY;

	//ユニットのステート状態を設定
	pEnemy -> m_nStateNumber = GAME_STATE_STAND_BY_OTHER;

	//メッシュの設定
	pEnemy ->SetMesh(CModelManager::GetMesh(pEnemy ->m_nMeshNumber));

	//ユニットの番号を設定
	pEnemy -> m_nUnitNumber = OBJ_NUM_ENEMY + m_nMakeNumber;

	//生きている
	pEnemy -> m_bSurvival = true;

	//自機へのポインタを取得しておく
	if(!m_Player)
	{
		m_Player = (CMeshObj*)pEnemy->Find(ID_PLAYER);
	}

    //txtファイルを1行ずつ読み込む(1度読み込めばあとは読み込んだデータ変数を読み込む)
	if(!m_bStatesLoad)
	{
		//ファイルの読み込み
		ifstream ifs(PATH_DATA_ENEMY);

		string str;
		
		int i = 0;	//格納配列係数
		
		string token;

		while(getline(ifs,str))
		{
		    istringstream stream(str);

		    //1行のうち、文字列とコンマを分割する
		    while(getline(stream,token,','))
			{
				m_nEnemyData[i] = stoi(token);
				i++;
				if(i >= STATES_MAX)
					break;
		    }
		}

		//ファイルを閉じる
		ifs.close();
		//読み込み完了
		m_bStatesLoad= true;
	}

    //txtファイルを1行ずつ読み込む(1度読み込めばあとは読み込んだデータ変数を読み込む)
	if(!m_bLevelUpLoad)
	{
		//ファイルの読み込み
		ifstream ifs(PATH_LEVEL_UP_ENEMY);

		string str;
		
		int i = 0;	//格納配列係数
		
		string token;

		while(getline(ifs,str))
		{
		    istringstream stream(str);

		    //1行のうち、文字列とコンマを分割する
		    while(getline(stream,token,','))
			{
				m_nLevelUpData[i] = stoi(token);
				i++;
				if(i >= UPSTATES_MAX)
					break;
		    }
		}

		//ファイルを閉じる
		ifs.close();
		//読み込み完了
		m_bStatesLoad= true;
	}
	
	//-----ステータスの設定-----

	//レベルを設定
	pEnemy -> m_nLevel = CGameScene::GetPlayerLevel() + (rand() % 6 - 3);

	//値が0以下にならない様に設定する
	if(pEnemy ->m_nLevel <= 0)
	{
		pEnemy->m_nLevel = 1;
	}

	//HPを設定
	pEnemy -> m_nMaxHP = m_nEnemyData[STATES_MAX_HP] + m_nLevelUpData[UPSTATES_MAX_HP] * pEnemy -> m_nLevel;
	pEnemy -> m_nHP = m_nEnemyData[STATES_HP] + m_nLevelUpData[UPSTATES_MAX_HP] * pEnemy -> m_nLevel;

	//攻撃力を設定
	pEnemy -> m_nAttack = m_nEnemyData[STATES_AT] + m_nLevelUpData[UPSTATES_AT] * pEnemy -> m_nLevel;

	//防御力を設定
	pEnemy -> m_nDefence = m_nEnemyData[STATES_DF] + m_nLevelUpData[UPSTATES_DF] * pEnemy -> m_nLevel;

	//-----レベルアップ時、上昇ステータスを設定-----
	//最大HP
	pEnemy -> m_nHPUpNum = m_nLevelUpData[UPSTATES_MAX_HP];
	//攻撃力
	pEnemy -> m_nAttackUpNum = m_nLevelUpData[UPSTATES_AT];
	//防御力
	pEnemy -> m_nDefenceUpNum = m_nLevelUpData[UPSTATES_DF];

	
	//位置情報を仮的に設定
	int PosX = rand()%MAP_SIZE;
	int PosZ = rand()%MAP_SIZE;

	//場所確認回数
	int nMakeLimit = 0;

	//位置情報を設定
	while(1)
	{
		//場所確認回数が一定数を超えたら生成を中止
		if(nMakeLimit > 15)
		{
			delete pEnemy;
			return;
		}

		//接地可能か確認
		if(FLOOR == CMapData::Get_TerrainMapSituation(PosX,PosZ) &&
			0 == CMapData::Get_UnitMapSituation(PosX,PosZ) && 
			CMapData::CheckInTheRoom(PosX,PosZ))
			break;

		//不可能だった場合、再設定する。
		PosX = rand()%MAP_SIZE;
		PosZ = rand()%MAP_SIZE;

		//場所確認回数を加算
		nMakeLimit ++;
	}

	pEnemy -> m_nUnit_Pos_X = PosX;
	pEnemy -> m_nUnit_Pos_Z = PosZ;
	

	//ミニマップ上に自身の位置を設定
	CMiniMap::SetIcon(pEnemy -> m_nUnit_Pos_X,pEnemy -> m_nUnit_Pos_Z,TEXTURE_RED_TEXTURE);

	//経験値蓄積値を設定
	pEnemy -> m_nExp = m_nEnemyData[STATES_EXP];

	//倒して得られる経験値を設定
	pEnemy -> m_nXp = m_nEnemyData[STATES_XP];
	
	//ワールドマトリックスからローカル軸抽出、座標抽出
	D3DXMATRIX world = pGenerator->GetWorld();

	//モデルのスケールを変更する
	D3DXMatrixScaling(&world,0.125f,0.125f,0.125f);

	//位置情報設定
	world._41 = (pEnemy -> m_nUnit_Pos_X - (MAP_SIZE / 2)) * GRIDSIZE + GRIDSIZE / 2;
	world._42 = 0.0f;
	world._43 = -((pEnemy -> m_nUnit_Pos_Z) - (MAP_SIZE / 2)) * GRIDSIZE - GRIDSIZE / 2;

	//ワールドマトリックスを設定
	pEnemy->SetWorld(world);

	//マーキング
	CMapData::Set_UnitMap(pEnemy -> m_nUnit_Pos_X,pEnemy -> m_nUnit_Pos_Z,pEnemy ->m_nUnitNumber);

	//目的地初期化
	pEnemy -> m_Pos = D3DXVECTOR3(world._41,world._42,world._43);
	
	//向きの初期化
	pEnemy -> m_fOldAngle = 0;

	//入力時間初期化
	pEnemy -> m_fTimer = 0.0f;

	//目的地に到達している
	pEnemy -> m_bDestination = true;

	//ステートの設定
	pEnemy ->m_nStateNumber = GAME_STATE_STAND_BY_OTHER;

	//入力待ちに存在するユニット数+1
	CTurn::AddCount(pEnemy ->m_nStateNumber);

	//生成完了
	pEnemy ->m_bMakeSuccess = true;

	//ユニット生成数をカウント
	m_nMakeNumber ++;
}
//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CEnemy::Update()
{
	//もし、エネミーの削除フラグが立っていたら、エネミーを削除する
	if(m_bDelete || m_nHP <= 0)
	{
		//マーキング消去
		CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);
	
		//現在自分が選択しているステートのユニットの数-1
		CTurn::SumCount(m_nStateNumber);

		//自身の削除
		delete this;
	}
	else
	{
		//ユニットとしての更新を行う
		CUnit::Update();
	}
}
//---------------------------------------------------------------------------------------
//入力更新(移動方向ルーチン)
//---------------------------------------------------------------------------------------
void CEnemy::InputUpdate()
{
	//回転度数
	m_Angle = D3DXVECTOR3(0.0f,0.0f,0.0f);

	//移動できたか
	bool MoveCompletion = false;

	
	//-----移動ルーチン作成-----
	if (m_Player)
	{
		D3DXVECTOR3 Distance = D3DXVECTOR3(0.0f,0.0f,0.0f);	//プレイヤーと自分との距離

		//ワールド上のプレイヤーの位置情報取得
		D3DXVECTOR3 PlayerPos = m_Player -> GetPos();
		
		//プレイヤーの位置情報を配列位置に変換
		int PlayerPos_X = (int)((PlayerPos.x - (MAP_SIZE / 2) * GRIDSIZE) / GRIDSIZE + (MAP_SIZE));
		int PlayerPos_Z = (int)(MAP_SIZE - ((PlayerPos.z - (MAP_SIZE / 2) * GRIDSIZE) / GRIDSIZE + (MAP_SIZE)));

		PlayerPos_X = m_Player->GetPosX();
		PlayerPos_Z = m_Player->GetPosZ();

		//差を計算
		int Distance_X = PlayerPos_X - m_nUnit_Pos_X;
		int Distance_Z = m_nUnit_Pos_Z - PlayerPos_Z;
		

		//攻撃判定(もしプレイヤーがそばに居たら攻撃をする)
		if(abs(Distance_X) <= 1 && abs(Distance_Z) <= 1)
		{

			//向きフラグ初期化
			for(int i = 0;i < MaxDirection;i++)
				m_bDirectionFlg[i] = false;

			//プレイヤーの方向を向く
			if(Distance_X > 0)
			{
				m_bDirectionFlg[Right] = true;
				m_bDirectionFlg[Left]  = false;
			}
			else if(Distance_X < 0)
			{
				m_bDirectionFlg[Left]  = true;
				m_bDirectionFlg[Right] = false;
			}
			else
			{
				m_bDirectionFlg[Left]  = false;
				m_bDirectionFlg[Right] = false;
			}

			if(Distance_Z < 0)
			{
				m_bDirectionFlg[Back] = true;
				m_bDirectionFlg[Forword] = false;
			}

			else if(Distance_Z > 0)
			{
				m_bDirectionFlg[Back] = false;
				m_bDirectionFlg[Forword] = true;
			}
			else
			{
				m_bDirectionFlg[Back] = false;
				m_bDirectionFlg[Forword] = false;
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

				
			int OldAngle = (int)(m_fOldAngle* 180 / PI );
			float RotateAngle = (float)(nAngle * PI / 180);

			m_Angle.y = RotateAngle - m_fOldAngle;

			m_fOldAngle = RotateAngle;

			//入力待ちに存在するユニットの数-1
			CTurn::SumCount(m_nStateNumber);

			//自身のステートの設定
			m_nStateNumber = GAME_STATE_ATTACK;

			//攻撃に存在するユニットの数+1
			CTurn::AddCount(m_nStateNumber);
			
			//繰り出す技の番号を指定
			m_nTrickNumber = TRICK_RANGE_FRONT;
		}
		//差があれば移動
		else if(abs(Distance_X) >= 1 || abs(Distance_Z) >= 1)
		{

			//向きフラグ初期化
			for(int i = 0;i < MaxDirection;i++)
				m_bDirectionFlg[i] = false;

			//上移動
			//移動先が床ならば移動可能
			if(Distance_Z > 0 
				&& FLOOR == CMapData::Get_TerrainMapSituation(m_nUnit_Pos_X,m_nUnit_Pos_Z - 1) 
				&& CMapData::Get_UnitMapSituation(m_nUnit_Pos_X,m_nUnit_Pos_Z - 1) == 0)
			{
				//マーキング消去
				CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);

				//ミニマップ上の位置情報を削除
				CMiniMap::Delete(m_nUnit_Pos_X,m_nUnit_Pos_Z);

				//向きフラグ上
				m_bDirectionFlg[Forword] = true;

				//指定位置に到達していない
				m_bDestination = false;
				m_fTimer = 0.0f;

				//移動完了
				MoveCompletion = true;

				//配列上を移動
				m_nUnit_Pos_Z--;
				
				//マーキング
				CMapData::Set_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z,m_nUnitNumber);

				//ミニマップ上に自身の位置を設定
				CMiniMap::SetIcon(m_nUnit_Pos_X,m_nUnit_Pos_Z,TEXTURE_RED_TEXTURE);

				//操作決定待ちに存在するユニットの数-1
				CTurn::SumCount(m_nStateNumber);

				//自身のステートの設定
				m_nStateNumber = GAME_STATE_MOVE;
				
				//移動ステートに存在するユニット+1
				CTurn::AddCount(m_nStateNumber);
			}
			//下移動
			//移動先が床ならば移動可能
			else if(Distance_Z < 0 
				&& FLOOR == CMapData::Get_TerrainMapSituation(m_nUnit_Pos_X,m_nUnit_Pos_Z + 1) 
				&& CMapData::Get_UnitMapSituation(m_nUnit_Pos_X,m_nUnit_Pos_Z + 1) == 0)
			{
				//マーキング消去
				CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);

				//ミニマップ上の位置情報を削除
				CMiniMap::Delete(m_nUnit_Pos_X,m_nUnit_Pos_Z);
				
				//向きフラグ下
				m_bDirectionFlg[Back] = true;

				//指定位置に到達していない
				m_bDestination = false;
				m_fTimer = 0.0f;

				//移動完了
				MoveCompletion = true;

				//配列上を移動
				m_nUnit_Pos_Z ++;
				
				//マーキング
				CMapData::Set_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z,m_nUnitNumber);

				//ミニマップ上に自身の位置を設定
				CMiniMap::SetIcon(m_nUnit_Pos_X,m_nUnit_Pos_Z,TEXTURE_RED_TEXTURE);

				//操作決定待ちに存在するユニットの数-1
				CTurn::SumCount(m_nStateNumber);

				//自身のステートの設定
				m_nStateNumber = GAME_STATE_MOVE;
				
				//移動ステートに存在するユニット+1
				CTurn::AddCount(m_nStateNumber);
			}
			//右移動
			if(Distance_X > 0 && 
				FLOOR == CMapData::Get_TerrainMapSituation(m_nUnit_Pos_X + 1,m_nUnit_Pos_Z) && 
				CMapData::Get_UnitMapSituation(m_nUnit_Pos_X + 1,m_nUnit_Pos_Z) == 0)
			{
				//マーキング消去
				CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);

				//ミニマップ上の位置情報を削除
				CMiniMap::Delete(m_nUnit_Pos_X,m_nUnit_Pos_Z);

				//向きフラグ右
				m_bDirectionFlg[Right] = true;

				//指定位置に到達していない
				m_bDestination = false;
				m_fTimer = 0.0f;

				//移動完了
				MoveCompletion = true;

				//配列上を移動
				m_nUnit_Pos_X ++;
				
				//マーキング
				CMapData::Set_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z,m_nUnitNumber);

				//ミニマップ上に自身の位置を設定
				CMiniMap::SetIcon(m_nUnit_Pos_X,m_nUnit_Pos_Z,TEXTURE_RED_TEXTURE);

				//操作決定待ちに存在するユニットの数-1
				CTurn::SumCount(m_nStateNumber);

				//自身のステートの設定
				m_nStateNumber = GAME_STATE_MOVE;
				
				//移動ステートに存在するユニット+1
				CTurn::AddCount(m_nStateNumber);
			}
			//左移動
			else if(Distance_X < 0 && 
				FLOOR == CMapData::Get_TerrainMapSituation(m_nUnit_Pos_X - 1,m_nUnit_Pos_Z) && 
				CMapData::Get_UnitMapSituation(m_nUnit_Pos_X - 1,m_nUnit_Pos_Z) == 0)
			{
				//マーキング消去
				CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);

				//ミニマップ上の位置情報を削除
				CMiniMap::Delete(m_nUnit_Pos_X,m_nUnit_Pos_Z);

				//向きフラグ左
				m_bDirectionFlg[Left] = true;

				//指定位置に到達していない
				m_bDestination = false;
				m_fTimer = 0.0f;

				//移動完了
				MoveCompletion = true;

				//配列上を移動
				m_nUnit_Pos_X --;
				
				//マーキング
				CMapData::Set_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z,m_nUnitNumber);

				//ミニマップ上に自身の位置を設定
				CMiniMap::SetIcon(m_nUnit_Pos_X,m_nUnit_Pos_Z,TEXTURE_RED_TEXTURE);

				//操作決定待ちに存在するユニットの数-1
				CTurn::SumCount(m_nStateNumber);

				//自身のステートの設定
				m_nStateNumber = GAME_STATE_MOVE;
				
				//移動ステートに存在するユニット+1
				CTurn::AddCount(m_nStateNumber);
			}
			//移動できなかった場合、エネミーのターンを終了する
			if(!MoveCompletion)
			{
				//入力待ちに存在するユニットの数-1
				CTurn::SumCount(m_nStateNumber);

				//自身のステートの設定
				m_nStateNumber = GAME_STATE_TURN_END;

				//ターン終了に存在するユニットの数+1
				CTurn::AddCount(m_nStateNumber);
			}
			
			//回頭
			int nAngle = 0;		//ユニットの回転させる角度
			
			if(m_nStateNumber == GAME_STATE_MOVE)
			{
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
			
					
				int OldAngle = (int)(m_fOldAngle* 180 / PI );
				float RotateAngle = (float)(nAngle * PI / 180);
			
				m_Angle.y = RotateAngle - m_fOldAngle;
			
				m_fOldAngle = RotateAngle;
			}
		}
		//移動できない
		else
		{
			//入力待ちに存在するユニットの数-1
			CTurn::SumCount(m_nStateNumber);

			//自身のステートの設定
			m_nStateNumber = GAME_STATE_TURN_END;

			//ターン終了に存在するユニットの数+1
			CTurn::AddCount(m_nStateNumber);
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

		vP = vP + (m_Pos - vP) * (m_fTimer / (float)ACTION_TIME);

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
void CEnemy::MoveUpdate()
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

			//自身のステート状態を入力待ちに設定
			m_nStateNumber = GAME_STATE_STAND_BY_OTHER;

			//入力待ちに存在するユニットの数+1
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

	vP = vP + (m_Pos - vP) * (m_fTimer / (float)ACTION_TIME);


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
//行動更新
//---------------------------------------------------------------------------------------
void CEnemy::ActUpdate()
{	
	//メッセージテスト
	MessageWindow::SetMassege(("行動した"));

	//行動更新に存在するユニットの数-1
	CTurn::SumCount(m_nStateNumber);

	//ステートの遷移(ターンの終了)
	m_nStateNumber = GAME_STATE_STAND_BY_OTHER;

	//入力待ちに存在するユニットの数+1
	CTurn::AddCount(m_nStateNumber);
}

//---------------------------------------------------------------------------------------
//アイテム更新
//---------------------------------------------------------------------------------------
void CEnemy::ItemUpdate()
{
	//アイテム使用ステートに存在するユニット数-1
	CTurn::SumCount(m_nStateNumber);

	//メッセージテスト
	MessageWindow::SetMassege(("アイテム使った"));

	//入力待ちステートに存在するユニット数+1
	CTurn::AddCount(m_nStateNumber);

	//ステートの遷移(ターンの終了)
	m_nStateNumber = GAME_STATE_STAND_BY_OTHER;
		
}
//---------------------------------------------------------------------------------------
//ターン終了更新
//---------------------------------------------------------------------------------------
void CEnemy::TurnEndUpdate()
{
	//ターンエンドステートに存在するユニット数-1
	CTurn::SumCount(m_nStateNumber);

	//ステートの遷移(ターンの終了)
	m_nStateNumber = GAME_STATE_STAND_BY_OTHER;

	//入力待ちに存在するユニットの数+1
	CTurn::AddCount(m_nStateNumber);
}
//---------------------------------------------------------------------------------------
//A*アルゴリズムを用いた移動を行う
//---------------------------------------------------------------------------------------
void CEnemy::A_StarMove()
{
	//プレイヤーの位置を取得する
	int PlayerPosX = m_Player->GetPosX();
	int PlayerPosZ = m_Player->GetPosZ();

	//現在探索を行っている場所
	AStar NowSearchPosition;

	//探索を終了させるフラグ
	bool SearchEndFlg = false;

	//構造体の初期化を行う
	InitAStarData();

	//開始位置を設定する
	AStarStartPosSet();

	//自身の位置から周囲の探索を行い、子供を設定する
	SearchPosition(m_nUnit_Pos_X,m_nUnit_Pos_Z);

	//設定した子供すべてをスコア付けを行う
	for(int i = 0;i < m_AStarData[m_nUnit_Pos_Z][m_nUnit_Pos_X].m_nChildNum;i++)
	{
		//子供の位置
		D3DXVECTOR2 ChildPos = m_AStarData[m_nUnit_Pos_Z][m_nUnit_Pos_X].m_ChildPos[i];

		//コストを計算
		m_AStarData[(int)ChildPos.y][(int)ChildPos.x].m_nCost = AStarCalculator(ChildPos.x,ChildPos.y,m_nUnit_Pos_X,m_nUnit_Pos_Z);

		//ヒューリスティック値の計算
		m_AStarData[(int)ChildPos.y][(int)ChildPos.x].m_nHeuristic = AStarCalculator(ChildPos.x,ChildPos.y,PlayerPosX,PlayerPosZ);
	}

	NowSearchPosition = m_AStarData[m_nUnit_Pos_Z][m_nUnit_Pos_X];

	//探索位置がプレイヤーの位置にまで到達する、又は探索不能になるまで処理
	while(!SearchEndFlg)
	{
		//もし自身の子供の位置が、プレイヤーの位置と一致したならば、探索を終了させる
		//自身の子供すべてに確認を取る
		for(int i = 0;i < NowSearchPosition.m_nChildNum;i++)
		{
			//子供の位置と、プレイヤーの位置が一致したならば、終了する
			if(NowSearchPosition.m_ChildPos[i].x == PlayerPosX && NowSearchPosition.m_ChildPos[i].y == PlayerPosZ)
			{
				//探索終了フラグを立てる
				SearchEndFlg = true;
			}

			//全ての探索できる場所を探索した場合、探索を終了させる
			if(NowSearchPosition.m_bMapStatus)
			{
				SearchEndFlg = true;
			}
		}
	}
}

//---------------------------------------------------------------------------------------
//A*アルゴリズムの開始位置を設定する
//---------------------------------------------------------------------------------------
void CEnemy::ASarSetData(int NowPosX,int NowPosZ)
{
	//プレイヤーの位置を取得する
	int PlayerPosX = m_Player->GetPosX();
	int PlayerPosZ = m_Player->GetPosZ();

	//自身の位置を構造体配列の中に格納する
	//コストを入力する
	m_AStarData[NowPosZ][NowPosX].m_nCost = AStarCalculator(NowPosX,NowPosZ,m_nUnit_Pos_X,m_nUnit_Pos_Z);
	//ヒューリステック値を入力する
	m_AStarData[NowPosZ][NowPosX].m_nHeuristic = AStarCalculator(NowPosX,NowPosZ,PlayerPosX,PlayerPosZ);
	//スコアを入力する(コスト+ヒューリスティック値)
	m_AStarData[NowPosZ][NowPosX].m_nScore = m_AStarData[NowPosZ][NowPosX].m_nCost + m_AStarData[NowPosZ][NowPosX].m_nHeuristic;

	//自身の親の位置を設定する(自身が最初の親)
	m_AStarData[m_nUnit_Pos_Z][NowPosX].m_ParentPos = D3DXVECTOR2(0,0);

}

//---------------------------------------------------------------------------------------
//A*アルゴリズム用構造体の初期化を行う
//---------------------------------------------------------------------------------------
void CEnemy::InitAStarData()
{
	//データの初期化を行う
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int k = 0;k < MAP_SIZE;k++)
		{
			//マップのオープンクローズフラグ初期化
			m_AStarData[i][k].m_bMapStatus = false;

			//コスト、ヒューリスティック値、スコア初期化
			m_AStarData[i][k].m_nCost = 0;
			m_AStarData[i][k].m_nHeuristic = 0;
			m_AStarData[i][k].m_nScore = 0;
			
			//自身の持つ子供の数を初期化
			m_AStarData[i][k].m_nCost = 0;

			//自身の子供のポインタを初期化
			for(int l = 0;l < MOVEVEC;l++)
			{
				m_AStarData[i][k].m_ChildPos[l] = D3DXVECTOR2(0,0);
			}

			//自身の親のポインタを初期化する
			m_AStarData[i][k].m_ParentPos = D3DXVECTOR2(0,0);
		}
	}
}


//---------------------------------------------------------------------------------------
//指定された位置周囲の移動可能な場所を検索し、自身の子供として設定する
//---------------------------------------------------------------------------------------
void CEnemy::SearchPosition(int PosX,int PosZ)
{
	//方向の補正値
	D3DXVECTOR2 CorrectionPos[MOVEVEC] = 
	{
		//			 X, Z
		D3DXVECTOR2(-1,-1),	//左上
		D3DXVECTOR2( 0,-1),	//上
		D3DXVECTOR2( 1,-1),	//右上
		D3DXVECTOR2( 1, 0),	//右
		D3DXVECTOR2( 1, 1),	//右下
		D3DXVECTOR2(0 , 1),	//下
		D3DXVECTOR2(-1, 1),	//左下
		D3DXVECTOR2(-1, 0)	//左
	};

	//周囲を確認する
	for(int i = 0;i < MOVEVEC;i++)
	{
		//確認した位置が床(移動可能)ならば、自身の子として、位置を持っておく
		int MapSituNum = CMapData::Get_TerrainMapSituation(PosX + CorrectionPos[i].x,PosZ + CorrectionPos[i].y);

		if(MapSituNum == FLOOR || MapSituNum == STAIRS)
		{
			//自身の子として位置情報を持っておく
			m_AStarData[PosZ][PosX].m_ChildPos[m_AStarData[PosZ][PosX].m_nChildNum].x = (int)(PosX + CorrectionPos[i].x);
			m_AStarData[PosZ][PosX].m_ChildPos[m_AStarData[PosZ][PosX].m_nChildNum].y = (int)(PosZ + CorrectionPos[i].y);
			//自身の子供の数を加算する
			m_AStarData[PosZ][PosX].m_nChildNum ++;

			//子供の親の位置を自身に設定する
			m_AStarData[(int)(PosZ + CorrectionPos[i].y)][(int)(PosX + CorrectionPos[i].x)].m_ParentPos.x = PosX;
			m_AStarData[(int)(PosZ + CorrectionPos[i].y)][(int)(PosX + CorrectionPos[i].x)].m_ParentPos.y = PosZ;
		}

	}
}
//---------------------------------------------------------------------------------------
//A*アルゴリズムにおける、ヒューリスティック値を計算する
//---------------------------------------------------------------------------------------
int CEnemy::AStarCalculator(int NowPosX,int NowPosZ,int GoalPosX,int GoalPosZ)
{
	//現在の位置と、目標地点の位置の距離を計算する
	int DistanceX = abs(NowPosX - GoalPosX);
	int DistanceZ = abs(NowPosZ - GoalPosZ);

	//ヒューリスティック値を暫定的に計算する
	int HeuristicScoreNum = DistanceX + DistanceZ;

	//斜め移動も可能なため、縦、横の数値の低い分、スコア値から減算する
	//引く数値
	int SubNum = DistanceX;

	if(DistanceX > DistanceZ)
		SubNum = DistanceZ;

	HeuristicScoreNum -= SubNum;

	//計算が完了した数値をヒューリスティック値として返す
	return HeuristicScoreNum;
}