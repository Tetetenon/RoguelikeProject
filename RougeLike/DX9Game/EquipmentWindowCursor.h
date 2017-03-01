#pragma once

#include "2DWindow.h"
class CEquipmentWindow;
class CEquipmentCommandWindow;
class CItemWindow;

class CEquipmentWindowCursor:
	public C2DWindow
{
private:
	//�V���O���g��
	static CEquipmentWindowCursor* m_pEquiomentInventoryCursor;
	int			m_Number;				//���ݑI�����Ă���A�C�e�������Ԗڂ̕������Ǘ�����
	int			m_nInterval;			//�{�^�����͂��s���Ă���̃C���^�[�o���^�C��

	CEquipmentWindow*			m_pEquipmentWindow;			//�����E�B���h�E�ւ̃|�C���^
	CEquipmentCommandWindow*	m_pEquipmentCommandWindow;	//�����R�}���h�E�B���h�E�ւ̃|�C���^
	CItemWindow*				m_pItemWindow;				//�A�C�e���E�B���h�E�ւ̃|�C���^

	CEquipmentWindowCursor(void);		//�R���X�g���N�^ 
	~CEquipmentWindowCursor(void);	//�f�X�g���N�^
public:
	static void Create();							//���̂̐���
	static void Delete();							//���̂̍폜
	static CEquipmentWindowCursor* GetPointer();	//���̂̃|�C���^�[��n��

	void Draw();				//�`��
	void Update();				//�X�V

	void SetVertex ();			//�|���S�����𖄂߂�

	void SetPos();				//�|���S���̈ʒu����ݒ肷��

	int GetItemNum();			//�I�����Ă���A�C�e���̏���ԋp����B

	//�����o�ϐ��̃|�C���^�̐ݒ�
	void SetPointer();
};

