#pragma once

#include "MeshObj.h"
#include "UnitManager.h"

class CGameScene;
class CMapObjManager;
class CMapData;

class CFieldObj :
	public CMeshObj
{
private:
	int m_ObjNumber;				//�I�u�W�F�N�g����ӂɒ�߂�ԍ�
	bool m_bNearUnitFlg;			//���g�̔z���ł̏�Ƀ��j�b�g�����݂��邩

	bool m_bDrawFlg;				//�`��t���O

	CMapObjManager* m_pMapObjManager;	//���g�̃}�l�[�W���[
	CUnitManager*	m_pUnitManager;		//���j�b�g�}�l�[�W���[
	CMapData*		m_pMapData;

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