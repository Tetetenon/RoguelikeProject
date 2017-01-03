#include "FieldObj.h"
#include "MapData.h"

#include "ModelManager.h"
#include "GameScene.h"
#include"MapObjManager.h"
int CFieldObj::m_nMakeNum_Debug = 0;
//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CFieldObj::CFieldObj(CGameScene* Scene):
CMeshObj(Scene)
{
	//ID�̐ݒ�
	m_uID = ID_MESHOOBJ;

	//���g�̔ԍ��̐ݒ�
	m_ObjNumber = CMapObjManager::GetNextNumber();
	//���̔ԍ���ݒ�
	CMapObjManager::SetNextNumber(m_ObjNumber + 1);

	//�I�u�W�F�N�g�����X�g�ɒǉ�
	CMapObjManager::Add(m_ObjNumber,this);
	m_nMakeNum_Debug++;
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CFieldObj::~CFieldObj(void)
{
	m_nMakeNum_Debug--;
	if (m_nMakeNum_Debug == 0)
	{
		int a = 0;
	}
}


//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CFieldObj::Update()
{
}
//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CFieldObj::Draw()
{
	m_pMesh->MaterialNoAlpha();
	CMeshObj::Draw();
}
//---------------------------------------------------------------------------------------
//�������`��
//---------------------------------------------------------------------------------------
void CFieldObj::DrawAlpha()
{
	m_pMesh->MaterialAlpha();
	CMeshObj::DrawAlpha();
}

//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void CFieldObj::Fin()
{
	CMeshObj::Fin();
}
//---------------------------------------------------------------------------------------
//�I�u�W�F�N�g�̐���
//---------------------------------------------------------------------------------------
void CFieldObj::SetObject(CMeshObj *pSetter,int SetNumber,int PosX,int PosY)
{
	//�Ăяo��������̃|�C���^������
	if(!pSetter)
		return;

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