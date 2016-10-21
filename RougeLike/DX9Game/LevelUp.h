#pragma once
#include "C2DTexture.h"

#define POLYGON_SIZE_X 2.0f	//�|���S���̃T�C�YX
#define POLYGON_SIZE_Y 2.0f	//�|���S���̃T�C�YY
#define POLYGON_SIZE_Z 2.0f	//�|���S���̃T�C�YZ

class CLevelUp :
	public C2DTexture
{
private:
	D3DXMATRIX				m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_Pos;				//�ʒu���
	D3DXVECTOR3				m_Scl;				// �X�P�[��
	LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuff;		//���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

	int						m_UpPos;			//������㏸�l���i�[
public:
	CLevelUp(D3DXVECTOR3 Pos);			//�R���X�g���N�^
	~CLevelUp(void);					//�f�X�g���N�^

	void Update(D3DXVECTOR3 Pos);			//�X�V
	void Draw();			//�`�揈��

	void SetVertex();		//���_���̐ݒ�
	HRESULT MakeVertex();		//���_���̍쐬

	int GetUpPos(){return m_UpPos;}	//���݂̏㏸�l�̎擾
};

