#ifndef __BOX_OPERATE_H_
#define __BOX_OPERATE_H_

#include "stm32f10x.h"

#define CLOSE_STAT       1//���ӹ�
#define OPEN_STAT        0//���ӿ�
#define WAIT_DOOR_TIME  700//�ȴ�������ȫ��ʱ�䣬����ʱ��͵ȴ�ʱ����������ǿ��䷴Ӧʱ��, ��󣹣���
#define OPEN_DOOR_TIME 700//����ʱ��700ms����������ʱʱ��

u8 ReadOneBox(u8 station_port);

void OpenOneDoor(u8 station_port);
u8 UserOpenBox(u8 station_port);

#endif
