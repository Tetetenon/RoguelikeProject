#pragma once

//�X�e�[�^�X��ʂ̍��ڂ�`�悷��

#include "C2DTexture.h"
#include "StatesDefine.h"

class CStatesFont :
	public C2DTexture
{
private:
	//�V���O���g��
	static CStatesFont* m_pStatesFont;
	//�g�p�e�N�X�`���ԍ��i�[�p
	int			m_nTextureNumber[STATES_FONT_MAX];		
	//�|���S�����i�[�p
	VERTEX_2D	m_aVertex[STATES_FONT_MAX][NUM_VERTEX];

	CStatesFont(void);		//�R���X�g���N�^
	~CStatesFont(void);		//�f�X�g���N�^
public:
	static void Create();				//���̂̍쐬
	static void Delete();				//���̂̍폜
	static CStatesFont* GetPointer();	//���̂̃|�C���^�[��n��
	void Draw();			//�`��

	void SetVertex ();		//�|���S�����̐ݒ�
};