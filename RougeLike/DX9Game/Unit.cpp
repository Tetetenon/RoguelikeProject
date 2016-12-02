#include "Unit.h"
#include "GameScene.h"
#include "MessageWindow.h"
#include "TextureManager.h"
#include "MapData.h"
#include "GameState.h"
#include "Battle.h"
#include "Turn.h"
#include "DeleteObj.h"
#include "HitObj.h"
#include "Particle.h"
#include "Player.h"
#include "ItemGenerator.h"
#include "EnemyGenerator.h"
#include "TrickWindowCursor.h"
#include "MiniMap.h"

#define JUMP_INTERVAL 30	//ジャンプしてから次のジャンプまでの間隔

#define _CRT_SECURE_NO_WARNINGS

#define FLASHTIME	5	//点滅時の切り替え時間
#define FLASHNUM	3	//点滅回数

//行動にかかる時間
#define ACTION_TIME	0.6f

//満腹度最大値
#define MAX_SATIETY	100

//静的メンバ実体定義
int	 CUnit::m_nMakeNumber = OBJ_NUM_PLAYER;	//生成したユニットの数
int  CUnit::m_nAttackNumber = 0;				//攻撃を行っているユニットの番号
bool CUnit::m_bMoveCanFlg = true;;					//移動可能フラグ

float	g_Timer = 0;		//処理を開始してからの時間計測
int		g_Damage = 0;		//戦闘で発生するダメージ
//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CUnit::CUnit(CGameScene* pScene):
CMeshObj(pScene)
{
	//シーンクラスのポインタ取得
	m_pScene = pScene;

	//リストの初期化
	m_pNextUnit = m_pBackUnit = NULL;

	//シーン上にオブジェクトの追加
	m_pScene -> AddUnit(this);

	//状態の初期化
	m_nState = UNIT_STATE_HEALTH;	//健康
	m_nState_Turn = 0;

	//レベル初期化
	m_nLevel = 1;

	//満腹度初期化
	m_nSatiety = MAX_SATIETY;

	//点滅時間初期化
	m_nDrawFlashTime = 0;
	//点滅回数初期化
	m_nFlashNum = 0;
	//描画フラグ初期化
	m_bDrawFlg = true;

	//ジャンプ上昇初期化
	m_bJump = true;
	//ジャンプ上昇値初期化
	m_fJumpPos = 0.0f;
	//ジャンプの間隔初期化
	m_nJumpInterval = 0;
	//ジャンプ開始フラグ初期化
	m_bJumpFlg = false;

	//アイテムインベントリポインタを取得
	m_pInventory = new CInventory();
	//装備インベントリポインタを取得
	m_pEquipment = new CEquipmentInventory();

	//技ウィンドウポインタを取得
	m_pTrickWindow = new CTrickWindow();

	//レベルアップポインタの初期化
	m_pLevelUp = NULL;

	//技番号の初期化
	m_nTrickNumber = TRICK_NAME_MAX + 1;
	
	//戦闘を行う敵のポインタの初期化
	m_pBattleUnit = NULL;
	m_pBattleNext = NULL;
	m_pBattleBack = NULL;

	//向いている方向の初期化
	for(int i = 0;i < MaxDirection;i++)
	{
		m_bDirectionFlg[i] = false;
	}
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CUnit::~CUnit(void)
{
	//アイテムインベントリのポインタを削除
	delete m_pInventory;

	//装備インベントリのポインタを削除
	delete m_pEquipment;

	//技ウィンドウポインタの削除
	delete m_pTrickWindow;

	//レベルアップポインタの中身があれば、削除
	if(m_pLevelUp != NULL)
	{
		delete m_pLevelUp;
		m_pLevelUp = NULL;
	}
	
	//戦闘を行う敵のポインタの初期化
	m_pBattleUnit = NULL;
	m_pBattleNext = NULL;
	m_pBattleBack = NULL;

	//シーン上から自身のユニットポインタを削除する
	m_pScene ->DelUnit(this);
}

	
//---------------------------------------------------------------------------------------
//初期化
//---------------------------------------------------------------------------------------
void CUnit::Init()
{
	//アイテムインベントリの初期化
	m_pInventory ->Init();
	//装備インベントリの初期化
	m_pEquipment->Init();

	//技インベントリの初期化
	m_pTrickWindow->Init();
}

//---------------------------------------------------------------------------------------
//終了
//---------------------------------------------------------------------------------------
void CUnit::Fin()
{

	//マーキング消去
	CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);
	
	//現在自分が選択しているステートのユニットの数-1
	CTurn::SumCount(m_nStateNumber);

	//生成数を初期化する
	m_nMakeNumber = OBJ_NUM_PLAYER;

	//自身の削除
	delete this;
}

//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CUnit::Update()
{

	//レベルアップポリゴンの更新
	if(m_pLevelUp != NULL)
	{
		m_pLevelUp->Update(D3DXVECTOR3(m_world._41,m_world._42,m_world._43));

		//上昇値が一定を超えたら削除
		if(m_pLevelUp->GetUpPos() >= 255.0f)
		{
			delete m_pLevelUp;
			m_pLevelUp = NULL;
		}
	}
	//ユニットサークルの位置情報を設定
	m_Circle.SetPos(C3DObj::GetPos());

	//現在のプレイヤーのステート情報を取得
	int nPlayerState = CPlayer::GetState();

	if(nPlayerState == m_nStateNumber)
	{
		int Debug = 0;
	}


	int State = CTurn::GetState();	//ステート情報を一時的に格納
	
	//現在のステートを選択しているユニットの数を選択する
	int StateSelectNum = CTurn::GetStateSelectNum(State);

	//もし現在のステートを選択しているユニットが存在しなければ、そのステートをスキップする
	if(StateSelectNum == 0)
		CTurn::State_Advance(State + 1);

	//待機中、飛んでいるようなモーションを行う
	if(m_bJumpFlg)
	{
		//上昇フラグが立っていれば上昇
		if(m_bJump)
			m_fJumpPos += 0.03f;
		//立っていなければ下降
		else
			m_fJumpPos -= 0.02f;

		//上昇最大地点まで行けば下降する
		if(m_fJumpPos >= 0.5)
			m_bJump = false;
		//着地すれば、ジャンプフラグを倒す
		if(m_fJumpPos <= 0)
		{
			m_bJumpFlg = false;
			m_bJump = true;
		}
	}

	//ジャンプフラグが立っていない場合、次のジャンプまでの時間を計測する
	if(!m_bJumpFlg)
	{
		m_nJumpInterval ++;

		if(m_nJumpInterval >= JUMP_INTERVAL)
		{
			m_nJumpInterval = 0;
			m_bJumpFlg = true;
		}
	}

	//ワールドマトリックスからローカル軸抽出、座標抽出
	D3DXMATRIX world = GetWorld();

	world._42 = 0.0f;	//原点へ移動させる

	world._42 = m_fJumpPos;

	//ワールドマトリックスを設定
	SetWorld(world);

	//もし、行動可能フラグが立っていなければ、処理をスキップ
	if(!m_bMoveCanFlg)
		return;

	//現在のターンが、自身のターンであれば更新を行う
	if(m_nStateNumber == State)
	{
		//自身と同じステートにプレイヤーが存在する場合、プレイヤーを先に処理するため、スキップ
		//自身がプレイヤーの場合、条件をスル―
		if(m_nStateNumber != nPlayerState || m_nUnitNumber == OBJ_NUM_PLAYER)
		{
			//状態異常の経過時間を減らす
			//自身のターンが始まったか確認する
			if(m_nStateNumber != m_nOldStateNumber)
			{
				//入力待ち状態でのみ処理する
				if(m_nStateNumber <= GAME_STATE_STAND_BY_OTHER)
				{
					//自身が状態異常になっているか確認する
					if(m_nState_Turn != 0)
						//状態異常の処理
						TurnStartStateProcessing();
				}
			}

			//旧ステート情報の確保
			m_nOldStateNumber = m_nStateNumber;

			//ステート状態によって処理を分岐させる
			switch(State)
			{
			//入力待ち(プレイヤー)
			case GAME_STATE_STAND_BY_PLAYER:
				InputUpdate();
				break;

			//入力待ち(エネミー)
			case GAME_STATE_STAND_BY_OTHER:
				InputUpdate();
				break;
				
			//アイテム
			case GAME_STATE_ITEM_USE:
				ItemUpdate();
				break;
				
			//移動
			case GAME_STATE_MOVE:
				MoveUpdate();
				break;
				
			//アクション
			case GAME_STATE_ACT:
				ActUpdate();
				break;
				
			//攻撃
			case GAME_STATE_ATTACK:
				AttackUpdate();
				break;

			//ターン終了
			case GAME_STATE_TURN_END:
				TurnEndUpdate();
				break;
			}
		}
	}

	//アイテムウィンドウを描画していたら
	if(CInventory::GetDrawFlg())
		//アイテムインベントリの更新
		m_pInventory->UpDate();

	//装備ウィンドウを描画していたら
	if(CEquipmentInventory::GetDrawFlg())
		//装備インベントリの更新
		m_pEquipment ->UpDate();

	//技ウィンドウを描画していたら
	if(CTrickWindow::GetDrawFlg())
		//技ウィンドウの更新
		m_pTrickWindow->UpDate();
}
	
