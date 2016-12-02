#include "Unit.h"
#include "GameScene.h"
#include "MessageWindow.h"
#include "TextureManager.h"
#include "MapData.h"
#include "GameState.h"
#include "Battle.h"
#include "Turn.h"
#include "DeleteObj.h"
#include "HitObj.h"
#include "Particle.h"
#include "Player.h"
#include "ItemGenerator.h"
#include "EnemyGenerator.h"
#include "TrickWindowCursor.h"
#include "MiniMap.h"

#define JUMP_INTERVAL 30	//�W�����v���Ă��玟�̃W�����v�܂ł̊Ԋu

#define _CRT_SECURE_NO_WARNINGS

#define FLASHTIME	5	//�_�Ŏ��̐؂�ւ�����
#define FLASHNUM	3	//�_�ŉ�

//�s���ɂ����鎞��
#define ACTION_TIME	0.6f

//�����x�ő�l
#define MAX_SATIETY	100

//�ÓI�����o���̒�`
int	 CUnit::m_nMakeNumber = OBJ_NUM_PLAYER;	//�����������j�b�g�̐�
int  CUnit::m_nAttackNumber = 0;				//�U�����s���Ă��郆�j�b�g�̔ԍ�
bool CUnit::m_bMoveCanFlg = true;;					//�ړ��\�t���O

float	g_Timer = 0;		//�������J�n���Ă���̎��Ԍv��
int		g_Damage = 0;		//�퓬�Ŕ�������_���[�W
//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CUnit::CUnit(CGameScene* pScene):
CMeshObj(pScene)
{
	//�V�[���N���X�̃|�C���^�擾
	m_pScene = pScene;

	//���X�g�̏�����
	m_pNextUnit = m_pBackUnit = NULL;

	//�V�[����ɃI�u�W�F�N�g�̒ǉ�
	m_pScene -> AddUnit(this);

	//��Ԃ̏�����
	m_nState = UNIT_STATE_HEALTH;	//���N
	m_nState_Turn = 0;

	//���x��������
	m_nLevel = 1;

	//�����x������
	m_nSatiety = MAX_SATIETY;

	//�_�Ŏ��ԏ�����
	m_nDrawFlashTime = 0;
	//�_�ŉ񐔏�����
	m_nFlashNum = 0;
	//�`��t���O������
	m_bDrawFlg = true;

	//�W�����v�㏸������
	m_bJump = true;
	//�W�����v�㏸�l������
	m_fJumpPos = 0.0f;
	//�W�����v�̊Ԋu������
	m_nJumpInterval = 0;
	//�W�����v�J�n�t���O������
	m_bJumpFlg = false;

	//�A�C�e���C���x���g���|�C���^���擾
	m_pInventory = new CInventory();
	//�����C���x���g���|�C���^���擾
	m_pEquipment = new CEquipmentInventory();

	//�Z�E�B���h�E�|�C���^���擾
	m_pTrickWindow = new CTrickWindow();

	//���x���A�b�v�|�C���^�̏�����
	m_pLevelUp = NULL;

	//�Z�ԍ��̏�����
	m_nTrickNumber = TRICK_NAME_MAX + 1;
	
	//�퓬���s���G�̃|�C���^�̏�����
	m_pBattleUnit = NULL;
	m_pBattleNext = NULL;
	m_pBattleBack = NULL;

	//�����Ă�������̏�����
	for(int i = 0;i < MaxDirection;i++)
	{
		m_bDirectionFlg[i] = false;
	}
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CUnit::~CUnit(void)
{
	//�A�C�e���C���x���g���̃|�C���^���폜
	delete m_pInventory;

	//�����C���x���g���̃|�C���^���폜
	delete m_pEquipment;

	//�Z�E�B���h�E�|�C���^�̍폜
	delete m_pTrickWindow;

	//���x���A�b�v�|�C���^�̒��g������΁A�폜
	if(m_pLevelUp != NULL)
	{
		delete m_pLevelUp;
		m_pLevelUp = NULL;
	}
	
	//�퓬���s���G�̃|�C���^�̏�����
	m_pBattleUnit = NULL;
	m_pBattleNext = NULL;
	m_pBattleBack = NULL;

	//�V�[���ォ�玩�g�̃��j�b�g�|�C���^���폜����
	m_pScene ->DelUnit(this);
}

	
//---------------------------------------------------------------------------------------
//������
//---------------------------------------------------------------------------------------
void CUnit::Init()
{
	//�A�C�e���C���x���g���̏�����
	m_pInventory ->Init();
	//�����C���x���g���̏�����
	m_pEquipment->Init();

	//�Z�C���x���g���̏�����
	m_pTrickWindow->Init();
}

//---------------------------------------------------------------------------------------
//�I��
//---------------------------------------------------------------------------------------
void CUnit::Fin()
{

	//�}�[�L���O����
	CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);
	
	//���ݎ������I�����Ă���X�e�[�g�̃��j�b�g�̐�-1
	CTurn::SumCount(m_nStateNumber);

	//������������������
	m_nMakeNumber = OBJ_NUM_PLAYER;

	//���g�̍폜
	delete this;
}

//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CUnit::Update()
{

	//���x���A�b�v�|���S���̍X�V
	if(m_pLevelUp != NULL)
	{
		m_pLevelUp->Update(D3DXVECTOR3(m_world._41,m_world._42,m_world._43));

		//�㏸�l�����𒴂�����폜
		if(m_pLevelUp->GetUpPos() >= 255.0f)
		{
			delete m_pLevelUp;
			m_pLevelUp = NULL;
		}
	}
	//���j�b�g�T�[�N���̈ʒu����ݒ�
	m_Circle.SetPos(C3DObj::GetPos());

	//���݂̃v���C���[�̃X�e�[�g�����擾
	int nPlayerState = CPlayer::GetState();

	if(nPlayerState == m_nStateNumber)
	{
		int Debug = 0;
	}


	int State = CTurn::GetState();	//�X�e�[�g�����ꎞ�I�Ɋi�[
	
	//���݂̃X�e�[�g��I�����Ă��郆�j�b�g�̐���I������
	int StateSelectNum = CTurn::GetStateSelectNum(State);

	//�������݂̃X�e�[�g��I�����Ă��郆�j�b�g�����݂��Ȃ���΁A���̃X�e�[�g���X�L�b�v����
	if(StateSelectNum == 0)
		CTurn::State_Advance(State + 1);

	//�ҋ@���A���ł���悤�ȃ��[�V�������s��
	if(m_bJumpFlg)
	{
		//�㏸�t���O�������Ă���Ώ㏸
		if(m_bJump)
			m_fJumpPos += 0.03f;
		//�����Ă��Ȃ���Ή��~
		else
			m_fJumpPos -= 0.02f;

		//�㏸�ő�n�_�܂ōs���Ή��~����
		if(m_fJumpPos >= 0.5)
			m_bJump = false;
		//���n����΁A�W�����v�t���O��|��
		if(m_fJumpPos <= 0)
		{
			m_bJumpFlg = false;
			m_bJump = true;
		}
	}

	//�W�����v�t���O�������Ă��Ȃ��ꍇ�A���̃W�����v�܂ł̎��Ԃ��v������
	if(!m_bJumpFlg)
	{
		m_nJumpInterval ++;

		if(m_nJumpInterval >= JUMP_INTERVAL)
		{
			m_nJumpInterval = 0;
			m_bJumpFlg = true;
		}
	}

	//���[���h�}�g���b�N�X���烍�[�J�������o�A���W���o
	D3DXMATRIX world = GetWorld();

	world._42 = 0.0f;	//���_�ֈړ�������

	world._42 = m_fJumpPos;

	//���[���h�}�g���b�N�X��ݒ�
	SetWorld(world);

	//�����A�s���\�t���O�������Ă��Ȃ���΁A�������X�L�b�v
	if(!m_bMoveCanFlg)
		return;

	//���݂̃^�[�����A���g�̃^�[���ł���΍X�V���s��
	if(m_nStateNumber == State)
	{
		//���g�Ɠ����X�e�[�g�Ƀv���C���[�����݂���ꍇ�A�v���C���[���ɏ������邽�߁A�X�L�b�v
		//���g���v���C���[�̏ꍇ�A�������X���\
		if(m_nStateNumber != nPlayerState || m_nUnitNumber == OBJ_NUM_PLAYER)
		{
			//��Ԉُ�̌o�ߎ��Ԃ����炷
			//���g�̃^�[�����n�܂������m�F����
			if(m_nStateNumber != m_nOldStateNumber)
			{
				//���͑҂���Ԃł̂ݏ�������
				if(m_nStateNumber <= GAME_STATE_STAND_BY_OTHER)
				{
					//���g����Ԉُ�ɂȂ��Ă��邩�m�F����
					if(m_nState_Turn != 0)
						//��Ԉُ�̏���
						TurnStartStateProcessing();
				}
			}

			//���X�e�[�g���̊m��
			m_nOldStateNumber = m_nStateNumber;

			//�X�e�[�g��Ԃɂ���ď����𕪊򂳂���
			switch(State)
			{
			//���͑҂�(�v���C���[)
			case GAME_STATE_STAND_BY_PLAYER:
				InputUpdate();
				break;

			//���͑҂�(�G�l�~�[)
			case GAME_STATE_STAND_BY_OTHER:
				InputUpdate();
				break;
				
			//�A�C�e��
			case GAME_STATE_ITEM_USE:
				ItemUpdate();
				break;
				
			//�ړ�
			case GAME_STATE_MOVE:
				MoveUpdate();
				break;
				
			//�A�N�V����
			case GAME_STATE_ACT:
				ActUpdate();
				break;
				
			//�U��
			case GAME_STATE_ATTACK:
				AttackUpdate();
				break;

			//�^�[���I��
			case GAME_STATE_TURN_END:
				TurnEndUpdate();
				break;
			}
		}
	}

	//�A�C�e���E�B���h�E��`�悵�Ă�����
	if(CInventory::GetDrawFlg())
		//�A�C�e���C���x���g���̍X�V
		m_pInventory->UpDate();

	//�����E�B���h�E��`�悵�Ă�����
	if(CEquipmentInventory::GetDrawFlg())
		//�����C���x���g���̍X�V
		m_pEquipment ->UpDate();

	//�Z�E�B���h�E��`�悵�Ă�����
	if(CTrickWindow::GetDrawFlg())
		//�Z�E�B���h�E�̍X�V
		m_pTrickWindow->UpDate();
}
	
