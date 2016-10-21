//���@�N���X�@����
#include "Player.h"
#include "Input.h"
#include "Enemy.h"
#include "ItemCommandCursor.h"
#include "ItemWindowCursor.h"
#include "EquipmentCommandWindow.h"
#include "EnemyGenerator.h"
#include "MessageWindow.h"
#include "ModelManager.h"
#include "Turn.h"
#include "GameScene.h"
#include "HPDraw.h"
#include "MenuWindow.h"
#include "EquipmentWindowCursor.h"
#include "TextureManager.h"
#include "MiniMap.h"

CInventoryCursor	CPlayer::m_InventoryCursor;	//�A�C�e���E�C���h�E�̃J�[�\���̈ʒu����肷��
CCommandCursor		CPlayer::m_CommandCursor;	//�R�}���h�J�[�\���̈ʒu����肷��

LPD3DXFONT			CPlayer::m_pFont;			//�`��t�H���g�̐ݒ�
RECT				CPlayer::m_FontDrawPos;		//�t�H���g�̕`��ʒu��ݒ肷��
int					CPlayer::m_nDividPattern;	//��������}�b�v�p�^�[��

int		CPlayer::m_State_Cpy;					//�O������X�e�[�g�̕ύX���|����
bool	CPlayer::m_bState_Change_Flg = false;;	//�O������̃X�e�[�g�ύX������������

#define PATH_DATA_PLAYER		("../data/txt/Player.txt")
#define PATH_LEVEL_UP_PLAYER	("../data/txt/LevelUp_Player.txt")
#define SPEED 0.0f

