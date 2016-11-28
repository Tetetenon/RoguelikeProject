#pragma once
#include "C2DTexture.h"
#include "MapData.h"

//�~�j�}�b�v�̂P�|���S���̃T�C�Y
#define POLYGON_SIZE		(200 / MAP_SIZE)
#define POLYGON_HALF_SIZE	(POLYGON_SIZE / 2)

class CMiniMap
{
private:
	static C2DTexture	m_MapPolygon[MAP_SIZE][MAP_SIZE];	//�}�b�v�f�[�^���i�[����
	static bool			m_DrawFlg[MAP_SIZE][MAP_SIZE];		//�}�b�v�f�[�^�̕`��t���O�𗧂Ă�
public:
	CMiniMap(void);								//�R���X�g���N�^
	~CMiniMap(void);							//�f�X�g���N�^

	void Init();								//������
	void Fin();									//�I������

	void Draw ();								//�`��
	void Update();								//�X�V

	static void DrawFlgUp(int nX,int nZ);				//���B���������̕`��t���O�𗧂Ă�
	static bool GetDrawFlg(int nX,int nZ);				//�w�肳�ꂽ�ʒu�̕`��t���O��Ԃ�

	static void SetIcon(int nX,int nZ,int nNumber);		//�w�肳�ꂽ�ʒu�Ɏw�肳�ꂽ�A�C�R����ݒu����
	static void Delete(int nX,int nZ);					//�w�肳�ꂽ�ʒu�̏���n�`���ɖ߂�

	static void MiniMapBack(int nX,int nZ);				//�w�肵���ʒu�̃}�b�v��Ԃ����Ƃɖ߂�
};

