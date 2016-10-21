#include "MiniMap.h"
#include "TextureManager.h"


C2DTexture	CMiniMap::m_MapPolygon[MAP_SIZE][MAP_SIZE];	//�}�b�v�f�[�^���i�[����
bool		CMiniMap::m_DrawFlg[MAP_SIZE][MAP_SIZE];		//�}�b�v�f�[�^�̕`��t���O�𗧂Ă�
//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CMiniMap::CMiniMap(void)
{
	//�S�Ă̕`��t���O������������
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
		{
			m_DrawFlg[i][j] = false;
		}
	}

	//�S�Ẵ}�b�v�f�[�^��ݒ�
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
		{
			//�ʒu���̐ݒ�
			m_MapPolygon[i][j].SetPos(SCREEN_WIDTH - 215.0f + i * POLYGON_SIZE + POLYGON_HALF_SIZE, 50 + j * POLYGON_SIZE + POLYGON_HALF_SIZE,POLYGON_SIZE,POLYGON_SIZE);

			//�A���t�@�l��ݒ肷��
			m_MapPolygon[i][j].SetAlpha(255 * 0.8);
		}
	}
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CMiniMap::~CMiniMap(void)
{
}


//---------------------------------------------------------------------------------------
//������
//---------------------------------------------------------------------------------------
void CMiniMap::Init(void)
{
	//�S�Ă̕`��t���O������������
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
		{
			m_DrawFlg[i][j] = false;
			m_DrawFlg[i][j] = true;
		}
	}

	//�S�Ẵ}�b�v�f�[�^��ݒ�
	for(int i = 0;i < MAP_SIZE;i++)
	{
		//�n�`�m�F
		for(int j = 0;j < MAP_SIZE;j++)
		{
			int k = 0;
			switch(CMapData::Get_TerrainMapSituation(i,j))
			{
			case STAIRS:
				k = TEXTURE_PURPLE_TEXTURE;
				break;
			case FLOOR:
				k = TEXTURE_FLOOR;
				break;
			default:
				k = TEXTURE_WALL;
				break;
			}
			//�g�p�e�N�X�`���̐ݒ�
			m_MapPolygon[i][j].SetTextureID(k);
		}
	}
}
//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void CMiniMap::Fin(void)
{
}

//---------------------------------------------------------------------------------------
//�~�j�}�b�v��̎w�肳�ꂽ�ʒu�ɃA�C�R����ݒu����
//---------------------------------------------------------------------------------------
void CMiniMap::SetIcon(int nX,int nY,int nNumber)
{
	m_MapPolygon[nX][nY].SetTextureID(nNumber);
}

//---------------------------------------------------------------------------------------
//�~�j�}�b�v��̎w�肳�ꂽ�ʒu��n�`���ɂ���
//---------------------------------------------------------------------------------------
void CMiniMap::Delete(int nX,int nY)
{

	int nTextureNumber = 0;
	switch(CMapData::Get_TerrainMapSituation(nX,nY))
	{
	case STAIRS:
		nTextureNumber = TEXTURE_RED_TEXTURE;
		break;
	case FLOOR:
		nTextureNumber = TEXTURE_FLOOR;
		break;
	default:
		nTextureNumber = TEXTURE_WALL;
		break;
	}
	//�g�p�e�N�X�`���̐ݒ�
	m_MapPolygon[nX][nY].SetTextureID(nTextureNumber);
}



//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CMiniMap::Draw()
{
	//�S�Ẵ|���S���ɑ΂��������s��
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE; j++)
		{
			//�`��t���O�������Ă����ꍇ�A�`����s��
			if(m_DrawFlg[i][j])
				m_MapPolygon[i][j].Draw();
		}
	}
}
//---------------------------------------------------------------------------------------
//�X�V����
//---------------------------------------------------------------------------------------
void CMiniMap::Update(void)
{
}
//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�ʒu�̕`��t���O�𗧂Ă�
//---------------------------------------------------------------------------------------
void CMiniMap::DrawFlgUp (int nX,int nZ)
{
	m_DrawFlg[nX][nZ] = true;
}
//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�ʒu�̕`��t���O��Ԃ�
//---------------------------------------------------------------------------------------
bool CMiniMap::GetDrawFlg(int nX,int nZ)
{
	return m_DrawFlg[nX][nZ];
}