//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CUnit::Draw()
{
	//自身の描画フラグが立っているか
	if(m_bDrawFlg)
	{
		//立っていれば、描画を行う

		//親クラスの描画処理を行う
		CMeshObj::Draw();

		//ユニットサークルの描画
		m_Circle.Draw(m_nUnitNumber);

		//レベルアップポリゴンのポインタの中身があれば、描画
		if(m_pLevelUp != NULL)
		{
			m_pLevelUp ->Draw();
		}

	}
}
//---------------------------------------------------------------------------------------
//ユニットの検索
//---------------------------------------------------------------------------------------
CUnit* CUnit::FindUnit(UINT uID,CUnit* p)
{
	//シーンオブジェクトが存在しなければ、ほかのオブジェクトも存在しないため
	//ここで最初に判定をする
	if(m_pScene)
		return m_pScene -> FindUnit(uID,p);
	return NULL;
}

//---------------------------------------------------------------------------------------
//アイテム検索
//---------------------------------------------------------------------------------------
CFieldItem* CUnit::ItemFind(UINT uID,CFieldItem* p)
{
	//シーンオブジェクトが存在しなければ、ほかのオブジェクトも存在しないため
	//ここで最初に判定をする
	if(m_pScene)
		return m_pScene -> FindItem(uID,p);
	return NULL;
}

//---------------------------------------------------------------------------------------
//入力更新
//---------------------------------------------------------------------------------------
void CUnit::InputUpdate()
{

}

//---------------------------------------------------------------------------------------
//移動更新
//---------------------------------------------------------------------------------------
void CUnit::MoveUpdate()
{
}

//---------------------------------------------------------------------------------------
//アクション更新
//---------------------------------------------------------------------------------------
void CUnit::ActUpdate()
{

}
//---------------------------------------------------------------------------------------
//攻撃更新
//---------------------------------------------------------------------------------------
void CUnit::AttackUpdate()
{
	//現在誰も攻撃アニメーションを行っていない、又は自身が攻撃アニメーションを行っている場合のみ更新する
	if(m_nUnitNumber == m_nAttackNumber || m_nAttackNumber == 0)
	{
		//自身が攻撃アニメーションを行っているよう、設定する
		m_nAttackNumber = m_nUnitNumber;

		//現在の戦闘ステートを取得する
		int nBattleState = CTurn::GetBattleState();

	//現在の戦闘ステート状態によって、更新内容を分岐させる
	switch(nBattleState)
	{
		//相手の方向に突撃する
	case BATTLE_STATE_GO:
		BattleGo();
		break;
		
		//今の位置から本来の位置へと戻る
	case BATTLE_STATE_RETURN:
		BattleReturn();
		break;

		//相手の検索、ダメージの計算
	case BATTLE_STATE_SEARCH:
		AttackSwitch();
		break;

		//相手に攻撃が当たった
	case BATTLE_STATE_HIT:
			BattleHit();
		break;
		
		//ダメージ受けた表現を行う
	case BATTLE_STATE_FLASHING:
			BattleFlasing();
		break;
		
		//メッセージウインドウにダメージ結果を送る
	case BATTLE_STATE_WINDOW:
			BattleWindow();
		break;

		//算出されたダメージを実際に相手から減らす
	case BATTLE_STATE_DAMAGE:
			BattleDamage();
		break;

		//戦闘終了、ステート関連の設定
	case BATTLE_STATE_END:
			BattleEnd();
		break;
	}
	}
}

//---------------------------------------------------------------------------------------
//アイテム更新
//---------------------------------------------------------------------------------------
void CUnit::ItemUpdate()
{

}
//---------------------------------------------------------------------------------------
//ターン終了更新
//---------------------------------------------------------------------------------------
void CUnit::TurnEndUpdate()
{

}

//---------------------------------------------------------------------------------------
//HPを減らす
//---------------------------------------------------------------------------------------
void CUnit::DamegeHP (int Damage)
{
	m_nHP -= Damage;	//体力を減らす

	//もし体力が0以下ならば、死亡メッセージを出させる
	if(m_nHP <= 0)
	{
		//表示時に-表記にならないよう
		m_nHP = 0;
		//メッセージ表記
		TCHAR	str[256];
		_stprintf_s(str,sizeof(str), _T("%sは倒れた!"),m_szName);
	
		//メッセージテスト
		MessageWindow::SetMassege(str);
	}
	//プレイヤーのHPが減った場合、画面のHP表示を変更
	if(m_uID == ID_PLAYER)
	{
		//画面に描画してもらうHPの数値を渡す
		CHPDraw::SetHP(m_nHP);
	}
}