//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CUnit::Draw()
{
	//���g�̕`��t���O�������Ă��邩
	if(m_bDrawFlg)
	{
		//�����Ă���΁A�`����s��

		//�e�N���X�̕`�揈�����s��
		CMeshObj::Draw();

		//���j�b�g�T�[�N���̕`��
		m_Circle.Draw(m_nUnitNumber);

		//���x���A�b�v�|���S���̃|�C���^�̒��g������΁A�`��
		if(m_pLevelUp != NULL)
		{
			m_pLevelUp ->Draw();
		}

	}
}
//---------------------------------------------------------------------------------------
//���j�b�g�̌���
//---------------------------------------------------------------------------------------
CUnit* CUnit::FindUnit(UINT uID,CUnit* p)
{
	//�V�[���I�u�W�F�N�g�����݂��Ȃ���΁A�ق��̃I�u�W�F�N�g�����݂��Ȃ�����
	//�����ōŏ��ɔ��������
	if(m_pScene)
		return m_pScene -> FindUnit(uID,p);
	return NULL;
}

//---------------------------------------------------------------------------------------
//�A�C�e������
//---------------------------------------------------------------------------------------
CFieldItem* CUnit::ItemFind(UINT uID,CFieldItem* p)
{
	//�V�[���I�u�W�F�N�g�����݂��Ȃ���΁A�ق��̃I�u�W�F�N�g�����݂��Ȃ�����
	//�����ōŏ��ɔ��������
	if(m_pScene)
		return m_pScene -> FindItem(uID,p);
	return NULL;
}

//---------------------------------------------------------------------------------------
//���͍X�V
//---------------------------------------------------------------------------------------
void CUnit::InputUpdate()
{

}

//---------------------------------------------------------------------------------------
//�ړ��X�V
//---------------------------------------------------------------------------------------
void CUnit::MoveUpdate()
{
}

//---------------------------------------------------------------------------------------
//�A�N�V�����X�V
//---------------------------------------------------------------------------------------
void CUnit::ActUpdate()
{

}
//---------------------------------------------------------------------------------------
//�U���X�V
//---------------------------------------------------------------------------------------
void CUnit::AttackUpdate()
{
	//���ݒN���U���A�j���[�V�������s���Ă��Ȃ��A���͎��g���U���A�j���[�V�������s���Ă���ꍇ�̂ݍX�V����
	if(m_nUnitNumber == m_nAttackNumber || m_nAttackNumber == 0)
	{
		//���g���U���A�j���[�V�������s���Ă���悤�A�ݒ肷��
		m_nAttackNumber = m_nUnitNumber;

		//���݂̐퓬�X�e�[�g���擾����
		int nBattleState = CTurn::GetBattleState();

	//���݂̐퓬�X�e�[�g��Ԃɂ���āA�X�V���e�𕪊򂳂���
	switch(nBattleState)
	{
		//����̕����ɓˌ�����
	case BATTLE_STATE_GO:
		BattleGo();
		break;
		
		//���̈ʒu����{���̈ʒu�ւƖ߂�
	case BATTLE_STATE_RETURN:
		BattleReturn();
		break;

		//����̌����A�_���[�W�̌v�Z
	case BATTLE_STATE_SEARCH:
		AttackSwitch();
		break;

		//����ɍU������������
	case BATTLE_STATE_HIT:
			BattleHit();
		break;
		
		//�_���[�W�󂯂��\�����s��
	case BATTLE_STATE_FLASHING:
			BattleFlasing();
		break;
		
		//���b�Z�[�W�E�C���h�E�Ƀ_���[�W���ʂ𑗂�
	case BATTLE_STATE_WINDOW:
			BattleWindow();
		break;

		//�Z�o���ꂽ�_���[�W�����ۂɑ��肩�猸�炷
	case BATTLE_STATE_DAMAGE:
			BattleDamage();
		break;

		//�퓬�I���A�X�e�[�g�֘A�̐ݒ�
	case BATTLE_STATE_END:
			BattleEnd();
		break;
	}
	}
}

//---------------------------------------------------------------------------------------
//�A�C�e���X�V
//---------------------------------------------------------------------------------------
void CUnit::ItemUpdate()
{

}
//---------------------------------------------------------------------------------------
//�^�[���I���X�V
//---------------------------------------------------------------------------------------
void CUnit::TurnEndUpdate()
{

}

//---------------------------------------------------------------------------------------
//HP�����炷
//---------------------------------------------------------------------------------------
void CUnit::DamegeHP (int Damage)
{
	m_nHP -= Damage;	//�̗͂����炷

	//�����̗͂�0�ȉ��Ȃ�΁A���S���b�Z�[�W���o������
	if(m_nHP <= 0)
	{
		//�\������-�\�L�ɂȂ�Ȃ��悤
		m_nHP = 0;
		//���b�Z�[�W�\�L
		TCHAR	str[256];
		_stprintf_s(str,sizeof(str), _T("%s�͓|�ꂽ!"),m_szName);
	
		//���b�Z�[�W�e�X�g
		MessageWindow::SetMassege(str);
	}
	//�v���C���[��HP���������ꍇ�A��ʂ�HP�\����ύX
	if(m_uID == ID_PLAYER)
	{
		//��ʂɕ`�悵�Ă��炤HP�̐��l��n��
		CHPDraw::SetHP(m_nHP);
	}
}

//---------------------------------------------------------------------------------------
//HP���񕜂�����
//---------------------------------------------------------------------------------------
void CUnit::RecoveryHP (int Recovery)
{
	m_nHP += Recovery;	//�̗͉�

	//�̗͂̏���𒴂��Ȃ��悤�ɂ���
	if(m_nHP > m_nMaxHP)
		m_nHP = m_nMaxHP;
	
	//���b�Z�[�W�\�L
	TCHAR	str[256];
	_stprintf_s(str,sizeof(str),_T("%d�񕜂���!"),Recovery);
	//���b�Z�[�W�o��
	MessageWindow::SetMassege(str);

	//�v���C���[��HP���������ꍇ�A��ʂ�HP�\����ύX
	if(m_uID == ID_PLAYER)
	{
		//��ʂɕ`�悵�Ă��炤HP�̐��l��n��
		CHPDraw::SetHP(m_nHP);
	}
}

