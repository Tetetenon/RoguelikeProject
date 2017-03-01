#pragma once
#include "C2DTexture.h"

//�X�e�[�^�X�E�B���h�E�N���X�̒�`
class CStatesWindow;
class CItemWindow;
class CTrickWindow;
class CEquipmentWindow;

//���j���[����
enum MENUTAG
{
	MENU_ITEM = 0,		//�A�C�e��
	MENU_TRICK,			//���U
	MENU_MAX
};

class CMenuSelect :
	public C2DTexture
{
private:
	//�V���O���g��
	static CMenuSelect* m_pMenuSelect;

	int	m_nSelectNumber;		//���ݑI�����Ă��郁�j���[�ԍ��i�[�p�ϐ�
	bool m_bOperationFlg;		//����\�t���O
	int	m_nInterval;			//�{�^�����͂̃C���^�[�o��

	CStatesWindow*		m_pStatesWindow;		//�X�e�[�^�X�E�B���h�E�̃|�C���^
	CItemWindow*		m_pItemWindow;
	CTrickWindow*		m_pTrickWindow;
	CEquipmentWindow*	m_pEquipmentWindow;

	CMenuSelect(void);					//�R���X�g���N�^
	~CMenuSelect(void);					//�f�X�g���N�^
public:
	//���̂̍쐬
	static void Create();
	//���̂̍폜
	static void Delete();
	//���̂̃|�C���^��n��
	static CMenuSelect* GetPointer();

	void Update();						//�X�V
	//���݂̑���t���O��Ԃ��擾
	bool GetOperationFlg()		{return m_bOperationFlg;}
	//�����o�ϐ��̃|�C���^��ݒ肷��
	void SetPointer();
};

