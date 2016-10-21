#pragma once

#include "2DWindow.h"
#include "EquipmentWindow.h"
#include "EquipmentCommandWindow.h"

class CEquipmentInventoryCursor:
	public C2DWindow
{
private:
	static int			m_Number;				//���ݑI�����Ă���A�C�e�������Ԗڂ̕������Ǘ�����
public:
	CEquipmentInventoryCursor(void);		//�R���X�g���N�^
	~CEquipmentInventoryCursor(void);	//�f�X�g���N�^

	void Init();				//������
	void Fin();					//�I������

	void Draw();				//�`��
	void Update();				//�X�V

	void SetVertex ();			//�|���S�����𖄂߂�

	void SetPos();				//�|���S���̈ʒu����ݒ肷��

	static int GetItemNum();			//�I�����Ă���A�C�e���̏���ԋp����B
};

