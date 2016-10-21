//�G�N���X�@����
#include "Enemy.h"
#include "Input.h"
#include "MessageWindow.h"
#include "ModelManager.h"
#include "Turn.h"
#include "Battle.h"
#include "MiniMap.h"
#include "TextureManager.h"
#include "GameScene.h"
#include "EnemyGenerator.h"
#include <math.h>


CMeshObj*	CEnemy::m_Player = NULL;			//�v���C���[���i�[
int			CEnemy::m_nEnemyData[STATES_MAX];	//�X�e�[�^�X���i�[
int			CEnemy::m_nLevelUpData[UPSTATES_MAX];	//���x���A�b�v���㏸�X�e�[�^�X���i�[
bool		CEnemy::m_bStatesLoad = false;		//�X�e�[�^�X���t�@�C���ǂݍ��݃t���O
bool		CEnemy::m_bLevelUpLoad = false;		//���x���A�b�v���㏸�l�t�@�C���ǂݍ��݃t���O
bool		CEnemy::m_bDelete = false;

#define PATH_DATA_ENEMY		("../data/txt/Enemy.txt")
#define PATH_LEVEL_UP_ENEMY ("../data/txt/LevelUp_Enemy.txt")

using namespace std;
//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CEnemy::CEnemy(CGameScene* pScene):
CUnit(pScene)
{
	//�I�u�W�F�N�gID�̐ݒ�
	m_uID = ID_ENEMY;

	//���j�b�g�̃X�e�[�g��Ԃ�ݒ�
	m_nStateNumber = GAME_STATE_STAND_BY_OTHER;
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CEnemy::~CEnemy(void)
{
	//���������S�Ɋ��������G�l�~�[�����ł���ꍇ�A
	if(m_bMakeSuccess)
	{
		//�A�C�e���C���x���g���̏I������
		m_pInventory ->Fin();

		//�����C���x���g���̏I������
		m_pEquipment ->Fin();

		//�}�[�L���O����
		CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);

		//�~�j�}�b�v��̏�������
		CMiniMap::Delete(m_nUnit_Pos_X,m_nUnit_Pos_Z);

		//�W�F�l���[�^�[�̐����������Z
		CEnemyGenerator::SumMakeEnemyNum();
	}
}

