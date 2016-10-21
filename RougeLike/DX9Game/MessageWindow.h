#pragma once


#include "Structure.h"
#include <tchar.h>

#define DRAW_NUM 5
#define FONT_NUM 41

class MessageWindow
{
private:
	LPD3DXFONT			m_pFont;						//�t�H���g�ւ̃|�C���^
	RECT				m_DrawFontPos[DRAW_NUM];		//�t�H���g�̕`��ʒu

	static _TCHAR		m_Message[DRAW_NUM][FONT_NUM];	//�i�[���郁�b�Z�[�W(������30����,�s��5)

	VERTEX_2D			m_aVertex[DRAW_NUM][NUM_VERTEX];	//�|���S�����_���i�[�p

	static bool			m_bDrawflg;						//�`��t���O
	static float		m_fDrawTime;					//�`��p������
public:
	MessageWindow(void);								//�R���X�g���N�^
	~MessageWindow(void);								//�f�X�g���N�^

	void Init ();										//������
	void Fin	();										//�I��
	void Update();										//�X�V
	void Draw();										//�`��

	void SetVertex ();							//�|���S�����̒��g�𖄂߂�

	void SetFontPos ();							//�t�H���g�`��ʒu��ݒ�
	
	static void SetMassege(_TCHAR String[], ...);		//��������Z�b�g����
};

