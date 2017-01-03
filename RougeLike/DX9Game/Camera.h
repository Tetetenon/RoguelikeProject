#pragma once

#include"C3DObj.h"

class CUnit;

enum ECamPos
{
	CP_FIXED = 0,	//�Œ�
	CP_FPVIEW,		//1�l��
	CP_TPVIEW,		//3�l��
	MAX_VIEW
};

class CSky;

class CCamera:public C3DObj 
{
private:
	//�ϐ�
	D3DXMATRIX m_proj;	//�v���W�F�N�V�����}�g���b�N�X
	static D3DXMATRIX m_view;	//�r���[�}�g���b�N�X
	CSky*		m_pSky;		// �X�J�C�h�[��
	CUnit*	m_pPlayer;	//���@

	ECamPos		m_cp;	//�J�������
	
	D3DXVECTOR3 m_at;	//�����_
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_Up;	//������x�N�g��

	D3DXVECTOR3 m_at2;	//�����_
	D3DXVECTOR3 m_pos2;
	D3DXVECTOR3 m_Up2;	//������x�N�g��

	float m_fFovy;		//����p
	float m_fAspect;	//�A�X�y�N�g��
	float m_fZNear;		//�O���N���b�v
	float m_fZFar;		//����N���b�v

	float m_nTimer;		//�o�ߎ��Ԃ�}��
	bool  m_bSwitch;	//��ʐ؂�ւ��t���O

	static CCamera* m_pCamera;	//�V���O���g��

	//�֐�
	CCamera(CGameScene* pScene);
	virtual ~CCamera(void);
public:
	static void Create(CGameScene* pScene);	//�I�u�W�F�N�g�̍쐬
	static void Delete();	//�I�u�W�F�N�g�̍폜
	static CCamera* GetPointer();	//�I�u�W�F�N�g�|�C���^��n��

	virtual void Init ();	//������
	virtual void Update();	//�X�V
	virtual void Draw();	//�`��
	virtual void DrawAlpha();	//�`��
	virtual void Fin();		//�I������

	void PostUpdate();		//�X�V�㏈��
	void PreDraw();			//�`��㏈��

	//�r���[�}�g���N�X�̎擾
	static D3DXMATRIX GetMtxView()	{return m_view;}
};