//---------------------------------------------------------------------------------------
//HPを回復させる
//---------------------------------------------------------------------------------------
void CUnit::RecoveryHP (int Recovery)
{
	m_nHP += Recovery;	//体力回復

	//体力の上限を超えないようにする
	if(m_nHP > m_nMaxHP)
		m_nHP = m_nMaxHP;
	
	//メッセージ表記
	TCHAR	str[256];
	_stprintf_s(str,sizeof(str),_T("%d回復した!"),Recovery);
	//メッセージ出力
	MessageWindow::SetMassege(str);

	//プレイヤーのHPが減った場合、画面のHP表示を変更
	if(m_uID == ID_PLAYER)
	{
		//画面に描画してもらうHPの数値を渡す
		CHPDraw::SetHP(m_nHP);
	}
}

//---------------------------------------------------------------------------------------
//自身の削除
//---------------------------------------------------------------------------------------
void CUnit::Delete()
{
	//マーキング消去
	CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);
	
	//現在自分が選択しているステートのユニットの数-1
	CTurn::SumCount(m_nStateNumber);

	m_bSurvival = false;

	//プレイヤーであった場合、シーンをリザルトに遷移させる
	if(m_uID == ID_PLAYER)
	{
		//ゲームメインを終了
		CFade::ChangeState(FADEMODE_OUT);

		//ゲームクリア状態をゲームオーバーに
		CGameScene::GameClearStateChange(GAME_OVER);

		//エネミーの生成数のリセット
		CEnemyGenerator::ResetMakeEnemyNum();

		//フィールドアイテム生成数のリセット
		CItemGenerator::ResetMakeItemNum();
	}

	//プレイヤー以外の場合消滅
	if(m_uID != ID_PLAYER)
	{
		//自身の削除
		delete this;
	}
}
//---------------------------------------------------------------------------------------
//名前の取得
//---------------------------------------------------------------------------------------
char* CUnit::GetName(char* pName)
{
	pName = m_szName;

	return pName;
}

//---------------------------------------------------------------------------------------
//正面へ突撃させる
//---------------------------------------------------------------------------------------
void CUnit::BattleGo()
{

	//ステート経過時間加算
	CTurn::TimeStateAdd();

	//現在のステート進行
	int nStateTime = CTurn::GetStateTime();

	//現在の突撃割合
	float fAttackPar = (float)nStateTime / STATE_TIME;

	//突撃方向の設定

	//突撃する方向
	float fAttackPosX = 0.0f;
	float fAttackPosZ = 0.0f;
	//上方向に突撃するかのチェック
	if(m_bDirectionFlg[Forword])
	{
		//上へ突撃
		fAttackPosZ--;
	}
	//下方向に突撃するかのチェック
	if(m_bDirectionFlg[Back])
	{
		//下へ突撃
		fAttackPosZ++;
	}
	//右方向に突撃するかのチェック
	if(m_bDirectionFlg[Right])
	{
		//右へ突撃
		fAttackPosX++;
	}
	//左方向に突撃するかのチェック
	if(m_bDirectionFlg[Left])
	{
		//左へ突撃
		fAttackPosX--;
	}
	
	//現在の進んでいる割合を計算
	fAttackPosX *= fAttackPar;
	fAttackPosZ *= fAttackPar;

	//ワールドマトリックスからローカル軸抽出、座標抽出
	D3DXMATRIX world = GetWorld();
	
	//位置情報設定
	world._41 = ((m_nUnit_Pos_X + fAttackPosX) - (MAP_SIZE / 2)) * GRIDSIZE + GRIDSIZE / 2;
	world._42 = 0.0f;
	world._43 = -((m_nUnit_Pos_Z + fAttackPosZ) - (MAP_SIZE / 2)) * GRIDSIZE - GRIDSIZE / 2;
	
	//ワールドマトリックスを設定
	SetWorld(world);

	//所定経過時間を超えたらステート遷移
	if(CTurn::GetStateTime() >= STATE_TIME)
	{
		//戦闘ステートを進める
		CTurn::BattleState_Advance(BATTLE_STATE_RETURN);

		//ステートリセット
		CTurn::TimeStateReset();
	}
}

//---------------------------------------------------------------------------------------
//突撃した相手の位置から自身の本来の位置へ戻る
//---------------------------------------------------------------------------------------
void CUnit::BattleReturn()
{
	//ステート経過時間加算
	CTurn::TimeStateAdd();
	
	//現在のステート進行
	int nStateTime = CTurn::GetStateTime();

	//現在の突撃割合
	float fAttackPar = (float)nStateTime / STATE_TIME;

	//突撃する方向
	float fAttackPosX = 0.0f;
	float fAttackPosZ = 0.0f;
	//上方向に突撃するかのチェック
	if(m_bDirectionFlg[Forword])
	{
		//上へ突撃
		fAttackPosZ--;
	}
	//下方向に突撃するかのチェック
	if(m_bDirectionFlg[Back])
	{
		//下へ突撃
		fAttackPosZ++;
	}
	//右方向に突撃するかのチェック
	if(m_bDirectionFlg[Right])
	{
		//右へ突撃
		fAttackPosX++;
	}
	//左方向に突撃するかのチェック
	if(m_bDirectionFlg[Left])
	{
		//左へ突撃
		fAttackPosX--;
	}
	
	//現在の進んでいる割合を計算
	fAttackPosX *= (1 - fAttackPar);
	fAttackPosZ *= (1 - fAttackPar);

	//ワールドマトリックスからローカル軸抽出、座標抽出
	D3DXMATRIX world = GetWorld();
	
	//位置情報設定
	world._41 = ((m_nUnit_Pos_X + fAttackPosX) - (MAP_SIZE / 2)) * GRIDSIZE + GRIDSIZE / 2;
	world._42 = 0.0f;
	world._43 = -((m_nUnit_Pos_Z + fAttackPosZ) - (MAP_SIZE / 2)) * GRIDSIZE - GRIDSIZE / 2;

	//ワールドマトリックスを設定
	SetWorld(world);

	//所定経過時間を超えたらステート遷移
	if(CTurn::GetStateTime() >= STATE_TIME)
	{
		//技番号の設定がされていなければ、設定する
		if(m_nTrickNumber > TRICK_NAME_MAX)
		{
			//技のIDを取得する
			m_nTrickNumber = m_pTrickWindow->GetRange(CTrickWindowCursor::GetTrickNum());
		}
		//戦闘ステートを進める
		CTurn::BattleState_Advance(BATTLE_STATE_SEARCH);

		//ステートリセット
		CTurn::TimeStateReset();
	}
}
//---------------------------------------------------------------------------------------
//技の範囲から、攻撃する相手を分岐させる
//---------------------------------------------------------------------------------------
void CUnit::AttackSwitch()
{
	//攻撃する際の技の範囲で、攻撃パターンを変化させる
	switch(m_nTrickNumber)
	{
		//正面のみに攻撃を行う
	case TRICK_RANGE_FRONT:
		AttackFront();
		break;
		//前方三マスの敵に攻撃を行う
	case TRICK_RANGE_WIDE:
		AttackWide();
		break;
	case TRICK_RANGE_ALL:
		//部屋の敵すべてに攻撃を行う
		AttackAll();
		break;

		//自身に効果を及ぼす
	case TRICK_RANGE_ME:
		switch(m_pTrickWindow->GetEffect(CTrickWindowCursor::GetTrickNum()))
		{
		case TRICK_EFFECT_STATES_UP:

			//ステータスを上昇させる
			m_nAttack ++;
			m_nDefence ++;

			MessageWindow::SetMassege(_T("ステータスが上昇した!"));
			break;
		case TRICK_EFFECT_RECOVERY:

			//今から回復する量
			int nRecoveryHP = m_nMaxHP / 2;

			//HPを半分回復する
			RecoveryHP(nRecoveryHP);
			break;
		}
		//ステートを進める
		CTurn::BattleState_Advance(BATTLE_STATE_END);
		break;
		//デバッグ
	case TRICK_RANGE_MAX:
		break;
	}
}
//---------------------------------------------------------------------------------------
//戦闘で発生するダメージ量の算出を行う
//---------------------------------------------------------------------------------------
void CUnit::BattleCalculation(CUnit *BattleUnit)
{
	//攻撃力を変動させるため、コピー
	int nAttack = m_nAttack;
	//クリティカル判定
	//5%の確率でクリティカルが出る
	if(rand()%20 == 0)
	{
		nAttack = static_cast<int>(nAttack*1.5f);
		
		//メッセージ表記
		MessageWindow::SetMassege( _T("急所に当たった!"));
	}

	//ダメージ計算(装備の値も計算に入れる)
	g_Damage = CBattle::DamageCalculation(nAttack + m_pEquipment->GetAttackTotalValue(),BattleUnit -> GetDF() + BattleUnit -> GetEquipmentDefenceNum());
}

