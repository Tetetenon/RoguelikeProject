#pragma once

//���j�b�g�ɍU�����q�b�g�����Ƃ��̃G�t�F�N�g�N���X

#include "EffectObj.h"

class CGameScene;

class CHitObj:
	public CEffectObj
{
private:
	static bool		m_bDrawFlg;			//�`��t���O

	static int		m_PosX;				//�I�u�W�F�N�g�̉����ʒu
	static int		m_PosY;				//�I�u�W�F�N�g�̏c���ʒu
public:
	CHitObj(CGameScene *pScene);		//�R���X�g���N�^
	~CHitObj(void);						//�f�X�g���N�^
	static void Generation(CMeshObj* pGenerator);	//����
};

