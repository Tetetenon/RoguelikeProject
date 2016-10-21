#include "HitObj.h"
#include "ModelManager.h"
#include "GameScene.h"


//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CHitObj::CHitObj(CGameScene *pScene):
CEffectObj(pScene)
{
	//�g�p���郂�f���̔ԍ���ݒ�
	m_nMeshNumber = MODEL_HIT;
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CHitObj::~CHitObj(void)
{
}
//---------------------------------------------------------------------------------------
//����
//---------------------------------------------------------------------------------------
void CHitObj::Generation(CMeshObj *pGenerator)
{
	//�Ăяo������̃|�C���^�����݂���
	if(!pGenerator)
		return;

	//���ŃI�u�W�F�N�g��ǉ�����
	CHitObj* pEffect = new CHitObj(pGenerator -> GetScene());

	//���b�V���̐ݒ�
	pEffect ->SetMesh(CModelManager::GetMesh(pEffect -> m_nMeshNumber));

	//�������Ԃ�ݒ�
	pEffect ->m_nLifeTime = OBJ_LIFE;

	//���[���h�}�g���b�N�X���烍�[�J�����𒊏o���A���W�𒊏o
	D3DXMATRIX world = pGenerator ->GetWorld();

	//���g�̃��[���h�}�g���b�N�X��ݒ�
	pEffect -> SetWorld(world);
}