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
#define PATH_MESH_HOME			_T("../data/model/model/Home.x")			//��
#define PATH_MESH_MUSHROOM		_T("../data/model/model/Mushroom.x")		//�L�m�R
#define PATH_MESH_FOUNTAIN		_T("../data/model/model/Fountain.x")		//����
#define PATH_MESH_DRAGON		_T("../data/model/model/Dragon.x")			//�h���S��

#define PATH_MESH_APPLE			_T("../data/model/model/Apple.x")			//�ь�
#define PATH_MESH_HERB			_T("../data/model/model/Herb.x")			//��
#define PATH_MESH_SWORD			_T("../data/model/model/Sword.x")			//��
#define PATH_MESH_SHIELD		_T("../data/model/model/Shield.x")			//��




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
	if (!m_MeshLoadFlg[MODEL_DELETE])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_DELETE] = m_MeshData[MODEL_DELETE].Initialize(PATH_MESH_DELETE, true);
	}

	//-----�Ƃ̓ǂݍ���-----
	if (!m_MeshLoadFlg[MODEL_HOME])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_HOME] = m_MeshData[MODEL_HOME].Initialize(PATH_MESH_HOME, true);
	}

	//-----�L�m�R�̓ǂݍ���-----
	if (!m_MeshLoadFlg[MODEL_MUSHROOM])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_MUSHROOM] = m_MeshData[MODEL_MUSHROOM].Initialize(PATH_MESH_MUSHROOM, true);
	}

	//-----�����̓ǂݍ���-----
	if (!m_MeshLoadFlg[MODEL_FOUNTAIN])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_FOUNTAIN] = m_MeshData[MODEL_FOUNTAIN].Initialize(PATH_MESH_FOUNTAIN, true);
	}

	//-----�h���S���̓ǂݍ���-----
	if (!m_MeshLoadFlg[MODEL_DRAGON])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_DRAGON] = m_MeshData[MODEL_DRAGON].Initialize(PATH_MESH_DRAGON, true);
	}
	//-----�ь�̓ǂݍ���-----
	if (!m_MeshLoadFlg[MODEL_APPLE])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_APPLE] = m_MeshData[MODEL_APPLE].Initialize(PATH_MESH_APPLE, true);
	}

	//-----�򑐂̓ǂݍ���-----
	if (!m_MeshLoadFlg[MODEL_HERB])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_HERB] = m_MeshData[MODEL_HERB].Initialize(PATH_MESH_HERB, true);
	}

	//-----���̓ǂݍ���-----
	if (!m_MeshLoadFlg[MODEL_SWORD])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_SWORD] = m_MeshData[MODEL_SWORD].Initialize(PATH_MESH_SWORD, true);
	}

	//-----���̓ǂݍ���-----
	if (!m_MeshLoadFlg[MODEL_SHIELD])
	{
		//���f���f�[�^�̃��[�h
		m_MeshLoadFlg[MODEL_SHIELD] = m_MeshData[MODEL_SHIELD].Initialize(PATH_MESH_SHIELD, true);
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