//---------------------------------------------------------------------------------------
//敵の探索を行う
//---------------------------------------------------------------------------------------
bool CUnit::FindEnemy(int PosX,int PosZ)
{
	//マップの情報を取得する
	int MapSituation;
	//攻撃している位置の状態取得
	MapSituation = CMapData::Get_UnitMapSituation(PosX,PosZ);

	//攻撃位置にエネミーがいるか確認する
	//戦闘を行うユニットの情報の所得を行う
	if(MapSituation > 0 && MapSituation != m_nUnitNumber)
	{
		//これから追加する戦闘ユニット
		CUnit *BattleUnit = NULL;

		//戦闘するユニットの検索
		BattleUnit = (CUnit*)FindUnit(MapSituation);

		//戦闘ダメージの計算を行う
		BattleCalculation(BattleUnit);

		//ヒットオブジェクトの作成
		CHitObj::Generation(BattleUnit);

		//戦闘を行うユニットを、戦闘ユニットリストに追加する。

		//戦闘ユニットリストの空きがあるところまで移動する
		//現在確認しているユニット
		CUnit* NowUnit = m_pBattleUnit;

		//中身が存在するかチェック
		if(m_pBattleUnit)
		{
			while(NowUnit ->m_pBattleNext)
			{
				NowUnit = NowUnit->m_pBattleNext;
			}

			//最後尾に戦闘を行うユニットを追加する
			NowUnit ->m_pBattleNext = BattleUnit;
			BattleUnit->m_pBattleBack = NowUnit;
			BattleUnit->m_pBattleNext = NULL;
		}
		//中身がない(初めて敵がヒットした)
		else
		{
			m_pBattleUnit = BattleUnit;
			BattleUnit->m_pBattleBack = NULL;
			BattleUnit->m_pBattleNext = NULL;
		}


		return true;
	}
	return false;

}
//---------------------------------------------------------------------------------------
//指定した位置の敵に攻撃を行う
//---------------------------------------------------------------------------------------
bool CUnit::Attack(int CorrectionPosX,int CorrectionPosY)
{
	//ユニットの攻撃をした配列位置
	int Direction_X = m_nUnit_Pos_X;
	int Direction_Z = m_nUnit_Pos_Z;

	//敵の探索を行い、その結果を変数とする
	return FindEnemy(Direction_X,Direction_Z);
}
//---------------------------------------------------------------------------------------
//正面の敵に攻撃を行う
//---------------------------------------------------------------------------------------
bool CUnit::FrontFind()
{
	//ユニットの攻撃をした配列位置
	int Direction_X = m_nUnit_Pos_X;
	int Direction_Z = m_nUnit_Pos_Z;

	//ユニットの向きから攻撃している位置を設定
	if(m_bDirectionFlg[Forword])
		Direction_Z --;
	if(m_bDirectionFlg[Back])
		Direction_Z ++;

	if(m_bDirectionFlg[Right])
		Direction_X ++;

	if(m_bDirectionFlg[Left])
		Direction_X--;

	//敵の探索を行い、その結果を変数とする
	return FindEnemy(Direction_X,Direction_Z);
}
//---------------------------------------------------------------------------------------
//右の敵に攻撃を行う
//---------------------------------------------------------------------------------------
bool CUnit::Side_Right()
{
	//ユニットの攻撃をした配列位置
	int Direction_X = m_nUnit_Pos_X;
	int Direction_Z = m_nUnit_Pos_Z;

	//ユニットの向きから攻撃している位置を設定
	if(m_bDirectionFlg[Forword])
		Direction_X ++;
	if(m_bDirectionFlg[Back])
		Direction_X --;

	if(m_bDirectionFlg[Right])
		Direction_Z ++;

	if(m_bDirectionFlg[Left])
		Direction_Z --;

	//敵の探索を行い、その結果を変数とする
	return FindEnemy(Direction_X,Direction_Z);
}
//---------------------------------------------------------------------------------------
//左の敵に攻撃を行う
//---------------------------------------------------------------------------------------
bool CUnit::Side_Left()
{
	//ユニットの攻撃をした配列位置
	int Direction_X = m_nUnit_Pos_X;
	int Direction_Z = m_nUnit_Pos_Z;

	//ユニットの向きから攻撃している位置を設定
	if(m_bDirectionFlg[Forword])
		Direction_X --;
	if(m_bDirectionFlg[Back])
		Direction_X ++;

	if(m_bDirectionFlg[Right])
		Direction_Z --;

	if(m_bDirectionFlg[Left])
		Direction_Z ++;

	//敵の探索を行い、その結果を変数とする
	return FindEnemy(Direction_X,Direction_Z);
}
//---------------------------------------------------------------------------------------
//後ろの敵に攻撃を行う
//---------------------------------------------------------------------------------------
bool CUnit::BackFind()
{
	//ユニットの攻撃をした配列位置
	int Direction_X = m_nUnit_Pos_X;
	int Direction_Z = m_nUnit_Pos_Z;

	//ユニットの向きから攻撃している位置を設定
	if(m_bDirectionFlg[Forword])
		Direction_Z ++;

	if(m_bDirectionFlg[Back])
		Direction_Z --;

	if(m_bDirectionFlg[Right])
		Direction_X --;

	if(m_bDirectionFlg[Left])
		Direction_X++;

	//敵の探索を行い、その結果を変数とする
	return FindEnemy(Direction_X,Direction_Z);
}
//---------------------------------------------------------------------------------------
//斜め右の敵に攻撃
//---------------------------------------------------------------------------------------
bool CUnit::SlightRight()
{
	//ユニットの攻撃をした配列位置
	int Direction_X = m_nUnit_Pos_X;
	int Direction_Z = m_nUnit_Pos_Z;

	//ユニットの向きから攻撃している位置を設定
	if(m_bDirectionFlg[Forword])
		Direction_Z --;
	if(m_bDirectionFlg[Back])
		Direction_Z ++;

	if(m_bDirectionFlg[Right])
		Direction_X ++;

	if(m_bDirectionFlg[Left])
		Direction_X--;

	//自身の斜め右に攻撃する
	if(m_bDirectionFlg[Forword])
	{
		if(m_bDirectionFlg[Right])
			Direction_Z ++;
		else
			Direction_X ++;
	}
	if(m_bDirectionFlg[Back])
	{
		if(m_bDirectionFlg[Left])
			Direction_Z --;
		else
			Direction_X --;
	}

	if(!m_bDirectionFlg[Forword] && !m_bDirectionFlg[Back])
	{
		if(m_bDirectionFlg[Right])
		{
			Direction_Z++;
		}
		if(m_bDirectionFlg[Left])
		{
			Direction_Z--;
		}
	}
	
	//敵の探索を行い、その結果を変数とする
	return FindEnemy(Direction_X,Direction_Z);
}
//---------------------------------------------------------------------------------------
//斜め左の敵に攻撃
//---------------------------------------------------------------------------------------
bool CUnit::SlightLeft()
{
	//ユニットの攻撃をした配列位置
	int Direction_X = m_nUnit_Pos_X;
	int Direction_Z = m_nUnit_Pos_Z;

	//ユニットの向きから攻撃している位置を設定
	if(m_bDirectionFlg[Forword])
		Direction_Z --;
	if(m_bDirectionFlg[Back])
		Direction_Z ++;

	if(m_bDirectionFlg[Right])
		Direction_X ++;

	if(m_bDirectionFlg[Left])
		Direction_X--;

	//自身の斜め右に攻撃する
	if(m_bDirectionFlg[Forword])
	{
		if(m_bDirectionFlg[Left])
			Direction_Z ++;
		else
			Direction_X --;
	}
	if(m_bDirectionFlg[Back])
	{
		if(m_bDirectionFlg[Right])
			Direction_Z --;
		else
			Direction_X ++;
	}

	if(!m_bDirectionFlg[Forword] && !m_bDirectionFlg[Back])
	{
		if(m_bDirectionFlg[Right])
		{
			Direction_Z--;
		}
		if(m_bDirectionFlg[Left])
		{
			Direction_Z++;
		}
	}

	//敵の探索を行い、その結果を変数とする
	return FindEnemy(Direction_X,Direction_Z);
}
//---------------------------------------------------------------------------------------
//斜め右後ろの敵に攻撃
//---------------------------------------------------------------------------------------
bool CUnit::SlightRightBack()
{
	//ユニットの攻撃をした配列位置
	int Direction_X = m_nUnit_Pos_X;
	int Direction_Z = m_nUnit_Pos_Z;

	//ユニットの向きから攻撃している位置を設定
	if(m_bDirectionFlg[Forword])
		Direction_Z ++;

	if(m_bDirectionFlg[Back])
		Direction_Z --;

	if(m_bDirectionFlg[Right])
		Direction_X --;

	if(m_bDirectionFlg[Left])
		Direction_X ++;

	//自身の斜め右に攻撃する
	if(m_bDirectionFlg[Forword])
	{
		if(m_bDirectionFlg[Left])
			Direction_Z ++;
		else
			Direction_X --;
	}
	if(m_bDirectionFlg[Back])
	{
		if(m_bDirectionFlg[Right])
			Direction_Z --;
		else
			Direction_X ++;
	}

	if(!m_bDirectionFlg[Forword] && !m_bDirectionFlg[Back])
	{
		if(m_bDirectionFlg[Right])
		{
			Direction_Z--;
		}
		if(m_bDirectionFlg[Left])
		{
			Direction_Z++;
		}
	}

	//敵の探索を行い、その結果を変数とする
	return FindEnemy(Direction_X,Direction_Z);
}
//---------------------------------------------------------------------------------------
//斜め左後ろの敵に攻撃
//---------------------------------------------------------------------------------------
bool CUnit::SlightLeftBack()
{
	//ユニットの攻撃をした配列位置
	int Direction_X = m_nUnit_Pos_X;
	int Direction_Z = m_nUnit_Pos_Z;

	//ユニットの向きから攻撃している位置を設定
	if(m_bDirectionFlg[Forword])
		Direction_Z ++;
	if(m_bDirectionFlg[Back])
		Direction_Z --;

	if(m_bDirectionFlg[Right])
		Direction_X --;

	if(m_bDirectionFlg[Left])
		Direction_X ++;

	//自身の斜め右に攻撃する
	if(m_bDirectionFlg[Forword])
	{
		if(m_bDirectionFlg[Left])
			Direction_Z ++;
		else
			Direction_X --;
	}
	if(m_bDirectionFlg[Back])
	{
		if(m_bDirectionFlg[Right])
			Direction_Z --;
		else
			Direction_X ++;
	}

	if(!m_bDirectionFlg[Forword] && !m_bDirectionFlg[Back])
	{
		if(m_bDirectionFlg[Right])
		{
			Direction_Z--;
		}
		if(m_bDirectionFlg[Left])
		{
			Direction_Z++;
		}
	}

	//敵の探索を行い、その結果を変数とする
	return FindEnemy(Direction_X,Direction_Z);
}
//---------------------------------------------------------------------------------------
//正面の敵のみに攻撃を行う
//---------------------------------------------------------------------------------------
void CUnit::AttackFront()
{
	//正面にエネミーがいるか確認する
	//戦闘を行うユニットの情報の所得を行う
	if(FrontFind())
	{
		//戦闘ステートを進める
		CTurn::BattleState_Advance(BATTLE_STATE_HIT);
	}

	//攻撃先にユニットが存在しなかった
	else
	{
		//メッセージ表記
		TCHAR	str[256];
		_stprintf_s(str, _T("%sの攻撃は外れた"),m_szName);
		
		//メッセージテスト
		MessageWindow::SetMassege(str);

		//ステートを進める
		CTurn::BattleState_Advance(BATTLE_STATE_END);
	}

	//ステートリセット
	CTurn::TimeStateReset();
}
//---------------------------------------------------------------------------------------
//前方三マスの敵に攻撃を行う
//---------------------------------------------------------------------------------------
void CUnit::AttackWide()
{
	bool bFront = FrontFind();
	bool bRight = SlightRight();
	bool bLeft = SlightLeft();

	//正面にエネミーがいるか確認する
	//戦闘を行うユニットの情報の所得を行う
	if(bFront || bRight || bLeft)
	{
		//戦闘ステートを進める
		CTurn::BattleState_Advance(BATTLE_STATE_HIT);
	}

	//攻撃先にユニットが存在しなかった
	else
	{
		//メッセージ表記
		TCHAR	str[256];
		_stprintf_s(str, _T("%sの攻撃は外れた"),m_szName);
		
		//メッセージテスト
		MessageWindow::SetMassege(str);

		//ステートを進める
		CTurn::BattleState_Advance(BATTLE_STATE_END);
	}

	//ステートリセット
	CTurn::TimeStateReset();

}
//---------------------------------------------------------------------------------------
//部屋の敵すべてに攻撃を行う
//---------------------------------------------------------------------------------------
void CUnit::AttackAll()
{
	//敵一体以上に攻撃がヒットしたか
	bool bHitFlg = false;

	//自身がいる部屋番号を取得する
	int nMyRoomNumber = CMapData::GetRoomNumber(m_nUnit_Pos_X,m_nUnit_Pos_Z);

	//自身が部屋にいる場合、部屋の中の敵の探索を行う
	if(!(nMyRoomNumber >= ROOM_MAX_NUM))
	{
		//部屋の間取りを受け取る
		RECT MyRoomData = CMapData::GetRoomFloorPlan(nMyRoomNumber);

		//間取りの分だけ、敵の探索を行う
		for(int i = MyRoomData.top;i < MyRoomData.bottom;i++)
		{
			for(int j = MyRoomData.left;j < MyRoomData.right;j++)
			{
				//指定した位置に敵がいたら当たったフラグをたてる
				if(FindEnemy(j,i))
				{
					bHitFlg = true;
				}
			}
		}
		//敵ユニットに一度でも攻撃が当たった
		if(bHitFlg)
		{
			//戦闘ステートを進める
			CTurn::BattleState_Advance(BATTLE_STATE_HIT);
		}

		//攻撃先にユニットが存在しなかった
		else
		{
			//メッセージ表記
			TCHAR	str[256];
			_stprintf_s(str, _T("%sの攻撃は外れた"),m_szName);
		
			//メッセージテスト
			MessageWindow::SetMassege(str);

			//ステートを進める
			CTurn::BattleState_Advance(BATTLE_STATE_END);
		}

		//ステートリセット
		CTurn::TimeStateReset();
	}

	//部屋の外で攻撃を行った
	else
	{
		//自身の周囲の敵に攻撃を行う

		//正面の敵に攻撃がヒットしたか
		bool bFrontHit = FrontFind();
		//背面の敵に攻撃がヒットしたか
		bool bBackHit = BackFind();
		//右側の敵に攻撃がヒットしたか
		bool bRightHit = Side_Right();
		//左側の敵に攻撃がヒットしたか
		bool bLeftHit = Side_Left();
		
		//斜め右前の敵に攻撃がヒットしたか
		bool bSlightRightHit = SlightRight();
		//斜め左前の敵に攻撃がヒットしたか
		bool bSlightLeftHit = SlightLeft();
		//斜め右後ろの敵に攻撃がヒットしたか
		bool bSlightRightBackHit = SlightRightBack();
		//斜め左後ろの敵に攻撃がヒットしたか
		bool bSlightLeftBackHit = SlightLeftBack();

		//全てのヒットフラグをまとめる
		bHitFlg = bFrontHit || bBackHit || bRightHit || bLeftHit || bSlightLeftHit || bSlightLeftBackHit || bSlightRightHit || bSlightRightBackHit;
		
		//敵ユニットに一度でも攻撃が当たった
		if(bHitFlg)
		{
			//戦闘ステートを進める
			CTurn::BattleState_Advance(BATTLE_STATE_HIT);
		}

		//攻撃先にユニットが存在しなかった
		else
		{
			//メッセージ表記
			TCHAR	str[256];
			_stprintf_s(str, _T("%sの攻撃は外れた"),m_szName);
		
			//メッセージテスト
			MessageWindow::SetMassege(str);
	
			//ステートを進める
			CTurn::BattleState_Advance(BATTLE_STATE_END);
		}

		//ステートリセット
		CTurn::TimeStateReset();
	}
}

