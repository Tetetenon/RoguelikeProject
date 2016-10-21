#pragma once

#include"C3DObj.h"
#include "Player.h"

enum ECamPos
{
	CP_FIXED = 0,	//固定
	CP_FPVIEW,		//1人称
	CP_TPVIEW,		//3人称
	MAX_VIEW
};

class CSky;

class CCamera:public C3DObj 
{
private:
	D3DXMATRIX m_proj;	//プロジェクションマトリックス
	static D3DXMATRIX m_view;	//ビューマトリックス
	CSky*		m_pSky;		// スカイドーム
	CPlayer*	m_pPlayer;	//自機

	ECamPos		m_cp;	//カメラ種別
	
	D3DXVECTOR3 m_at;	//注視点
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_Up;	//上方向ベクトル

	D3DXVECTOR3 m_at2;	//注視点
	D3DXVECTOR3 m_pos2;
	D3DXVECTOR3 m_Up2;	//上方向ベクトル

	float m_fFovy;		//視野角
	float m_fAspect;	//アスペクト比
	float m_fZNear;		//前方クリップ
	float m_fZFar;		//後方クリップ

	float m_nTimer;		//経過時間を図る
	bool  m_bSwitch;	//画面切り替えフラグ
public:
	CCamera(CGameScene* pScene);
	virtual ~CCamera(void);

	virtual void Init ();	//初期化
	virtual void Update();	//更新
	virtual void Draw();	//描画
	virtual void DrawAlpha();	//描画
	virtual void Fin();		//終了処理

	void PostUpdate();		//更新後処理
	void PreDraw();			//描画後処理

	//ビューマトリクスの取得
	static D3DXMATRIX GetMtxView()	{return m_view;}
};

