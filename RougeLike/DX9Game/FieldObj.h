#pragma once

#include "MeshObj.h"
#include "Unit.h"

class CGameScene;
class CFieldObj :
	public CMeshObj
{
private:
	int m_ObjNumber;				//�I�u�W�F�N�g����ӂɒ�߂�ԍ�
	bool m_bNearUnitFlg;			//���g�̔z���ł̏�Ƀ��j�b�g�����݂��邩
public:
	CFieldObj(CGameScene* pScene);		//�R���X�g���N�^
	virtual ~CFieldObj(void);		//�f�X�g���N�^

	void Draw();					//�`��
	void DrawAlpha();				//�`��(������)
	void Update();					//�X�V(�폜�t���O�̊m�F�p)
	void Fin();						//�I������

	//���g�̏�Ƀ��j�b�g�����݂��邩
	bool GetNearUnitFlg()
	{
		return m_bNearUnitFlg;
	}

	//�t�B�[���h��ɃI�u�W�F�N�g��ݒu����
	static void SetObject(CMeshObj *pSetter,int nSetNumber,int PosX,int PosY);
};