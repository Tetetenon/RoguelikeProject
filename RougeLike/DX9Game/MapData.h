#pragma once


#include "EnemyGenerator.h"
#include "ItemGenerator.h"
#include "define.h"

#include "Structure.h"

//���̃T�C�Y
#define SECTION_MIN_SIZE 8
#define SECTION_MAX_SIZE 10

//�ړ��ł�������̐�
#define MOVEVEC 8

//�}�b�v�T�C�Y
#define MAP_SIZE 30

//�����ł��镔���̍ő吔
#define ROOM_MAX_NUM	(MAP_SIZE / SECTION_MIN_SIZE) * (MAP_SIZE / SECTION_MIN_SIZE)

//�Ƃ����Ă����Ԃ̃T�C�Y
#define MakeHomeSize (6)

//�}�b�v�̏�
enum Situation
{
	//��{�n
	WALL,				//�J�x
	FLOOR,				//��
	ROOT,				//�ʘH
	ROOT_ENTRANCE,		//�ʘH����
	STAIRS,				//�K�i

	BASIC_MAX,

	//�I�u�W�F�N�g�n
	LAKE,			//��
	LAKE_LEFTUP,	//�΍���
	LAKE_LEFTDOWN,	//�΍���
	LAKE_RIGHTUP,	//�ΉE��
	LAKE_RIGHTDOWN,	//�ΉE��
	FOUNTAIN,			//����
	MUSHROOM,			//�L�m�R
	HOME,				//��

	OBJ_MAX,

	//㩌n
	TRAP_POISON,
	TRAP_NUMBNESS,
	TRAP_SLEEP,
	TRAP_CONFUSION,

	TRAP_MAX,

	etc
};

//�}�b�v�����i�[����\����
struct Map
{
	Situation m_terrain;
	int m_item;
	ObjectNumber m_unit;
	int m_isVisible;
	int m_roomnumber;
};

//A*�A���S���Y���Ŏg�p����ۂɗp����\����
struct AStar
{
	int			m_nPosX;
	int			m_nPosZ;
	int			m_nMapStatus;		//�}�b�v�̏�Ԃ�ۑ�
	float		m_nCost;			//�X�^�[�g�ʒu���玩�g�̈ʒu�܂ł̈ړ��R�X�g
	float		m_nHeuristic;		//���g�̈ʒu����ڕW�n�_�܂ł̃R�X�g
	float		m_nScore;			//�R�X�g�ƃq���[���X�e�B�b�N�l�̍��v�l
	D3DXVECTOR2	m_ParentPos;		//���g�̐e�̈ʒu
};

//A*�A���S���Y���ŗp���郊�X�g
struct AStarList
{
	AStar AstarData;
	AStarList* NextData;
};


//�}�b�v���̊Ǘ�
class CMapData
{
private:

	//-----�}�b�v�f�[�^-----
	static Map						m_MapData[MAP_SIZE][MAP_SIZE];				// �V�����}�b�v���

	static bool						m_bCheckFlg[MAP_SIZE][MAP_SIZE];			//�m�F������������
	static int						m_nCost[MAP_SIZE][MAP_SIZE];				//���ݒn����̈ړ��R�X�g
	static int						m_nScore[MAP_SIZE][MAP_SIZE];				//����̈ʒu����ڕW�ʒu�܂ł̃R�X�g

	static LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;								//���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
	static LPDIRECT3DINDEXBUFFER9	m_pD3DIdxBuff;								//�C���f�b�N�X�o�b�t�@
	static D3DXMATRIX				m_mtxWorld;									//���[���h�}�g���b�N�X

	static int						m_NumVertexIndex;							//�C���f�b�N�X��
	static int						m_NumVertex;								//�����_��
	static int						m_NumPolygon;								//�|���S����

	static RECT						m_Section[ROOM_MAX_NUM];					//���
	static RECT						m_Room[ROOM_MAX_NUM];						//�����̑傫��(�Ԏ��?)

	static int						m_CountMakeRoom;							//���ۂɐ������������̐�

	static int						m_nHierarchyNum;							//�K�w����ێ�����

	static LPD3DXFONT				m_pFont;									//�`��t�H���g�̐ݒ�
	static RECT						m_FontDrawPos;								//�t�H���g�̕`��ʒu��ݒ肷��
	static int						m_nDividPattern;							//��������}�b�v�p�^�[��
	

	static AStar		m_AStarData[MAP_SIZE][MAP_SIZE];//A*�A���S���Y���Ɏg�p����\����
	static AStarList*	m_pAstarList;
public:
	//����
	enum VectorFlg
	{
		//�c
		Vectical = 0,
		//��
		Horizon,
		Max
	};

