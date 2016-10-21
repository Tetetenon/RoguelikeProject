#include "FieldItem.h"
#include "GameScene.h"
#include "define.h"
#include "MapData.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "MiniMap.h"

//�ÓI�����o��`
int		CFieldItem::m_MakeItemNum = 1;
bool	CFieldItem::m_Delete = false;

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CFieldItem::CFieldItem(CGameScene *pScene):
CMeshObj(pScene)
{
	m_uID = ID_ITEM;

	//�g�p���郂�f���̔ԍ�
	m_nMeshNumber = MODEL_TREASUREBOX;

	//�V�[���̃|�C���^���擾
	m_pScene = pScene;

	//���X�g�̏�����
	m_pNextFieldItem = m_pBackFieldItem = NULL;

	//�V�[���ɃI�u�W�F�N�g��ǉ�����
	m_pScene -> AddItem(this);
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CFieldItem::~CFieldItem(void)
{
	//�~�j�}�b�v�ォ�玩�g���폜����
	CMiniMap::Delete((int)m_Pos.x,(int)m_Pos.y);
	//�V�[���ォ�玩�g���폜����
	m_pScene ->DelItem(this);
}

//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CFieldItem::Update		()
{
	//�����S�A�C�e���f���[�g�t���O�������Ă�����폜���s��
	if(m_Delete)
		delete this;

	if(!m_ItemDelete)
		delete this;
}
//---------------------------------------------------------------------------------------
//�`�揈��
//---------------------------------------------------------------------------------------
void CFieldItem::Draw	()
{
	//�e�̕`�揈�����s��
	CMeshObj::Draw();
	//�T�[�N���̕`����s��
	m_Circle.Draw(OBJ_NUM_ITEM);
}
//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void CFieldItem::Fin		()
{
	CMeshObj::Fin();
	delete this;
}
//---------------------------------------------------------------------------------------
//���g�̍폜
//---------------------------------------------------------------------------------------
void CFieldItem::Delete		()
{
	m_ItemDelete = false;
	CMeshObj::Fin();
	delete this;
}

//---------------------------------------------------------------------------------------
//�A�C�e���̐���
//---------------------------------------------------------------------------------------
void CFieldItem::Generation(CMeshObj *pGeneration)
{
	//���b�V����񂠂�&�Ăяo���̃|�C���^��񂪂���
	if(!pGeneration)
		return;

	//�A�C�e����ǉ�
	CFieldItem* pFieldItem = new CFieldItem(pGeneration ->GetScene());

	//�A�C�e���̔ԍ���ݒ肷��
	pFieldItem ->m_FieldID = m_MakeItemNum;

	//�A�C�e���̐����J�E���g�����Z
	m_MakeItemNum ++;

	//ID�̐ݒ�
	pFieldItem ->m_Item.SetID(1 + rand()%ITEM_SHIELD);

	//�A�C�e��ID����A���O��ݒ肷��
	pFieldItem ->m_Item.FindName(pFieldItem ->m_Item.GetID());

	//�A�C�e��ID����A�A�C�e���̌��\�̎�ނ�ݒ肷��
	pFieldItem ->m_Item.EffectSetting(pFieldItem ->m_Item.GetID());

	//�A�C�e���̌��\��ݒ肷��
	pFieldItem ->m_Item.SetValue(rand()%10 + 5);

	//���b�V���̐ݒ�
	pFieldItem ->SetMesh(CModelManager::GetMesh(pFieldItem -> m_nMeshNumber));

	//�����t���O
	pFieldItem ->m_ItemDelete = true;


	//-----�ʒu���̐ݒ�-----
	//�A�C�e���̈ʒu���̐ݒ�
	pFieldItem ->m_Pos.x = (float)(rand()%MAP_SIZE);
	pFieldItem ->m_Pos.y = (float)(rand()%MAP_SIZE);

	//�A�C�e���ݒu�\��ꏊ�������̒����K�i�̏�ȊO�A�A�C�e���������Ă��Ȃ�
	while(!CMapData::CheckInTheRoom((int)pFieldItem ->m_Pos.x,(int)pFieldItem ->m_Pos.y)
		|| CMapData::CheckStairs((int)pFieldItem ->m_Pos.x,(int)pFieldItem ->m_Pos.y)
		|| CMapData::Get_ItemMapSituation((int)pFieldItem ->m_Pos.x,(int)pFieldItem ->m_Pos.y) != 0)
	{

		//�A�C�e���̈ʒu���̍Đݒ�
		pFieldItem ->m_Pos.x = (rand()%MAP_SIZE);
		pFieldItem ->m_Pos.y = (rand()%MAP_SIZE);
	}

	//�}�b�v�f�[�^��Ɏ��g�̑��݂�ݒ�
	CMapData::Set_ItemMap((int)pFieldItem ->m_Pos.x,(int)pFieldItem ->m_Pos.y,pFieldItem ->m_FieldID);

	//�~�j�}�b�v��Ɏ��g���Z�b�g
	CMiniMap::SetIcon((int)pFieldItem ->m_Pos.x,(int)pFieldItem ->m_Pos.y,TEXTURE_ORANGE_TEXTURE);
	//���[���h�}�g���b�N�X���烍�[�J�����W���o
	D3DXMATRIX world = pGeneration ->GetWorld();

	//���f���̃X�P�[����ύX����
	D3DXMatrixScaling(&world,0.03f,0.03f,0.03f);
	

	//���ꂼ��̎��̒l���i�[����
	D3DXVECTOR3 vX,vY,vZ,vP;
	
	vX = D3DXVECTOR3(world._11,world._12,world._13);	//vX:X����]
	vY = D3DXVECTOR3(world._21,world._22,world._23);	//vY:Y����]
	vZ = D3DXVECTOR3(world._31,world._32,world._33);	//vZ:Z����]
	vP = D3DXVECTOR3(world._41,world._42,world._43);	//�ʒu���
	
	//��]�s��̍쐬
	D3DXMATRIX rot_X,rot_Y,rot_Z;
	D3DXMatrixRotationAxis(&rot_X,&vX,0);		//&rot_Y��vY��angle.y�̒l���|�����킹���s����i�[����
	D3DXMatrixRotationAxis(&rot_Y,&vY,PI + PI / 2);		//&rot_Z�Ɍ��݂̊p�x(vY)�ɉ�]�x��(angle.y)���������l�̍s����i�[
	D3DXMatrixRotationAxis(&rot_Z,&vZ,0);		//&rot_Z�Ɍ��݂̊p�x(vZ)�ɉ�]�x��(angle.z)���������l�̍s����i�[

	//�v�Z���ʂ̍s������[���h�s��ɔ��f������
	world *= (rot_Z *rot_Y * rot_X);

	//���[���h���W��̈ʒu���̐ݒ�
	world._41 = (pFieldItem ->m_Pos.x - (MAP_SIZE / 2)) * GRIDSIZE + GRIDSIZE / 2;
	world._42 = 0.0f;
	world._43 = -((pFieldItem ->m_Pos.y) - (MAP_SIZE / 2)) * GRIDSIZE - GRIDSIZE / 2;


	//���[���h�}�g���b�N�X��ݒ�
	pFieldItem ->SetWorld(world);

	//�A�C�e���T�[�N���̈ʒu���w��
	pFieldItem ->m_Circle.SetPos(D3DXVECTOR3(world._41,world._42,world._43));
}
//---------------------------------------------------------------------------------------
//�S�A�C�e���̍폜�t���O�𗧂Ă�
//---------------------------------------------------------------------------------------
void	CFieldItem::DeleteAllItem()
{
	m_Delete = true;

	//��������������
	m_MakeItemNum = 0;
}