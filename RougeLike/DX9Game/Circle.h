#pragma once
//ユニットサークルクラス

#include "Structure.h"

class CCircle
{
private:
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;								//頂点バッファインタフェースへのポインタ
	LPDIRECT3DINDEXBUFFER9	m_pD3DIdxBuff;								// インデックスバッファ
	D3DXMATRIX				m_mtxWorld;									//ワールドマトリックス

	int						m_NumVertexIndex;							//インデックス数
	int						m_NumVertex;								//総頂点数
	int						m_NumPolygon;								//ポリゴン数
public:
	CCircle(void);				//コンストラクタ
	~CCircle(void);				//デストラクタ

	void Init();					//初期化
	void Update();					//更新
	void Draw(int UnitNumber);		//描画
	void Fin();						//終了処理

	void SetPos(D3DXVECTOR3 Pos);	//位置情報設定
};