	CMapData(void);										//�R���X�g���N�^
	~CMapData(void);									//�f�X�g���N�^

	void Init();										//������
	void UpDate();										//�X�V
	void Draw();										//�`��
	void Fin();											//�I������
	
	void SetFontPos();									//�����`��ʒu��ݒ�

	//���݂̊K�w�����擾
	static int GetHierarchieNum()	{return m_nHierarchyNum;}

	// ----�n�`���̎擾
	static const Map& Get_MapData(int,int);

	//-----�n�`�}�b�v��Ԏ擾-----
	static int Get_TerrainMapSituation (int,int);				//�n�`�z��̈ʒu���w�肵��Ԃ�Ԃ�

	//-----���j�b�g�}�b�v��Ԏ擾-----
	static int Get_UnitMapSituation (int,int);					//���j�b�g�z��̈ʒu���w�肵�A��Ԃ�Ԃ�

	//-----�A�C�e���}�b�v��Ԏ擾-----
	static int Get_ItemMapSituation (int,int);					//�A�C�e���z��̈ʒu���擾���A��Ԃ�Ԃ�

	//-----���j�b�g�}�b�v����-----
	static void Back_UnitMap	(int,int);				//�w�肵���ʒu�������ɖ߂��B
	static void Set_UnitMap		(int,int,int);			//�w�肵���ʒu�����w�肵���l�ɕύX����B

	//-----����-----
	static void SetDark(int,int, BOOL);
	static void SetVisibleProcess(int,int);
	static void SetRoomVisible(int);

	//-----�A�C�e���}�b�v����-----
	static void Back_ItemMap	(int,int);				//�w�肵���ʒu�������ɖ߂��B
	static void Set_ItemMap		(int,int,int);				//�w�肵���ʒu�����w�肵���l�ɕύX����B

	//-----�}�b�v�����ׂď���������-----
	static void AllInitMapData();

	//-----�}�b�v�𐶐�����-----
	static void MapGeneration();

	//�}�b�v�����ŕ�������
	static void DivideMap();

	//�������쐬����
	static void MakeRoom();

	//�ʘH���쐬����
	static void MakeRoot();

	//�K�i�̈ʒu�����肷��
	static void StairsSet();

	//�w�肳�ꂽ�ʒu���A�����̒������肷��
	static bool CheckInTheRoom(int,int);

	//�w�肳�ꂽ�ʒu�ɊK�i�����邩���f����
	static bool CheckStairs(int,int);

	//�w�肳�ꂽ�ʒu���A�ǂ̕������A���ʂ��A�����ԍ���Ԃ�(�����ɂ��Ȃ���΁A�ő啔���ԍ���n��)
	static int GetRoomNumber(int,int);

	//�w�肳�ꂽ�����ԍ��̊Ԏ����擾����
	static RECT GetRoomFloorPlan(int);

	//���݂̊K�w����`�悷��
	static void DrawHierarchyNum();

	//A*�A���S���Y���p�\���̂̏��������s��
	static void InitAStarData();	

	//A*�A���S���Y���̍\���̂̃f�[�^��ݒ肷��
	static void ASarSetData(int NowPosX,int NowPosZ,int EnemyPosX,int EnemyPosZ,int PlayerPosX,int PlayerPosZ);

	//�w�肳�ꂽ�ʒu���͂̈ړ��\�ȏꏊ�����������X�g�֒ǉ�����
	static void SearchPosition(int SearchPosX,int SearchPosZ,int EnemyPosX,int EnemyPosZ,int PlayerPosX,int PlayerPosZ);

	//A*�A���S���Y���ɂ�����A�l���v�Z����
	static float AStarCalculator(int NowPosX,int NowPosZ,int GoalPosX,int GoalPosZ);

	//���X�g���́A�ł��X�R�A�̏������ʒu���������A�n��
	static void SearchMinScoreData(int *PosX,int *PosZ);

	//�Z���̏�Ԃ�J�ڂ�����
	static void CompleteCellCal(int PosX,int PosZ,int State);

	//�w�肳�ꂽ�ʒu�̐e�̏ꏊ��Ԃ�
	static void GetParentPos(int ChildPosX,int ChildPosZ,int *ParentPosX,int *ParentPosZ);

	//�w�肳�ꂽ��擯�m���ꕔ�ł��d�Ȃ��Ă��邩�Ԃ�
	static bool CheckSectionOverRide(int Section1,int Section2, VectorFlg VectorFlg);

	//�t�B�[���h��ɃI�u�W�F�N�g��z�u����
	static void SetFieldObj();

	//�������������̐����擾����
	static int GetMakeRoomNum()
	{
		return m_CountMakeRoom;
	}
};