//---------------------------------------------------------------------------------------
//���g�̍폜
//---------------------------------------------------------------------------------------
void CUnit::Delete()
{
	//�}�[�L���O����
	CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);
	
	//���ݎ������I�����Ă���X�e�[�g�̃��j�b�g�̐�-1
	CTurn::SumCount(m_nStateNumber);

	m_bSurvival = false;

	//�v���C���[�ł������ꍇ�A�V�[�������U���g�ɑJ�ڂ�����
	if(m_uID == ID_PLAYER)
	{
		//�Q�[�����C�����I��
		CFade::ChangeState(FADEMODE_OUT);

		//�Q�[���N���A��Ԃ��Q�[���I�[�o�[��
		CGameScene::GameClearStateChange(GAME_OVER);

		//�G�l�~�[�̐������̃��Z�b�g
		CEnemyGenerator::ResetMakeEnemyNum();

		//�t�B�[���h�A�C�e���������̃��Z�b�g
		CItemGenerator::ResetMakeItemNum();
	}

	//�v���C���[�ȊO�̏ꍇ����
	if(m_uID != ID_PLAYER)
	{
		//���g�̍폜
		delete this;
	}
}
//---------------------------------------------------------------------------------------
//���O�̎擾
//---------------------------------------------------------------------------------------
char* CUnit::GetName(char* pName)
{
	pName = m_szName;

	return pName;
}

//---------------------------------------------------------------------------------------
//���ʂ֓ˌ�������
//---------------------------------------------------------------------------------------
void CUnit::BattleGo()
{

	//�X�e�[�g�o�ߎ��ԉ��Z
	CTurn::TimeStateAdd();

	//���݂̃X�e�[�g�i�s
	int nStateTime = CTurn::GetStateTime();

	//���݂̓ˌ�����
	float fAttackPar = (float)nStateTime / STATE_TIME;

	//�ˌ������̐ݒ�

	//�ˌ��������
	float fAttackPosX = 0.0f;
	float fAttackPosZ = 0.0f;
	//������ɓˌ����邩�̃`�F�b�N
	if(m_bDirectionFlg[Forword])
	{
		//��֓ˌ�
		fAttackPosZ--;
	}
	//�������ɓˌ����邩�̃`�F�b�N
	if(m_bDirectionFlg[Back])
	{
		//���֓ˌ�
		fAttackPosZ++;
	}
	//�E�����ɓˌ����邩�̃`�F�b�N
	if(m_bDirectionFlg[Right])
	{
		//�E�֓ˌ�
		fAttackPosX++;
	}
	//�������ɓˌ����邩�̃`�F�b�N
	if(m_bDirectionFlg[Left])
	{
		//���֓ˌ�
		fAttackPosX--;
	}
	
	//���݂̐i��ł��銄�����v�Z
	fAttackPosX *= fAttackPar;
	fAttackPosZ *= fAttackPar;

	//���[���h�}�g���b�N�X���烍�[�J�������o�A���W���o
	D3DXMATRIX world = GetWorld();
	
	//�ʒu���ݒ�
	world._41 = ((m_nUnit_Pos_X + fAttackPosX) - (MAP_SIZE / 2)) * GRIDSIZE + GRIDSIZE / 2;
	world._42 = 0.0f;
	world._43 = -((m_nUnit_Pos_Z + fAttackPosZ) - (MAP_SIZE / 2)) * GRIDSIZE - GRIDSIZE / 2;
	
	//���[���h�}�g���b�N�X��ݒ�
	SetWorld(world);

	//����o�ߎ��Ԃ𒴂�����X�e�[�g�J��
	if(CTurn::GetStateTime() >= STATE_TIME)
	{
		//�퓬�X�e�[�g��i�߂�
		CTurn::BattleState_Advance(BATTLE_STATE_RETURN);

		//�X�e�[�g���Z�b�g
		CTurn::TimeStateReset();
	}
}

//---------------------------------------------------------------------------------------
//�ˌ���������̈ʒu���玩�g�̖{���̈ʒu�֖߂�
//---------------------------------------------------------------------------------------
void CUnit::BattleReturn()
{
	//�X�e�[�g�o�ߎ��ԉ��Z
	CTurn::TimeStateAdd();
	
	//���݂̃X�e�[�g�i�s
	int nStateTime = CTurn::GetStateTime();

	//���݂̓ˌ�����
	float fAttackPar = (float)nStateTime / STATE_TIME;

	//�ˌ��������
	float fAttackPosX = 0.0f;
	float fAttackPosZ = 0.0f;
	//������ɓˌ����邩�̃`�F�b�N
	if(m_bDirectionFlg[Forword])
	{
		//��֓ˌ�
		fAttackPosZ--;
	}
	//�������ɓˌ����邩�̃`�F�b�N
	if(m_bDirectionFlg[Back])
	{
		//���֓ˌ�
		fAttackPosZ++;
	}
	//�E�����ɓˌ����邩�̃`�F�b�N
	if(m_bDirectionFlg[Right])
	{
		//�E�֓ˌ�
		fAttackPosX++;
	}
	//�������ɓˌ����邩�̃`�F�b�N
	if(m_bDirectionFlg[Left])
	{
		//���֓ˌ�
		fAttackPosX--;
	}
	
	//���݂̐i��ł��銄�����v�Z
	fAttackPosX *= (1 - fAttackPar);
	fAttackPosZ *= (1 - fAttackPar);

	//���[���h�}�g���b�N�X���烍�[�J�������o�A���W���o
	D3DXMATRIX world = GetWorld();
	
	//�ʒu���ݒ�
	world._41 = ((m_nUnit_Pos_X + fAttackPosX) - (MAP_SIZE / 2)) * GRIDSIZE + GRIDSIZE / 2;
	world._42 = 0.0f;
	world._43 = -((m_nUnit_Pos_Z + fAttackPosZ) - (MAP_SIZE / 2)) * GRIDSIZE - GRIDSIZE / 2;

	//���[���h�}�g���b�N�X��ݒ�
	SetWorld(world);

	//����o�ߎ��Ԃ𒴂�����X�e�[�g�J��
	if(CTurn::GetStateTime() >= STATE_TIME)
	{
		//�Z�ԍ��̐ݒ肪����Ă��Ȃ���΁A�ݒ肷��
		if(m_nTrickNumber > TRICK_NAME_MAX)
		{
			//�Z��ID���擾����
			m_nTrickNumber = m_pTrickWindow->GetRange(CTrickWindowCursor::GetTrickNum());
		}
		//�퓬�X�e�[�g��i�߂�
		CTurn::BattleState_Advance(BATTLE_STATE_SEARCH);

		//�X�e�[�g���Z�b�g
		CTurn::TimeStateReset();
	}
}
//---------------------------------------------------------------------------------------
//�Z�͈̔͂���A�U�����鑊��𕪊򂳂���
//---------------------------------------------------------------------------------------
void CUnit::AttackSwitch()
{
	//�U������ۂ̋Z�͈̔͂ŁA�U���p�^�[����ω�������
	switch(m_nTrickNumber)
	{
		//���ʂ݂̂ɍU�����s��
	case TRICK_RANGE_FRONT:
		AttackFront();
		break;
		//�O���O�}�X�̓G�ɍU�����s��
	case TRICK_RANGE_WIDE:
		AttackWide();
		break;
	case TRICK_RANGE_ALL:
		//�����̓G���ׂĂɍU�����s��
		AttackAll();
		break;

		//���g�Ɍ��ʂ��y�ڂ�
	case TRICK_RANGE_ME:
		switch(m_pTrickWindow->GetEffect(CTrickWindowCursor::GetTrickNum()))
		{
		case TRICK_EFFECT_STATES_UP:

			//�X�e�[�^�X���㏸������
			m_nAttack ++;
			m_nDefence ++;

			MessageWindow::SetMassege(_T("�X�e�[�^�X���㏸����!"));
			break;
		case TRICK_EFFECT_RECOVERY:

			//������񕜂����
			int nRecoveryHP = m_nMaxHP / 2;

			//HP�𔼕��񕜂���
			RecoveryHP(nRecoveryHP);
			break;
		}
		//�X�e�[�g��i�߂�
		CTurn::BattleState_Advance(BATTLE_STATE_END);
		break;
		//�f�o�b�O
	case TRICK_RANGE_MAX:
		break;
	}
}
//---------------------------------------------------------------------------------------
//�퓬�Ŕ�������_���[�W�ʂ̎Z�o���s��
//---------------------------------------------------------------------------------------
void CUnit::BattleCalculation(CUnit *BattleUnit)
{
	//�U���͂�ϓ������邽�߁A�R�s�[
	int nAttack = m_nAttack;
	//�N���e�B�J������
	//5%�̊m���ŃN���e�B�J�����o��
	if(rand()%20 == 0)
	{
		nAttack = static_cast<int>(nAttack*1.5f);
		
		//���b�Z�[�W�\�L
		MessageWindow::SetMassege( _T("�}���ɓ�������!"));
	}

	//�_���[�W�v�Z(�����̒l���v�Z�ɓ����)
	g_Damage = CBattle::DamageCalculation(nAttack + m_pEquipment->GetAttackTotalValue(),BattleUnit -> GetDF() + BattleUnit -> GetEquipmentDefenceNum());
}

