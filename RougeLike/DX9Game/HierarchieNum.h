#pragma once

//���݂̊K�w����\������
#include "C2DTexture.h"

//�K�w�\���Ɏg�p����|���S����
#define HIERARCHIENUM (3)

class CHierarchieNum :
	public C2DTexture
{
private:
	//�|���S�����
	static VERTEX_2D	m_aVertex[HIERARCHIENUM][NUM_VERTEX];
public:
	CHierarchieNum(void);	//�R���X�g���N�^
	~CHierarchieNum(void);	//�f�X�g���N�^

	void Draw();		//�`��
	void SetVertex();	//�|���S�����̐ݒ�
};

