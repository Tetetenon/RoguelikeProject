#include "ModelManager.h"

CMesh	CModelManager::m_MeshData[MODEL_MAX];				//���b�V���f�[�^�ۑ��p
bool	CModelManager::m_MeshLoadFlg[MODEL_MAX] = {false};	//���f���f�[�^�ǂݍ��݃t���O


//-----���f���f�[�^�p�X-----

#define PATH_MESH_PLAYER		_T("../data/model/model/RedHood.x")			//�v���C���[(�Ԃ�����)
#define PATH_MESH_BEE			_T("../data/model/model/Bee.x")				//�G�l�~�[(�I)
#define PATH_MESH_BEAR			_T("../data/model/model/Bear.x")			//�G�l�~�[(�N�})
#define PATH_MESH_WOLF			_T("../data/model/model/Wolf.x")			//�G�l�~�[(�T)
#define PATH_MESH_TREE			_T("../data/model/model/Tree.x")			//�t�B�[���h�I�u�W�F(��)
#define PATH_MESH_WALL			_T("../data/model/model/Wall.x")			//�t�B�[���h�I�u�W�F(��)
#define PATH_MESH_ITEM			_T("../data/model/model/TreasureBox.x")		//�t�B�[���h�I�u�W�F(��)
#define PATH_MESH_STAIRS		_T("../data/model/model/Stairs.x")			//�t�B�[���h�I�u�W�F(�K�i)
#define PATH_MESH_HIT			_T("../data/model/model/Hit.x")				//�퓬���q�b�g
#define PATH_MESH_DELETE		_T("../data/model/model/Delete.x")			//�퓬������




//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CModelManager::CModelManager(void)
{
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CModelManager::~CModelManager(void)
{
}

//---------------------------------------------------------------------------------------
//���b�V���f�[�^�����[�h����
//---------------------------------------------------------------------------------------
void CModelManager::LoadMesh()
{
	//���b�V���f�[�^�̏�����
	ReleaseMesh();
	
	//-----�v���C���[���f���̓ǂݍ���-----
	if(!m_MeshLoadFlg[MODEL_PLAYER])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_PLAYER] = m_MeshData[MODEL_PLAYER].Initialize(PATH_MESH_PLAYER,true);
	}

	//-----�I���f���̓ǂݍ���-----
	if(!m_MeshLoadFlg[MODEL_BEE])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_BEE] = m_MeshData[MODEL_BEE].Initialize(PATH_MESH_BEE,true);
	}
	
	//-----�N�}���f���̓ǂݍ���-----
	if(!m_MeshLoadFlg[MODEL_BEAR])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_BEAR] = m_MeshData[MODEL_BEAR].Initialize(PATH_MESH_BEAR,true);
	}

	//-----�T���f���̓ǂݍ���-----
	if(!m_MeshLoadFlg[MODEL_WOLF])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_WOLF] = m_MeshData[MODEL_WOLF].Initialize(PATH_MESH_WOLF,true);
	}

	//-----�؃��f���̓ǂݍ���-----
	if(!m_MeshLoadFlg[MODEL_TREE])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_TREE] = m_MeshData[MODEL_TREE].Initialize(PATH_MESH_TREE,true);
	}

	//-----�ǃ��f���̓ǂݍ���-----
	if(!m_MeshLoadFlg[MODEL_WALL])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_WALL] = m_MeshData[MODEL_WALL].Initialize(PATH_MESH_WALL,true);
	}

	//-----�󔠃��f���̓ǂݍ���-----
	if(!m_MeshLoadFlg[MODEL_TREASUREBOX])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_TREASUREBOX] = m_MeshData[MODEL_TREASUREBOX].Initialize(PATH_MESH_ITEM,true);
	}

	//-----�K�i���f���̓ǂݍ���-----
	if(!m_MeshLoadFlg[MODEL_STAIRS])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_STAIRS] = m_MeshData[MODEL_STAIRS].Initialize(PATH_MESH_STAIRS,true);
	}

	//-----�퓬�q�b�g�ǂݍ���-----
	if(!m_MeshLoadFlg[MODEL_HIT])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_HIT] = m_MeshData[MODEL_HIT].Initialize(PATH_MESH_HIT,true);
	}

	//-----�퓬���ł̓ǂݍ���-----
	if(!m_MeshLoadFlg[MODEL_DELETE])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_DELETE] = m_MeshData[MODEL_DELETE].Initialize(PATH_MESH_DELETE,true);
	}


}

//---------------------------------------------------------------------------------------
//�S�Ẵ��b�V���f�[�^���폜����
//---------------------------------------------------------------------------------------
void CModelManager::ReleaseMesh()
{
	//���b�V���f�[�^�����݂���΁A�폜�����ׂẴ��b�V���f�[�^�ɑ΂��s��
	for(int i = 0;i < MODEL_MAX;i++)
	{
		//���b�V���f�[�^���ǂݍ��܂�Ă���
		if(m_MeshLoadFlg[i])
		{
			//���b�V���̏I������
			m_MeshData[i].Finalize();
			//�t���O��|��
			m_MeshLoadFlg[i] = false;
		}
	}

}

//---------------------------------------------------------------------------------------
//�w�肳�ꂽ���b�V���f�[�^��n��
//---------------------------------------------------------------------------------------
CMesh*	CModelManager::GetMesh(int nNumber)
{
	return &m_MeshData[nNumber];
}