//---------------------------------------------------------------------------------------
//�G�̒T�����s��
//---------------------------------------------------------------------------------------
bool CUnit::FindEnemy(int PosX,int PosZ)
{
	//�}�b�v�̏����擾����
	int MapSituation;
	//�U�����Ă���ʒu�̏�Ԏ擾
	MapSituation = CMapData::Get_UnitMapSituation(PosX,PosZ);

	//�U���ʒu�ɃG�l�~�[�����邩�m�F����
	//�퓬���s�����j�b�g�̏��̏������s��
	if(MapSituation > 0 && MapSituation != m_nUnitNumber)
	{
		//���ꂩ��ǉ�����퓬���j�b�g
		CUnit *BattleUnit = NULL;

		//�퓬���郆�j�b�g�̌���
		BattleUnit = (CUnit*)FindUnit(MapSituation);

		//�퓬�_���[�W�̌v�Z���s��
		BattleCalculation(BattleUnit);

		//�q�b�g�I�u�W�F�N�g�̍쐬
		CHitObj::Generation(BattleUnit);

		//�퓬���s�����j�b�g���A�퓬���j�b�g���X�g�ɒǉ�����B

		//�퓬���j�b�g���X�g�̋󂫂�����Ƃ���܂ňړ�����
		//���݊m�F���Ă��郆�j�b�g
		CUnit* NowUnit = m_pBattleUnit;

		//���g�����݂��邩�`�F�b�N
		if(m_pBattleUnit)
		{
			while(NowUnit ->m_pBattleNext)
			{
				NowUnit = NowUnit->m_pBattleNext;
			}

			//�Ō���ɐ퓬���s�����j�b�g��ǉ�����
			NowUnit ->m_pBattleNext = BattleUnit;
			BattleUnit->m_pBattleBack = NowUnit;
			BattleUnit->m_pBattleNext = NULL;
		}
		//���g���Ȃ�(���߂ēG���q�b�g����)
		else
		{
			m_pBattleUnit = BattleUnit;
			BattleUnit->m_pBattleBack = NULL;
			BattleUnit->m_pBattleNext = NULL;
		}


		return true;
	}
	return false;

}
//---------------------------------------------------------------------------------------
//�w�肵���ʒu�̓G�ɍU�����s��
//---------------------------------------------------------------------------------------
bool CUnit::Attack(int CorrectionPosX,int CorrectionPosY)
{
	//���j�b�g�̍U���������z��ʒu
	int Direction_X = m_nUnit_Pos_X;
	int Direction_Z = m_nUnit_Pos_Z;

	//�G�̒T�����s���A���̌��ʂ�ϐ��Ƃ���
	return FindEnemy(Direction_X,Direction_Z);
}
//---------------------------------------------------------------------------------------
//���ʂ̓G�ɍU�����s��
//---------------------------------------------------------------------------------------
bool CUnit::FrontFind()
{
	//���j�b�g�̍U���������z��ʒu
	int Direction_X = m_nUnit_Pos_X;
	int Direction_Z = m_nUnit_Pos_Z;

	//���j�b�g�̌�������U�����Ă���ʒu��ݒ�
	if(m_bDirectionFlg[Forword])
		Direction_Z --;
	if(m_bDirectionFlg[Back])
		Direction_Z ++;

	if(m_bDirectionFlg[Right])
		Direction_X ++;

	if(m_bDirectionFlg[Left])
		Direction_X--;

	//�G�̒T�����s���A���̌��ʂ�ϐ��Ƃ���
	return FindEnemy(Direction_X,Direction_Z);
}
//---------------------------------------------------------------------------------------
//�E�̓G�ɍU�����s��
//---------------------------------------------------------------------------------------
bool CUnit::Side_Right()
{
	//���j�b�g�̍U���������z��ʒu
	int Direction_X = m_nUnit_Pos_X;
	int Direction_Z = m_nUnit_Pos_Z;

	//���j�b�g�̌�������U�����Ă���ʒu��ݒ�
	if(m_bDirectionFlg[Forword])
		Direction_X ++;
	if(m_bDirectionFlg[Back])
		Direction_X --;

	if(m_bDirectionFlg[Right])
		Direction_Z ++;

	if(m_bDirectionFlg[Left])
		Direction_Z --;

	//�G�̒T�����s���A���̌��ʂ�ϐ��Ƃ���
	return FindEnemy(Direction_X,Direction_Z);
}
//---------------------------------------------------------------------------------------
//���̓G�ɍU�����s��
//---------------------------------------------------------------------------------------
bool CUnit::Side_Left()
{
	//���j�b�g�̍U���������z��ʒu
	int Direction_X = m_nUnit_Pos_X;
	int Direction_Z = m_nUnit_Pos_Z;

	//���j�b�g�̌�������U�����Ă���ʒu��ݒ�
	if(m_bDirectionFlg[Forword])
		Direction_X --;
	if(m_bDirectionFlg[Back])
		Direction_X ++;

	if(m_bDirectionFlg[Right])
		Direction_Z --;

	if(m_bDirectionFlg[Left])
		Direction_Z ++;

	//�G�̒T�����s���A���̌��ʂ�ϐ��Ƃ���
	return FindEnemy(Direction_X,Direction_Z);
}
//---------------------------------------------------------------------------------------
//���̓G�ɍU�����s��
//---------------------------------------------------------------------------------------
bool CUnit::BackFind()
{
	//���j�b�g�̍U���������z��ʒu
	int Direction_X = m_nUnit_Pos_X;
	int Direction_Z = m_nUnit_Pos_Z;

	//���j�b�g�̌�������U�����Ă���ʒu��ݒ�
	if(m_bDirectionFlg[Forword])
		Direction_Z ++;

	if(m_bDirectionFlg[Back])
		Direction_Z --;

	if(m_bDirectionFlg[Right])
		Direction_X --;

	if(m_bDirectionFlg[Left])
		Direction_X++;

	//�G�̒T�����s���A���̌��ʂ�ϐ��Ƃ���
	return FindEnemy(Direction_X,Direction_Z);
}
//---------------------------------------------------------------------------------------
//�΂߉E�̓G�ɍU��
//---------------------------------------------------------------------------------------
bool CUnit::SlightRight()
{
	//���j�b�g�̍U���������z��ʒu
	int Direction_X = m_nUnit_Pos_X;
	int Direction_Z = m_nUnit_Pos_Z;

	//���j�b�g�̌�������U�����Ă���ʒu��ݒ�
	if(m_bDirectionFlg[Forword])
		Direction_Z --;
	if(m_bDirectionFlg[Back])
		Direction_Z ++;

	if(m_bDirectionFlg[Right])
		Direction_X ++;

	if(m_bDirectionFlg[Left])
		Direction_X--;

	//���g�̎΂߉E�ɍU������
	if(m_bDirectionFlg[Forword])
	{
		if(m_bDirectionFlg[Right])
			Direction_Z ++;
		else
			Direction_X ++;
	}
	if(m_bDirectionFlg[Back])
	{
		if(m_bDirectionFlg[Left])
			Direction_Z --;
		else
			Direction_X --;
	}

	if(!m_bDirectionFlg[Forword] && !m_bDirectionFlg[Back])
	{
		if(m_bDirectionFlg[Right])
		{
			Direction_Z++;
		}
		if(m_bDirectionFlg[Left])
		{
			Direction_Z--;
		}
	}
	
	//�G�̒T�����s���A���̌��ʂ�ϐ��Ƃ���
	return FindEnemy(Direction_X,Direction_Z);
}
//---------------------------------------------------------------------------------------
//�΂ߍ��̓G�ɍU��
//---------------------------------------------------------------------------------------
bool CUnit::SlightLeft()
{
	//���j�b�g�̍U���������z��ʒu
	int Direction_X = m_nUnit_Pos_X;
	int Direction_Z = m_nUnit_Pos_Z;

	//���j�b�g�̌�������U�����Ă���ʒu��ݒ�
	if(m_bDirectionFlg[Forword])
		Direction_Z --;
	if(m_bDirectionFlg[Back])
		Direction_Z ++;

	if(m_bDirectionFlg[Right])
		Direction_X ++;

	if(m_bDirectionFlg[Left])
		Direction_X--;

	//���g�̎΂߉E�ɍU������
	if(m_bDirectionFlg[Forword])
	{
		if(m_bDirectionFlg[Left])
			Direction_Z ++;
		else
			Direction_X --;
	}
	if(m_bDirectionFlg[Back])
	{
		if(m_bDirectionFlg[Right])
			Direction_Z --;
		else
			Direction_X ++;
	}

	if(!m_bDirectionFlg[Forword] && !m_bDirectionFlg[Back])
	{
		if(m_bDirectionFlg[Right])
		{
			Direction_Z--;
		}
		if(m_bDirectionFlg[Left])
		{
			Direction_Z++;
		}
	}

	//�G�̒T�����s���A���̌��ʂ�ϐ��Ƃ���
	return FindEnemy(Direction_X,Direction_Z);
}
//---------------------------------------------------------------------------------------
//�΂߉E���̓G�ɍU��
//---------------------------------------------------------------------------------------
bool CUnit::SlightRightBack()
{
	//���j�b�g�̍U���������z��ʒu
	int Direction_X = m_nUnit_Pos_X;
	int Direction_Z = m_nUnit_Pos_Z;

	//���j�b�g�̌�������U�����Ă���ʒu��ݒ�
	if(m_bDirectionFlg[Forword])
		Direction_Z ++;

	if(m_bDirectionFlg[Back])
		Direction_Z --;

	if(m_bDirectionFlg[Right])
		Direction_X --;

	if(m_bDirectionFlg[Left])
		Direction_X ++;

	//���g�̎΂߉E�ɍU������
	if(m_bDirectionFlg[Forword])
	{
		if(m_bDirectionFlg[Left])
			Direction_Z ++;
		else
			Direction_X --;
	}
	if(m_bDirectionFlg[Back])
	{
		if(m_bDirectionFlg[Right])
			Direction_Z --;
		else
			Direction_X ++;
	}

	if(!m_bDirectionFlg[Forword] && !m_bDirectionFlg[Back])
	{
		if(m_bDirectionFlg[Right])
		{
			Direction_Z--;
		}
		if(m_bDirectionFlg[Left])
		{
			Direction_Z++;
		}
	}

	//�G�̒T�����s���A���̌��ʂ�ϐ��Ƃ���
	return FindEnemy(Direction_X,Direction_Z);
}
//---------------------------------------------------------------------------------------
//�΂ߍ����̓G�ɍU��
//---------------------------------------------------------------------------------------
bool CUnit::SlightLeftBack()
{
	//���j�b�g�̍U���������z��ʒu
	int Direction_X = m_nUnit_Pos_X;
	int Direction_Z = m_nUnit_Pos_Z;

	//���j�b�g�̌�������U�����Ă���ʒu��ݒ�
	if(m_bDirectionFlg[Forword])
		Direction_Z ++;
	if(m_bDirectionFlg[Back])
		Direction_Z --;

	if(m_bDirectionFlg[Right])
		Direction_X --;

	if(m_bDirectionFlg[Left])
		Direction_X ++;

	//���g�̎΂߉E�ɍU������
	if(m_bDirectionFlg[Forword])
	{
		if(m_bDirectionFlg[Left])
			Direction_Z ++;
		else
			Direction_X --;
	}
	if(m_bDirectionFlg[Back])
	{
		if(m_bDirectionFlg[Right])
			Direction_Z --;
		else
			Direction_X ++;
	}

	if(!m_bDirectionFlg[Forword] && !m_bDirectionFlg[Back])
	{
		if(m_bDirectionFlg[Right])
		{
			Direction_Z--;
		}
		if(m_bDirectionFlg[Left])
		{
			Direction_Z++;
		}
	}

	//�G�̒T�����s���A���̌��ʂ�ϐ��Ƃ���
	return FindEnemy(Direction_X,Direction_Z);
}
//---------------------------------------------------------------------------------------
//���ʂ̓G�݂̂ɍU�����s��
//---------------------------------------------------------------------------------------
void CUnit::AttackFront()
{
	//���ʂɃG�l�~�[�����邩�m�F����
	//�퓬���s�����j�b�g�̏��̏������s��
	if(FrontFind())
	{
		//�퓬�X�e�[�g��i�߂�
		CTurn::BattleState_Advance(BATTLE_STATE_HIT);
	}

	//�U����Ƀ��j�b�g�����݂��Ȃ�����
	else
	{
		//���b�Z�[�W�\�L
		TCHAR	str[256];
		_stprintf_s(str, _T("%s�̍U���͊O�ꂽ"),m_szName);
		
		//���b�Z�[�W�e�X�g
		MessageWindow::SetMassege(str);

		//�X�e�[�g��i�߂�
		CTurn::BattleState_Advance(BATTLE_STATE_END);
	}

	//�X�e�[�g���Z�b�g
	CTurn::TimeStateReset();
}
//---------------------------------------------------------------------------------------
//�O���O�}�X�̓G�ɍU�����s��
//---------------------------------------------------------------------------------------
void CUnit::AttackWide()
{
	bool bFront = FrontFind();
	bool bRight = SlightRight();
	bool bLeft = SlightLeft();

	//���ʂɃG�l�~�[�����邩�m�F����
	//�퓬���s�����j�b�g�̏��̏������s��
	if(bFront || bRight || bLeft)
	{
		//�퓬�X�e�[�g��i�߂�
		CTurn::BattleState_Advance(BATTLE_STATE_HIT);
	}

	//�U����Ƀ��j�b�g�����݂��Ȃ�����
	else
	{
		//���b�Z�[�W�\�L
		TCHAR	str[256];
		_stprintf_s(str, _T("%s�̍U���͊O�ꂽ"),m_szName);
		
		//���b�Z�[�W�e�X�g
		MessageWindow::SetMassege(str);

		//�X�e�[�g��i�߂�
		CTurn::BattleState_Advance(BATTLE_STATE_END);
	}

	//�X�e�[�g���Z�b�g
	CTurn::TimeStateReset();

}
//---------------------------------------------------------------------------------------
//�����̓G���ׂĂɍU�����s��
//---------------------------------------------------------------------------------------
void CUnit::AttackAll()
{
	//�G��̈ȏ�ɍU�����q�b�g������
	bool bHitFlg = false;

	//���g�����镔���ԍ����擾����
	int nMyRoomNumber = CMapData::GetRoomNumber(m_nUnit_Pos_X,m_nUnit_Pos_Z);

	//���g�������ɂ���ꍇ�A�����̒��̓G�̒T�����s��
	if(!(nMyRoomNumber >= ROOM_MAX_NUM))
	{
		//�����̊Ԏ����󂯎��
		RECT MyRoomData = CMapData::GetRoomFloorPlan(nMyRoomNumber);

		//�Ԏ��̕������A�G�̒T�����s��
		for(int i = MyRoomData.top;i < MyRoomData.bottom;i++)
		{
			for(int j = MyRoomData.left;j < MyRoomData.right;j++)
			{
				//�w�肵���ʒu�ɓG�������瓖�������t���O�����Ă�
				if(FindEnemy(j,i))
				{
					bHitFlg = true;
				}
			}
		}
		//�G���j�b�g�Ɉ�x�ł��U������������
		if(bHitFlg)
		{
			//�퓬�X�e�[�g��i�߂�
			CTurn::BattleState_Advance(BATTLE_STATE_HIT);
		}

		//�U����Ƀ��j�b�g�����݂��Ȃ�����
		else
		{
			//���b�Z�[�W�\�L
			TCHAR	str[256];
			_stprintf_s(str, _T("%s�̍U���͊O�ꂽ"),m_szName);
		
			//���b�Z�[�W�e�X�g
			MessageWindow::SetMassege(str);

			//�X�e�[�g��i�߂�
			CTurn::BattleState_Advance(BATTLE_STATE_END);
		}

		//�X�e�[�g���Z�b�g
		CTurn::TimeStateReset();
	}

	//�����̊O�ōU�����s����
	else
	{
		//���g�̎��͂̓G�ɍU�����s��

		//���ʂ̓G�ɍU�����q�b�g������
		bool bFrontHit = FrontFind();
		//�w�ʂ̓G�ɍU�����q�b�g������
		bool bBackHit = BackFind();
		//�E���̓G�ɍU�����q�b�g������
		bool bRightHit = Side_Right();
		//�����̓G�ɍU�����q�b�g������
		bool bLeftHit = Side_Left();
		
		//�΂߉E�O�̓G�ɍU�����q�b�g������
		bool bSlightRightHit = SlightRight();
		//�΂ߍ��O�̓G�ɍU�����q�b�g������
		bool bSlightLeftHit = SlightLeft();
		//�΂߉E���̓G�ɍU�����q�b�g������
		bool bSlightRightBackHit = SlightRightBack();
		//�΂ߍ����̓G�ɍU�����q�b�g������
		bool bSlightLeftBackHit = SlightLeftBack();

		//�S�Ẵq�b�g�t���O���܂Ƃ߂�
		bHitFlg = bFrontHit || bBackHit || bRightHit || bLeftHit || bSlightLeftHit || bSlightLeftBackHit || bSlightRightHit || bSlightRightBackHit;
		
		//�G���j�b�g�Ɉ�x�ł��U������������
		if(bHitFlg)
		{
			//�퓬�X�e�[�g��i�߂�
			CTurn::BattleState_Advance(BATTLE_STATE_HIT);
		}

		//�U����Ƀ��j�b�g�����݂��Ȃ�����
		else
		{
			//���b�Z�[�W�\�L
			TCHAR	str[256];
			_stprintf_s(str, _T("%s�̍U���͊O�ꂽ"),m_szName);
		
			//���b�Z�[�W�e�X�g
			MessageWindow::SetMassege(str);
	
			//�X�e�[�g��i�߂�
			CTurn::BattleState_Advance(BATTLE_STATE_END);
		}

		//�X�e�[�g���Z�b�g
		CTurn::TimeStateReset();
	}
}

