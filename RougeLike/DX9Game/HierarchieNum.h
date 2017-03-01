#pragma once

//現在の階層数を表示する
#include "C2DTexture.h"

//階層表示に使用するポリゴン数
#define HIERARCHIENUM (3)

class CMapData;
class CFade;

class CHierarchieNum :
	public C2DTexture
{
private:
	//シングルトン
	static CHierarchieNum* m_pHierarchieNum;
	//ポリゴン情報
	VERTEX_2D	m_aVertex[HIERARCHIENUM][NUM_VERTEX];

	CMapData*	m_pMapData;
	CFade*		m_pFade;

	CHierarchieNum(void);	//コンストラクタ
	~CHierarchieNum(void);	//デストラクタ
public:
	static void Create();					//実体の作成
	static void Delete();					//実体の削除
	static CHierarchieNum* GetPointer();	//実体のポインタを渡す

	//メンバ変数のポインタをセットする
	void SetPointer();

	void Draw();		//描画
	void SetVertex();	//ポリゴン情報の設定
};

