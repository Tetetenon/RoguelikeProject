#pragma once
#include "MapData.h"
#include "C2DTexture.h"

class CEditTexture;

class CMiniMap : public C2DTexture
{
public:
	enum
	{
		GRID_SIZE = 7,
		LINE_SPACE = 1,
		GRID_NUM = MAP_SIZE,
		POLYGON_WIDTH = GRID_SIZE * GRID_NUM + (GRID_NUM - 1) * LINE_SPACE,
		POLYGON_HEIGHT = GRID_SIZE * GRID_NUM + (GRID_NUM - 1) * LINE_SPACE,
		POLYGON_ORIGIN_X = 550,
		POLYGON_ORIGIN_Y = 30,
		MINIMAP_ALPHA = 200,
	};
private:

	CEditTexture*		m_pEditTexture;						//�~�j�}�b�v�e�N�X�`������
public:
	CMiniMap(void);								//�R���X�g���N�^
	~CMiniMap(void);							//�f�X�g���N�^
	void Update();								// �X�V
	void Draw () override;						//�`��
};