#pragma once

//���j�b�g�����ł����Ƃ��̃G�t�F�N�g�N���X
#include "EffectObj.h"

class CGameScene;

class CDeleteObj:
	public CEffectObj
{
public:
	CDeleteObj(CGameScene *pScene);		//�R���X�g���N�^
	~CDeleteObj(void);					//�f�X�g���N�^

	static void Generation(CMeshObj* pGenerator);	//�G�t�F�N�g�̐���
};

