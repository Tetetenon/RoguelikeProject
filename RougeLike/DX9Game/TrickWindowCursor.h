#pragma once

#include "2DWindow.h"

class CTrickWindow;

class CTrickWindowCursor:
	public C2DWindow
{
private:
	//�V���O���g��
	static CTrickWindowCursor* m_pTrickWindowCursor;

	CTrickWindow*	m_pTrickWindow;

	int	m_nNumber;			//���ݑI�����Ă��邪���Ԗڂ̕������Ǘ�����
	int			m_nInterval;		//�{�^�����͌o�ߎ���

	CTrickWindowCursor(void);		//�R���X�g���N�^
	~CTrickWindowCursor(void);	//�f�X�g���N�^
public:
	static void Create();
	static void Delete();
	static CTrickWindowCursor* GetPointer();

	void Draw();				//�`��
	void Update();				//�X�V

	void SetVertex ();			//�|���S�����𖄂߂�

	void SetPos();				//�|���S���̈ʒu����ݒ肷��

	int GetTrickNum();			//�I�����Ă���Z�̏���ԋp����B

	//�����o�ϐ��̃|�C���^��ݒ肷��
	void SetPointer();
};

