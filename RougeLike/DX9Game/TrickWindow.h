#pragma once

#include "2DWindow.h"
#include "Trick.h"
#include "define.h"

class CUnit;
class CMenuWindow;

class CTrickWindow:
	public CTrick,
	public C2DWindow
{
private:
	//�V���O���g��
	static CTrickWindow* m_pTrickWindow;

	CTrick				m_Trick[TRICK_NUM_MAX];			//�Z�f�[�^(�Z�̎��Ă鐔)
	LPD3DXFONT			m_Font;							//�`��p�t�H���g
	RECT				m_Pos[TRICK_NUM_MAX];			//�E�B���h�E�\���ʒu
	bool				m_bDrawFlg;							//�`��t���O

	CUnit*				m_pPlayer;
	CMenuWindow*		m_pMenuWindow;

	VERTEX_2D				m_aVertex[TRICK_NUM_MAX][NUM_VERTEX];	//�|���S�����_���i�[�p

	int					m_nInputInterval;		//�{�^�����͂��Ă���̌o�ߎ���

	CTrickWindow(void);							//�R���X�g���N�^
	~CTrickWindow(void);						//�f�X�g���N�^
public:
	static void Create();						//���̂̍쐬
	static void Delete();						//���̂̍폜
	static CTrickWindow* GetPointer();			//���̂̃|�C���^��n��

	void UpDate();								//�X�V��
	void Draw();								//�`��

	void DrawFlgChange();				//�`��t���O��ON/OFF����

	void SetVertex();							//�|���S�����𖄂߂�
	void SetFontPos();							//�t�H���g�`��ʒu�ݒ�

	//�`��̃t���O�󋵂��擾
	bool GetDrawFlg()	{return m_bDrawFlg;}

	//�w�肳�ꂽ�Z�f�[�^��n��
	CTrick GetTrick (int Coefficient)	{return m_Trick[Coefficient];}

	//�w�肳�ꂽ�A�C�e���̖��O��Ԃ�
	_TCHAR* GetTrickName(int Coefficient){return m_Trick[Coefficient].GetName();}

	//�w�肳�ꂽ�Z�͈̔͂�Ԃ�
	int GetRange(int Receipt);

	int GetEffect(int Receipt);					//�w�肳�ꂽ�A�C�e���̌��ʃW��������ԋp

	int GetEffectValue(int Receipt);			//�w�肳�ꂽ�A�C�e���̌��\��ԋp����

	void FindName	(int nID,int Receipt);		//ID���疼�O����������

	//�����o�ϐ��̃|�C���^��ݒ肷��
	void SetPointer();
};

