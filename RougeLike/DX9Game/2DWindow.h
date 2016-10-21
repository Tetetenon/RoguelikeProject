#pragma once

//メニューウインドウに用いる基底クラス

#include "Structure.h"
class C2DWindow
{
protected:
	//ポリゴン情報格納用変数
	VERTEX_2D m_aVertex[NUM_VERTEX];
public:
	C2DWindow(void);		//コンストラクタ
	~C2DWindow(void);		//デストラクタ

	virtual void Init();			//初期化
	virtual void Fin();				//終了処理

	virtual void Draw();			//描画
	virtual void Update();			//更新

	virtual void SetVertex();		//ポリゴン情報を設定

	virtual void SetPos();			//ポリゴン位置情報を設定
};

