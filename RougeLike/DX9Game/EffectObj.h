#pragma once

//3D�G�t�F�N�g���Ǘ�����N���X
#include "MeshObj.h"

#define OBJ_LIFE 30	//�I�u�W�F�N�g�̐�������

//�N���X��`
class CGameScene;

class CEffectObj :
	public CMeshObj
{
protected:
	int m_nLifeTime;	//��������
public:
	CEffectObj(CGameScene *pScene);				//�R���X�g���N�^
	~CEffectObj(void);								//�f�X�g���N�^

	void Update();									//�X�V
	void Fin();										//�I������
};

