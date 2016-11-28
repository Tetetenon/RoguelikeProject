#pragma once
#include "C2DTexture.h"
#include "Item.h"

#define DESCRIPTION_FONT_MAX	(100)

class CItemDescriptionFrame :
	public C2DTexture
{
private:
	LPD3DXFONT		m_Font;						//説明文描画用フォント
	RECT			m_FontPosition;				//説明用フォント位置
	_TCHAR			m_Description[ITEM_MAX][DESCRIPTION_FONT_MAX];	//説明文
public:
	CItemDescriptionFrame(void);		//コンストラクタ
	~CItemDescriptionFrame(void);		//デストラクタ

	void Init(void);					//初期化

	void Draw(int ItemNumber);			//描画

	void SetVertex(void);				//ポリゴン情報の設定
	void SetFontPos(void);				//フォント描画位置設定

	void FontDataSet(void);				//フォントを入力する
};