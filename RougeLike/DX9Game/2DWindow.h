#pragma once

//���j���[�E�C���h�E�ɗp������N���X

#include "Structure.h"
class C2DWindow
{
protected:
	//�|���S�����i�[�p�ϐ�
	VERTEX_2D m_aVertex[NUM_VERTEX];
public:
	C2DWindow(void);		//�R���X�g���N�^
	~C2DWindow(void);		//�f�X�g���N�^

	virtual void Init();			//������
	virtual void Fin();				//�I������

	virtual void Draw();			//�`��
	virtual void Update();			//�X�V

	virtual void SetVertex();		//�|���S������ݒ�

	virtual void SetPos();			//�|���S���ʒu����ݒ�
};

