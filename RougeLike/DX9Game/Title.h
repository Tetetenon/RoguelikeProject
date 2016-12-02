#pragma once
//タイトル描画クラス

#include "C2DTexture.h"
#include "Structure.h"

class CEditTexture;

class CTitle:
	public C2DTexture
{
public:
	CTitle(void);		//コンストラクタ
	~CTitle(void);		//デストラクタ
	//void Draw() override;

//private:
//	CEditTexture* m_pEditTexture;
};

