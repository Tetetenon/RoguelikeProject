#pragma once

#include "EnemyGenerator.h"
#include "ItemGenerator.h"

#include "Structure.h"

//���̃T�C�Y
#define SECTION_MIN_SIZE 8
#define SECTION_MAX_SIZE 10

//�}�b�v�T�C�Y
#define MAP_SIZE 30

//�����ł��镔���̍ő吔
#define ROOM_MAX_NUM	(MAP_SIZE / SECTION_MIN_SIZE) * (MAP_SIZE / SECTION_MIN_SIZE)


//�}�b�v�����i�[����\����
typedef struct
{
	int m_Map_Situation;		//�}�b�v��(�ǁA���A�ǂ̒��A�v���C���[������A�G�l�~�[������cect)
}Map;

//�}�b�v�̏�
enum Situation
{
	IN_THE_WALL = -1,	//�ǂ̒�
	WALL_UP  = 1,	//��(�����)
	WALL_DOWN,		//��(������)
	WALL_RIGH,		//��(�E����)
	WALL_LEFT,		//��(������)
	FLOOR,			//��
	STAIRS,			//�K�i
	etc
};

//�}�b�v���̊Ǘ�
class CMapData
{
private:

	//-----�}�b�v�f�[�^-----
	static Map						m_TerrainMap[MAP_SIZE][MAP_SIZE];			//�}�b�v���
	static Map						m_ItemMap[MAP_SIZE][MAP_SIZE];				//�}�b�v��̃A�C�e�����i�[
	static Map						m_UnitMap[MAP_SIZE][MAP_SIZE];				//�}�b�v��̃��j�b�g���i�[


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
public:
	CMapData(void);										//�R���X�g���N�^
	~CMapData(void);									//�f�X�g���N�^

	void Init();										//������
	void UpDate();										//�X�V
	void Draw();										//�`��
	void Fin();											//�I������
	
	void SetFontPos();									//�����`��ʒu��ݒ�


	//-----�n�`�}�b�v��Ԏ擾-----
	static int Get_TerrainMapSituation (int,int);				//�n�`�z��̈ʒu���w�肵��Ԃ�Ԃ�

	//-----���j�b�g�}�b�v��Ԏ擾-----
	static int Get_UnitMapSituation (int,int);					//���j�b�g�z��̈ʒu���w�肵�A��Ԃ�Ԃ�

	//-----�A�C�e���}�b�v��Ԏ擾-----
	static int Get_ItemMapSituation (int,int);					//�A�C�e���z��̈ʒu���擾���A��Ԃ�Ԃ�

	//-----���j�b�g�}�b�v����-----
	static void Back_UnitMap	(int,int);				//�w�肵���ʒu�������ɖ߂��B
	static void Set_UnitMap		(int,int,int);			//�w�肵���ʒu�����w�肵���l�ɕύX����B

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
};

