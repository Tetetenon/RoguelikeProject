#pragma once

#include "2DWindow.h"
#include "Turn.h"
#include "EquipmentCommandWindow.h"

//�R�}���h�I����ʂ̃J�[�\��

class CEquipmentCommandCursor:
	public C2DWindow
{
private:
	static int					m_Command;				//���Ԗڂ̃R�}���h��I�����Ă��邩���i�[����

	static int					m_nInterval;			//�{�^�����͂̃C���^�[�o��
	CTurn						m_Turn;					//�^�[���X�e�[�g�ύX�p
public:
	CEquipmentCommandCursor(void);								//�R���X�g���N�^
	virtual ~CEquipmentCommandCursor(void);						//�f�X�g���N�^

	void Init();										//������
	void Fin();											//�I������

	void Draw();										//�`��
	void Update();										//�X�V

	void SetVertex();									//�|���S�����𖄂߂�
	void SetPos();										//�|���S���̈ʒu����ݒ肷��

	static int  GetCommand();									//�I�������R�}���h��Ԃ� 
};

