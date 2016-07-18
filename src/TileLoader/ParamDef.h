#ifndef THP_WMTSPARAMDEF_H__
#define THP_WMTSPARAMDEF_H__

/// �·������
#define THP_MAX_PATH	512

/// �����Ƭ�ȼ�
#define THP_MAX_LEVEL	22

/// Ĭ��ͼ��LRUʹ���ڴ棬��λMB
#define THP_WMTS_DEFAULT_MEM_OCCUPY		512//1024

/// ͼ�㻺���С����λkb
#define THP_WMTS_DEFAULT_LRU_CACHE      1048576 // 1024*1024 1GB

/// �ļ�������׺��
#define THP_WMTS_BUNDLE_EXIST_IDXFILE_POSFIX	".bdi"

//localhost:9092/WMTS?service=WMTS&request=GetTile&version=1.0.0&
//layer=img&style=default&format=tiles&TileMatrixSet=c&TileMatrix=3&TileRow=2&TileCol=2
#define WMTS_SERVICE		"SERVICE"
#define WMTS_REQUEST		"REQUEST"
#define WMTS_VERSION		"VERSION"
#define WMTS_LAYER			"LAYER"
#define WMTS_LAYER_STYLE	"STYLE"
#define WMTS_TILE_FORMAT	"FORMAT"
#define WMTS_TILEMATRIXSET	"TILEMATRIXSET"
#define WMTS_TILEMATRIX		"TILEMATRIX"
#define WMTS_TILEROW		"TILEROW"
#define WMTS_TILECOL		"TILECOL"

#define WMTS_SERVICE_VALUE				"WMTS"

#define WMTS_REQUEST_VL_GETTILE			"GetTile"
#define WMTS_REQUEST_VL_CAPABILITIES	"Capabilities"

#define WMTS_VERSION_VL					"1.0.0"

// LRU��������Դ����
#define LAYLRU_MAX_COLDBUNDLE_NUM		10 

#ifndef NULL
#define NULL 0
#endif// #ifndef NULL

/// ����ĳ�ȼ���bundle������ 
struct TileID
{
	/// �ȼ�
	int level;

	/// �к�
	int row;

	/// �к�
	int col;
};

/// ���ļ�(��׺��Ϊ��bundle) ���
struct BundleID
{
	/// �ȼ�
	int nLevel;

	// bundle ���ڵȼ������кſ���ͨ��unBunldeID���㣬Ϊ�˼��ټ������������������ʵ��bundle���
	// �������б�Ų���
	/// bundle ���ڵȼ����к� 
	int nBeginRow;

	/// bundle ���ڵȼ����к� 
	int nBeginCol;
};


#endif // THP_WMTSPARAMDEF_H__
