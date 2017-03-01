#include "EffectObj.h"
#include "ModelManager.h"
#include "GameScene.h"
#include"EffectObjManager.h"

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CEffectObj::CEffectObj(CGameScene *pScene):
CMeshObj(pScene),
m_nLifeTime(OBJ_LIFE)
{
	//�|�C���^���擾
	m_pEffectObjManager = CEffectObjManager::GetPointer();

	//���g�̔ԍ���ݒ�
	m_nEffectID = m_pEffectObjManager->GetEffectNumber();

	//���̃G�t�F�N�g�ԍ��̐ݒ�
	m_pEffectObjManager->SetEffectNumber(m_nEffectID + 1);

	//�}�l�[�W���[�ɒǉ�
	m_pEffectObjManager->Add(m_nEffectID,this);
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CEffectObj::~CEffectObj(void)
{
}

//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CEffectObj::Update()
{
	//�������Ԃ����Z
	m_nLifeTime --;

	//�e�֐��̍X�V
	CMeshObj::Update();
}
//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void CEffectObj::Fin()
{
	//�e�̏I������
	CMeshObj::Fin();
}