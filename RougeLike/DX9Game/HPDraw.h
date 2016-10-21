#pragma once

//�v���C���[�̏���`�悷��

#include "Structure.h"
#include <tchar.h>

class CHPDraw
{
private:
	static int					m_nHP;					//�`�悷�郆�j�b�g�̌��݂�HP

	static LPD3DXFONT			m_pFont;					//�`��t�H���g�̐ݒ�
	static RECT					m_FontDrawPos;				//�t�H���g�̕`��ʒu��ݒ肷��

	static char				m_States[256];	//�X�e�[�^�X(HP���)���i�[����

	static VERTEX_2D			m_aVertex[NUM_VERTEX];		//�e�N�X�`���̕`��ʒu

	static int					m_nMaxHP;					//�`�悷�郆�j�b�g�̍ő�HP

public:
	CHPDraw(void);										//�R���X�g���N�^
	~CHPDraw(void);										//�f�X�g���N�^

	void Init();											//������
	void Fin();												//�I������

	void Update();											//�X�V
	void Draw();											//�`�揈��

	static void SetVertex();										//�|���S���e�����ݒ�

	static void SetPosition();										//�|���S���̈ʒu���Đݒ�

	static void SetFontPos();										//�����`��ʒu��ݒ�

	static void SetHP (int nHP);							//�`�悷��HP���l���Z�b�g

	static void SetMaxHP (int nMaxHP);						//�`�悷��HP�̍ő�HP���Z�b�g

};

