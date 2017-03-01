//���@�N���X�@��`
#pragma once

#include "Unit.h"

class CItemWindowCursor;
class CItemCommandCursor;
class CHPDraw;
class CEquipmentCommandWindow;
class CEquipmentWindowCursor;
class CStatesValue;
class CFade;
class CMenuWindow;


class CPlayer :
	public CUnit 
{
private:
	CItemWindowCursor*			m_pInventoryCursor;				//�A�C�e���E�C���h�E�̃J�[�\���̈ʒu����肷��
	CItemCommandCursor*			m_pCommandCursor;				//�R�}���h�J�[�\���̈ʒu����肷��
	CHPDraw*					m_pHPDraw;						//HP�o�[�ւ̃|�C���^
	CEquipmentCommandWindow*	m_pEquipmentCommandWindow;		//�����R�}���h�ւ̃|�C���^
	CEquipmentWindowCursor*	m_pEquipmentInventoryCursor;	//�����A�C�e���J�[�\���̃|�C���^
	CStatesValue*				m_pStatesValue;					//�X�e�[�^�X���l�`��ւ̃|�C���^
	CFade*						m_pFade;						//�t�F�[�h�ւ̃|�C���^
	CMenuWindow*				m_pMenuWindow;					//���j���[�E�B���h�E�ւ̃|�C���^
	int							m_nEquipmentInterval;			//�����R�}���h��`�悵�Ă���A���b��������
	LPD3DXFONT					m_pFont;						//�`��t�H���g�̐ݒ�
	RECT						m_FontDrawPos;					//�t�H���g�̕`��ʒu��ݒ肷��
	int							m_nRecoveryInterval;			//�񕜂���Ԋu���l
public:
	CPlayer(CGameScene* pScene);					//�R���X�g���N�^
	~CPlayer(void);								//�f�X�g���N�^

	void Update();						//�X�V����
	void Draw();						//�`��
	
	void SetFontPos();					//�����`��ʒu��ݒ�

	//�X�e�[�g�ʍX�V
	void InputUpdate();					//���͍X�V

	void MoveUpdate();					//�ړ��X�V

	void ActUpdate();					//�A�N�V�����X�V

	void ItemUpdate();					//�A�C�e���g�p�X�V
	void TurnEndUpdate();				//�^�[���I���X�V

	void SetPos();					//�ʒu�����Đݒ肷��

	//�v���C���[�̋Z�̕`��t���O���m�F
	bool GetPlayerTrickWindowFlg(){return m_pTrickWindow->GetDrawFlg();}

	//���݂̃��x����`�悷��
	void DrawLevel();

	//�����o�ϐ��̃|�C���^���擾����
	void MemberPointerGet();
};

