#pragma once

#include "define.h"
#include "Mesh.h"

//�g�p���郂�f���ꗗ
enum MODELNUM
{
	MODEL_PLAYER = 0,		//�v���C���[(�Ԃ�����)
	MODEL_BEE,				//�G�l�~�[(�I)
	MODEL_BEAR,				//�G�l�~�[(�N�})
	MODEL_WOLF,				//�G�l�~�[(�T)
	MODEL_TREE,				//�t�B�[���h�I�u�W�F(��)
	MODEL_WALL,				//�t�B�[���h�I�u�W�F(��)
	MODEL_TREASUREBOX,		//�t�B�[���h�I�u�W�F(��)
	MODEL_STAIRS,			//�t�B�[���h�I�u�W�F(�K�i)
	MODEL_HIT,				//�퓬���q�b�g�I�u�W�F�g
	MODEL_DELETE,			//�퓬������
	MODEL_MAX
};

class CModelManager
{
private:
	static CMesh	m_MeshData[MODEL_MAX];		//���b�V���f�[�^�ۑ��p
	static bool		m_MeshLoadFlg[MODEL_MAX];	//���f���f�[�^�ǂݍ��݃t���O
public:
	CModelManager(void);						//�R���X�g���N�^
	~CModelManager(void);						//�f�X�g���N�^

	static void		LoadMesh();					//���b�V���f�[�^�����[�h����

	static void		ReleaseMesh();				//�S�Ẵ��b�V���f�[�^���폜����

	static CMesh*	GetMesh(int nNumber);		//�w�肳�ꂽ���b�V���f�[�^��n��
};