//---------------------------------------------------------------------------------------
//ヒットエフェクトを発生させる
//---------------------------------------------------------------------------------------
void CUnit::BattleHit()
{
	//ステート経過時間加算
	CTurn::TimeStateAdd();

	//所定経過時間を超えたらステート遷移
	if(CTurn::GetStateTime() >= STATE_TIME / 2)
	{
		//戦闘ステートを進める
		CTurn::BattleState_Advance(BATTLE_STATE_FLASHING);

		//ステートリセット
		CTurn::TimeStateReset();
		

		//戦闘ユニットリストに存在するすべてのユニットに対し、適用する
		//現在確認しているユニット
		CUnit* pNowUnit = m_pBattleUnit;

		while(pNowUnit)
		{
			//相手の描画フラグを一時的に下げる
			pNowUnit->ChangeDrawFlg();

			//次のユニットへうつる
			pNowUnit = pNowUnit->m_pBattleNext;
		}
	}
}

//---------------------------------------------------------------------------------------
//相手の描画を点滅させる
//---------------------------------------------------------------------------------------
void CUnit::BattleFlasing()
{
	//点滅回数の格納
	int FlashNum = 0;
	
	//戦闘ユニットリストに存在するすべてのユニットに対し、適用する
	//現在確認しているユニット
	CUnit* pNowUnit = m_pBattleUnit;

	while(pNowUnit)
	{
		//敵ユニットの点滅時間を加算する
		pNowUnit->FlashAddTimer();

		//敵ユニットの点滅時間を取得
		int FlashTime = pNowUnit ->GetFlashTime();
		FlashTime %= FLASHTIME;

		//フラッシュの時間が一定時間を超えているか
		if(FlashTime == 0)
		{
			//敵ユニットの描画を反転させる
			pNowUnit ->ChangeDrawFlg();

			//点滅回数を加算
			pNowUnit ->FlashAddNum();

			//点滅回数を取得する
			FlashNum = pNowUnit ->GetFlashNum();
		}

		//次のユニットへうつる
		pNowUnit = pNowUnit->m_pBattleNext;
	}

	
	//点滅回数が一定以上か？
	if(FlashNum >= FLASHNUM || !m_pBattleUnit)
	{
		CUnit* pNowUnit = m_pBattleUnit;

		while(pNowUnit)
		{
			pNowUnit->UpDrawFlg();

			//次のユニットへうつる
			pNowUnit = pNowUnit->m_pBattleNext;
		}
		//戦闘ステートを進める
		CTurn::BattleState_Advance(BATTLE_STATE_WINDOW);
		//ステートリセット
		CTurn::TimeStateReset();
	}

}

