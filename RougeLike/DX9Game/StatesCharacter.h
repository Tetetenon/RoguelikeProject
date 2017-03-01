#pragma once

#include "C2DTexture.h"

class CStatesCharacter :
	public C2DTexture
{
private:
	//シングルトン
	static CStatesCharacter* m_pStatesCharacter;

	CStatesCharacter(void);		//コンストラクタ
	~CStatesCharacter(void);		//デストラクタ
public:
	static void Create();					//実体作成
	static void Delete();					//実体削除
	static CStatesCharacter* GetPointer();	//実体のポインタを渡す

	void ChangeTexture(int nPlayerState);		//使用するテクスチャの交換
};

