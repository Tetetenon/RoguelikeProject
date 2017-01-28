//ユニットクラスの定義
#pragma once

#include "MeshObj.h"
#include "define.h"
#include "FieldItem.h"
#include "Circle.h"
#include "ItemWindow.h"
#include "EquipmentWindow.h"
#include "TrickWindow.h"
#include "LevelUp.h"
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>

#include"Turn.h"

//行動にかかる時間
#define ACTION_TIME	0.6f

//満腹度最大値
#define MAX_SATIETY	100

//経験値最大値
#define MAX_EXP		100

//装備できる最大数
#define EQUIPMENTMAX 5

//健康状態列挙
enum UNIT_STATE
{
	UNIT_STATE_HEALTH = 0,		//健康そのものである。
	UNIT_STATE_POISON,			//毒
	UNIT_STATE_CONFUSION,		//少し混乱している!
	UNIT_STATE_WINCE,			//ひるみ
	UNIT_STATE_PARALYSIS,		//麻痺
	UNIT_STATE_SLEEP,			//睡眠
	UNIT_STATE_NO_MONEY,		//金欠
	UNIT_STATE_MAX
};

//方向
enum Direction
{
	Forword = 0,
	Right,
	Back,
	Left,
	MaxDirection
};


//八方向の定義
enum Vector8Define
{
	VEC_LEFT_UP = 0,
	VEC_UP,
	VEC_RIGHT_UP,
	VEC_RIGHT,
	VEC_RIGHT_DOWN,
	VEC_DOWN,
	VEC_LEFT_DOWN,
	VEC_LEFT,
	VEC_MAX,
};

//八方向
const int Vector_8[8][2] = 
{
	{-1,-1},							//左上
	{ 0,-1},							//上
	{ 1,-1},							//右上
	{ 1, 0},							//右
	{ 1, 1},							//右下
	{ 0, 1},							//下
	{-1, 1},							//左下
	{-1, 0},							//左
};


//毒ダメージ
#define PoisonDamage 5

//ステータス列挙
enum UNITSTATES
{
	STATES_MAX_HP = 0,
	STATES_HP,			//HP
	STATES_AT,			//攻撃力
	STATES_DF,			//防御力
	STATES_POS_X,		//配列上の位置X
	STATES_POS_Z,		//配列上の位置Y
	STATES_EXP,			//経験値
	STATES_XP,			//倒して得られる経験値
	STATES_MAX
};

//レベルアップで上昇するステータス一覧
enum UNIT_UP_STATES
{
	UPSTATES_MAX_HP = 0,	//HP最大値
	UPSTATES_AT,			//攻撃力
	UPSTATES_DF,			//防御力
	UPSTATES_MAX
};

//状態異常継続時間
#define STATE_TURN_DEFINE 5	//基本的に状態異常の継続時間は5ターン
#define STATE_TURN_WINCE  1 //怯みの継続時間は1ターン

class CGameScene;

