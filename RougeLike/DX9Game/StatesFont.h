#pragma once

//�X�e�[�^�X��ʂ̍��ڂ�`�悷��

#include "C2DTexture.h"
#include "StatesDefine.h"

class CStatesFont :
	public C2DTexture
{
private:
	//�g�p�e�N�X�`���ԍ��i�[�p
	static int			m_nTextureNumber[STATES_FONT_MAX];		
	//�|���S�����i�[�p
	static	VERTEX_2D	m_aVertex[STATES_FONT_MAX][NUM_VERTEX];
public:
	CStatesFont(void);		//�R���X�g���N�^
	~CStatesFont(void);		//�f�X�g���N�^

	void Draw();			//�`��

	void SetVertex ();		//�|���S�����̐ݒ�
};