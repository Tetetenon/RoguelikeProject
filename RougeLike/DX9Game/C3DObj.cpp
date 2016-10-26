//3D�I�u�W�F�N�g�N���X����
#include "C3DObj.h"
#include "GameScene.h"

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
C3DObj::C3DObj(CGameScene* pScene):
	m_uID(ID_3DOBJ)
{
	//���[���h���W�̏�����
	D3DXMatrixIdentity(&m_world);

	//�V�[���N���X�̃|�C���^���擾
	m_pScene = pScene;

	//���X�g�f�[�^�̏�����
	m_pNext = m_pBack = NULL;

	//�V�[���ɃI�u�W�F�N�g��ǉ�����
	//this�|�C���^:�������g��\��
	m_pScene -> Add(this);
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
C3DObj::~C3DObj(void)
{
	//�V�[���I�u�W�F�N�g�̍폜
	m_pScene ->Del(this);
}

//---------------------------------------------------------------------------------------
//������
//---------------------------------------------------------------------------------------
void C3DObj::Init()
{
}
//---------------------------------------------------------------------------------------
// �������㏈��
//---------------------------------------------------------------------------------------
void C3DObj::PostInit()
{
}
//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void C3DObj::Fin()
{

}
//---------------------------------------------------------------------------------------
//�X�V����
//---------------------------------------------------------------------------------------
void C3DObj::Update()
{
}
//---------------------------------------------------------------------------------------
//�`�揈��
//---------------------------------------------------------------------------------------
void C3DObj::Draw()
{

}

//---------------------------------------------------------------------------------------
//����������
//---------------------------------------------------------------------------------------
void C3DObj::DrawAlpha()
{

}

//---------------------------------------------------------------------------------------
//�ʒu���擾
//---------------------------------------------------------------------------------------
D3DXVECTOR3 C3DObj::GetPos()
{
	D3DXVECTOR3 pos(m_world._41,m_world._42,m_world._43);
	return pos;
}
//---------------------------------------------------------------------------------------
//������x�N�g���̎擾
//---------------------------------------------------------------------------------------
D3DXVECTOR3 C3DObj::GetUp()
{
	
	D3DXVECTOR3 Up(m_world._21,m_world._22,m_world._23);
	return Up;
}
//---------------------------------------------------------------------------------------
//�O���x�N�g���̎擾
//---------------------------------------------------------------------------------------
D3DXVECTOR3 C3DObj::GetForward()
{
	D3DXVECTOR3 Forward(m_world._31,m_world._32,m_world._33);
	return Forward;
}
//---------------------------------------------------------------------------------------
//X�E�x�N�g���̎擾
//---------------------------------------------------------------------------------------
D3DXVECTOR3 C3DObj::GetRight()
{
	D3DXVECTOR3 Right(m_world._31,m_world._32,m_world._33);
	return Right;
}
//---------------------------------------------------------------------------------------
//�I�u�W�F�N�g�̌���
//---------------------------------------------------------------------------------------
C3DObj* C3DObj::Find(UINT uID,C3DObj* p)
{
	//�V�[���I�u�W�F�N�g�����݂��Ȃ���΁A�ق��̃I�u�W�F�N�g�����݂��Ȃ�����
	//�����ōŏ��ɔ��������
	if(m_pScene)
		return m_pScene ->Find(uID,p);
	return NULL;
}

//---------------------------------------------------------------------------------------
//�z��ʒu���擾(X)
//---------------------------------------------------------------------------------------
int C3DObj::GetPosX ()
{
	return m_nUnit_Pos_X;
}

//---------------------------------------------------------------------------------------
//�z��ʒu���擾(Z)
//---------------------------------------------------------------------------------------
int C3DObj::GetPosZ ()
{
	return m_nUnit_Pos_Z;
}