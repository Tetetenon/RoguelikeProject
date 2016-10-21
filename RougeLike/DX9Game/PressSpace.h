#pragma once
//プレススペース

#include "C2DTexture.h"

class CPressSpace :
	public C2DTexture
{
private:
	bool	m_bAlphaSwitch;	//透過加算スイッチ
	int		m_nFlashTimer;	//点滅時間
public:
	CPressSpace(void);		//コンストラクタ
	~CPressSpace(void);		//デストラクタ
	void Update();			//更新
};