//---------------------------------------------------------------------------------------
//�q�b�g�G�t�F�N�g�𔭐�������
//---------------------------------------------------------------------------------------
void CUnit::BattleHit()
{
	//�X�e�[�g�o�ߎ��ԉ��Z
	CTurn::TimeStateAdd();

	//����o�ߎ��Ԃ𒴂�����X�e�[�g�J��
	if(CTurn::GetStateTime() >= STATE_TIME / 2)
	{
		//�퓬�X�e�[�g��i�߂�
		CTurn::BattleState_Advance(BATTLE_STATE_FLASHING);

		//�X�e�[�g���Z�b�g
		CTurn::TimeStateReset();
		

		//�퓬���j�b�g���X�g�ɑ��݂��邷�ׂẴ��j�b�g�ɑ΂��A�K�p����
		//���݊m�F���Ă��郆�j�b�g
		CUnit* pNowUnit = m_pBattleUnit;

		while(pNowUnit)
		{
			//����̕`��t���O���ꎞ�I�ɉ�����
			pNowUnit->ChangeDrawFlg();

			//���̃��j�b�g�ւ���
			pNowUnit = pNowUnit->m_pBattleNext;
		}
	}
}

//---------------------------------------------------------------------------------------
//����̕`���_�ł�����
//---------------------------------------------------------------------------------------
void CUnit::BattleFlasing()
{
	//�_�ŉ񐔂̊i�[
	int FlashNum = 0;
	
	//�퓬���j�b�g���X�g�ɑ��݂��邷�ׂẴ��j�b�g�ɑ΂��A�K�p����
	//���݊m�F���Ă��郆�j�b�g
	CUnit* pNowUnit = m_pBattleUnit;

	while(pNowUnit)
	{
		//�G���j�b�g�̓_�Ŏ��Ԃ����Z����
		pNowUnit->FlashAddTimer();

		//�G���j�b�g�̓_�Ŏ��Ԃ��擾
		int FlashTime = pNowUnit ->GetFlashTime();
		FlashTime %= FLASHTIME;

		//�t���b�V���̎��Ԃ���莞�Ԃ𒴂��Ă��邩
		if(FlashTime == 0)
		{
			//�G���j�b�g�̕`��𔽓]������
			pNowUnit ->ChangeDrawFlg();

			//�_�ŉ񐔂����Z
			pNowUnit ->FlashAddNum();

			//�_�ŉ񐔂��擾����
			FlashNum = pNowUnit ->GetFlashNum();
		}

		//���̃��j�b�g�ւ���
		pNowUnit = pNowUnit->m_pBattleNext;
	}

	
	//�_�ŉ񐔂����ȏォ�H
	if(FlashNum >= FLASHNUM || !m_pBattleUnit)
	{
		CUnit* pNowUnit = m_pBattleUnit;

		while(pNowUnit)
		{
			pNowUnit->UpDrawFlg();

			//���̃��j�b�g�ւ���
			pNowUnit = pNowUnit->m_pBattleNext;
		}
		//�퓬�X�e�[�g��i�߂�
		CTurn::BattleState_Advance(BATTLE_STATE_WINDOW);
		//�X�e�[�g���Z�b�g
		CTurn::TimeStateReset();
	}

}

