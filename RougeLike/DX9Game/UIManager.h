#pragma once

//�S�Ă�UI�̕`��A�X�V�Ȃǂ̊Ǘ����s��

//�N���X�̒�`
class CItemWindow;					//�A�C�e���E�B���h�E
class CItemWindowCursor;			//�A�C�e���J�[�\��
class CItemCommandWindow;			//�A�C�e���R�}���h�E�B���h�E
class CItemCommandCursor;			//�R�}���h�I���J�[�\��

class CHPDraw;						//HP�̕`��

class CMenuWindow;					//���j���[�E�B���h�E
class CMenuSelect;					//���j���[�Z���N�g�J�[�\��
class CMenuWindow_Back;				//���j���[�E�B���h�E�̔w�i

class CMenuStatesWindow;			//���j���[�X�e�[�^�X�E�B���h�E

class CStatesWindow;				//�X�e�[�^�X�E�B���h�E
class CStatesCharacter;				//�L�����N�^�[�摜
class CStatesFont;					//�L�����N�^�[�X�e�[�^�X�̕���
class CStatesValue;					//�L�����N�^�[�X�e�[�^�X���l

class CEquipmentWindow;				//�����E�B���h�E
class CEquipmentWindowCursor;		//�����I���J�[�\��
class CEquipmentCommandWindow;		//�����R�}���h�E�B���h�E
class CEquipmentCommandCursor;		//�����R�}���h�J�[�\��

class CTrickWindow;					//�Z�E�B���h�E
class CTrickWindowCursor;			//�Z�J�[�\��

class COperation;					//�������
class CMiniMap;						//�~�j�}�b�v
class CMessageWindow;				//���b�Z�[�W�E�B���h�E

class CUIManager
{
private:
	//�V���O���g���ɂ��邱�ƂŁAUI�̑��d�쐬��h�~���A���j�[�N�����m��
	static CUIManager* m_pUIManager;

	//�e�Ǘ��N���X�̃|�C���^
	CItemWindow*				m_pItemWindow;
	CItemWindowCursor*			m_pItemWindowCursor;
	CItemCommandWindow*			m_pItemCommandWindow;
	CItemCommandCursor*			m_pItemCommandCursor;

	CHPDraw*					m_pHPDraw;

	CMenuWindow*				m_pMenuWindow;
	CMenuSelect*				m_pMenuSelect;
	CMenuWindow_Back*			m_pMenuBack;

	CMenuStatesWindow*			m_pMenuStatesWindow;

	CStatesWindow*				m_pStatesWindow;
	CStatesCharacter*			m_pStatesCharcter;
	CStatesFont*				m_pStatesFont;
	CStatesValue*				m_pStatesValue;

	CEquipmentWindow*			m_pEquipmentWindow;
	CEquipmentWindowCursor*		m_pEquipmentWindowCursor;
	CEquipmentCommandWindow*	m_pEquipmentCommandWindow;
	CEquipmentCommandCursor*	m_pEquipmentCommandCursor;

	CTrickWindow*				m_pTrickWindow;
	CTrickWindowCursor*			m_pTrickWindowCursor;

	COperation*					m_pOperation;
	CMiniMap*					m_pMiniMap;
	CMessageWindow*				m_pMessageWindow;

	CUIManager();						//�R���X�g���N�^
	~CUIManager();						//�f�X�g���N�^
public:
	static void Create();				//�}�l�[�W���[�̍쐬
	static void Delete();				//�}�l�[�W���[�̍폜

	static CUIManager* GetPointer();	//�}�l�W���[�|�C���^�̎擾

	void ManageUIInit();				//�eUI�̏�����
	void ManageUIUpdate();				//�eUI�̍X�V
	void ManageUIDraw();				//�eUI�̕`��	

	void ItemWindowUpdate();			//�A�C�e���E�B���h�E�̍X�V
	void ItemWindowDraw();				//�A�C�e���E�B���h�E�̕`��

	void ManageUISetPointer();			//�eUI�����o�ϐ��̃|�C���^��ݒ肷��
};