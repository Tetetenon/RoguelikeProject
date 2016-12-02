#pragma once
//テクスチャ描画クラス

#include "Structure.h"

class C2DTexture
{
protected:
	VERTEX_2D		m_aVertex[NUM_VERTEX];		//ポリゴン情報格納
	int				m_nTextureID;				//使用するテクスチャID
public:
	C2DTexture(void);							//コンストラクタ
	~C2DTexture(void);							//デストラクタ

	virtual void Draw();						//描画

	void SetVertex();							//ポリゴン情報を設定する

	void SetPos(float fPosX,float fPosY,float fHalfSizeX,float fHalfSizeY);	//ポリゴンの位置情報を設定する
	void SetPosLeftUpOrigin(float fPosX, float fPosY, float fWidth, float fHeight);
	void SetTextureID(int nID)	{m_nTextureID = nID;}				//テクスチャIDを設定する
	void SetAlpha(int nAlpha);												//ポリゴンのアルファ値を設定する
};

