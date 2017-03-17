#pragma once
#include "MapData.h"
#include "C2DTexture.h"

class CEditTexture;
class CMapData;

class CMiniMap : public C2DTexture
{
public:
	enum
	{
		GRID_SIZE = 3,
		LINE_SPACE = 1,
		GRID_NUM = MAP_SIZE,
		POLYGON_WIDTH = GRID_SIZE * GRID_NUM + (GRID_NUM - 1) * LINE_SPACE,
		POLYGON_HEIGHT = GRID_SIZE * GRID_NUM + (GRID_NUM - 1) * LINE_SPACE,
		POLYGON_ORIGIN_X = 600,
		POLYGON_ORIGIN_Y = 10,
		MINIMAP_ALPHA = 180,
	};
	enum
	{
		NORMAL_MAP_MODE = 0,
		BIG_MAP_MODE,
		DELETE_MAP_MODE,
		MAX_MAP_MODE
	};

private:
	static CMiniMap* m_pMinimap;
	CEditTexture*		m_pEditTexture;						//�~�j�}�b�v�e�N�X�`������
	CMapData*			m_pMapData;

	int m_nMapMode;								//�}�b�v�̃|���S���T�C�Y
	int	m_nInterval;

	CMiniMap(void);								//�R���X�g���N�^
	~CMiniMap(void);							//�f�X�g���N�^
public:
	static void Create();						//���̂̍쐬
	static void Delete();						//���̂̍폜
	static CMiniMap* GetPointer();				//���̂̃|�C���^��n��

	void Update();								// �X�V
	void Draw () override;						//�`��

	//�����o�ϐ��̃|�C���^��n��
	void SetPointer();

	//�|���S���̃T�C�Y��ύX����
	void SizeChange();
};