#pragma once
#include "C2DTexture.h"

//���j���[����
enum MENUTAG
{
	MENU_ITEM = 0,		//�A�C�e��
	MENU_TRICK,			//���U
	MENU_EQUIPMENT,		//�����m�F
	MENU_STATES,		//�X�e�[�^�X
	MENU_MAX
};

class CMenuSelect :
	public C2DTexture
{
private:
	static int	m_nSelectNumber;		//���ݑI�����Ă��郁�j���[�ԍ��i�[�p�ϐ�
	static bool m_bOperationFlg;		//����\�t���O
	static int	m_nInterval;			//�{�^�����͂̃C���^�[�o��		
public:
	CMenuSelect(void);					//�R���X�g���N�^
	~CMenuSelect(void);					//�f�X�g���N�^

	void Update();						//�X�V

	//���݂̑���t���O��Ԃ��擾
	static bool GetOperationFlg()		{return m_bOperationFlg;}
	//����t���O�̔��]
	static void ChangeDrawFlg();
};

