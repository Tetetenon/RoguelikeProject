#pragma once
//���j�b�g�T�[�N���N���X

#include "Structure.h"

class CCircle
{
private:
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;								//���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_pD3DIdxBuff;								// �C���f�b�N�X�o�b�t�@
	D3DXMATRIX				m_mtxWorld;									//���[���h�}�g���b�N�X

	int						m_NumVertexIndex;							//�C���f�b�N�X��
	int						m_NumVertex;								//�����_��
	int						m_NumPolygon;								//�|���S����
public:
	CCircle(void);				//�R���X�g���N�^
	~CCircle(void);				//�f�X�g���N�^

	void Init();					//������
	void Update();					//�X�V
	void Draw(int UnitNumber);		//�`��
	void Fin();						//�I������

	void SetPos(D3DXVECTOR3 Pos);	//�ʒu���ݒ�
};

