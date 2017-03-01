#pragma once
//パーティクル
#include "C3DObj.h"

class CCamera;
class CParticleManager;

//パーティクルのパターン
enum ParticlePattern
{
	PARTICLE_PATTERN_DELETE = 0,
	PARTICLE_PATTERN_IMPACT,
	PARTICLE_PATTERN_MAX
};

enum EParticleCoord
{
	eCartesian = 0,				// 直交座標系(x,y,z)
	eSpherical,					// 球座標系(r,φ,θ)
	eCylindrical,				// 円筒座標系(r,h,θ)

	eMaxParticleCoord
};

struct TParticleParam
{
	int				TextureNumber;		//使用するテクスチャ番号
	ESynthetic		synthetic;			// 描画方法
	EParticleCoord	coord;				// 座標系
	float			fDuration;			// 生成周期
	UINT			uMaxParticles;		// 最大パーティクル数
	bool			bLooping;			// 繰り返し
	float			fGravity;			// 重力加速度
	float			fStartSpeed;		// 初速
	float			fStartSpeed2;		// 初速2
	float			fStartSize;			// 初期サイズ
	float			fStartSize2;		// 初期サイズ2
	float			fStartRotation;		// 初期角度
	float			fStartRotation2;	// 初期角度2
	D3DCOLOR		cStartColor;		// 初期カラー
	D3DCOLOR		cStartColor2;		// 初期カラー2
	float			fStartLifetime;		// 寿命
	float			fStartLifetime2;	// 寿命2
	UINT			uRate;				// 1秒あたりのパーティクル生成数
	float			fCornAngle;			// コーン角度
	float			fRadius;			// 半径(180:半球、360:球)
	bool			bColorOverLifetime;	// 生存時間で色を変更(初期カラーが無効になる)
	D3DCOLOR		cOverLifetime[2];	// [0]:開始色、[1]:終了色
	bool			bSizeOverLifetime;	// 生存時間でサイズを変更(初期サイズが無効になる)
	float			fOverLifetime[2];	// [0]:開始サイズ、[1]:終了サイズ
};

class CParticle:
	public C3DObj
{
private:
	CParticleManager* m_pParticlemanager;

	TParticleParam		m_pp;
	float				m_fTime;			// パーティクル生成時間
	float				m_fRate;			// パーティクル生成数ワーク
	UINT				m_uParticles;		// 残りパーティクル数	

	float				m_fLifeTime;		//生存時間

	int					m_nID;				//パーティクル一意の番号
	bool				m_bDeleteFlg;		//削除フラグ
	struct TGrain 
	{
		TGrain*		m_pBack;
		TGrain*		m_pNext;
		D3DXVECTOR3	m_pos;
		D3DXVECTOR3	m_startPos;
		D3DXVECTOR3	m_velocity;
		D3DXVECTOR3	m_accel;
		float		m_size;
		float		m_startSize;
		float		m_angle;
		D3DCOLOR	m_color;
		D3DCOLOR	m_startColor;
		float		m_lifetime;
		float		m_startLifetime;
	};

	TGrain*		m_pGrain;
	TGrain*		m_pUse;
	TGrain*		m_pUnused;
	UINT		m_uUse;

	struct TVertex 
	{
		D3DVECTOR	m_pos;
		D3DVECTOR	m_normal;
		D3DCOLOR	m_diffuse;
		float		m_u, m_v;
	};

	TVertex*	m_pVertex;
	WORD*		m_pIndex;
public:
	CParticle(CGameScene* pScene);							//コンストラクタ
	CParticle(CGameScene* pScene, TParticleParam* ppp);		//コンストラクタ
	virtual ~CParticle(void);							//デストラクタ

	virtual void PostInit(void);						//初期化後の処理
	void Delete(TGrain* p);								//削除
	TGrain* New(void);									//生成
	virtual void Update(void);							//更新
	virtual void Draw(void);							//描画
	virtual void DrawAlpha(void);						//半透明描画
	virtual void Fin(void);								//終了処理
	void DrawLast(void);								
	void SetParam(TParticleParam& pp);					//パラメーター設定
	void GetDefaultParam(TParticleParam& pp);			//デフォルトパラメーター設定

	static void Generation(C3DObj* pGenetator,int Pattern);		//自身の生成

	void SetParmData_Delete(D3DXMATRIX world);					//パラメーターデータを設定する（消滅）
	
	//削除フラグの状態を取得
	bool GetDeleteFlg() { return m_bDeleteFlg; }
};