//---------------------------------------------------------------------------------------
//メッセージウインドウにメッセージを送る
//---------------------------------------------------------------------------------------
void CUnit::BattleWindow()
{
	//相手ユニットの名前を取得
	char* pszName = NULL;
	
	//戦闘ユニットリストに存在するすべてのユニットに対し、適用する
	//現在確認しているユニット
	CUnit* pNowUnit = m_pBattleUnit;

	while(pNowUnit)
	{
		pszName = pNowUnit->GetName(pszName);

		//メッセージ表記
		//TCHAR	str[256];
		//_stprintf_s(str, _T("%sに%dのダメージ!"),pszName,g_Damage);

		//メッセージテスト
		MessageWindow::SetMassege(_T("%sに%dのダメージ!"),pszName,g_Damage);

		//次のユニットへうつる
		pNowUnit = pNowUnit->m_pBattleNext;
	}
	//戦闘ステートを進める
	CTurn::BattleState_Advance(BATTLE_STATE_DAMAGE);
	//ステートリセット
	CTurn::TimeStateReset();
}

//---------------------------------------------------------------------------------------
//相手に算出されたダメージを与える
//---------------------------------------------------------------------------------------
void CUnit::BattleDamage()
{
	
	//戦闘ユニットリストに存在するすべてのユニットに対し、適用する
	//現在確認しているユニット
	CUnit* pNowUnit = m_pBattleUnit;

	//消滅エフェクトステートへ移行するか否か
	bool bDeleteEffectFlg = false;

	while(pNowUnit)
	{
		//ダメージを与える
		pNowUnit -> DamegeHP(g_Damage);

		//HPが無くなったら次の消滅エフェクトを出すステートへ
		if(pNowUnit -> GetHP() <= 0)
		{
			//消滅ステートに飛ぶように設定する
			bDeleteEffectFlg = true;

			//パーティクル生成!(テスト)
			CParticle::Generation(pNowUnit,PARTICLE_PATTERN_DELETE);

			//倒した相手の被経験値を取得
			int Exp = pNowUnit ->GetXP();
			//倒した相手の被経験値を加算
			m_nExp += Exp;

			//上限値を超えていたら、レベルアップ
			if(m_nExp >= MAX_EXP && m_nLevel < 100)
			{
				if(m_pLevelUp == NULL)
				{
					//レベルアップポリゴンの作成
					m_pLevelUp = new CLevelUp(D3DXVECTOR3(m_world._41,m_world._42,m_world._43));
				}
				//メッセージ表記用変数
				TCHAR	str[256];
				//レベルアップメッセージを出す
				_stprintf_s(str, _T("%sはレベルが上がった!"),m_szName);
				//メッセージ出力
				MessageWindow::SetMassege(str);

				//レベルを加算
				m_nLevel ++;

				//ステータス値を加算

				//最大HP
				m_nMaxHP += m_nHPUpNum;
				//ステータス値をメッセージとして出す
				_stprintf_s(str, _T("HPが%d上がった!"),m_nHPUpNum);
				//メッセージ出力
				MessageWindow::SetMassege(str);

				//攻撃
				m_nAttack += m_nAttackUpNum;
				//ステータス値をメッセージとして出す
				_stprintf_s(str, _T("攻撃が%d上がった!"),m_nAttackUpNum);
				//メッセージ出力
				MessageWindow::SetMassege(str);

				//防御
				m_nDefence += m_nDefenceUpNum;
				//ステータス値をメッセージとして出す
				_stprintf_s(str, _T("防御が%d上がった!"),m_nDefenceUpNum);
				//メッセージ出力
				MessageWindow::SetMassege(str);

				//経験値を最大経験値分引く
				m_nExp -= MAX_EXP;
			};
		}
			//次のユニットへうつる
			pNowUnit = pNowUnit->m_pBattleNext;
	}
	
	//戦闘ユニットリストに存在するすべてのユニットを確認する
	//現在確認しているユニット
	pNowUnit = m_pBattleUnit;
	//全ての敵の確認が終わるまでループ
	while(pNowUnit)
	{
		//確認中の敵のHPが0になった
		if(pNowUnit ->GetHP() <= 0)
		{

			//ユニットを削除

			//先頭のバトルユニットを削除する場合、ポインタを変更する
			if(m_pBattleUnit == pNowUnit)
			{
				m_pBattleUnit = pNowUnit ->m_pBattleNext;
			}
			//自身のリストの前に他のユニットが存在している場合、前のユニットのNextUnitを変更する
			if(pNowUnit ->m_pBattleBack)
			{
				pNowUnit ->m_pBattleBack->m_pBattleNext = pNowUnit->m_pBattleNext;
			}

			//自身のリストの後ろにほかのユニットが存在していたら、後ろのユニットのBackUnitを変更する
			if(pNowUnit ->m_pBattleNext)
			{
				pNowUnit->m_pBattleNext->m_pBattleBack = pNowUnit ->m_pBattleBack;
			}

			//次のユニットポインタ
			CUnit* Next = pNowUnit->m_pBattleNext;

			//ユニットを削除
			pNowUnit ->Delete();

			//一度初期化
			pNowUnit = NULL;

			//次のユニットへポインタを移動
			pNowUnit = Next;

		}
		else
		{
			//次のユニットへ
			pNowUnit = pNowUnit->m_pBattleNext;
		}
	}
	
	//ステートを進める
	CTurn::BattleState_Advance(BATTLE_STATE_END);
	//ステートリセット
	CTurn::TimeStateReset();
}
//---------------------------------------------------------------------------------------
//バトルステート初期化、自身のターンステート更新
//---------------------------------------------------------------------------------------
void CUnit::BattleEnd()
{
	//アタックステートに存在するユニットの数-1
	CTurn::SumCount(m_nStateNumber);

	//ステートの遷移(ターンの終了)
	if(m_uID == ID_PLAYER)
		m_nStateNumber = GAME_STATE_STAND_BY_PLAYER;
	else
		m_nStateNumber = GAME_STATE_STAND_BY_OTHER;


	//入力待ちステートに存在するユニットの数+1
	CTurn::AddCount(m_nStateNumber);

	//ステートリセット
	CTurn::TimeStateReset();

	//ステートを計算へ
	CTurn::BattleState_Advance(BATTLE_STATE_GO);
	
	//戦闘を行った敵の初期化
	//現在みているユニット
	CUnit* pNowUnit = m_pBattleUnit;
	while(pNowUnit)
	{
		//ユニットを削除
		//自身のリストの前に他のユニットが存在している場合、前のユニットのNextUnitを変更する
		if(pNowUnit ->m_pBattleBack)
		{
			pNowUnit ->m_pBattleBack->m_pBattleNext = pNowUnit->m_pBattleNext;
		}

		//自身のリストの後ろにほかのユニットが存在していたら、後ろのユニットのBackUnitを変更する
		if(pNowUnit ->m_pBattleNext)
		{
			pNowUnit->m_pBattleNext->m_pBattleBack = pNowUnit ->m_pBattleBack;
		}

		//もし削除するユニットのデータが、先頭のポインタの場合、先頭ポインタを入れ替える
		if(pNowUnit == m_pBattleUnit)
		{
			m_pBattleUnit = m_pBattleUnit ->m_pBattleNext;
		}

		//次のユニットポインタ
		CUnit* Next = pNowUnit->m_pBattleNext;

		//ユニットポインタを解放
		pNowUnit = NULL;

		//次のユニットへポインタを移動
		pNowUnit = Next;
	}

	//攻撃したユニットのポインタを初期化
	m_pBattleUnit = NULL;

	//攻撃しているユニット番号初期化
	m_nAttackNumber = 0;

	//技番号の初期化
	m_nTrickNumber = TRICK_NAME_MAX + 1;
}