//---------------------------------------------------------------------------------------
//�v���C���[�|�C���^������
//---------------------------------------------------------------------------------------
void CEnemy::PlayerPointInit()
{
	m_Player = NULL;
}
//---------------------------------------------------------------------------------------
//�G�l�~�[�̐���
//---------------------------------------------------------------------------------------
void CEnemy::Generation(CMeshObj *pGenerator)
{
	//���b�V����񂠂�&�Ăяo������̃|�C���^����
	if(!pGenerator)
		return;

	//�G�l�~�[��ǉ�
	CEnemy* pEnemy = new CEnemy(pGenerator ->GetScene());

	//���j�b�g�Ƃ��Đe�N���X�̏������������s��
	pEnemy -> CUnit::Init();

	//�G�l�~�[�̎��
	int nEnemyType = rand()%3;

	//���������󋵏�����
	pEnemy ->m_bMakeSuccess = false;

	//�G�l�~�[�̎�ʂ�ݒ�
	switch(nEnemyType)
	{
	case 0:
		//���O�̐ݒ�
		_stprintf(pEnemy -> m_szName, _T("�͂�"));

		//���f���f�[�^�̓ǂݍ���
		pEnemy -> m_nMeshNumber = MODEL_BEE;
		break;
	case 1:
		//���O�̐ݒ�
		_stprintf(pEnemy -> m_szName, _T("��������"));

		//���f���f�[�^�ǂݍ���
		pEnemy -> m_nMeshNumber = MODEL_WOLF;
		break;
	case 2:
		//���O�̐ݒ�
		_stprintf(pEnemy -> m_szName, _T("����"));

		//���f���f�[�^�ǂݍ���
		pEnemy -> m_nMeshNumber = MODEL_BEAR;
		break;

		//�f�o�b�O�p����
	default:
		//���O�̐ݒ�
		_stprintf(pEnemy -> m_szName, _T("����"));

		//���f���f�[�^�ǂݍ���
		pEnemy ->m_nMeshNumber = MODEL_WALL;
		break;
	}
	
	//�I�u�W�F�N�gID�̐ݒ�
	pEnemy -> m_uID = ID_ENEMY;

	//���j�b�g�̃X�e�[�g��Ԃ�ݒ�
	pEnemy -> m_nStateNumber = GAME_STATE_STAND_BY_OTHER;

	//���b�V���̐ݒ�
	pEnemy ->SetMesh(CModelManager::GetMesh(pEnemy ->m_nMeshNumber));

	//���j�b�g�̔ԍ���ݒ�
	pEnemy -> m_nUnitNumber = OBJ_NUM_ENEMY + m_nMakeNumber;

	//�����Ă���
	pEnemy -> m_bSurvival = true;

	//���@�ւ̃|�C���^���擾���Ă���
	if(!m_Player)
	{
		m_Player = (CMeshObj*)pEnemy->Find(ID_PLAYER);
	}

    //txt�t�@�C����1�s���ǂݍ���(1�x�ǂݍ��߂΂��Ƃ͓ǂݍ��񂾃f�[�^�ϐ���ǂݍ���)
	if(!m_bStatesLoad)
	{
		//�t�@�C���̓ǂݍ���
		ifstream ifs(PATH_DATA_ENEMY);

		string str;
		
		int i = 0;	//�i�[�z��W��
		
		string token;

		while(getline(ifs,str))
		{
		    istringstream stream(str);

		    //1�s�̂����A������ƃR���}�𕪊�����
		    while(getline(stream,token,','))
			{
				m_nEnemyData[i] = stoi(token);
				i++;
				if(i >= STATES_MAX)
					break;
		    }
		}

		//�t�@�C�������
		ifs.close();
		//�ǂݍ��݊���
		m_bStatesLoad= true;
	}

    //txt�t�@�C����1�s���ǂݍ���(1�x�ǂݍ��߂΂��Ƃ͓ǂݍ��񂾃f�[�^�ϐ���ǂݍ���)
	if(!m_bLevelUpLoad)
	{
		//�t�@�C���̓ǂݍ���
		ifstream ifs(PATH_LEVEL_UP_ENEMY);

		string str;
		
		int i = 0;	//�i�[�z��W��
		
		string token;

		while(getline(ifs,str))
		{
		    istringstream stream(str);

		    //1�s�̂����A������ƃR���}�𕪊�����
		    while(getline(stream,token,','))
			{
				m_nLevelUpData[i] = stoi(token);
				i++;
				if(i >= UPSTATES_MAX)
					break;
		    }
		}

		//�t�@�C�������
		ifs.close();
		//�ǂݍ��݊���
		m_bStatesLoad= true;
	}
	
	//-----�X�e�[�^�X�̐ݒ�-----

	//���x����ݒ�
	pEnemy -> m_nLevel = CGameScene::GetPlayerLevel() + (rand() % 6 - 3);

	//�l��0�ȉ��ɂȂ�Ȃ��l�ɐݒ肷��
	if(pEnemy ->m_nLevel <= 0)
	{
		pEnemy->m_nLevel = 1;
	}

	//HP��ݒ�
	pEnemy -> m_nMaxHP = m_nEnemyData[STATES_MAX_HP] + m_nLevelUpData[UPSTATES_MAX_HP] * pEnemy -> m_nLevel;
	pEnemy -> m_nHP = m_nEnemyData[STATES_HP] + m_nLevelUpData[UPSTATES_MAX_HP] * pEnemy -> m_nLevel;

	//�U���͂�ݒ�
	pEnemy -> m_nAttack = m_nEnemyData[STATES_AT] + m_nLevelUpData[UPSTATES_AT] * pEnemy -> m_nLevel;

	//�h��͂�ݒ�
	pEnemy -> m_nDefence = m_nEnemyData[STATES_DF] + m_nLevelUpData[UPSTATES_DF] * pEnemy -> m_nLevel;

	//-----���x���A�b�v���A�㏸�X�e�[�^�X��ݒ�-----
	//�ő�HP
	pEnemy -> m_nHPUpNum = m_nLevelUpData[UPSTATES_MAX_HP];
	//�U����
	pEnemy -> m_nAttackUpNum = m_nLevelUpData[UPSTATES_AT];
	//�h���
	pEnemy -> m_nDefenceUpNum = m_nLevelUpData[UPSTATES_DF];

	
	//�ʒu�������I�ɐݒ�
	int PosX = rand()%MAP_SIZE;
	int PosZ = rand()%MAP_SIZE;

	//�ꏊ�m�F��
	int nMakeLimit = 0;

	//�ʒu����ݒ�
	while(1)
	{
		//�ꏊ�m�F�񐔂���萔�𒴂����琶���𒆎~
		if(nMakeLimit > 15)
		{
			delete pEnemy;
			return;
		}

		//�ڒn�\���m�F
		if(FLOOR == CMapData::Get_TerrainMapSituation(PosX,PosZ) &&
			0 == CMapData::Get_UnitMapSituation(PosX,PosZ) && 
			CMapData::CheckInTheRoom(PosX,PosZ))
			break;

		//�s�\�������ꍇ�A�Đݒ肷��B
		PosX = rand()%MAP_SIZE;
		PosZ = rand()%MAP_SIZE;

		//�ꏊ�m�F�񐔂����Z
		nMakeLimit ++;
	}

	pEnemy -> m_nUnit_Pos_X = PosX;
	pEnemy -> m_nUnit_Pos_Z = PosZ;
	

	//�~�j�}�b�v��Ɏ��g�̈ʒu��ݒ�
	CMiniMap::SetIcon(pEnemy -> m_nUnit_Pos_X,pEnemy -> m_nUnit_Pos_Z,TEXTURE_RED_TEXTURE);

	//�o���l�~�ϒl��ݒ�
	pEnemy -> m_nExp = m_nEnemyData[STATES_EXP];

	//�|���ē�����o���l��ݒ�
	pEnemy -> m_nXp = m_nEnemyData[STATES_XP];
	
	//���[���h�}�g���b�N�X���烍�[�J�������o�A���W���o
	D3DXMATRIX world = pGenerator->GetWorld();

	//���f���̃X�P�[����ύX����
	D3DXMatrixScaling(&world,0.125f,0.125f,0.125f);

	//�ʒu���ݒ�
	world._41 = (pEnemy -> m_nUnit_Pos_X - (MAP_SIZE / 2)) * GRIDSIZE + GRIDSIZE / 2;
	world._42 = 0.0f;
	world._43 = -((pEnemy -> m_nUnit_Pos_Z) - (MAP_SIZE / 2)) * GRIDSIZE - GRIDSIZE / 2;

	//���[���h�}�g���b�N�X��ݒ�
	pEnemy->SetWorld(world);

	//�}�[�L���O
	CMapData::Set_UnitMap(pEnemy -> m_nUnit_Pos_X,pEnemy -> m_nUnit_Pos_Z,pEnemy ->m_nUnitNumber);

	//�ړI�n������
	pEnemy -> m_Pos = D3DXVECTOR3(world._41,world._42,world._43);
	
	//�����̏�����
	pEnemy -> m_fOldAngle = 0;

	//���͎��ԏ�����
	pEnemy -> m_fTimer = 0.0f;

	//�ړI�n�ɓ��B���Ă���
	pEnemy -> m_bDestination = true;

	//�X�e�[�g�̐ݒ�
	pEnemy ->m_nStateNumber = GAME_STATE_STAND_BY_OTHER;

	//���͑҂��ɑ��݂��郆�j�b�g��+1
	CTurn::AddCount(pEnemy ->m_nStateNumber);

	//��������
	pEnemy ->m_bMakeSuccess = true;

	//���j�b�g���������J�E���g
	m_nMakeNumber ++;
}
//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CEnemy::Update()
{
	//�����A�G�l�~�[�̍폜�t���O�������Ă�����A�G�l�~�[���폜����
	if(m_bDelete || m_nHP <= 0)
	{
		//�}�[�L���O����
		CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);
	
		//���ݎ������I�����Ă���X�e�[�g�̃��j�b�g�̐�-1
		CTurn::SumCount(m_nStateNumber);

		//���g�̍폜
		delete this;
	}
	else
	{
		//���j�b�g�Ƃ��Ă̍X�V���s��
		CUnit::Update();
	}
}
//---------------------------------------------------------------------------------------
//���͍X�V(�ړ��������[�`��)
//---------------------------------------------------------------------------------------
void CEnemy::InputUpdate()
{
	//��]�x��
	m_Angle = D3DXVECTOR3(0.0f,0.0f,0.0f);

	//�ړ��ł�����
	bool MoveCompletion = false;

	
	//-----�ړ����[�`���쐬-----
	if (m_Player)
	{
		D3DXVECTOR3 Distance = D3DXVECTOR3(0.0f,0.0f,0.0f);	//�v���C���[�Ǝ����Ƃ̋���

		//���[���h��̃v���C���[�̈ʒu���擾
		D3DXVECTOR3 PlayerPos = m_Player -> GetPos();
		
		//�v���C���[�̈ʒu����z��ʒu�ɕϊ�
		int PlayerPos_X = (int)((PlayerPos.x - (MAP_SIZE / 2) * GRIDSIZE) / GRIDSIZE + (MAP_SIZE));
		int PlayerPos_Z = (int)(MAP_SIZE - ((PlayerPos.z - (MAP_SIZE / 2) * GRIDSIZE) / GRIDSIZE + (MAP_SIZE)));

		PlayerPos_X = m_Player->GetPosX();
		PlayerPos_Z = m_Player->GetPosZ();

		//�����v�Z
		int Distance_X = PlayerPos_X - m_nUnit_Pos_X;
		int Distance_Z = m_nUnit_Pos_Z - PlayerPos_Z;
		

		//�U������(�����v���C���[�����΂ɋ�����U��������)
		if(abs(Distance_X) <= 1 && abs(Distance_Z) <= 1)
		{

			//�����t���O������
			for(int i = 0;i < MaxDirection;i++)
				m_bDirectionFlg[i] = false;

			//�v���C���[�̕���������
			if(Distance_X > 0)
			{
				m_bDirectionFlg[Right] = true;
				m_bDirectionFlg[Left]  = false;
			}
			else if(Distance_X < 0)
			{
				m_bDirectionFlg[Left]  = true;
				m_bDirectionFlg[Right] = false;
			}
			else
			{
				m_bDirectionFlg[Left]  = false;
				m_bDirectionFlg[Right] = false;
			}

			if(Distance_Z < 0)
			{
				m_bDirectionFlg[Back] = true;
				m_bDirectionFlg[Forword] = false;
			}

			else if(Distance_Z > 0)
			{
				m_bDirectionFlg[Back] = false;
				m_bDirectionFlg[Forword] = true;
			}
			else
			{
				m_bDirectionFlg[Back] = false;
				m_bDirectionFlg[Forword] = false;
			}
			
			//��
			int nAngle = 0;		//���j�b�g�̉�]������p�x

			//�t���O�̏󋵂���p�x��ݒ肷��
			if(m_bDirectionFlg[0])
			{
				if(m_bDirectionFlg[1])
					nAngle = 45;
				else if(m_bDirectionFlg[3])
					nAngle = 315;
				else
					nAngle = 0;
			}

			else if(m_bDirectionFlg[2])
			{
				if(m_bDirectionFlg[1])
					nAngle = 135;
				else if(m_bDirectionFlg[3])
					nAngle = 225;
				else
					nAngle = 180;
			}
			else if(m_bDirectionFlg[1])
				nAngle = 90;
			else if(m_bDirectionFlg[3])
				nAngle = 270;

				
			int OldAngle = (int)(m_fOldAngle* 180 / PI );
			float RotateAngle = (float)(nAngle * PI / 180);

			m_Angle.y = RotateAngle - m_fOldAngle;

			m_fOldAngle = RotateAngle;

			//���͑҂��ɑ��݂��郆�j�b�g�̐�-1
			CTurn::SumCount(m_nStateNumber);

			//���g�̃X�e�[�g�̐ݒ�
			m_nStateNumber = GAME_STATE_ATTACK;

			//�U���ɑ��݂��郆�j�b�g�̐�+1
			CTurn::AddCount(m_nStateNumber);
			
			//�J��o���Z�̔ԍ����w��
			m_nTrickNumber = TRICK_RANGE_FRONT;
		}
		//��������Έړ�
		else if(abs(Distance_X) >= 1 || abs(Distance_Z) >= 1)
		{

			//�����t���O������
			for(int i = 0;i < MaxDirection;i++)
				m_bDirectionFlg[i] = false;

			//��ړ�
			//�ړ��悪���Ȃ�Έړ��\
			if(Distance_Z > 0 
				&& FLOOR == CMapData::Get_TerrainMapSituation(m_nUnit_Pos_X,m_nUnit_Pos_Z - 1) 
				&& CMapData::Get_UnitMapSituation(m_nUnit_Pos_X,m_nUnit_Pos_Z - 1) == 0)
			{
				//�}�[�L���O����
				CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);

				//�~�j�}�b�v��̈ʒu�����폜
				CMiniMap::Delete(m_nUnit_Pos_X,m_nUnit_Pos_Z);

				//�����t���O��
				m_bDirectionFlg[Forword] = true;

				//�w��ʒu�ɓ��B���Ă��Ȃ�
				m_bDestination = false;
				m_fTimer = 0.0f;

				//�ړ�����
				MoveCompletion = true;

				//�z�����ړ�
				m_nUnit_Pos_Z--;
				
				//�}�[�L���O
				CMapData::Set_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z,m_nUnitNumber);

				//�~�j�}�b�v��Ɏ��g�̈ʒu��ݒ�
				CMiniMap::SetIcon(m_nUnit_Pos_X,m_nUnit_Pos_Z,TEXTURE_RED_TEXTURE);

				//���쌈��҂��ɑ��݂��郆�j�b�g�̐�-1
				CTurn::SumCount(m_nStateNumber);

				//���g�̃X�e�[�g�̐ݒ�
				m_nStateNumber = GAME_STATE_MOVE;
				
				//�ړ��X�e�[�g�ɑ��݂��郆�j�b�g+1
				CTurn::AddCount(m_nStateNumber);
			}
			//���ړ�
			//�ړ��悪���Ȃ�Έړ��\
			else if(Distance_Z < 0 
				&& FLOOR == CMapData::Get_TerrainMapSituation(m_nUnit_Pos_X,m_nUnit_Pos_Z + 1) 
				&& CMapData::Get_UnitMapSituation(m_nUnit_Pos_X,m_nUnit_Pos_Z + 1) == 0)
			{
				//�}�[�L���O����
				CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);

				//�~�j�}�b�v��̈ʒu�����폜
				CMiniMap::Delete(m_nUnit_Pos_X,m_nUnit_Pos_Z);
				
				//�����t���O��
				m_bDirectionFlg[Back] = true;

				//�w��ʒu�ɓ��B���Ă��Ȃ�
				m_bDestination = false;
				m_fTimer = 0.0f;

				//�ړ�����
				MoveCompletion = true;

				//�z�����ړ�
				m_nUnit_Pos_Z ++;
				
				//�}�[�L���O
				CMapData::Set_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z,m_nUnitNumber);

				//�~�j�}�b�v��Ɏ��g�̈ʒu��ݒ�
				CMiniMap::SetIcon(m_nUnit_Pos_X,m_nUnit_Pos_Z,TEXTURE_RED_TEXTURE);

				//���쌈��҂��ɑ��݂��郆�j�b�g�̐�-1
				CTurn::SumCount(m_nStateNumber);

				//���g�̃X�e�[�g�̐ݒ�
				m_nStateNumber = GAME_STATE_MOVE;
				
				//�ړ��X�e�[�g�ɑ��݂��郆�j�b�g+1
				CTurn::AddCount(m_nStateNumber);
			}
			//�E�ړ�
			if(Distance_X > 0 && 
				FLOOR == CMapData::Get_TerrainMapSituation(m_nUnit_Pos_X + 1,m_nUnit_Pos_Z) && 
				CMapData::Get_UnitMapSituation(m_nUnit_Pos_X + 1,m_nUnit_Pos_Z) == 0)
			{
				//�}�[�L���O����
				CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);

				//�~�j�}�b�v��̈ʒu�����폜
				CMiniMap::Delete(m_nUnit_Pos_X,m_nUnit_Pos_Z);

				//�����t���O�E
				m_bDirectionFlg[Right] = true;

				//�w��ʒu�ɓ��B���Ă��Ȃ�
				m_bDestination = false;
				m_fTimer = 0.0f;

				//�ړ�����
				MoveCompletion = true;

				//�z�����ړ�
				m_nUnit_Pos_X ++;
				
				//�}�[�L���O
				CMapData::Set_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z,m_nUnitNumber);

				//�~�j�}�b�v��Ɏ��g�̈ʒu��ݒ�
				CMiniMap::SetIcon(m_nUnit_Pos_X,m_nUnit_Pos_Z,TEXTURE_RED_TEXTURE);

				//���쌈��҂��ɑ��݂��郆�j�b�g�̐�-1
				CTurn::SumCount(m_nStateNumber);

				//���g�̃X�e�[�g�̐ݒ�
				m_nStateNumber = GAME_STATE_MOVE;
				
				//�ړ��X�e�[�g�ɑ��݂��郆�j�b�g+1
				CTurn::AddCount(m_nStateNumber);
			}
			//���ړ�
			else if(Distance_X < 0 && 
				FLOOR == CMapData::Get_TerrainMapSituation(m_nUnit_Pos_X - 1,m_nUnit_Pos_Z) && 
				CMapData::Get_UnitMapSituation(m_nUnit_Pos_X - 1,m_nUnit_Pos_Z) == 0)
			{
				//�}�[�L���O����
				CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);

				//�~�j�}�b�v��̈ʒu�����폜
				CMiniMap::Delete(m_nUnit_Pos_X,m_nUnit_Pos_Z);

				//�����t���O��
				m_bDirectionFlg[Left] = true;

				//�w��ʒu�ɓ��B���Ă��Ȃ�
				m_bDestination = false;
				m_fTimer = 0.0f;

				//�ړ�����
				MoveCompletion = true;

				//�z�����ړ�
				m_nUnit_Pos_X --;
				
				//�}�[�L���O
				CMapData::Set_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z,m_nUnitNumber);

				//�~�j�}�b�v��Ɏ��g�̈ʒu��ݒ�
				CMiniMap::SetIcon(m_nUnit_Pos_X,m_nUnit_Pos_Z,TEXTURE_RED_TEXTURE);

				//���쌈��҂��ɑ��݂��郆�j�b�g�̐�-1
				CTurn::SumCount(m_nStateNumber);

				//���g�̃X�e�[�g�̐ݒ�
				m_nStateNumber = GAME_STATE_MOVE;
				
				//�ړ��X�e�[�g�ɑ��݂��郆�j�b�g+1
				CTurn::AddCount(m_nStateNumber);
			}
			//�ړ��ł��Ȃ������ꍇ�A�G�l�~�[�̃^�[�����I������
			if(!MoveCompletion)
			{
				//���͑҂��ɑ��݂��郆�j�b�g�̐�-1
				CTurn::SumCount(m_nStateNumber);

				//���g�̃X�e�[�g�̐ݒ�
				m_nStateNumber = GAME_STATE_TURN_END;

				//�^�[���I���ɑ��݂��郆�j�b�g�̐�+1
				CTurn::AddCount(m_nStateNumber);
			}
			
			//��
			int nAngle = 0;		//���j�b�g�̉�]������p�x
			
			if(m_nStateNumber == GAME_STATE_MOVE)
			{
				//�t���O�̏󋵂���p�x��ݒ肷��
				if(m_bDirectionFlg[0])
				{
					if(m_bDirectionFlg[1])
						nAngle = 45;
					else if(m_bDirectionFlg[3])
						nAngle = 315;
					else
						nAngle = 0;
				}
			
				else if(m_bDirectionFlg[2])
				{
					if(m_bDirectionFlg[1])
						nAngle = 135;
					else if(m_bDirectionFlg[3])
						nAngle = 225;
					else
						nAngle = 180;
				}
				else if(m_bDirectionFlg[1])
					nAngle = 90;
				else if(m_bDirectionFlg[3])
					nAngle = 270;
			
					
				int OldAngle = (int)(m_fOldAngle* 180 / PI );
				float RotateAngle = (float)(nAngle * PI / 180);
			
				m_Angle.y = RotateAngle - m_fOldAngle;
			
				m_fOldAngle = RotateAngle;
			}
		}
		//�ړ��ł��Ȃ�
		else
		{
			//���͑҂��ɑ��݂��郆�j�b�g�̐�-1
			CTurn::SumCount(m_nStateNumber);

			//���g�̃X�e�[�g�̐ݒ�
			m_nStateNumber = GAME_STATE_TURN_END;

			//�^�[���I���ɑ��݂��郆�j�b�g�̐�+1
			CTurn::AddCount(m_nStateNumber);
		}

		//���[���h�}�g���b�N�X���烍�[�J�������o�A���W���o
		D3DXMATRIX world = GetWorld();

		//���ꂼ��̎��̒l���i�[����
		D3DXVECTOR3 vX,vY,vZ,vP;
		
		vX = D3DXVECTOR3(world._11,world._12,world._13);	//vX:X����]
		vY = D3DXVECTOR3(world._21,world._22,world._23);	//vY:Y����]
		vZ = D3DXVECTOR3(world._31,world._32,world._33);	//vZ:Z����]
		vP = D3DXVECTOR3(world._41,world._42,world._43);	//�ʒu���

		world._41 = world._43 = 0.0f;	//���_�ֈړ�������
			
		m_Pos.x = (m_nUnit_Pos_X - (MAP_SIZE / 2)) * GRIDSIZE + GRIDSIZE / 2;
		m_Pos.z = -((m_nUnit_Pos_Z) - (MAP_SIZE / 2)) * GRIDSIZE - GRIDSIZE / 2;

		vP = vP + (m_Pos - vP) * (m_fTimer / (float)ACTION_TIME);

		//��]�s��̍쐬
		D3DXMATRIX rot_X,rot_Y,rot_Z;
		D3DXMatrixRotationAxis(&rot_X,&vX,m_Angle.x);		//&rot_Y��vY��angle.y�̒l���|�����킹���s����i�[����
		D3DXMatrixRotationAxis(&rot_Y,&vY,m_Angle.y);		//&rot_Z�Ɍ��݂̊p�x(vY)�ɉ�]�x��(angle.y)���������l�̍s����i�[
		D3DXMatrixRotationAxis(&rot_Z,&vZ,m_Angle.z);		//&rot_Z�Ɍ��݂̊p�x(vZ)�ɉ�]�x��(angle.z)���������l�̍s����i�[

		//��]�x��������
		m_Angle = D3DXVECTOR3(0.0f,0.0f,0.0f);	

		//�v�Z���ʂ̍s������[���h�s��ɔ��f������
		world *= (rot_Z *rot_Y * rot_X);

		world._41 = vP.x;
		world._42 = vP.y;
		world._43 = vP.z;

		//���[���h�}�g���b�N�X��ݒ�
		SetWorld(world);
	}
}


