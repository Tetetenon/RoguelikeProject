#pragma once

#include "MeshObj.h"

class CFieldObjMaker:
	public CMeshObj
{
private:
public:
	CFieldObjMaker(CGameScene* pScene);		//�R���X�g���N�^
	~CFieldObjMaker(void);		//�f�X�g���N�^

	//�t�B�[���h�I�u�W�F�ݒu�֐�
	void PutObj(int SetNumber,int PosX,int PosY);
};

