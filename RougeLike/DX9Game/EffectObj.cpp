#include "EffectObj.h"
#include "ModelManager.h"
#include "GameScene.h"


//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CEffectObj::CEffectObj(CGameScene *pScene):
CMeshObj(pScene),
m_nLifeTime(OBJ_LIFE)
{
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

	//�����A�������Ԃ������Ȃ�΁A
	if(m_nLifeTime <= 0)
	{
		//���g�̍폜
		delete this;

		return;
	}

	//�e�֐��̍X�V
	CMeshObj::Update();
}
//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void CEffectObj::Fin()
{
	//�e�̍X�V
	CMeshObj::Fin();

	//���g�̍폜
	delete this;
}