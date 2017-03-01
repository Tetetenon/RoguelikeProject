#pragma once

#include "2DWindow.h"

class CItemCommandWindow;
class CItemWindow;

class CItemWindowCursor:
	public C2DWindow
{
private:
	//�V���O���g���ɂ��邱�ƂŁA��Ӑ����m��
	static CItemWindowCursor* m_pItemWindowCursor;

	int			m_nNumber;				//���ݑI�����Ă���A�C�e�������Ԗڂ̕������Ǘ�����
	int			m_nInterval;			//�{�^�����͂��Ă���̌o�ߎ��Ԃ�ۑ�����

	CItemCommandWindow* m_pItemCommandWindow;
	CItemWindow*		m_pItemWindow;

	CItemWindowCursor(void);		//�R���X�g���N�^
	~CItemWindowCursor(void);	//�f�X�g���N�^
public:
	static void Create();		//���g�̎��Ԃ��쐬
	static void Delete();		//���g�̎��Ԃ��폜
	static CItemWindowCursor* GetPointer();	//���g�̃|�C���^��n��

	void Draw();				//�`��
	void Update();				//�X�V

	void SetVertex ();			//�|���S�����𖄂߂�

	void SetPos();				//�|���S���̈ʒu����ݒ肷��

	int GetItemNum();			//�I�����Ă���A�C�e���̏���ԋp����B

	//�����o�ϐ��̃|�C���^��ݒ肷��
	void SetPointer();
};

