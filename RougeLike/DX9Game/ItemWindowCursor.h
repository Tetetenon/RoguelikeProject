#pragma once

#include "2DWindow.h"
#include "ItemWindow.h"
#include "ItemCommandWindow.h"

class CInventoryCursor:
	public C2DWindow
{
private:
	static int			m_Number;				//���ݑI�����Ă���A�C�e�������Ԗڂ̕������Ǘ�����

public:
	CInventoryCursor(void);		//�R���X�g���N�^
	~CInventoryCursor(void);	//�f�X�g���N�^

	void Init();				//������
	void Fin();					//�I������

	void Draw();				//�`��
	void Update();				//�X�V

	void SetVertex ();			//�|���S�����𖄂߂�

	void SetPos();				//�|���S���̈ʒu����ݒ肷��

	static int GetItemNum();			//�I�����Ă���A�C�e���̏���ԋp����B
};

