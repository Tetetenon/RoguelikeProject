#pragma once

#include "2DWindow.h"
#include "TrickWindow.h"

class CTrickWindowCursor:
	public C2DWindow
{
private:
	static int	m_Number;			//���ݑI�����Ă��邪���Ԗڂ̕������Ǘ�����
	int			m_nInterval;		//�{�^�����͌o�ߎ���
public:
	CTrickWindowCursor(void);		//�R���X�g���N�^
	~CTrickWindowCursor(void);	//�f�X�g���N�^

	void Init();				//������
	void Fin();					//�I������

	void Draw();				//�`��
	void Update();				//�X�V

	void SetVertex ();			//�|���S�����𖄂߂�

	void SetPos();				//�|���S���̈ʒu����ݒ肷��

	static int GetTrickNum();			//�I�����Ă���Z�̏���ԋp����B
};

