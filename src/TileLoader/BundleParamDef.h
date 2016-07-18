#ifndef BUNDLEPARAMDEF_H__
#define BUNDLEPARAMDEF_H__

#define BUNDLE_MAX_PATH		512

// bundlx ǰ�����16���ֽ����� ���ɴ����һЩ������Ϣ = 80KB
#define BUNDLX_SIZE		81952 

// bundlx ǰ�����16���ֽ����� ���ɴ����һЩ������Ϣ
#define BUNDLE_TOTAL		81952
#define BUNDLX_DOM			16		
#define BUNDLX_DOMX2		32
#define BUNDLX_CONTENT_SIZE 81920
#define BUNDLX_NODE_SIZE	5

// 128 * 128 ��
#define BUNDLE_EDGE				128
#define BUNDLE_MAX_TILE_NUM		16384
// bundle�ļ��м�¼Tileռ���ڴ��ֽ������ֽڳ���
#define BUNDLE_TILE_SIZE	4

// bundle �ļ�ͷ��С
#define BUNDLE_HEADER_SIZE	60

// bundle ����������Ƭ����λ�ã��ֽ�ƫ����)
#define BUNDLE_POS_TILECOUNT 0x10

// bundle �����ļ���С���ֽ���)���ݵ��ֽ�ƫ��
#define BUNDLE_POS_FILESIZE  0x18

// bundle ����������Ƭ��������(�ֽ���)
#define INT_SIZE 4

// ��¼��Ƭ��ʼ�����ļ��е�ƫ����
#define BUNDLE_POS_BEGINROW  0x2c

// ��¼��Ƭ��ʼ�����ļ��е�ƫ����
#define BUNDLE_POS_BEGINCOL  0x34

// ��¼��Ƭ���������ļ��е�ƫ����
#define BUNDLE_POS_ENDROW	0x30

// ��¼��Ƭ���������ļ��е�ƫ����
#define BUNDLE_POS_ENDCOL  0x38






#endif // BundleParamDef_h__