//---------------------------------------------------------------------------------------
//�ړ��X�V
//---------------------------------------------------------------------------------------
void CEnemy::MoveUpdate()
{	
	//�ړI�n�ɓ��B���Ă��Ȃ��ꍇ�A�{�^�����͌o�ߎ��Ԃ����Z
	if(!m_bDestination)
	{
		//���͂���̌o�߂��v�Z
		m_fTimer += 0.1f;
		//�ړ�����
		if(m_fTimer >= ACTION_TIME)
		{
			//���͂���̌o�߂����Z�b�g
			m_fTimer = 0.0f;

			//�����̃A�C�e���̃`�F�b�N
			ChackFeetItem();

			//�ړ��X�e�[�g�ɑ��݂��郆�j�b�g�̐�-1
			CTurn::SumCount(m_nStateNumber);

			//���g�̃X�e�[�g��Ԃ���͑҂��ɐݒ�
			m_nStateNumber = GAME_STATE_STAND_BY_OTHER;

			//���͑҂��ɑ��݂��郆�j�b�g�̐�+1
			CTurn::AddCount(m_nStateNumber);
		}
	}

	//���[���h�}�g���b�N�X���烍�[�J�������o�A���W���o
	D3DXMATRIX world = GetWorld();

	//���ꂼ��̎��̒l���i�[����
	D3DXVECTOR3 vX,vY,vZ,vP;
	
	vX = D3DXVECTOR3(world._11,world._12,world._13);	//vX:X����]
	vY = D3DXVECTOR3(world._21,world._22,world._23);	//vY:Y����]
	vZ = D3DXVECTOR3(world._31,world._32,world._33);	//vZ:Z����]
	vP = D3DXVECTOR3(world._41,world._42,world._43);	//�ʒu���

	world._41 = world._43 = 0.0f;	//���_�ֈړ�������
		
	m_Pos.x = (m_nUnit_Pos_X - (MAP_SIZE / 2)) * GRIDSIZE + GRIDSIZE / 2;
	m_Pos.z = -((m_nUnit_Pos_Z) - (MAP_SIZE / 2)) * GRIDSIZE - GRIDSIZE / 2;

	vP = vP + (m_Pos - vP) * (m_fTimer / (float)ACTION_TIME);


	if(vP == m_Pos)
	{
		m_bDestination = true;
	}

	//��]�s��̍쐬
	D3DXMATRIX rot_X,rot_Y,rot_Z;
	D3DXMatrixRotationAxis(&rot_X,&vX,m_Angle.x);		//&rot_Y��vY��angle.y�̒l���|�����킹���s����i�[����
	D3DXMatrixRotationAxis(&rot_Y,&vY,m_Angle.y);		//&rot_Z�Ɍ��݂̊p�x(vY)�ɉ�]�x��(angle.y)���������l�̍s����i�[
	D3DXMatrixRotationAxis(&rot_Z,&vZ,m_Angle.z);		//&rot_Z�Ɍ��݂̊p�x(vZ)�ɉ�]�x��(angle.z)���������l�̍s����i�[

	//��]�x��������
	m_Angle = D3DXVECTOR3(0.0f,0.0f,0.0f);	

	//�v�Z���ʂ̍s������[���h�s��ɔ��f������
	world *= (rot_Z *rot_Y * rot_X);

	world._41 = vP.x;
	world._42 = vP.y;
	world._43 = vP.z;

	//���[���h�}�g���b�N�X��ݒ�
	SetWorld(world);
}

