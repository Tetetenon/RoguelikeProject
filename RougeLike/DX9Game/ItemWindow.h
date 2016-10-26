#pragma once

#include "2DWindow.h"
#include "Item.h"

class CCommandWindow;
class CInventoryCursor;


//�����ł���ő�A�C�e����
#define ITEM_NUM_MAX 10

class CInventory:
	public CItem,
	public C2DWindow
{
private:
	CItem				m_Item[ITEM_NUM_MAX];	//�A�C�e���f�[�^(�A�C�e���̎��Ă鐔)
	LPD3DXFONT			m_Font;					//�`��p�t�H���g
	RECT				m_Pos[ITEM_NUM_MAX];	//�E�B���h�E�\���ʒu
	static bool			m_bDrawFlg;				//�`��t���O

	VERTEX_2D	m_aVertex[ITEM_NUM_MAX][NUM_VERTEX];	//�|���S�����_���i�[�p

	static CCommandWindow		m_CommandWindow;		//�R�}���h�E�C���h�E�̕`��t���O�ύX�p
	static CInventoryCursor	m_InventoryCursor;		//�I�����Ă���A�C�e���E�C���h�E�̎擾
public:
	CInventory(void);							//�R���X�g���N�^
	~CInventory(void);							//�f�X�g���N�^

	void Init();								//������
	void Fin();									//�I������

	void UpDate();								//�X�V��
	void Draw();								//�`��

	static void DrawFlgChange();				//�`��t���O��ON/OFF����

	void SetVertex();							//�|���S�����𖄂߂�
	void SetFontPos();							//�t�H���g�`��ʒu�ݒ�

	//�`��̃t���O�󋵂��擾
	static bool GetDrawFlg()	{return m_bDrawFlg;}

	bool SetItem(CItem Item);		//�X�g���[�W�ɃA�C�e�����Z�b�g

	//�w�肳�ꂽ�A�C�e���f�[�^��n��
	CItem GetItem (int Coefficient)	{return m_Item[Coefficient];}

	//�w�肳�ꂽ�A�C�e���̖��O��Ԃ�
	_TCHAR* GetInventoryItemName(int Coefficient){return m_Item[Coefficient].GetName();}

	void DelInventory(int Receipt);				//�w�肵���ԍ��̃A�C�e��������

	int GetEffect(int Receipt);					//�w�肳�ꂽ�A�C�e���̌��ʃW��������ԋp

	int GetEffectValue(int Receipt);			//�w�肳�ꂽ�A�C�e���̌��\��ԋp����

	void FindName	(int nID,int Receipt);		//ID���疼�O����������
};
