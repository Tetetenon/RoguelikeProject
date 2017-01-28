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
#include"UnitManager.h"

int			CEnemy::m_nEnemyData[STATES_MAX];		//ステータス情報格納
int			CEnemy::m_nLevelUpData[UPSTATES_MAX];	//レベルアップ時上昇ステータス情報格納
bool		CEnemy::m_bStatesLoad = false;			//ステータス情報ファイル読み込みフラグ
bool		CEnemy::m_bLevelUpLoad = false;			//レベルアップ時上昇値ファイル読み込みフラグ

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
	m_nStateNumber = CTurn::GAME_STATE_STAND_BY;
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

		//ジェネレーターの生成数を減算
		CEnemyGenerator::SumMakeEnemyNum();
	}
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
		sprintf_s(pEnemy -> m_szName, ("はち"));

		//モデルデータの読み込み
		pEnemy -> m_nMeshNumber = MODEL_BEE;
		break;
	case 1:
		//名前の設定
		sprintf_s(pEnemy -> m_szName, ("おおかみ"));

		//モデルデータ読み込み
		pEnemy -> m_nMeshNumber = MODEL_WOLF;
		break;
	case 2:
		//名前の設定
		sprintf_s(pEnemy -> m_szName, ("くま"));

		//モデルデータ読み込み
		pEnemy -> m_nMeshNumber = MODEL_BEAR;
		break;

		//デバッグ用処理
	default:
		//名前の設定
		sprintf_s(pEnemy -> m_szName, ("かべ"));

		//モデルデータ読み込み
		pEnemy ->m_nMeshNumber = MODEL_WALL;
		break;
	}
	
	//オブジェクトIDの設定
	pEnemy -> m_uID = ID_ENEMY;

	//ユニットのステート状態を設定
	pEnemy -> m_nStateNumber = CTurn::GAME_STATE_STAND_BY;

	//メッシュの設定
	pEnemy ->SetMesh(CModelManager::GetMesh(pEnemy ->m_nMeshNumber));

	//ユニットの番号を設定
	pEnemy -> m_nUnitNumber = OBJ_NUM_ENEMY + m_nMakeNumber;

	//生きている
	pEnemy -> m_bSurvival = true;

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
	pEnemy -> m_nLevel = CUnitManager::GetPlayerLevel() + (rand() % 6 - 3);

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
	pEnemy ->m_nStateNumber = CTurn::GAME_STATE_STAND_BY;

	//生成完了
	pEnemy ->m_bMakeSuccess = true;

	//ユニット生成数をカウント
	m_nMakeNumber ++;

	//シーン上にオブジェクトの追加
	CUnitManager::Add(pEnemy->m_nUnitNumber, pEnemy);
}
//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CEnemy::Update()
{
	//ユニットとしての更新を行う
	CUnit::Update();
}
//---------------------------------------------------------------------------------------
//入力更新(移動方向ルーチン)
//---------------------------------------------------------------------------------------
void CEnemy::InputUpdate()
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
	}

	//旧ステート情報の確保
	m_nOldStateNumber = m_nStateNumber;

	//移動できたか
	bool MoveCompletion = false;

	//A*による移動
	MoveCompletion = A_StarMove();

	//プレイヤーの位置情報を取得
	int PlayerPos_X = CUnitManager::GetPlayerPosX();
	int PlayerPos_Z = CUnitManager::GetPlayerPosZ();

	//差を計算
	int Distance_X = PlayerPos_X - m_nUnit_Pos_X;
	int Distance_Z = m_nUnit_Pos_Z - PlayerPos_Z;

	if(!MoveCompletion)
	{
		
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

			//自身のステートの設定
			m_nStateNumber = CTurn::GAME_STATE_ATTACK;
			
			//繰り出す技の番号を指定
			m_nTrickNumber = TRICK_RANGE_FRONT;
		}
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

			//自身のステート状態をターンの終了に設定
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

	//ステートの遷移(ターンの終了)
	m_nStateNumber = CTurn::GAME_STATE_TURN_END;
}

