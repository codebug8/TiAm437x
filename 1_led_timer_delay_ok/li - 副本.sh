#!/bin/bash

#170722�������ж�U��
#170724������echo�����ɫ

myPath="/mnt/hgfs/G/"  #���������"�ļ�����"U�̵�·��
RED_COLOR='\E[1;31m'         #��
GREEN_COLOR='\E[1;32m'       #��
YELOW_COLOR='\E[1;33m'       #��
BLUE_COLOR='\E[1;34m'        #��
PINK='\E[1;35m'              #�ۺ�
RES='\E[0m'                  #END

#����MLO
function creat_MLO()
{
	rm -f /mnt/hgfs/G/MLO
	make clean 
	make
#	gcc -o ti_make_rawboot ti_make_rawboot.c
	gcc  ./image_tool/tiimage.c  -o  tiimage.out

#	./ti_make_rawboot   0x40300000    am437x_hardware.bin  raw.bin
	./tiimage.out   0x40300000    MMCSD    am437x_hardware.bin   /mnt/hgfs/G/MLO  
#	rm   -f *.dis  *.bin  *.o  *_elf tiimage.out
	ls /mnt/hgfs/G/MLO -l && echo -e  "${GREEN_COLOR}======MLO OK!======${RES}" || echo -e  "${RED_COLOR}======MLO ERROR!======${RES}"
	sync
}

#�ж�U��·���Ƿ���ڣ�
#����������MLO������������������ʾ����
if [ ! -d "$myPath" ];then  
  echo -e  "${RED_COLOR}======Check USB Disk!======${RES}"	
else
	creat_MLO	 
fi  
sync
exit
