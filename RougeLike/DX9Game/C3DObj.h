//	3D�I�u�W�F�N�g �N���X��`
#pragma once

#include "Graphics.h"

enum OBJID
{
	ID_3DOBJ = 0,
	ID_MESHOOBJ,
	ID_CAMERA,		//�J����
	ID_PLAYER,		//���@
	ID_SKY,			// �X�J�C�h�[��
	ID_ENEMY,		//�G�@
	ID_ITEM,		//�A�C�e��
	ID_EXPLOSION,	// ����
	ID_PARTICLE,	// �p�[�e�B�N��
	MAX_ID
};


// �`����@
enum ESynthetic {
	eNone = 0,		// �ʏ�`��
	eAdditive,		// ���Z����
	eAlphaBlend,	// ����������
	eSubtractive,	// ���Z����

	eMaxSynthetic
};
class CGameScene;

class C3DObj
{
protected:
	UINT		m_uID;		//�I�u�W�F�N�g���
	D3DXMATRIX	m_world;	//���[���h�ϊ��s��

	CGameScene*		m_pScene;	//��������V�[��
	C3DObj*		m_pNext;	//���I�u�W�F�N�g
	C3DObj*		m_pBack;	//�O�I�u�W�F�N�g
	ESynthetic		m_synthetic;	// �������`��t���O
	
	//�z���̈ʒu���
	int						m_nUnit_Pos_X;
	int						m_nUnit_Pos_Z;
public:
	C3DObj(CGameScene* pScene);
	virtual ~C3DObj(void);

	virtual void Init();	//������
	virtual void Fin();		//�I������
	virtual void Update();	//�X�V
	virtual void Draw();	//�`�揈��
	virtual void DrawAlpha();	//�������`�揈��
	D3DXMATRIX& GetWorld()	{return m_world;}
	void SetWorld(D3DXMATRIX& world){m_world = world;}


	D3DXVECTOR3 GetPos();		//���W�擾
	D3DXVECTOR3 GetUp();		//��x�N�g���擾
	D3DXVECTOR3 GetForward();	//�O���x�N�g���擾
	D3DXVECTOR3 GetRight();		//�E�x�N�g���擾
	
	//C3DObj* GetNext () {return m_pNext;}				//���̃|�C���^�̎擾
	//void	SetNext (C3DObj *pNext) {m_pNext = pNext;}	//���̃|�C���^�̐ݒ�
	//C3DObj* GetBack () {return m_pBack;}				//�O�̃|�C���^�̎擾
	//void	SetBack (C3DObj *pBack) {m_pBack = pBack;}	//�O�̃|�C���^�̐ݒ�

	CGameScene* GetScene() {return m_pScene;}				//�V�[���̎擾

	UINT GetID() {return m_uID;}						//ID���擾

	//C3DObj* Find(UINT uID,C3DObj* p = NULL);			//�I�u�W�F�N�g�̒T��

	void SetPos (D3DXVECTOR3& pos)	{m_world._41 = pos.x,m_world._42 = pos.y;m_world._43 = pos.z;}
	
	int GetPosX ();									//�z��ʒu���X��Ԃ�
	int GetPosZ ();									//�z��ʒu���Z��Ԃ�
};

