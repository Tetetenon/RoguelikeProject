#pragma once

//���݂̊K�w����\������
#include "C2DTexture.h"

//�K�w�\���Ɏg�p����|���S����
#define HIERARCHIENUM (3)

class CMapData;
class CFade;

class CHierarchieNum :
	public C2DTexture
{
private:
	//�V���O���g��
	static CHierarchieNum* m_pHierarchieNum;
	//�|���S�����
	VERTEX_2D	m_aVertex[HIERARCHIENUM][NUM_VERTEX];

	CMapData*	m_pMapData;
	CFade*		m_pFade;

	CHierarchieNum(void);	//�R���X�g���N�^
	~CHierarchieNum(void);	//�f�X�g���N�^
public:
	static void Create();					//���̂̍쐬
	static void Delete();					//���̂̍폜
	static CHierarchieNum* GetPointer();	//���̂̃|�C���^��n��

	//�����o�ϐ��̃|�C���^���Z�b�g����
	void SetPointer();

	void Draw();		//�`��
	void SetVertex();	//�|���S�����̐ݒ�
};

