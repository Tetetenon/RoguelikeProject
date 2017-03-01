#pragma once

#include <tchar.h>
#include"2DWindow.h"
#include "define.h"

#define FONT_MAX 10

class CTurn;
class CItemWindow;
class CUnit; 
class CMenuWindow;

class CItemCommandWindow:
	public C2DWindow
{
	//�V���O���g��
	static CItemCommandWindow* m_pItemCommandWindow;
	CUnit*			m_pPlayer;								//�v���C���[�̃|�C���^
	_TCHAR			m_CommandName[COMMAND_MAX][FONT_MAX];	//�R�}���h��
	LPD3DXFONT		m_Font;									//�`��p�t�H���g
	RECT			m_Pos[COMMAND_MAX];						//�E�B���h�E�\���ʒu
	bool			m_bDrawFlg;								//�`��t���O
	VERTEX_2D		m_aVertex[COMMAND_MAX][NUM_VERTEX];		//�|���S�����_���i�[�p
	CTurn*			m_pTurn;								//�X�e�[�g�ύX
	CItemWindow*	m_pItemWindow;							//�C���x���g���̕`��t���O�ύX�p
	CMenuWindow*	m_pMenuWindow;							//���j���[�E�B���h�E�ւ̃|�C���^
	int				m_EnterInterval;						//�A�C�e���I�����ɃG���^�[�L�[���N���b�N���Ă���o�������Ԃ��v������(�A����Trigger���������邱�Ƃ�����邽��)


	CItemCommandWindow(void);						//�R���X�g���N�^
	~CItemCommandWindow(void);						//�f�X�g���N�^
public:
	static void Create();						//���̂̍쐬
	static void Delete();						//���̂̍폜
	static CItemCommandWindow* GetPointer();	//���g�̃|�C���^��n��

	void UpDate();								//�X�V��
	void Draw();								//�`��

	void DrawFlgChange();						//�`��t���O��ON/OFF����

	void SetVertex();							//�|���S�����𖄂߂�
	void SetFontPos();							//�t�H���g�`��ʒu�ݒ�

	void SetCommand();							//�E�B���h�E�̃R�}���h�𖄂߂�

	//�`��̃t���O�󋵂��擾
	bool GetDrawFlg()	{return m_bDrawFlg;}

	//�����o�ϐ��̃|�C���^��ݒ肷��
	void SetPointer();
};