//---------------------------------------------------------------------------------------
//���b�Z�[�W�E�C���h�E�Ƀ��b�Z�[�W�𑗂�
//---------------------------------------------------------------------------------------
void CUnit::BattleWindow()
{
	//���胆�j�b�g�̖��O���擾
	char* pszName = NULL;
	
	//�퓬���j�b�g���X�g�ɑ��݂��邷�ׂẴ��j�b�g�ɑ΂��A�K�p����
	//���݊m�F���Ă��郆�j�b�g
	CUnit* pNowUnit = m_pBattleUnit;

	while(pNowUnit)
	{
		pszName = pNowUnit->GetName(pszName);

		//���b�Z�[�W�\�L
		//TCHAR	str[256];
		//_stprintf_s(str, _T("%s��%d�̃_���[�W!"),pszName,g_Damage);

		//���b�Z�[�W�e�X�g
		MessageWindow::SetMassege(_T("%s��%d�̃_���[�W!"),pszName,g_Damage);

		//���̃��j�b�g�ւ���
		pNowUnit = pNowUnit->m_pBattleNext;
	}
	//�퓬�X�e�[�g��i�߂�
	CTurn::BattleState_Advance(BATTLE_STATE_DAMAGE);
	//�X�e�[�g���Z�b�g
	CTurn::TimeStateReset();
}

