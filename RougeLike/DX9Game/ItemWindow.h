#pragma once

#include "2DWindow.h"
#include "Inventory.h"

class CItemCommandWindow;
class CItemWindowCursor;
class CItemDescriptionFrame;

class CItemWindow:
	public C2DWindow
{
private:
	//�V���O���g��
	static CItemWindow* m_pItemWindow;
	LPD3DXFONT			m_Font;					//�`��p�t�H���g
	RECT				m_Pos[ITEM_NUM_MAX];	//�E�B���h�E�\���ʒu
	bool				m_bDrawFlg;				//�`��t���O
	bool				m_bUpdateFlg;				//�X�V�t���O

	VERTEX_2D	m_aVertex[ITEM_NUM_MAX][NUM_VERTEX];	//�|���S�����_���i�[�p

	CItemCommandWindow*		m_pCommandWindow;	//�R�}���h�E�C���h�E�̕`��t���O�ύX�p
	CItemWindowCursor*		m_pIItemWindowCursor;	//�I�����Ă���A�C�e���E�C���h�E�̎擾
	CItemDescriptionFrame*	m_pDescription;		//�A�C�e��������
	CInventory*				m_pPlayerInventory;	//�v���C���[�̏����A�C�e���|�C���^

	int						m_nInterval;		//���͌o�ߎ���

	CItemWindow(void);							//�R���X�g���N�^
	~CItemWindow(void);							//�f�X�g���N�^
public:
	static void Create();						//���̂��쐬
	static void Delete();						//���̂̍폜
	static CItemWindow*	GetPointer();			//�|�C���^��n��

	void UpDate();								//�X�V��
	void Draw();								//�`��

	void DrawFlgChange(bool);				//�`��t���O��ON/OFF����
	void UpdateFlgChange(bool);					//�X�V�t���O��ON/OFF

	void SetVertex();							//�|���S�����𖄂߂�
	void SetFontPos();							//�t�H���g�`��ʒu�ݒ�

	//�`��̃t���O�󋵂��擾
	bool GetDrawFlg()	{return m_bDrawFlg;}
	bool GetUpdateFlg() { return m_bUpdateFlg; }

	//�����o�ϐ��̃|�C���^��ݒ肷��
	void SetPoiner();
};

