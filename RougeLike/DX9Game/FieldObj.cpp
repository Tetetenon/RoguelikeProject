#include "FieldObj.h"
#include "MapData.h"

#include "ModelManager.h"
#include "GameScene.h"

CMeshObj*	CFieldObj::m_pPlayer = NULL;
bool		CFieldObj::m_bDeleteObj = false;
int			CFieldObj::m_Counter = 0;
//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CFieldObj::CFieldObj(CGameScene* Scene):
CMeshObj(Scene)
{
	//ID�̐ݒ�
	m_uID = ID_MESHOOBJ;
	//�S�I�u�W�F�N�g�폜�t���O��|��
	m_bDeleteObj = false;

	//�v���C���[�ւ̃|�C���^���擾
	m_pPlayer = (CMeshObj*)Find(ID_PLAYER);
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CFieldObj::~CFieldObj(void)
{
	m_Counter = 0;
	m_bDeleteObj = true;

	//�v���C���[�|�C���^���폜
	m_pPlayer = NULL;
}


//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CFieldObj::Update()
{
	//�S�I�u�W�F�N�g�폜�t���O�������Ă����ꍇ�A�폜���s��
	if(m_bDeleteObj)
	{
		Fin();
	}
}
//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CFieldObj::Draw()
{
	//�v���C���[�̋߂��̃��f���́A�������ɂ��ĕ`����s��
	if(m_pPlayer)
	{
		//�v���C���[�̈ʒu���擾����
		D3DXVECTOR3 PlayerPos = m_pPlayer ->GetPos();
		
		//���g�̈ʒu�ƃv���C���[�̈ʒu�̔�r
		float DistanceX = abs(m_world._41 - PlayerPos.x);
		float DistanceZ = m_world._43 - PlayerPos.z;
		
		//���g�̈ʒu�ƁA�v���C���[�̈ʒu���߂���΁A���f���𔼓����̕��ɕύX����
		if(DistanceX <= GRIDSIZE)
		{
			if(DistanceZ < 0 && DistanceZ > - GRIDSIZE * 1.5)
			{
				return;
			}
			else
			{
				m_pMesh->MaterialNoAlpha();
				CMeshObj::Draw();
			}
		}
		else
		{
			m_pMesh->MaterialNoAlpha();
			CMeshObj::Draw();
		}
	}
}
//---------------------------------------------------------------------------------------
//�������`��
//---------------------------------------------------------------------------------------
void CFieldObj::DrawAlpha()
{
	//�v���C���[�̋߂��̃��f���́A�������ɂ��ĕ`����s��
	if(m_pPlayer)
	{
		//�v���C���[�̈ʒu���擾����
		D3DXVECTOR3 PlayerPos = m_pPlayer ->GetPos();
		
		//���g�̈ʒu�ƃv���C���[�̈ʒu�̔�r
		float DistanceX = abs(m_world._41 - PlayerPos.x);
		float DistanceZ = m_world._43 - PlayerPos.z;
		
		//���g�̈ʒu�ƁA�v���C���[�̈ʒu���߂���΁A���f���𔼓����̕��ɕύX����
		if(DistanceX <= GRIDSIZE)
		{
			if(DistanceZ < 0 && DistanceZ > -GRIDSIZE * 2)
			{
				m_pMesh->MaterialAlpha();
				CMeshObj::DrawAlpha();
			}
			else
			{
				return;
			}
		}
		else
		{
			return;
		}
	}
}

//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void CFieldObj::Fin()
{
	CMeshObj::Fin();

	delete this;
}
//---------------------------------------------------------------------------------------
//�I�u�W�F�N�g�̐���
//---------------------------------------------------------------------------------------
void CFieldObj::SetObject(CMeshObj *pSetter,int SetNumber,int PosX,int PosY)
{
	//�Ăяo��������̃|�C���^������
	if(!pSetter)
		return;

	//����������Z
	m_Counter++;

	//�I�u�W�F�N�g��ǉ�
	CFieldObj *pFieldObj = new CFieldObj(pSetter ->GetScene());

	//���b�V���̐ݒ�
	pFieldObj ->SetMesh(CModelManager::GetMesh(SetNumber));

	//���[���h���擾
	D3DXMATRIX world = pSetter->GetWorld();

	//���f���̊p�x��ύX����
	D3DXMatrixRotationY(&world,90.0f);
	
	//���f���̃X�P�[����ύX����
	D3DXMatrixScaling(&world,0.3f,0.3f,0.3f);


	//�ʒu����ݒ�
	world._41 = (PosX - (MAP_SIZE / 2)) * GRIDSIZE + GRIDSIZE / 2;
	world._42 = 0.0f;
	world._43 = -((PosY) - (MAP_SIZE / 2)) * GRIDSIZE - GRIDSIZE / 2;

	//���[���h�}�g���b�N�X��ݒ�
	pFieldObj ->SetWorld(world);
}