//---------------------------------------------------------------------------------------
//アイテム更新
//---------------------------------------------------------------------------------------
void CEnemy::ItemUpdate()
{

	//メッセージテスト
	MessageWindow::SetMassege(("アイテム使った"));

	//ステートの遷移(ターンの終了)
	m_nStateNumber = CTurn::GAME_STATE_TURN_END;
		
}
//---------------------------------------------------------------------------------------
//ターン終了更新
//---------------------------------------------------------------------------------------
void CEnemy::TurnEndUpdate()
{
	CUnit::TurnEndUpdate();

	//ステートの遷移(ターンの終了)
	m_nStateNumber = CTurn::GAME_STATE_STAND_BY;

	//自身のターンが終了した
	m_bTurnEndFlg = true;
}
//---------------------------------------------------------------------------------------
//A*アルゴリズムを用いた移動を行う
//---------------------------------------------------------------------------------------
bool CEnemy::A_StarMove()
{
	//A*で用いるデータ群の初期化
	CMapData::InitAStarData();

	//探索を行う場所
	int SearchPositionX = m_nUnit_Pos_X;
	int SearchPositionZ = m_nUnit_Pos_Z;

	//プレイヤーの位置情報
	int PlayerPositionX = CUnitManager::GetPlayerPosX();
	int PlayerPositionZ = CUnitManager::GetPlayerPosZ();

	//探索した位置をクローズ化
	CMapData::CompleteCellCal(SearchPositionX,SearchPositionZ,2);

	//探索を行う位置がプレイヤーの位置、又は異常値が返ってくるまで処理を行う
	while((SearchPositionX != PlayerPositionX || SearchPositionZ != PlayerPositionZ) && (SearchPositionX != -99 && SearchPositionZ != -99))
	{
		//周囲を探索する
		CMapData::SearchPosition(SearchPositionX,SearchPositionZ,m_nUnit_Pos_X,m_nUnit_Pos_Z,PlayerPositionX,PlayerPositionZ);

		//最もスコアの小さい位置を取得
		CMapData::SearchMinScoreData(&SearchPositionX,&SearchPositionZ);
		
		//探索した位置をクローズ化
		CMapData::CompleteCellCal(SearchPositionX,SearchPositionZ,2);
	}

	//探索終了

	//もし異常値が返ってきて処理が終了した場合、移動処理を終了(その場で待機)
	if((SearchPositionX == -99) || (SearchPositionZ == -99))
	{
		//自身のステートの設定
		m_nStateNumber = CTurn::GAME_STATE_TURN_END;

		//A*で用いるデータ群の初期化
		CMapData::InitAStarData();
		return false;
	}
	//プレイヤーのもとにたどり着いた場合

	//エネミーの位置の一つ前に戻る
	int ParentPosX = SearchPositionX;
	int ParentPosZ = SearchPositionZ;

	//親の位置がエネミー自身の位置になるまでループ
	while(ParentPosX != m_nUnit_Pos_X || ParentPosZ != m_nUnit_Pos_Z)
	{
		SearchPositionX = ParentPosX;
		SearchPositionZ = ParentPosZ;

		CMapData::GetParentPos(SearchPositionX,SearchPositionZ,&ParentPosX,&ParentPosZ);
	}

	//その位置がプレイヤーの位置の場合、移動しない
	int UnitMapSituation = CMapData::Get_UnitMapSituation(SearchPositionX,SearchPositionZ);
	if(UnitMapSituation != 0)
	{
		//自身のステートの設定
		m_nStateNumber = CTurn::GAME_STATE_TURN_END;

		//A*で用いるデータ群の初期化
		CMapData::InitAStarData();
		return false;
	}
	//その位置に移動
	//マーキング消去
	CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);

	//向きフラグ設定

	//フラグ初期化
	for(int i = 0;i < MaxDirection;i++)
	{
		m_bDirectionFlg[i] = false;
	}

	//移動する位置と現在の位置の差分を計算
	int DistanceX = m_nUnit_Pos_X - SearchPositionX;
	int DistanceZ = SearchPositionZ - m_nUnit_Pos_Z;
	
	//X軸の数値に変更がある場合処理
	if(abs(DistanceX))
	{
		//左へ移動した
		if(DistanceX > 0)
		{
			m_bDirectionFlg[Left] = true;	
		}
	
		//右へ移動した
		else
		{
			m_bDirectionFlg[Right] = true;	
		}
	}
	//Z軸の数値に変更がある場合処理
	if(abs(DistanceZ))
	{
		//後ろへ移動した
		if(DistanceZ > 0)
		{
			m_bDirectionFlg[Back] = true;	
		}
	
		//前へ移動した
		else
		{
			m_bDirectionFlg[Forword] = true;	
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
	
		
	int OldAngle = (int)(m_fOldAngle* 180 / PI );
	float RotateAngle = (float)((nAngle) * PI / 180);
	
	m_Angle.x = 0.0f;
	m_Angle.y = RotateAngle - m_fOldAngle;
	m_Angle.z = 0.0f;
	
	m_fOldAngle = RotateAngle;

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

	//指定位置に到達していない
	m_bDestination = false;
	m_fTimer = 0.0f;

	//配列上を移動
	m_nUnit_Pos_X = SearchPositionX;
	m_nUnit_Pos_Z = SearchPositionZ;
	
	//マーキング
	CMapData::Set_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z,m_nUnitNumber);

	//自身のステートの設定
	m_nStateNumber = CTurn::GAME_STATE_MOVE;

	//A*で用いるデータ群の初期化
	CMapData::InitAStarData();

	return true;
}