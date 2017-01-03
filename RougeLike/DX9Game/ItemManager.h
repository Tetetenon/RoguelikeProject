#pragma once

//�t�B�[���h��̃A�C�e���̊Ǘ����s���B

//�C���N���[�h
#include <map>
#include<list>
#include<vector>

class CFieldItem;

typedef std::vector<CFieldItem*>		ITEM_LIST;		//�t�B�[���h��̃A�C�e���̃��X�g
typedef std::map<int, ITEM_LIST>		ITEM_MAP;		//�t�B�[���h��̃A�C�e���̃��X�g+ID
typedef std::pair<int, ITEM_LIST>		ITEM_PAIR;		//�t�B�[���h��̃A�C�e�����X�g�y�A

class CItemManager
{
private:
	//�ϐ��錾

	//�V���O���g��
	static ITEM_MAP *m_pItemManager;


	static int		m_MakeItemNum;			//�A�C�e���̎��Ɋ���U����ID
	static bool		m_Delete;				//�S�A�C�e���f���[�g�t���O

	//�֐��錾
	CItemManager();							//�R���X�g���N�^
	~CItemManager();						//�f�X�g���N�^
public:
	static void Init();						//������
	static void Fin();						//�I������
	static void Update();					//�X�V
	static void Draw();						//�`��

	static void Create();					//�A�C�e���}�l�[�W���[�̍쐬
	static void Delete();					//�A�C�e���}�l�[�W���[�̍폜

	static ITEM_MAP* GetPointer();		//�}�l�[�W���[�f�o�C�X�̃|�C���^��n��

	static void	CleatePermit(bool ChangeFlg) { m_Delete = ChangeFlg; }		//�S�A�C�e���폜�t���O��|��
	static int	GetNextItemID() { return m_MakeItemNum;	}	//���Ɋ���U����ID��Ԃ�
	static void NextItemID(int NextID) { m_MakeItemNum = NextID; }

	//-----�A�C�e���֘A�̑���-----
	//�A�C�e����ǉ�����
	static void Add(int ItemID,CFieldItem* pItem);
	//�A�C�e�����폜����
	static void Del(int ItemID);
	//�A�C�e����T��
	static CFieldItem* Find(int ItemID);
};

