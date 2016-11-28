#pragma once

//現在の階層数を表示する
#include "C2DTexture.h"

//階層表示に使用するポリゴン数
#define HIERARCHIENUM (3)

class CHierarchieNum :
	public C2DTexture
{
private:
	//ポリゴン情報
	static VERTEX_2D	m_aVertex[HIERARCHIENUM][NUM_VERTEX];
public:
	CHierarchieNum(void);	//コンストラクタ
	~CHierarchieNum(void);	//デストラクタ

	void Draw();		//描画
	void SetVertex();	//ポリゴン情報の設定
};

