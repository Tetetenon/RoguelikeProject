#pragma once

#include "MeshObj.h"
#include "Unit.h"

class CGameScene;
class CFieldObj :
	public CMeshObj
{
private:
	static CMeshObj*	m_pPlayer;	//�v���C���[�̈ʒu���擾�p
	static bool m_bDeleteObj;		//�S�t�B�[���h�I�u�W�F�폜�t���O
	static int	m_Counter;			//�������	
public:
	CFieldObj(CGameScene* pScene);		//�R���X�g���N�^
	virtual ~CFieldObj(void);		//�f�X�g���N�^

	void Draw();					//�`��
	void DrawAlpha();				//�`��(������)
	void Update();					//�X�V(�폜�t���O�̊m�F�p)
	void Fin();						//�I������

	//�t�B�[���h��ɃI�u�W�F�N�g��ݒu����
	static void SetObject(CMeshObj *pSetter,int nSetNumber,int PosX,int PosY);

	//�폜�t���O���グ��
	static void DeleteObjFlgUp(){m_bDeleteObj = true;}

	//�폜�t���O��������
	static void DeleteObjFlgDown(){m_bDeleteObj = false;}
};

