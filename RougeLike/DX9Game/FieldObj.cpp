#include "FieldObj.h"
#include "MapData.h"

#include "ModelManager.h"
#include "GameScene.h"
#include"MapObjManager.h"
//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CFieldObj::CFieldObj(CGameScene* Scene):
CMeshObj(Scene)
{
	//�|�C���^���擾
	m_pMapObjManager = CMapObjManager::GetPointer();
	m_pMapData = CMapData::GetPointer();

	//ID�̐ݒ�
	m_uID = ID_MESHOOBJ;

	//���g�̔ԍ��̐ݒ�
	m_ObjNumber = m_pMapObjManager->GetNextNumber();
	//���̔ԍ���ݒ�
	m_pMapObjManager->SetNextNumber(m_ObjNumber + 1);

	//�I�u�W�F�N�g�����X�g�ɒǉ�
	m_pMapObjManager->Add(m_ObjNumber,this);
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CFieldObj::~CFieldObj(void)
{
}


//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CFieldObj::Update()
{
	//�}�b�v��ň�ԏ�̃I�u�W�F�N�g�̏ꍇ�A��Ƀ��j�b�g�����邩�m�F����K�v���Ȃ����߁A�X���\
	if (m_nUnit_Pos_Z <= 0)
		return;

	//���g�̏�Ƀ��j�b�g�����݂��邩�ǂ������m�F����
	if ((0 != m_pMapData->Get_UnitMapSituation(m_nUnit_Pos_X,m_nUnit_Pos_Z - 1)) || (0 != m_pMapData->Get_ItemMapSituation(m_nUnit_Pos_X, m_nUnit_Pos_Z - 1)))
	{
		//���j�b�g�����݂���ꍇ�A�t���O�𗧂ĂāA�������`��ɐ؂�ւ���
		m_bNearUnitFlg = true;
	}
	else
	{
		//���݂��Ȃ��ꍇ�A�s�����`��ɂ���
		m_bNearUnitFlg = false;
	}
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

	//���g�̃}�b�v�z���ł̈ʒu��ݒ肷��
	pFieldObj->m_nUnit_Pos_X = PosX;
	pFieldObj->m_nUnit_Pos_Z = PosY;

	//���g�̏�ɃI�u�W�F�N�g�����݂��邩�̃t���O������������
	pFieldObj->m_bNearUnitFlg = false;

	//�ʒu����ݒ�
	world._41 = (PosX - (MAP_SIZE / 2)) * GRIDSIZE + GRIDSIZE / 2;
	world._42 = 0.0f;
	world._43 = -((PosY) - (MAP_SIZE / 2)) * GRIDSIZE - GRIDSIZE / 2;

	//���[���h�}�g���b�N�X��ݒ�
	pFieldObj ->SetWorld(world);
}