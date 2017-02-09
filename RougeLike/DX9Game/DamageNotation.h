#pragma once
#include "C2DTexture.h"

//クラスの定義
class  CDamageBillBoardManager;

//ダメージの数値を表示するクラス
#define POLYGON_SIZE_X 1.0f
#define POLYGON_SIZE_Y 3.0f
#define POLYGON_SIZE_Z 3.0f

//表示する桁数
#define DrawDigit 3

//生存時間
#define LifeTime 60

//ポリゴン用構造体
struct PolygonData
{
	D3DXMATRIX				m_mtxWorld;			// ワールドマトリックス
	D3DXVECTOR3				m_Pos;				//位置情報
	D3DXVECTOR3				m_Scl;				// スケール
	LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuff;		//頂点バッファインターフェースへのポインタ
	int						m_nTextureNumber;	//使用するテクスチャ番号
	bool					m_bDrawFlg;			//描画するか、しないか
};

//移動限界値
const float MoveRimit_X = 5;
const float MoveRimit_Y = 5;
const float MoveRimit_Z = 5;

//移動方向
const float MoveVecX = 0.0f;
const float MoveVecY = 0.01f;
const float MoveVecZ = 0.0f;

class CDamageNotation :
	public C2DTexture
{
private:
	PolygonData m_NumPolygon[DrawDigit];	//表示するポリゴンデータ
	D3DXVECTOR3 m_MoveVector;				//移動方向
	D3DXVECTOR3 m_AmountMovement;			//移動量
	int			m_nAlpha;					//透明度

	CDamageBillBoardManager* m_pManager;	//マネージャーのポインタ
	float		m_LifeTime;					//生存時間
	int			m_nID;						//固有ID
public:
	CDamageNotation(int Damage,D3DXVECTOR3 Pos);		//コンストラクタ
	~CDamageNotation();					//デストラクタ

	void Update();						//更新
	void Draw();						//描画

	float GetLifeTime()
	{
		return m_LifeTime;
	}

	HRESULT MakeVertex();				//頂点情報の作成


};