//---------------------------------------------------------------------------------------
//状態を変更させる
//---------------------------------------------------------------------------------------
void CUnit::SetStateAbnormal(int nStateNum)
{
	//引数として渡された状態異常を自身の状態異常にセット
	m_nState = nStateNum;
	//セットされた状態異常から、継続時間を設定
	//怯みかどうかで継続時間数を判別
	if(m_nState == UNIT_STATE_WINCE)
		//怯みの場合、1ターンのみ
		m_nState_Turn = STATE_TURN_WINCE;
	else
		//その他の場合、5ターンの継続時間とする
		m_nState_Turn = STATE_TURN_DEFINE;

	//状態異常になったメッセージ
	TCHAR	str[256];
	switch(nStateNum)
	{
	case UNIT_STATE_POISON:
		//メッセージ表記
		_stprintf_s(str, _T("毒状態になった!"));
		//メッセージ出力
		MessageWindow::SetMassege( _T("毒状態になった!"));
		break;
	case UNIT_STATE_PARALYSIS:
		//メッセージ表記
		_stprintf_s(str, _T("麻痺状態になった!"));
		//メッセージ出力
		MessageWindow::SetMassege( _T("麻痺状態になった!"));
		break;
	case UNIT_STATE_CONFUSION:
		//メッセージ表記
		_stprintf_s(str, _T("混乱した!"));
		//メッセージ出力
		MessageWindow::SetMassege( _T("混乱した!"));
		break;
	case UNIT_STATE_SLEEP:
		//メッセージ表記
		_stprintf_s(str, _T("眠ってしまった!"));
		//メッセージ出力
		MessageWindow::SetMassege( _T("眠ってしまった!"));
		break;
	case UNIT_STATE_WINCE:
		//メッセージ表記
		_stprintf_s(str, _T("ひるんでいる!"));
		//メッセージ出力
		MessageWindow::SetMassege( _T("ひるんでいる!"));
		break;
	default:
		//メッセージ表記
		_stprintf_s(str, _T("バグった!"));
		//メッセージ出力
		MessageWindow::SetMassege( _T("バグった!"));
		break;
	}
}

