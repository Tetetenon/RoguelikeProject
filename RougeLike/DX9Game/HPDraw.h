#pragma once

//プレイヤーの情報を描画する

#include "Structure.h"
#include <tchar.h>

class CHPDraw
{
private:
	//シングルトン
	static CHPDraw* m_pHPDraw;

	int					m_nHP;						//描画するユニットの現在のHP

	LPD3DXFONT			m_pFont;					//描画フォントの設定
	RECT					m_FontDrawPos;				//フォントの描画位置を設定する

	char				m_States[256];				//ステータス(HP情報)を格納する

	VERTEX_2D			m_aVertex[NUM_VERTEX];		//テクスチャの描画位置

	int					m_nMaxHP;					//描画するユニットの最大HP

	CHPDraw(void);									//コンストラクタ
	~CHPDraw(void);									//デストラクタ
public:
	static void Create();							//実体の作成
	static void Delete();							//実体の削除
	static CHPDraw* GetPointer();					//自身のポインタの取得

	void Update();									//更新
	void Draw();									//描画処理

	void SetVertex();								//ポリゴン各種情報を設定

	void SetPosition();								//ポリゴンの位置を再設定

	void SetFontPos();								//文字描画位置を設定

	void SetHP (int nHP);							//描画するHP数値をセット

	void SetMaxHP (int nMaxHP);						//描画するHPの最大HPをセット
};