//---------------------------------------------------------------------------------------
//�s���X�V
//---------------------------------------------------------------------------------------
void CEnemy::ActUpdate()
{	
	//���b�Z�[�W�e�X�g
	MessageWindow::SetMassege(_T("�s������"));

	//�s���X�V�ɑ��݂��郆�j�b�g�̐�-1
	CTurn::SumCount(m_nStateNumber);

	//�X�e�[�g�̑J��(�^�[���̏I��)
	m_nStateNumber = GAME_STATE_STAND_BY_OTHER;

	//���͑҂��ɑ��݂��郆�j�b�g�̐�+1
	CTurn::AddCount(m_nStateNumber);
}

//---------------------------------------------------------------------------------------
//�A�C�e���X�V
//---------------------------------------------------------------------------------------
void CEnemy::ItemUpdate()
{
	//�A�C�e���g�p�X�e�[�g�ɑ��݂��郆�j�b�g��-1
	CTurn::SumCount(m_nStateNumber);

	//���b�Z�[�W�e�X�g
	MessageWindow::SetMassege(_T("�A�C�e���g����"));

	//���͑҂��X�e�[�g�ɑ��݂��郆�j�b�g��+1
	CTurn::AddCount(m_nStateNumber);

	//�X�e�[�g�̑J��(�^�[���̏I��)
	m_nStateNumber = GAME_STATE_STAND_BY_OTHER;
		
}
//---------------------------------------------------------------------------------------
//�^�[���I���X�V
//---------------------------------------------------------------------------------------
void CEnemy::TurnEndUpdate()
{
	//�^�[���G���h�X�e�[�g�ɑ��݂��郆�j�b�g��-1
	CTurn::SumCount(m_nStateNumber);

	//�X�e�[�g�̑J��(�^�[���̏I��)
	m_nStateNumber = GAME_STATE_STAND_BY_OTHER;

	//���͑҂��ɑ��݂��郆�j�b�g�̐�+1
	CTurn::AddCount(m_nStateNumber);
}