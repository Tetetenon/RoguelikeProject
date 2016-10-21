#include "DeleteObj.h"
#include "ModelManager.h"
#include "GameScene.h"

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CDeleteObj::CDeleteObj(CGameScene *pScene):
CEffectObj(pScene)
{
	//�g�p���郂�f���̔ԍ���ݒ�
	m_nMeshNumber = MODEL_DELETE;
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CDeleteObj::~CDeleteObj(void)
{
}
//---------------------------------------------------------------------------------------
//����
//---------------------------------------------------------------------------------------
void CDeleteObj::Generation(CMeshObj *pGenerator)
{
	//�Ăяo������̃|�C���^�����݂���
	if(!pGenerator)
		return;

	//���ŃI�u�W�F�N�g��ǉ�����
	CDeleteObj* pEffect = new CDeleteObj(pGenerator -> GetScene());

	//���b�V���̐ݒ�
	pEffect ->SetMesh(CModelManager::GetMesh(pEffect -> m_nMeshNumber));

	//�������Ԃ�ݒ�
	pEffect ->m_nLifeTime = OBJ_LIFE;

	//���[���h�}�g���b�N�X���烍�[�J�����𒊏o���A���W�𒊏o
	D3DXMATRIX world = pGenerator ->GetWorld();

	//���g�̃��[���h�}�g���b�N�X��ݒ�
	pEffect -> SetWorld(world);
}