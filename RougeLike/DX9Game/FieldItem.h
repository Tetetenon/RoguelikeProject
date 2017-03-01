#pragma once

//�t�B�[���h��ɑ��݂���A�C�e���N���X

#include "meshobj.h"
#include "Item.h"
#include "MapData.h"
#include "Circle.h"

class CGameScene;				//�V�[���N���X������`
class CMapData;
class CItemManager;

class CFieldItem :
	public CMeshObj,
	public CItem
{
private:
	static int n_Debug;
	CItem			m_Item;
	D3DXVECTOR2		m_Pos;					//�z���̈ʒu���
	int				m_FieldID;				//�t�B�[���h��̃A�C�e����ID

	bool			m_ItemDelete;			//���g�̃f���[�g�t���O

	CCircle			m_Circle;				//�A�C�e���T�[�N��
	CMapData*		m_pMapData;
	CItemManager*	m_pItemManager;
public:
	CFieldItem(CGameScene* pScene);				//�R���X�g���N�^
	~CFieldItem(void);						//�f�X�g���N�^

	void Draw();							//�`�揈��
	void Update();							//�X�V
	void Fin();								//�I������

	static void Generation(CMeshObj *pGeneration);			//����
	int		GetFieldID ()	{return m_FieldID;}			//�A�C�e����ID�̎擾
	int		GetID ()		{return m_Item.GetID();}	//ID���擾
	CItem	GetItemData()	{return m_Item;}

	void	Delete();			//���g�̍폜
};