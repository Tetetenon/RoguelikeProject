//モデルデータの管理
#pragma once

#include "Config.h"

class CModel :
	public CMeshObj
{
private:
	static CMesh m_Mesh[];		//メッシュデータ格納用
	static CPiece m_Piece[];	//破片データ格納用
public:
	CModel();					//コンストラクタ
	~CModel();					//デストラクタ

	void Init ();				//初期化
	void Fin  ();				//終了処理

	CMesh GetModelData();		//メッシュデータの取得
	CPiece GetPieceData();		//破片データの取得
};