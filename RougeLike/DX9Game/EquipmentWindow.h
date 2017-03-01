#pragma once

#include "2DWindow.h"
#include "Item.h"
#include "Equipment.h"

class CEquipmentCommandWindow;
class CEquipmentWindowCursor;
class CMenuWindow;
class CItemWindow;

class CEquipmentWindow:
	public CItem,
	public C2DWindow
{
private:
	//�V���O���g��
	static CEquipmentWindow* m_pEquipmentWindow;

	LPD3DXFONT			m_Font;					//�`��p�t�H���g
	RECT				m_Pos[EQUIPMENT_NUM_MAX];	//�E�B���h�E�\���ʒu
	bool				m_bDrawFlg;				//�`��t���O
	VERTEX_2D			m_aVertex[EQUIPMENT_NUM_MAX][NUM_VERTEX];	//�|���S�����_���i�[�p

	int					m_nInterval;

	CEquipmentCommandWindow*		m_pCommandWindow;		//�R�}���h�E�C���h�E�̕`��t���O�ύX�p
	CEquipmentWindowCursor*			m_pInventoryCursor;		//�I�����Ă���A�C�e���E�C���h�E�̎擾
	CEquipment*						m_pPlayerEquipment;		//�v���C���[�̑����A�C�e���ւ̃|�C���^
	CMenuWindow*					m_pMenuWindow;			//���j���[�E�B���h�E�ւ̃|�C���^
	CItemWindow*					m_pItemWindow;			//�A�C�e���E�B���h�E�|�C���^
	CEquipmentWindow(void);							//�R���X�g���N�^
	~CEquipmentWindow(void);							//�f�X�g���N�^
public:
	static void Create();						//���̂̍쐬
	static void Delete();						//���̂̍폜
	static CEquipmentWindow* GetPointer();	//���̂̃|�C���^��n��

	void UpDate();								//�X�V��
	void Draw();								//�`��

	void DrawFlgChange();				//�`��t���O��ON/OFF����

	void SetVertex();							//�|���S�����𖄂߂�
	void SetFontPos();							//�t�H���g�`��ʒu�ݒ�

	//�`��̃t���O�󋵂��擾
	bool GetDrawFlg()	{return m_bDrawFlg;}

	//�����o�ϐ��̃|�C���^��ݒ肷��
	void SetPointer();
};