using namespace std;
//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CPlayer::CPlayer(CGameScene* pScene):
CUnit(pScene)
{
	//�I�u�W�F�N�g��ID��ݒ�
	m_uID = ID_PLAYER;

	//���j�b�g�̃X�e�[�g��ݒ�
	m_nStateNumber = GAME_STATE_STAND_BY_PLAYER;

	//�g�p���郂�f���ԍ���ݒ�
	m_nMeshNumber = MODEL_PLAYER;
	
	//�f�o�C�X�i�[
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//�t�H���g�ւ̃|�C���^���擾����
	D3DXCreateFont(pDevice,24,0,1,0,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,NULL,&m_pFont);
	//�t�H���g�`��ʒu��ݒ�
	SetFontPos();
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CPlayer::~CPlayer(void)
{
}

//---------------------------------------------------------------------------------------
//������
//---------------------------------------------------------------------------------------
void CPlayer::Init()
{
	//���j�b�g�̔ԍ���ݒ�
	m_nUnitNumber = OBJ_NUM_PLAYER;

	//���j�b�g���������J�E���g
	m_nMakeNumber ++;

	//���b�V���I�u�W�F�N�g�Ƃ��ď�����
	CMeshObj::Init();

	//���j�b�g�Ƃ��ď�����
	CUnit::Init();

	//�I�u�W�F�N�g��ID��ݒ�
	m_uID = ID_PLAYER;

	//���b�V���f�[�^�̐ݒ�
	SetMesh(CModelManager::GetMesh(m_nMeshNumber));
	
	//-----�X�e�[�^�X�f�[�^�̓ǂݍ���-----
    //�t�@�C���̓ǂݍ���
    ifstream ifs(PATH_DATA_PLAYER);

    if(!ifs)
	{
		LPCTSTR szMsg = _T("�ǂݍ��ݎ��s!");
   		 MessageBox(NULL, szMsg, NULL, MB_OK);
	}
    //txt�t�@�C����1�s���ǂݍ���
    string str;
	int i = 0;	//�i�[�z��W��
	int PlayerData[STATES_MAX];	//�X�e�[�^�X�l

    while(getline(ifs,str))
	{
        string token;
        istringstream stream(str);

        //1�s�̂����A������ƃR���}�𕪊�����(�R���}���o�Ă���܂œǂݍ���)
        while(getline(stream,token,','))
		{
			PlayerData[i] = (int)stof(token);
			i++;
        }
    }
	//�t�@�C�������
	ifs.close();

	//-----���x���A�b�v�f�[�^�̓ǂݍ���-----
    //�t�@�C���̓ǂݍ���
	ifstream ifsLevel(PATH_LEVEL_UP_PLAYER);

    if(!ifsLevel)
	{
		LPCTSTR szMsg = _T("�ǂݍ��ݎ��s!");
   		 MessageBox(NULL, szMsg, NULL, MB_OK);
	}
    //txt�t�@�C����1�s���ǂݍ���
	int PlayerUpData[UPSTATES_MAX];	//���x���A�b�v���㏸�l�i�[
	i = 0;
    while(getline(ifsLevel,str))
	{
        string token;
        istringstream stream(str);

        //1�s�̂����A������ƃR���}�𕪊�����(�R���}���o�Ă���܂œǂݍ���)
        while(getline(stream,token,','))
		{
			PlayerUpData[i] = (int)stof(token);
			i++;
        }
    }
	//�t�@�C�������
	ifs.close();

	//-----�X�e�[�^�X�̐ݒ�-----

	//���O�̐ݒ�
	_stprintf(m_szName, _T("�Ԃ�����"));

	//HP��ݒ�
	m_nMaxHP = PlayerData[STATES_MAX_HP];
	m_nHP = PlayerData[STATES_HP];

	//�U���͂�ݒ�
	m_nAttack = PlayerData[STATES_AT];

	//�h��͂�ݒ�
	m_nDefence = PlayerData[STATES_DF];

	//�o���l�~�ϒl��ݒ�
	m_nExp = PlayerData[STATES_EXP];

	//�|���ē�����o���l��ݒ�
	m_nXp = PlayerData[STATES_XP];

	//-----���x���A�b�v���̏㏸�l��ݒ�-----
	//�ő�HP
	m_nHPUpNum = PlayerUpData[UPSTATES_MAX_HP];
	//�U����
	m_nAttackUpNum = PlayerUpData[UPSTATES_AT];
	//�h���
	m_nDefenceUpNum = PlayerUpData[UPSTATES_DF];

	//�����Ă���
	m_bSurvival = true;

	//�ʒu���̐ݒ�
	SetPos();

	//��ʂɕ`�悵�Ă��炤�ő�HP��n��
	CHPDraw::SetMaxHP(m_nMaxHP);

	//��ʂɕ`�悵�Ă��炤HP�̐��l��n��
	CHPDraw::SetHP(m_nHP);

	//�X�e�[�g�̐ݒ�
	m_nStateNumber = m_State_Cpy = GAME_STATE_STAND_BY_PLAYER;

	//�O������̃X�e�[�g�ύX�Ȃ�
	m_bState_Change_Flg = false;

	//���͑҂��ɑ��݂��郆�j�b�g��+1
	CTurn::AddCount(m_nStateNumber);

	//�����R�}���h�E�B���h�E�`�掞�Ԃ�������
	m_nEquipmentInterval = 0;

	m_bDirectionFlg[Forword] = true;
}
//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void CPlayer::Fin()
{
	//���b�V���I�u�W�F�N�g�Ƃ��Ă̏I������
	CMeshObj::Fin();
	//�A�C�e���C���x���g���̏I������
	m_pInventory ->Fin();

	//�����C���x���g���̏I������
	m_pEquipment ->Fin();
}
//---------------------------------------------------------------------------------------
//�����`��ʒu��ݒ�
//---------------------------------------------------------------------------------------
void CPlayer::SetFontPos()
{
	m_FontDrawPos.left		= (LONG)125.0f;
	m_FontDrawPos.top		= (LONG) 70.0f;
	m_FontDrawPos.right		= (LONG)230.0f;
	m_FontDrawPos.bottom	= (LONG) 90.0f;
}

//---------------------------------------------------------------------------------------
//�X�V����
//---------------------------------------------------------------------------------------
void CPlayer::Update()
{

	//�O������ύX�����X�e�[�g���m�F���A�Ⴆ�Ζ{���̃X�e�[�g���ύX��������
	if(m_bState_Change_Flg)
	{
		m_nStateNumber = m_State_Cpy;
		m_bState_Change_Flg = false;
	}

	//�R�s�[��ݒ�
	m_State_Cpy = m_nStateNumber;
	//���j�b�g�{���̍X�V��������
	CUnit::Update();

	//������ʂ̃R�}���h��`�悵�Ă��āA����{�^���������Ă���΁A�����A�C�e�����A�C�e�����ɖ߂�
	if(CEquipmentCommandWindow::GetDrawFlg())
	{
		//�����R�}���h�E�B���h�E�̕`�掞�Ԃ����Z
		m_nEquipmentInterval++;

		if(CInput::GetKeyTrigger(DIK_L) && m_nEquipmentInterval > 30)
		{
			if(m_pInventory->SetItem(m_pEquipment->GetItem(CEquipmentInventoryCursor::GetItemNum())))
			{
				//���b�Z�[�W�\�L
				TCHAR	str[256];
				_stprintf(str, _T("%s��߂���"),m_pEquipment->GetInventoryItemName(CEquipmentInventoryCursor::GetItemNum()));
	
				//���b�Z�[�W�e�X�g
				MessageWindow::SetMassege(str);

				//�����C���x���g�����̃A�C�e���̔j��
				m_pEquipment->DelInventory(CEquipmentInventoryCursor::GetItemNum());

				//�R�}���h�E�B���h�E�`�掞�Ԃ�������
				m_nEquipmentInterval= 0;
			}
			else
			{
	
				//���b�Z�[�W�e�X�g
				MessageWindow::SetMassege(_T("�A�C�e���������ς�������!"));

				//�R�}���h�E�B���h�E�`�掞�Ԃ�������
				m_nEquipmentInterval= 0;
			}
		}
	}

	//-----�X�e�[�^�X�`��̂��߁A�v���C���[�̃X�e�[�^�X�f�[�^��n��-----
	//�U����(�������Z�̕����`��)
	CStatesValue::SetNumAttack(m_nAttack + m_pEquipment -> GetAttackTotalValue());
	//�h���(�������Z�����`��)
	CStatesValue::SetNumDefence(m_nDefence + m_pEquipment ->GetDefenceTotalValue());
	//�o���l
	CStatesValue::SetNumExp(m_nExp);
}

//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CPlayer::Draw()
{
	//���j�b�g�Ƃ��Ă̕`�揈��
	CUnit::Draw();
}
//---------------------------------------------------------------------------------------
//�O������X�e�[�g�̕ύX��������
//---------------------------------------------------------------------------------------
void CPlayer::SetState(int nState)
{
	m_State_Cpy = nState;
	m_bState_Change_Flg = true;
}

//---------------------------------------------------------------------------------------
//���݂̃X�e�[�g����n��
//---------------------------------------------------------------------------------------
int CPlayer::GetState()	
{
	return m_State_Cpy;
}
//---------------------------------------------------------------------------------------
//���͍X�V
//---------------------------------------------------------------------------------------
void CPlayer::InputUpdate()
{
	//�A�C�e���E�C���h�E��`�悵�Ă��Ȃ���΍X�V
	if(!m_pInventory->GetDrawFlg() && m_nStateNumber == CTurn::GetState())
	{
		//��]�x��������
		m_Angle = D3DXVECTOR3(0.0f,0.0f,0.0f);

		//�ړ��t���O
		bool bMoveSuccess = false;

		//-----�����L�[���͂�����-----
		if(CInput::GetKeyPress(DIK_W) || CInput::GetKeyPress(DIK_S) || CInput::GetKeyPress(DIK_A) || CInput::GetKeyPress(DIK_D))
		{
			//���j���[�E�B���h�E���o�Ă��Ȃ���΍U��
			if(!CMenuWindow::GetDrawFlg())
			{
				//�����t���O������
				for(int i = 0;i < MaxDirection;i++)
					m_bDirectionFlg[i] = false;
		
				//�ړ��\��̈ʒu
				int PosX = m_nUnit_Pos_X;
				int PosZ = m_nUnit_Pos_Z;
				//-----��ړ�-----
				if(CInput::GetKeyPress(DIK_W))
				{	
					//�����t���O��
					m_bDirectionFlg[Forword] = true;

					//�X�y�[�X�L�[�������Ă��Ȃ������ꍇ�A�ړ�����
					if(!CInput::GetKeyPress(DIK_Q))
					{
						//�s����ݒ�
						PosZ --;

						//�ړ��t���O�@�^
						bMoveSuccess = true;
					}
				}
				//-----���ړ�-----
				if(CInput::GetKeyPress(DIK_S))
				{
					//�����t���O��
					m_bDirectionFlg[Back] = true;

					//�X�y�[�X�L�[�������Ă��Ȃ������ꍇ�A�ړ�����
					if(!CInput::GetKeyPress(DIK_Q))
					{
						//�s����ݒ�
						PosZ ++;

						//�ړ��t���O�@�^
						bMoveSuccess = true;
					}
				}
				//-----�E�ړ�-----
				if(CInput::GetKeyPress(DIK_D))
				{
					//�����t���O�E
					m_bDirectionFlg[Right] = true;

					//�X�y�[�X�L�[�������Ă��Ȃ������ꍇ�A�ړ�
					if(!CInput::GetKeyPress(DIK_Q))
					{
						//�s����ݒ�
						PosX ++;

						//�ړ��t���O�@�^
						bMoveSuccess = true;
					}
				}
				//-----���ړ�-----
				if(CInput::GetKeyPress(DIK_A))
				{
					//�����t���O��
					m_bDirectionFlg[Left] = true;

					//�X�y�[�X�������Ă��Ȃ������ꍇ�A�ړ�����
					if(!CInput::GetKeyPress(DIK_Q))
					{
						//�s����ݒ�
						PosX --;

						//�ړ��t���O�@�^
						bMoveSuccess = true;
					}
				}
				
				//������Ԃ̏ꍇ�A�ړ������������_���ɕύX����
				if(m_nState == UNIT_STATE_CONFUSION && bMoveSuccess)
				{
					//�����t���O������
					for(int i = 0;i < MaxDirection;i++)
						m_bDirectionFlg[i] = false;
		
					//�ړ��\��̈ʒu������
					PosX = m_nUnit_Pos_X;
					PosZ = m_nUnit_Pos_Z;

					//�ړ��������l�����烉���_���ɐݒ�
					switch(rand()%2)
					{
					case 0:
						//�s��ݒ�
						PosZ--;
						//�����t���O��
						m_bDirectionFlg[Forword] = true;
						break;
					case 1:
						//�s��ݒ�
						PosZ ++;
						//�����t���O��
						m_bDirectionFlg[Back] = true;
						break;
					}
					switch(rand()%3)
					{
					case 0:
						//�s��ݒ�
						PosX--;
						//�����t���O��
						m_bDirectionFlg[Left] = true;
						break;
					case 1:
						//�s��ݒ�
						PosX ++;
						//�����t���O�E
						m_bDirectionFlg[Right] = true;
						break;
					default:
						//�ړ����Ȃ�
						break;
					}
				}

				//�ړ��t���O�������Ă����ꍇ
				if(bMoveSuccess)
				{

					//�ړ���̃}�b�v�󋵂��擾����
					int Situation = CMapData::Get_TerrainMapSituation(PosX,PosZ);

					//�ړ���ɃG�l�~�[���ق��̃��j�b�g�����Ȃ����m�F����
					int EnemySearch = CMapData::Get_UnitMapSituation(PosX,PosZ);

					//�ړ��悪��(���͊K�i)�Ȃ�Έړ��\
					if((FLOOR == Situation || STAIRS == Situation) && EnemySearch == 0)
					{
						//�}�[�L���O����
						CMapData::Back_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z);

						//�~�j�}�b�v��̈ʒu�����폜
						CMiniMap::Delete(m_nUnit_Pos_X,m_nUnit_Pos_Z);

						//�ړI�n�ɓ��B���Ă��Ȃ�
						m_bDestination = false;
						m_fTimer = 0.0f;
						
						//�ړ����{���̈ʒu�ɐݒ�
						m_nUnit_Pos_X = PosX;
						m_nUnit_Pos_Z = PosZ;

						//�}�[�L���O
						CMapData::Set_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z,m_nUnitNumber);

						//�~�j�}�b�v��Ɉʒu�����Z�b�g
						CMiniMap::SetIcon(m_nUnit_Pos_X,m_nUnit_Pos_Z,TEXTURE_BLUE_TEXTURE);

						//���͑҂��ɑ��݂��郆�j�b�g�̐�-1
						CTurn::SumCount(m_nStateNumber);

						//�X�e�[�g�̑J��
						m_nStateNumber =  m_State_Cpy = GAME_STATE_MOVE;

						//�ړ��X�e�[�g�ɑ��݂��郆�j�b�g��+1
						CTurn::AddCount(m_nStateNumber);


						//�������K�i�ł���Ώ��
						if(Situation == STAIRS)
						{
							//�V�[���̃}�b�v�Đ����t���O�𗧂Ă�
							CGameScene::MapReMake();
						}
					}
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

				int OldAngle = (int)(m_fOldAngle * 180 / PI );
				float RotateAngle = (float)(nAngle * PI / 180);

				m_Angle.y = RotateAngle - m_fOldAngle;

				m_fOldAngle = RotateAngle;
			}
		}
		//-----�U��-----
		if(CInput::GetKeyTrigger(DIK_L))
		{
			//���j���[�E�B���h�E���o�Ă��Ȃ���΍U��
			if(!CMenuWindow::GetDrawFlg())
			{
				//���͑҂��ɑ��݂��郆�j�b�g�̐�-1
				CTurn::SumCount(m_nStateNumber);

				//�X�e�[�g�̑J��
				m_nStateNumber =  m_State_Cpy = GAME_STATE_ATTACK;

				//�U���X�e�[�g�ɑ��݂��郆�j�b�g��+1
				CTurn::AddCount(m_nStateNumber);

				//�J��o���Z�̔ԍ����w��
				m_nTrickNumber = TRICK_RANGE_FRONT;
			}
		}

		//-----������-----
		if(CInput::GetKeyTrigger(DIK_E))
		{
			//�^�[���X�L�b�v
			
			//���͑҂��ɑ��݂��郆�j�b�g�̐�-1
			CTurn::SumCount(m_nStateNumber);

			//���g�̃X�e�[�g�̐ݒ�
			m_nStateNumber = GAME_STATE_TURN_END;

			//�^�[���I���ɑ��݂��郆�j�b�g�̐�+1
			CTurn::AddCount(m_nStateNumber);
		}
		
		//�e�X�g(��)
		if(CInput::GetKeyTrigger(DIK_UP))
		{
			SetStateAbnormal(UNIT_STATE_POISON);
		}
		//�e�X�g(����)
		if(CInput::GetKeyTrigger(DIK_DOWN))
		{
			SetStateAbnormal(UNIT_STATE_CONFUSION);
		}
		//�e�X�g(���)
		if(CInput::GetKeyTrigger(DIK_RIGHT))
		{
			SetStateAbnormal(UNIT_STATE_PARALYSIS);
		}
		//�e�X�g(����)
		if(CInput::GetKeyTrigger(DIK_LEFT))
		{
			SetStateAbnormal(UNIT_STATE_SLEEP);
		}
		//�e�X�g
		if(CInput::GetKeyPress(DIK_V))
		{
			//�V�[���̃}�b�v�Đ����t���O�𗧂Ă�
			CGameScene::MapReMake();
		}

		//-----���j���[�E�B���h�E-----
		if(CInput::GetKeyTrigger(DIK_I))
		{
			//���j���[�E�C���h�E�`��t���O�𗧂Ă�
			CMenuWindow::ChangDrawFlg();
		}

		//���[���h�}�g���b�N�X���烍�[�J�������o�A���W���o
		D3DXMATRIX world = GetWorld();

		//���ꂼ��̎��̒l���i�[����
		D3DXVECTOR3 vX,vY,vZ,vP;
		
		vX = D3DXVECTOR3(world._11,world._12,world._13);	//vX:X����]
		vY = D3DXVECTOR3(world._21,world._22,world._23);	//vY:Y����]
		vZ = D3DXVECTOR3(world._31,world._32,world._33);	//vZ:Z����]
		vP = D3DXVECTOR3(world._41,world._42,world._43);	//�ʒu���

		
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
void CPlayer::MoveUpdate()
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
			
			//�X�e�[�g�̑J��(�^�[���̏I��)
			m_nStateNumber =  m_State_Cpy = GAME_STATE_STAND_BY_PLAYER;
			
			//���͑҂��X�e�[�g�ɑ��݂��郆�j�b�g��+1
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

	vP = vP + (m_Pos - vP) * (m_fTimer / ACTION_TIME);

	//�ړ�����
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
//�A�N�V�����X�V
//---------------------------------------------------------------------------------------
void CPlayer::ActUpdate()
{
	//�A�N�V�����X�e�[�g�ɑ��݂��郆�j�b�g�̐�-1
	CTurn::SumCount(m_nStateNumber);

	//�X�e�[�g�̑J��(�^�[���̏I��)
	m_nStateNumber =  m_State_Cpy = GAME_STATE_STAND_BY_PLAYER;

	//���͑҂��ɑ��݂��郆�j�b�g�̐�+1
	CTurn::AddCount(m_nStateNumber);

	//���b�Z�[�W�e�X�g
	MessageWindow::SetMassege(_T("�s������"));
}
//---------------------------------------------------------------------------------------
//�^�[���I���X�V
//---------------------------------------------------------------------------------------
void CPlayer::TurnEndUpdate()
{
	//�^�[���I���X�e�[�g�ɑ��݂��郆�j�b�g�̐�-1
	CTurn::SumCount(m_nStateNumber);

	//�X�e�[�g�̑J��(�^�[���̏I��)
	m_nStateNumber =  m_State_Cpy = GAME_STATE_STAND_BY_PLAYER;

	//���͑҂��X�e�[�g�ɑ��݂��郆�j�b�g�̐�+1
	CTurn::AddCount(m_nStateNumber);
}
//---------------------------------------------------------------------------------------
//�A�C�e���X�V
//---------------------------------------------------------------------------------------
void CPlayer::ItemUpdate()
{
	//�I�����ꂽ�R�}���h�ɂ���ď����𕪊򂳂���
	switch(m_CommandCursor.GetCommand())
	{
		//�A�C�e�����g�p����
	case COMMAND_USE:

		//���b�Z�[�W�e�X�g
		MessageWindow::SetMassege(_T("�A�C�e�����g����"));

		//�A�C�e���̌��ʂɂ���Ď擾����l��ύX����
		switch(m_pInventory->GetEffect(m_InventoryCursor.GetItemNum()))
		{
			//���ʂȂ�
		case EFFECT_NON:
		case EFFECT_EQUIPMENT_ATTACK:
		case EFFECT_EQUIPMENT_DEFENCE:
			//���b�Z�[�W�e�X�g
			MessageWindow::SetMassege(_T("�c���A�����N����Ȃ�����"));
			break;
			//�񕜌���
		case EFFECT_RECOVERY:

			//�A�C�e���̉񕜌��ʂ̉񕜗ʂ��擾����
			RecoveryHP(m_pInventory->GetEffectValue(m_InventoryCursor.GetItemNum()));

			//���b�Z�[�W�e�X�g
			MessageWindow::SetMassege(_T("�̗͂��񕜂���!"));
		//��ʂɕ`�悵�Ă��炤HP�̐��l��n��
		CHPDraw::SetHP(m_nHP);
			
			break;

			//�f�o�b�O�p
		default:
			//���b�Z�[�W�e�X�g
			MessageWindow::SetMassege(_T("�Ȃ񂩊Ԉ���Ă�?"));
			break;
		}

		//�g�p�A�C�e���̔j��
		m_pInventory->DelInventory(m_InventoryCursor.GetItemNum());

		break;
		//�A�C�e���𑕔�����
	case COMMAND_EQUIPMENT:

		//�����C���x���g������A�����ł���X�y�[�X�����邩�T���A����Α����C���x���g���Ɋi�[����
		if(m_pEquipment->SetItem(m_pInventory->GetItem(m_InventoryCursor.GetItemNum())))
		{
			//���b�Z�[�W�\�L
			TCHAR	str[256];
			_stprintf(str, _T("%s��%s�𑕔�����"),m_szName,m_pInventory->GetInventoryItemName(m_InventoryCursor.GetItemNum()));
	
			//���b�Z�[�W�e�X�g
			MessageWindow::SetMassege(str);

			//�A�C�e���C���x���g�����̃A�C�e���̔j��
			m_pInventory->DelInventory(m_InventoryCursor.GetItemNum());
		}
		else
		{
			//���b�Z�[�W�\�L
			TCHAR	str[256];
			_stprintf(str, _T("�����������ς�������!"));
	
			//���b�Z�[�W�e�X�g
			MessageWindow::SetMassege(_T("�����������ς�������"));
		}
		break;
		//�A�C�e�����̂Ă�
	case COMMAND_RELINQUISH:

		//�A�C�e���̔j��
		m_pInventory->DelInventory(m_InventoryCursor.GetItemNum());

		//���b�Z�[�W�e�X�g
		MessageWindow::SetMassege(_T("�A�C�e�����̂Ă�"));

		break;
	}

	//�A�C�e���g�p�X�e�[�g�ɑ��݂��郆�j�b�g-1
	CTurn::SumCount(m_nStateNumber);

	//�X�e�[�g�̑J��(�^�[���̏I��)
	m_nStateNumber =  m_State_Cpy = GAME_STATE_TURN_END;

	//���͑҂��X�e�[�g�ɑ��݂��郆�j�b�g��+1
	CTurn::AddCount(m_nStateNumber);
}

//---------------------------------------------------------------------------------------
//�ʒu�̍Đݒ�
//---------------------------------------------------------------------------------------
void CPlayer::SetPos()
{
	//�ʒu����ݒ�
	m_nUnit_Pos_X = rand()%MAP_SIZE;
	m_nUnit_Pos_Z = rand()%MAP_SIZE;

	//�ʒu���ݒu�s�\�Ȃ�΁A�Đݒ�
	while(!CMapData::CheckInTheRoom(m_nUnit_Pos_X,m_nUnit_Pos_Z))
	{
		m_nUnit_Pos_X = rand()%MAP_SIZE;
		m_nUnit_Pos_Z = rand()%MAP_SIZE;
	}

	//���[���h�}�g���b�N�X���烍�[�J�������o�A���W���o
	D3DXMATRIX world = GetWorld();
	
	//���f���̃X�P�[����ύX����
	D3DXMatrixScaling(&world,0.2f,0.2f,0.2f);

	//�ʒu���ݒ�
	world._41 = (m_nUnit_Pos_X - (MAP_SIZE / 2)) * GRIDSIZE + GRIDSIZE / 2;
	world._42 = 0.0f;
	world._43 = -((m_nUnit_Pos_Z) - (MAP_SIZE / 2)) * GRIDSIZE - GRIDSIZE / 2;

	//���[���h�}�g���b�N�X��ݒ�
	SetWorld(world);

	//�}�[�L���O
	CMapData::Set_UnitMap(m_nUnit_Pos_X,m_nUnit_Pos_Z,m_nUnitNumber);

	//�~�j�}�b�v��Ɏ��g�̈ʒu��ݒ�
	CMiniMap::SetIcon(m_nUnit_Pos_X,m_nUnit_Pos_Z,TEXTURE_BLUE_TEXTURE);

	//�ړ��X�e�[�g�ɑ��݂��郆�j�b�g�̐�-1
	CTurn::SumCount(m_nStateNumber);
	
	//�X�e�[�g�̑J��(�^�[���̏I��)
	m_nStateNumber =  m_State_Cpy = GAME_STATE_STAND_BY_PLAYER;
	
	//���͑҂��X�e�[�g�ɑ��݂��郆�j�b�g��+1
	CTurn::AddCount(m_nStateNumber);

	//�ړI�n������
	m_Pos = D3DXVECTOR3(world._41,world._42,world._43);
	
	//������������
	m_fOldAngle = 0;

	//���͎��ԏ�����
	m_fTimer = 0.0f;

	//�ړI�n�ɓ��B���Ă���
	m_bDestination = true;
}
//---------------------------------------------------------------------------------------
//�A�C�e���E�B���h�E�̕`��
//---------------------------------------------------------------------------------------
void CPlayer::DrawInventory()
{
	m_pInventory ->Draw();
}
//---------------------------------------------------------------------------------------
//�����E�B���h�E�̕`��
//---------------------------------------------------------------------------------------
void CPlayer::DrawEquipment()
{
	m_pEquipment ->Draw();
}
//---------------------------------------------------------------------------------------
//�Z�E�B���h�E�̕`��
//---------------------------------------------------------------------------------------
void CPlayer::DrawTrick()
{
	m_pTrickWindow ->Draw();
}
//---------------------------------------------------------------------------------------
//���x���̕`��
//---------------------------------------------------------------------------------------
void CPlayer::DrawLevel()
{
	char Level[256];
	_stprintf(Level, _T("Level:%d"), m_nLevel);
	//���l(����)�`��
	m_pFont ->DrawText(NULL,Level,-1,&m_FontDrawPos,DT_LEFT,D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
}