//---------------------------------------------------------------------------------------
//����ɎZ�o���ꂽ�_���[�W��^����
//---------------------------------------------------------------------------------------
void CUnit::BattleDamage()
{
	
	//�퓬���j�b�g���X�g�ɑ��݂��邷�ׂẴ��j�b�g�ɑ΂��A�K�p����
	//���݊m�F���Ă��郆�j�b�g
	CUnit* pNowUnit = m_pBattleUnit;

	//���ŃG�t�F�N�g�X�e�[�g�ֈڍs���邩�ۂ�
	bool bDeleteEffectFlg = false;

	while(pNowUnit)
	{
		//�_���[�W��^����
		pNowUnit -> DamegeHP(g_Damage);

		//HP�������Ȃ����玟�̏��ŃG�t�F�N�g���o���X�e�[�g��
		if(pNowUnit -> GetHP() <= 0)
		{
			//���ŃX�e�[�g�ɔ�Ԃ悤�ɐݒ肷��
			bDeleteEffectFlg = true;

			//�p�[�e�B�N������!(�e�X�g)
			CParticle::Generation(pNowUnit,PARTICLE_PATTERN_DELETE);

			//�|��������̔�o���l���擾
			int Exp = pNowUnit ->GetXP();
			//�|��������̔�o���l�����Z
			m_nExp += Exp;

			//����l�𒴂��Ă�����A���x���A�b�v
			if(m_nExp >= MAX_EXP && m_nLevel < 100)
			{
				if(m_pLevelUp == NULL)
				{
					//���x���A�b�v�|���S���̍쐬
					m_pLevelUp = new CLevelUp(D3DXVECTOR3(m_world._41,m_world._42,m_world._43));
				}
				//���b�Z�[�W�\�L�p�ϐ�
				TCHAR	str[256];
				//���x���A�b�v���b�Z�[�W���o��
				_stprintf_s(str, _T("%s�̓��x�����オ����!"),m_szName);
				//���b�Z�[�W�o��
				MessageWindow::SetMassege(str);

				//���x�������Z
				m_nLevel ++;

				//�X�e�[�^�X�l�����Z

				//�ő�HP
				m_nMaxHP += m_nHPUpNum;
				//�X�e�[�^�X�l�����b�Z�[�W�Ƃ��ďo��
				_stprintf_s(str, _T("HP��%d�オ����!"),m_nHPUpNum);
				//���b�Z�[�W�o��
				MessageWindow::SetMassege(str);

				//�U��
				m_nAttack += m_nAttackUpNum;
				//�X�e�[�^�X�l�����b�Z�[�W�Ƃ��ďo��
				_stprintf_s(str, _T("�U����%d�オ����!"),m_nAttackUpNum);
				//���b�Z�[�W�o��
				MessageWindow::SetMassege(str);

				//�h��
				m_nDefence += m_nDefenceUpNum;
				//�X�e�[�^�X�l�����b�Z�[�W�Ƃ��ďo��
				_stprintf_s(str, _T("�h�䂪%d�オ����!"),m_nDefenceUpNum);
				//���b�Z�[�W�o��
				MessageWindow::SetMassege(str);

				//�o���l���ő�o���l������
				m_nExp -= MAX_EXP;
			};
		}
			//���̃��j�b�g�ւ���
			pNowUnit = pNowUnit->m_pBattleNext;
	}
	
	//�퓬���j�b�g���X�g�ɑ��݂��邷�ׂẴ��j�b�g���m�F����
	//���݊m�F���Ă��郆�j�b�g
	pNowUnit = m_pBattleUnit;
	//�S�Ă̓G�̊m�F���I���܂Ń��[�v
	while(pNowUnit)
	{
		//�m�F���̓G��HP��0�ɂȂ���
		if(pNowUnit ->GetHP() <= 0)
		{

			//���j�b�g���폜

			//�擪�̃o�g�����j�b�g���폜����ꍇ�A�|�C���^��ύX����
			if(m_pBattleUnit == pNowUnit)
			{
				m_pBattleUnit = pNowUnit ->m_pBattleNext;
			}
			//���g�̃��X�g�̑O�ɑ��̃��j�b�g�����݂��Ă���ꍇ�A�O�̃��j�b�g��NextUnit��ύX����
			if(pNowUnit ->m_pBattleBack)
			{
				pNowUnit ->m_pBattleBack->m_pBattleNext = pNowUnit->m_pBattleNext;
			}

			//���g�̃��X�g�̌��ɂق��̃��j�b�g�����݂��Ă�����A���̃��j�b�g��BackUnit��ύX����
			if(pNowUnit ->m_pBattleNext)
			{
				pNowUnit->m_pBattleNext->m_pBattleBack = pNowUnit ->m_pBattleBack;
			}

			//���̃��j�b�g�|�C���^
			CUnit* Next = pNowUnit->m_pBattleNext;

			//���j�b�g���폜
			pNowUnit ->Delete();

			//��x������
			pNowUnit = NULL;

			//���̃��j�b�g�փ|�C���^���ړ�
			pNowUnit = Next;

		}
		else
		{
			//���̃��j�b�g��
			pNowUnit = pNowUnit->m_pBattleNext;
		}
	}
	
	//�X�e�[�g��i�߂�
	CTurn::BattleState_Advance(BATTLE_STATE_END);
	//�X�e�[�g���Z�b�g
	CTurn::TimeStateReset();
}
//---------------------------------------------------------------------------------------
//�o�g���X�e�[�g�������A���g�̃^�[���X�e�[�g�X�V
//---------------------------------------------------------------------------------------
void CUnit::BattleEnd()
{
	//�A�^�b�N�X�e�[�g�ɑ��݂��郆�j�b�g�̐�-1
	CTurn::SumCount(m_nStateNumber);

	//�X�e�[�g�̑J��(�^�[���̏I��)
	if(m_uID == ID_PLAYER)
		m_nStateNumber = GAME_STATE_STAND_BY_PLAYER;
	else
		m_nStateNumber = GAME_STATE_STAND_BY_OTHER;


	//���͑҂��X�e�[�g�ɑ��݂��郆�j�b�g�̐�+1
	CTurn::AddCount(m_nStateNumber);

	//�X�e�[�g���Z�b�g
	CTurn::TimeStateReset();

	//�X�e�[�g���v�Z��
	CTurn::BattleState_Advance(BATTLE_STATE_GO);
	
	//�퓬���s�����G�̏�����
	//���݂݂Ă��郆�j�b�g
	CUnit* pNowUnit = m_pBattleUnit;
	while(pNowUnit)
	{
		//���j�b�g���폜
		//���g�̃��X�g�̑O�ɑ��̃��j�b�g�����݂��Ă���ꍇ�A�O�̃��j�b�g��NextUnit��ύX����
		if(pNowUnit ->m_pBattleBack)
		{
			pNowUnit ->m_pBattleBack->m_pBattleNext = pNowUnit->m_pBattleNext;
		}

		//���g�̃��X�g�̌��ɂق��̃��j�b�g�����݂��Ă�����A���̃��j�b�g��BackUnit��ύX����
		if(pNowUnit ->m_pBattleNext)
		{
			pNowUnit->m_pBattleNext->m_pBattleBack = pNowUnit ->m_pBattleBack;
		}

		//�����폜���郆�j�b�g�̃f�[�^���A�擪�̃|�C���^�̏ꍇ�A�擪�|�C���^�����ւ���
		if(pNowUnit == m_pBattleUnit)
		{
			m_pBattleUnit = m_pBattleUnit ->m_pBattleNext;
		}

		//���̃��j�b�g�|�C���^
		CUnit* Next = pNowUnit->m_pBattleNext;

		//���j�b�g�|�C���^�����
		pNowUnit = NULL;

		//���̃��j�b�g�փ|�C���^���ړ�
		pNowUnit = Next;
	}

	//�U���������j�b�g�̃|�C���^��������
	m_pBattleUnit = NULL;

	//�U�����Ă��郆�j�b�g�ԍ�������
	m_nAttackNumber = 0;

	//�Z�ԍ��̏�����
	m_nTrickNumber = TRICK_NAME_MAX + 1;
}

