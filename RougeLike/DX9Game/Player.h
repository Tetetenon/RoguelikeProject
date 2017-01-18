//���@�N���X�@��`
#pragma once

#include "Unit.h"

class CInventoryCursor;
class CCommandCursor;


class CPlayer :
	public CUnit 
{
private:
	static CInventoryCursor m_InventoryCursor;		//�A�C�e���E�C���h�E�̃J�[�\���̈ʒu����肷��
	static CCommandCursor	m_CommandCursor;		//�R�}���h�J�[�\���̈ʒu����肷��

	static CTurn::GameState	m_State_Cpy;			//�X�e�[�g���O������ύX��������ۂɎg�p����
	static bool				m_bState_Change_Flg;	//�X�e�[�g�ɕύX������������

	int						m_nEquipmentInterval;	//�����R�}���h��`�悵�Ă���A���b��������

	static LPD3DXFONT		m_pFont;				//�`��t�H���g�̐ݒ�
	static RECT				m_FontDrawPos;			//�t�H���g�̕`��ʒu��ݒ肷��
	static int				m_nDividPattern;		//��������}�b�v�p�^�[��
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

	static void SetState(CTurn::GameState nState);//�O������X�e�[�g�̏�Ԃ�ύX������

	//���݂̃X�e�[�g����n��
	static int GetState();

	void	SetPos();					//�ʒu�����Đݒ肷��

	void DrawInventory();				//���g�̃A�C�e����`�悳����
	void DrawEquipment();				//���g�̑�����`�悳����
	void DrawTrick();					//���g�̋Z��`�悳����

	//�v���C���[�̋Z�̕`��t���O���m�F
	bool GetPlayerTrickWindowFlg(){return m_pTrickWindow->GetDrawFlg();}

	//���݂̃��x����`�悷��
	void DrawLevel();
};

