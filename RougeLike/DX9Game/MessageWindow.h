#pragma once


#include "Structure.h"
#include <tchar.h>

#define DRAW_NUM 5
#define FONT_NUM 41

class CMessageWindow
{
private:
	//�V���O���g��
	static CMessageWindow* m_pMessageWindow;

	LPD3DXFONT			m_pFont;						//�t�H���g�ւ̃|�C���^
	RECT				m_DrawFontPos[DRAW_NUM];		//�t�H���g�̕`��ʒu

	_TCHAR		m_Message[DRAW_NUM][FONT_NUM];	//�i�[���郁�b�Z�[�W(������30����,�s��5)

	VERTEX_2D			m_aVertex[DRAW_NUM][NUM_VERTEX];	//�|���S�����_���i�[�p

	bool			m_bDrawflg;						//�`��t���O
	float		m_fDrawTime;					//�`��p������

	CMessageWindow(void);					//�R���X�g���N�^
	~CMessageWindow(void);					//�f�X�g���N�^
public:
	static void Create();					//���̂̍쐬
	static void Delete();					//���̂̍폜
	static CMessageWindow* GetPointer();	//���̂̃|�C���^��n��

	void Update();							//�X�V
	void Draw();							//�`��

	void SetVertex ();						//�|���S�����̒��g�𖄂߂�

	void InitFontData();					//�t�H���g�̃f�[�^������������

	void SetFontPos ();						//�t�H���g�`��ʒu��ݒ�
	
	void SetMassege(_TCHAR String[], ...);	//��������Z�b�g����
};

