#pragma once

//�v���C���[�̏���`�悷��

#include "Structure.h"
#include <tchar.h>

class CHPDraw
{
private:
	//�V���O���g��
	static CHPDraw* m_pHPDraw;

	int					m_nHP;						//�`�悷�郆�j�b�g�̌��݂�HP

	LPD3DXFONT			m_pFont;					//�`��t�H���g�̐ݒ�
	RECT					m_FontDrawPos;				//�t�H���g�̕`��ʒu��ݒ肷��

	char				m_States[256];				//�X�e�[�^�X(HP���)���i�[����

	VERTEX_2D			m_aVertex[NUM_VERTEX];		//�e�N�X�`���̕`��ʒu

	int					m_nMaxHP;					//�`�悷�郆�j�b�g�̍ő�HP

	CHPDraw(void);									//�R���X�g���N�^
	~CHPDraw(void);									//�f�X�g���N�^
public:
	static void Create();							//���̂̍쐬
	static void Delete();							//���̂̍폜
	static CHPDraw* GetPointer();					//���g�̃|�C���^�̎擾

	void Update();									//�X�V
	void Draw();									//�`�揈��

	void SetVertex();								//�|���S���e�����ݒ�

	void SetPosition();								//�|���S���̈ʒu���Đݒ�

	void SetFontPos();								//�����`��ʒu��ݒ�

	void SetHP (int nHP);							//�`�悷��HP���l���Z�b�g

	void SetMaxHP (int nMaxHP);						//�`�悷��HP�̍ő�HP���Z�b�g
};

