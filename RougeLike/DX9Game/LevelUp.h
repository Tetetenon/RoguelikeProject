#pragma once
#include "C2DTexture.h"

#define POLYGON_SIZE_X 2.0f	//ポリゴンのサイズX
#define POLYGON_SIZE_Y 2.0f	//ポリゴンのサイズY
#define POLYGON_SIZE_Z 2.0f	//ポリゴンのサイズZ

class CLevelUp :
	public C2DTexture
{
private:
	D3DXMATRIX				m_mtxWorld;			// ワールドマトリックス
	D3DXVECTOR3				m_Pos;				//位置情報
	D3DXVECTOR3				m_Scl;				// スケール
	LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuff;		//頂点バッファインターフェースへのポインタ

	int						m_UpPos;			//上方向上昇値を格納
public:
	CLevelUp(D3DXVECTOR3 Pos);			//コンストラクタ
	~CLevelUp(void);					//デストラクタ

	void Update(D3DXVECTOR3 Pos);			//更新
	void Draw();			//描画処理

	void SetVertex();		//頂点情報の設定
	HRESULT MakeVertex();		//頂点情報の作成

	int GetUpPos(){return m_UpPos;}	//現在の上昇値の取得
};

