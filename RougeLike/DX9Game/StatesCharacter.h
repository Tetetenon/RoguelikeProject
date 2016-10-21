#pragma once

#include "C2DTexture.h"

class CStatesCharacter :
	public C2DTexture
{
public:
	CStatesCharacter(void);		//コンストラクタ
	~CStatesCharacter(void);		//デストラクタ

	void Update(int nPlayerState);				//テクスチャデータの更新
};