//---------------------------------------------------------------------------------------
//��Ԃ�ύX������
//---------------------------------------------------------------------------------------
void CUnit::SetStateAbnormal(int nStateNum)
{
	//�����Ƃ��ēn���ꂽ��Ԉُ�����g�̏�Ԉُ�ɃZ�b�g
	m_nState = nStateNum;
	//�Z�b�g���ꂽ��Ԉُ킩��A�p�����Ԃ�ݒ�
	//���݂��ǂ����Ōp�����Ԑ��𔻕�
	if(m_nState == UNIT_STATE_WINCE)
		//���݂̏ꍇ�A1�^�[���̂�
		m_nState_Turn = STATE_TURN_WINCE;
	else
		//���̑��̏ꍇ�A5�^�[���̌p�����ԂƂ���
		m_nState_Turn = STATE_TURN_DEFINE;

	//��Ԉُ�ɂȂ������b�Z�[�W
	TCHAR	str[256];
	switch(nStateNum)
	{
	case UNIT_STATE_POISON:
		//���b�Z�[�W�\�L
		_stprintf_s(str, _T("�ŏ�ԂɂȂ���!"));
		//���b�Z�[�W�o��
		MessageWindow::SetMassege( _T("�ŏ�ԂɂȂ���!"));
		break;
	case UNIT_STATE_PARALYSIS:
		//���b�Z�[�W�\�L
		_stprintf_s(str, _T("��჏�ԂɂȂ���!"));
		//���b�Z�[�W�o��
		MessageWindow::SetMassege( _T("��჏�ԂɂȂ���!"));
		break;
	case UNIT_STATE_CONFUSION:
		//���b�Z�[�W�\�L
		_stprintf_s(str, _T("��������!"));
		//���b�Z�[�W�o��
		MessageWindow::SetMassege( _T("��������!"));
		break;
	case UNIT_STATE_SLEEP:
		//���b�Z�[�W�\�L
		_stprintf_s(str, _T("�����Ă��܂���!"));
		//���b�Z�[�W�o��
		MessageWindow::SetMassege( _T("�����Ă��܂���!"));
		break;
	case UNIT_STATE_WINCE:
		//���b�Z�[�W�\�L
		_stprintf_s(str, _T("�Ђ��ł���!"));
		//���b�Z�[�W�o��
		MessageWindow::SetMassege( _T("�Ђ��ł���!"));
		break;
	default:
		//���b�Z�[�W�\�L
		_stprintf_s(str, _T("�o�O����!"));
		//���b�Z�[�W�o��
		MessageWindow::SetMassege( _T("�o�O����!"));
		break;
	}
}

//---------------------------------------------------------------------------------------
//�^�[�����߂̏�Ԉُ�̏������s��
//---------------------------------------------------------------------------------------
void CUnit::TurnStartStateProcessing()
{

	//���b�Z�[�W�\�L
	TCHAR	str[256];
	//���݂̏�Ԉُ�ŏ����𕪊�
	switch(m_nState)
	{
		//�ŏ�Ԃ̏���
	case UNIT_STATE_POISON:
		//HP��5�̃_���[�W
		DamegeHP(5);

		//��ʂɕ`�悵�Ă��炤HP�̐��l��n��
		CHPDraw::SetHP(m_nHP);
		//���b�Z�[�W�i�[
		_stprintf_s(str, _T("�ł�%s��%d�̃_���[�W"),m_szName,PoisonDamage);

		//���b�Z�[�W�o��
		MessageWindow::SetMassege(str);
		break;

		//��჏�Ԃ̏ꍇ
	case UNIT_STATE_PARALYSIS:
		//25%�̊m���ōs���s�\�ɂ���
		if(rand()%4)
		{
			//���b�Z�[�W�i�[
			_stprintf_s(str, _T("%s��Ⴢ�ē����Ȃ�"),m_szName);
			
			//���b�Z�[�W�o��
			MessageWindow::SetMassege(str);

			//���͑҂��ɑ��݂��郆�j�b�g�̐�-1
			CTurn::SumCount(m_nStateNumber);

			//���g�̃X�e�[�g�̐ݒ�
			m_nStateNumber = GAME_STATE_TURN_END;

			//�^�[���I���ɑ��݂��郆�j�b�g�̐�+1
			CTurn::AddCount(m_nStateNumber);
		}
		break;

		//������Ԃ̏ꍇ
	case UNIT_STATE_SLEEP:
		//���b�Z�[�W�i�[
		_stprintf_s(str, _T("%s�͖����Ă���"),m_szName);
		
		//���b�Z�[�W�o��
		MessageWindow::SetMassege(str);

		//���͑҂��ɑ��݂��郆�j�b�g�̐�-1
		CTurn::SumCount(m_nStateNumber);

		//���g�̃X�e�[�g�̐ݒ�
		m_nStateNumber = GAME_STATE_TURN_END;

		//�^�[���I���ɑ��݂��郆�j�b�g�̐�+1
		CTurn::AddCount(m_nStateNumber);
		break;

		//���ݏ�Ԃ̏ꍇ
	case UNIT_STATE_WINCE:
		//���b�Z�[�W�i�[
		_stprintf_s(str, _T("%s�͂Ђ��ł���!"),m_szName);
		
		//���b�Z�[�W�o��
		MessageWindow::SetMassege(str);

		//���͑҂��ɑ��݂��郆�j�b�g�̐�-1
		CTurn::SumCount(m_nStateNumber);

		//���g�̃X�e�[�g�̐ݒ�
		m_nStateNumber = GAME_STATE_TURN_END;

		//�^�[���I���ɑ��݂��郆�j�b�g�̐�+1
		CTurn::AddCount(m_nStateNumber);
		break;
	}
	
	//�o�ߎ��Ԃ����炷
	m_nState_Turn --;

	//�����p�����Ԃ�0�ɂȂ�����A��Ԉȏ�����N��Ԃ֑J�ڂ�����
	if(m_nState_Turn == 0)
	{
		//���b�Z�[�W�o��
		MessageWindow::SetMassege(_T("��Ԃ����ɖ߂���!"));

		m_nState = UNIT_STATE_HEALTH;
	}
}
//---------------------------------------------------------------------------------------
//���g�̑������Ă���A�C�e���̍U���͍��v�l��n��
//---------------------------------------------------------------------------------------
int CUnit::GetEquipmentAttackNum()
{
	return m_pEquipment->GetAttackTotalValue();
}
//---------------------------------------------------------------------------------------
//���g�̑������Ă���A�C�e���̖h��͍��v�l��n��
//---------------------------------------------------------------------------------------
int CUnit::GetEquipmentDefenceNum()
{
	return m_pEquipment ->GetDefenceTotalValue();
}

//---------------------------------------------------------------------------------------
//�����̃A�C�e���̊m�F
//---------------------------------------------------------------------------------------
void CUnit::ChackFeetItem()
{
	//�����̃A�C�e���̏����擾
	int ItemSearch = CMapData::Get_ItemMapSituation(m_nUnit_Pos_X,m_nUnit_Pos_Z);
													
	//�����̃A�C�e���̌���
	if(ItemSearch != 0)
	{
		m_pFootItem =  (CFieldItem*)ItemFind(ItemSearch);
	
		//�C���x���g���ɏE�����A�C�e����ǉ�
		if(m_pInventory->SetItem(m_pFootItem->GetItemData()))
		{
			//���b�Z�[�W�\�L
			TCHAR	str[256];
			_stprintf_s(str, _T("%s�̓A�C�e�����E����"),m_szName);
	
			//���b�Z�[�W�e�X�g
			MessageWindow::SetMassege(str);
	
			//�}�b�v�ォ�猻�݂̈ʒu�̃A�C�e����������
			CMapData::Back_ItemMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);
	
			//�E�����A�C�e���͍폜
			m_pFootItem->Delete();
		}
		else 
		{
			//���b�Z�[�W�`��
			MessageWindow::SetMassege(_T("�A�C�e�����E���Ȃ�����!"));
		}
	}
}

//---------------------------------------------------------------------------------------
//���j�b�g�S�Ă̍s���\�t���O��ύX����
//---------------------------------------------------------------------------------------
void CUnit::ChangeMoveCanFlg(bool ChangeFlg)
{
	m_bMoveCanFlg = ChangeFlg;
}