//メッシュオブジェクト定義
#pragma once
#include "Mesh.h"
#include "C3DObj.h"

class CMeshObj :
	public C3DObj
{
protected:
	CMesh*	m_pMesh;				//メッシュデータポインタ
	int		m_nMeshNumber;			//使用するメッシュデータの番号
public:
	CMeshObj(CGameScene* pScene);
	CMeshObj();
	virtual ~CMeshObj(void);

	virtual void Init();	//初期化
	virtual void Fin();		//終了処理
	virtual void Update();	//更新
	virtual void Draw();	//描画処理
	virtual void DrawAlpha();	//描画処理

	void SetMesh (CMesh *pMesh){m_pMesh = pMesh;}
	CMesh* GetMesh(){return m_pMesh;}
	
	DWORD GetPieceCount();
	void GetInitPiece(PIECE* pPiece);
};

