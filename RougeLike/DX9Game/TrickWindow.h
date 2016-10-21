#pragma once

#include "2DWindow.h"
#include "Trick.h"
#include "define.h"

class CTrickWindowCursor;

class CTrickWindow:
	public CTrick,
	public C2DWindow
{
private:
	CTrick				m_Trick[TRICK_NUM_MAX];	//�Z�f�[�^(�Z�̎��Ă鐔)
	LPD3DXFONT			m_Font;					//�`��p�t�H���g
	RECT				m_Pos[TRICK_NUM_MAX];	//�E�B���h�E�\���ʒu
	static bool			m_bDrawFlg;				//�`��t���O

	VERTEX_2D	m_aVertex[TRICK_NUM_MAX][NUM_VERTEX];	//�|���S�����_���i�[�p
	static CTrickWindowCursor	m_TrickCursor;			//�I�����Ă���A�C�e���E�C���h�E�̎擾
public:
	CTrickWindow(void);							//�R���X�g���N�^
	~CTrickWindow(void);						//�f�X�g���N�^

	void Init();								//������
	void Fin();									//�I������

	void UpDate();								//�X�V��
	void Draw();								//�`��

	static void DrawFlgChange();				//�`��t���O��ON/OFF����

	void SetVertex();							//�|���S�����𖄂߂�
	void SetFontPos();							//�t�H���g�`��ʒu�ݒ�

	//�`��̃t���O�󋵂��擾
	static bool GetDrawFlg()	{return m_bDrawFlg;}

	//�w�肳�ꂽ�Z�f�[�^��n��
	CTrick GetTrick (int Coefficient)	{return m_Trick[Coefficient];}

	//�w�肳�ꂽ�A�C�e���̖��O��Ԃ�
	_TCHAR* GetTrickName(int Coefficient){return m_Trick[Coefficient].GetName();}

	//�w�肳�ꂽ�Z�͈̔͂�Ԃ�
	int GetRange(int Receipt);

	int GetEffect(int Receipt);					//�w�肳�ꂽ�A�C�e���̌��ʃW��������ԋp

	int GetEffectValue(int Receipt);			//�w�肳�ꂽ�A�C�e���̌��\��ԋp����

	void FindName	(int nID,int Receipt);		//ID���疼�O����������

};

