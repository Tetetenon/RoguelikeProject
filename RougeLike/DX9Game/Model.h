//���f���f�[�^�̊Ǘ�
#pragma once

#include "Config.h"

class CModel :
	public CMeshObj
{
private:
	static CMesh m_Mesh[];		//���b�V���f�[�^�i�[�p
	static CPiece m_Piece[];	//�j�Ѓf�[�^�i�[�p
public:
	CModel();					//�R���X�g���N�^
	~CModel();					//�f�X�g���N�^

	void Init ();				//������
	void Fin  ();				//�I������

	CMesh GetModelData();		//���b�V���f�[�^�̎擾
	CPiece GetPieceData();		//�j�Ѓf�[�^�̎擾
};