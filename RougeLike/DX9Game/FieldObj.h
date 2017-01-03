#pragma once

#include "MeshObj.h"
#include "Unit.h"

class CGameScene;
class CFieldObj :
	public CMeshObj
{
private:
	int m_ObjNumber;				//�I�u�W�F�N�g����ӂɒ�߂�ԍ�
	static int m_nMakeNum_Debug;		
public:
	CFieldObj(CGameScene* pScene);		//�R���X�g���N�^
	virtual ~CFieldObj(void);		//�f�X�g���N�^

	void Draw();					//�`��
	void DrawAlpha();				//�`��(������)
	void Update();					//�X�V(�폜�t���O�̊m�F�p)
	void Fin();						//�I������

	//�t�B�[���h��ɃI�u�W�F�N�g��ݒu����
	static void SetObject(CMeshObj *pSetter,int nSetNumber,int PosX,int PosY);
};