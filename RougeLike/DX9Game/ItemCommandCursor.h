#pragma once

#include "2DWindow.h"
#include "Turn.h"
class CItemCommandWindow;

//�R�}���h�I����ʂ̃J�[�\��

class CItemCommandCursor:
	public C2DWindow
{
private:
	//�V���O���g��
	static CItemCommandCursor* m_pItemCommandCursor;

	int					m_Command;				//���Ԗڂ̃R�}���h��I�����Ă��邩���i�[����

	CItemCommandWindow*	m_pItemCommandWindow;
	int							m_nInterval;			//�{�^�����͌o�ߎ��Ԃ�ۑ�

	CItemCommandCursor(void);								//�R���X�g���N�^
	virtual ~CItemCommandCursor(void);						//�f�X�g���N�^
public:
	static void Create();
	static void Delete();
	static CItemCommandCursor* GetPointer();

	void Draw();										//�`��
	void Update();										//�X�V

	void SetVertex();									//�|���S�����𖄂߂�
	void SetPos();										//�|���S���̈ʒu����ݒ肷��

	int  GetCommand();									//�I�������R�}���h��Ԃ� 

	//�����o�ϐ��̃|�C���^��ݒ肷��
	void SetPointer();
};

