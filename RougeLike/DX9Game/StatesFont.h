#pragma once

//ステータス画面の項目を描画する

#include "C2DTexture.h"
#include "StatesDefine.h"

class CStatesFont :
	public C2DTexture
{
private:
	//シングルトン
	static CStatesFont* m_pStatesFont;
	//使用テクスチャ番号格納用
	int			m_nTextureNumber[STATES_FONT_MAX];		
	//ポリゴン情報格納用
	VERTEX_2D	m_aVertex[STATES_FONT_MAX][NUM_VERTEX];

	CStatesFont(void);		//コンストラクタ
	~CStatesFont(void);		//デストラクタ
public:
	static void Create();				//実体の作成
	static void Delete();				//実体の削除
	static CStatesFont* GetPointer();	//実体のポインターを渡す
	void Draw();			//描画

	void SetVertex ();		//ポリゴン情報の設定
};