class CUnit :
	public CMeshObj
{
protected:
	//-----ユニットステータス-----
	char					m_szName[10];					//名前
	int						m_nID;							//ユニットの種類識別ID
	int						m_nUnitNumber;					//ユニットを一意に定める番号
	static int				m_nMakeNumber;					//ユニットを何体生成したか。
	int						m_nLevel;						//レベル
	int						m_nHP;							//体力
	int						m_nMaxHP;						//体力最大値
	int						m_nAttack;						//攻撃力
	int						m_nDefence;						//防御力
	int						m_nExp;							//経験値蓄積値
	int						m_nXp;							//倒して得られる経験値
	int						m_nMoney;						//お金
	int						m_nSatiety;						//満腹度
	int						m_nTrickNumber;					//今から使用する技の番号

	bool					m_bTurn;						//自身のターン処理が1度でもされたか
	bool					m_bTurnEndFlg;					//自身のターンが終了したか確認する

	//レベルアップ時ステータス上昇値
	int						m_nHPUpNum;						//レベルアップ時HP上昇値
	int						m_nAttackUpNum;					//レベルアップ時攻撃力上昇値
	int						m_nDefenceUpNum;				//レベルアップ時防御力上昇値


	bool					m_bSurvival;					//生存フラグ
	D3DXVECTOR3				m_Pos;							//移動先の位置
	bool					m_bDestination;					//目標地点到達フラグ
	float					m_fTimer;						//キー入力をしてからの時間を測定する
	bool					m_bDirectionFlg[MaxDirection];	//向くべき方向をフラグで管理する
	D3DXVECTOR3				m_Angle;						//向く角度
	float					m_fOldAngle;					//今の角度

	CUnit*					m_pBattleUnit;					//戦闘を行う敵のポインタ
	CUnit*					m_pBattleNext;					//戦闘をおこなうユニットの前のユニットを指す
	CUnit*					m_pBattleBack;					//戦闘をおこなうユニットの後のユニットを指す

	CFieldItem*				m_pFootItem;					//足元のアイテムの情報を格納する

	CTurn::GameState		m_nStateNumber;					//ステート番号
	int						m_nOldStateNumber;				//1フレーム前のステート番号
	CCircle					m_Circle;						//ユニットサークル

	int						m_nState;						//自身の健康状態
	int						m_nState_Turn;					//自身の状態異常の継続時間

	bool					m_bDrawFlg;						//描画フラグ
	int						m_nDrawFlashTime;				//描画点滅時間
	int						m_nFlashNum;					//点滅回数

	bool					m_bJump;						//ジャンプモーション時の上昇フラグ
	float					m_fJumpPos;						//ジャンプ時の位置
	bool					m_bJumpFlg;						//ジャンプの開始フラグ
	int						m_nJumpInterval;				//ジャンプの間隔
	

	//-----インベントリ-----
	CInventory*				m_pInventory;					//アイテムインベントリ
	CEquipmentInventory*	m_pEquipment;					//装備インベントリ

	CTrickWindow*			m_pTrickWindow;					//技

	CLevelUp*				m_pLevelUp;						//レベルアップテクスチャ
public:
	CUnit(CGameScene* pScene);								//コンストラクタ
	~CUnit(void);											//デストラクタ
	
	virtual void Init();									//初期化
	virtual void Fin();										//終了
	void WaitUpdate();										//待機更新
	void TurnUpdate();										//行動更新	
	virtual void Draw();									//描画

	//ステート別更新
	virtual void InputUpdate();		//入力更新
	virtual void MoveUpdate();		//移動更新
	virtual void ActUpdate();		//アクション更新
	virtual void ItemUpdate();		//アイテム使用更新
	
	//描画フラグを反転させる
	void ChangeDrawFlg()	{m_bDrawFlg = !m_bDrawFlg;}
	//描画フラグを立てる
	void UpDrawFlg()	{m_bDrawFlg = true;}

	//点滅時間を加算させる
	void FlashAddTimer()	{m_nDrawFlashTime++;}
	//現在の点滅時間を取得
	int GetFlashTime(){return m_nDrawFlashTime;}

	//点滅回数の加算
	void FlashAddNum()	{m_nFlashNum++;}
	//点滅回数の取得
	int GetFlashNum()	{return m_nFlashNum;}

	//-----戦闘更新関連-----
	bool AttackUpdate();			//攻撃更新分岐

	void BattleGo();				//相手の方向へ突撃させる
	void BattleReturn();			//突撃した相手の位置から自身の本来の位置へ戻る
	void AttackSwitch();			//技の範囲から、攻撃する相手を分岐させる

	void BattleCalculation(CUnit* BattleUnit);		//戦闘で発生するダメージ量の算出を行う

	bool FrontFind();				//正面の敵に攻撃
	bool Side_Right();				//右の敵に攻撃
	bool Side_Left();				//左の敵に攻撃
	bool BackFind();				//後ろの敵に攻撃
	bool SlightRight();				//斜め右の敵に攻撃
	bool SlightLeft();				//斜め左の敵に攻撃
	bool SlightRightBack();			//斜め右後ろの敵に攻撃
	bool SlightLeftBack();			//斜め左後ろの敵に攻撃

	bool Attack(int CorrectionPosX,int CorrectionPosY);	//指定した補正値の場所へ攻撃を行う

	bool FindEnemy(int,int);		//指定した位置に敵がいるか

	void AttackFront();				//正面の敵のみに攻撃を行う
	void AttackWide();				//前方三マスの敵に攻撃を行う
	void AttackAll();				//部屋の敵全てに攻撃を行う

	void BattleHit();				//ヒットエフェクトを発生させる
	void BattleFlasing();			//相手の描画を点滅させる
	void BattleWindow();			//メッセージウインドウにメッセージを送る
	void BattleDamage();			//相手に算出されたダメージを与える
	void BattleEnd();				//戦闘ステートが最後まで行ったので、バトルステート初期化、自身のターンステート更新
	virtual void TurnEndUpdate();	//ターン終了更新

	//-----HP関連-----
	virtual void DamegeHP (int Damage);		//HPを減らす
	void RecoveryHP (int Recovery);	//HPを回復させる
	//-----状態異常関連-----
	//状態を変更させる
	void SetStateAbnormal(int nStateNum);
	//ターン初めの状態異常の処理を行う
	void TurnStartStateProcessing();

	int		GetNumber()						{return m_nUnitNumber;}				//ユニットの番号の取得
	void	Delete();															//HPをチェックし削除を判定	

	//-----ステータスゲッター-----
	//レベルを取得
	int		GetLevel()	{return m_nLevel;}
	//名前を取得
	char*	GetName	(char *pName);
	//HPを取得
	int		GetHP()			{return m_nHP;}
	//攻撃力を取得
	int		GetAT ()		{return m_nAttack;}
	//防御力を取得
	int		GetDF ()		{return m_nDefence;}
	//経験値の取得
	int		GetExp()		{return m_nExp;}
	//非経験値の取得
	int		GetXP()			{return m_nXp;}
	//現在の状態を取得
	int		GetStatesMode()	{return m_nState;}

	//自身の装備しているアイテムの攻撃力合計値を渡す
	int GetEquipmentAttackNum();
	//自身の装備しているアイテムの防御力合計値を渡す
	int GetEquipmentDefenceNum();

	//足元のアイテムの確認
	void ChackFeetItem();

	//ユニットのターンステート情報の取得
	CTurn::GameState GetUnitTurnState();
	//ユニットの処理状況の取得
	bool GetUnitProc();

	//自身のターンが終了したか確認する
	bool GetTurnEndFlg() 
	{
		return m_bTurnEndFlg; 
	}
	//ターン終了状態を変更する
	void setTurnEndFlg(bool ChangeFlg) 
	{
		m_bTurnEndFlg = ChangeFlg; 
	}
};