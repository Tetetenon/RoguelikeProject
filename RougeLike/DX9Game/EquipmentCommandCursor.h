#pragma once

#include "2DWindow.h"
#include "Turn.h"
#include "EquipmentCommandWindow.h"

//�R�}���h�I����ʂ̃J�[�\��

class CEquipmentCommandWindow;

class CEquipmentCommandCursor:
	public C2DWindow
{
private:
	//�V���O���g��
	static CEquipmentCommandCursor* m_pEquipmentCommandCursor;

	int		m_Command;				//���Ԗڂ̃R�}���h��I�����Ă��邩���i�[����
	int		m_nInterval;			//�{�^�����͂̃C���^�[�o��
	CEquipmentCommandWindow* m_pEquipmentCommandWindow;

	CEquipmentCommandCursor(void);								//�R���X�g���N�^
	virtual ~CEquipmentCommandCursor(void);						//�f�X�g���N�^
public:
	static void Create();								//���̂̍쐬
	static void Delete();								//���̂̍폜
	static CEquipmentCommandCursor* GetPointer();		//���̂̃|�C���^��n��

	void Draw();										//�`��
	void Update();										//�X�V

	void SetVertex();									//�|���S�����𖄂߂�
	void SetPos();										//�|���S���̈ʒu����ݒ肷��

	int  GetCommand();									//�I�������R�}���h��Ԃ� 

	//�����o�ϐ��̃|�C���^�̐ݒ�
	void SetPointer();
};