//---------------------------------------------------------------------------------------
//ターン初めの状態異常の処理を行う
//---------------------------------------------------------------------------------------
void CUnit::TurnStartStateProcessing()
{

	//メッセージ表記
	TCHAR	str[256];
	//現在の状態異常で処理を分岐
	switch(m_nState)
	{
		//毒状態の処理
	case UNIT_STATE_POISON:
		//HPに5のダメージ
		DamegeHP(5);

		//画面に描画してもらうHPの数値を渡す
		CHPDraw::SetHP(m_nHP);
		//メッセージ格納
		_stprintf_s(str, _T("毒で%sに%dのダメージ"),m_szName,PoisonDamage);

		//メッセージ出力
		MessageWindow::SetMassege(str);
		break;

		//麻痺状態の場合
	case UNIT_STATE_PARALYSIS:
		//25%の確率で行動不能にする
		if(rand()%4)
		{
			//メッセージ格納
			_stprintf_s(str, _T("%sは痺れて動けない"),m_szName);
			
			//メッセージ出力
			MessageWindow::SetMassege(str);

			//入力待ちに存在するユニットの数-1
			CTurn::SumCount(m_nStateNumber);

			//自身のステートの設定
			m_nStateNumber = GAME_STATE_TURN_END;

			//ターン終了に存在するユニットの数+1
			CTurn::AddCount(m_nStateNumber);
		}
		break;

		//睡眠状態の場合
	case UNIT_STATE_SLEEP:
		//メッセージ格納
		_stprintf_s(str, _T("%sは眠っている"),m_szName);
		
		//メッセージ出力
		MessageWindow::SetMassege(str);

		//入力待ちに存在するユニットの数-1
		CTurn::SumCount(m_nStateNumber);

		//自身のステートの設定
		m_nStateNumber = GAME_STATE_TURN_END;

		//ターン終了に存在するユニットの数+1
		CTurn::AddCount(m_nStateNumber);
		break;

		//怯み状態の場合
	case UNIT_STATE_WINCE:
		//メッセージ格納
		_stprintf_s(str, _T("%sはひるんでいる!"),m_szName);
		
		//メッセージ出力
		MessageWindow::SetMassege(str);

		//入力待ちに存在するユニットの数-1
		CTurn::SumCount(m_nStateNumber);

		//自身のステートの設定
		m_nStateNumber = GAME_STATE_TURN_END;

		//ターン終了に存在するユニットの数+1
		CTurn::AddCount(m_nStateNumber);
		break;
	}
	
	//経過時間を減らす
	m_nState_Turn --;

	//もし継続時間が0になったら、状態以上を健康状態へ遷移させる
	if(m_nState_Turn == 0)
	{
		//メッセージ出力
		MessageWindow::SetMassege(_T("状態が元に戻った!"));

		m_nState = UNIT_STATE_HEALTH;
	}
}
//---------------------------------------------------------------------------------------
//自身の装備しているアイテムの攻撃力合計値を渡す
//---------------------------------------------------------------------------------------
int CUnit::GetEquipmentAttackNum()
{
	return m_pEquipment->GetAttackTotalValue();
}
//---------------------------------------------------------------------------------------
//自身の装備しているアイテムの防御力合計値を渡す
//---------------------------------------------------------------------------------------
int CUnit::GetEquipmentDefenceNum()
{
	return m_pEquipment ->GetDefenceTotalValue();
}

//---------------------------------------------------------------------------------------
//足元のアイテムの確認
//---------------------------------------------------------------------------------------
void CUnit::ChackFeetItem()
{
	//足元のアイテムの情報を取得
	int ItemSearch = CMapData::Get_ItemMapSituation(m_nUnit_Pos_X,m_nUnit_Pos_Z);
													
	//足元のアイテムの検索
	if(ItemSearch != 0)
	{
		m_pFootItem =  (CFieldItem*)ItemFind(ItemSearch);
	
		//インベントリに拾ったアイテムを追加
		if(m_pInventory->SetItem(m_pFootItem->GetItemData()))
		{
			//メッセージ表記
			TCHAR	str[256];
			_stprintf_s(str, _T("%sはアイテムを拾った"),m_szName);
	
			//メッセージテスト
			MessageWindow::SetMassege(str);
	
			//マップ上から現在の位置のアイテム反応消去
			CMapData::Back_ItemMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);
	
			//拾ったアイテムは削除
			m_pFootItem->Delete();
		}
		else 
		{
			//メッセージ描画
			MessageWindow::SetMassege(_T("アイテムを拾えなかった!"));
		}
	}
}

//---------------------------------------------------------------------------------------
//ユニット全ての行動可能フラグを変更する
//---------------------------------------------------------------------------------------
void CUnit::ChangeMoveCanFlg(bool ChangeFlg)
{
	m_bMoveCanFlg = ChangeFlg;
}