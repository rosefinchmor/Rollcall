#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include<string>
#define N 0.3	//��׼�� 
#define pi 3.1415926
#define e 2.71828
//code:gzrosefinch
using namespace std;
//���� 
string firstName = "��Ǯ��������֣��������������������������ʩ�ſײ��ϻ���κ�ս���������ˮ��������˸��ɷ�����³Τ������ﻨ������Ԭ����ʷ�Ʒ����Ѧ�׺�������";
//���� 
string firstName_2 = "��ٹ˾���Ϲ�ŷ���ĺ�������˶��������ʸ�ξ�ٹ����̨��ұ����������ڵ���̫����������������ԯ����������ĳ���Ľ����������˾ͽ˾��";
//�� 
string name = "��׳˼���ֹ��������Ѻӽ���ǫ��֮�����������󶰿�������ʿ��������ʢ衹����ŷ纽���ѩ����������ܿ�����˼�������";

//ѧ���ṹ��
struct stu
{
	char sname[20]={'\0'};		//���� 
	int sex;	//�Ա���Ϊ0��ŮΪ1 
	int flag[20]={0};	//����״��������Ϊ0��ȱϯΪ1 
	float ratio = 0;
	double grade;
}; 

//���������㷨
int mycmp(const void * p1, const void * p2){
	const stu *a = (const stu *)p1;
	const stu *b = (const stu *)p2;
	int res = a->grade > b->grade?1:-1;
	return res;
} 

//�������ѧ�������Ա� 
stu random_info()
{
	stu s;
	
	int tmp = rand()%5;	//����ѧ��Լռ��ѧ������%5 
	char t[3] = {'\0'};
	if(tmp > 0){	//���� 
		tmp = rand()%firstName.length();
		if(tmp%2) tmp--;
		t[0] = firstName[tmp];
		t[1] = firstName[tmp+1];
		strcat(s.sname,(const char*)t);
	}
	else{	//���� 
		tmp = rand()%firstName_2.length();
		if(tmp%2) tmp--;
		t[0] = firstName_2[tmp];
		t[1] = firstName_2[++tmp]; 
		strcat(s.sname,(const char*)t);
		t[0] = firstName_2[++tmp];
		t[1] = firstName_2[++tmp]; 
		strcat(s.sname,(const char*)t);
	}
	tmp = rand()%2;
	if(tmp > 0){
		tmp = rand()%name.length();
		if(tmp%2) tmp--;
		t[0] = firstName[tmp];
		t[1] = firstName[++tmp];
		strcat(s.sname,(const char*)t);
	}
	//�� 
	tmp = rand()%111;
	if(tmp%2) tmp--;
	t[0] = firstName[tmp];
	t[1] = firstName[++tmp];
	strcat(s.sname,(const char*)t);
	//�Ա� 
	s.sex = rand()%2;
	return s;
}

//��Box_Muller�㷨������˹�ֲ����������uΪ��ֵ 
double gaussian(double u) 
{
	double r,t,z,x;
	double s1,s2;
	s1=(1.0+rand())/(RAND_MAX+1.0);
	s2=(1.0+rand())/(RAND_MAX+1.0);
	r=sqrt(-2*log(s2)/log(e));
	t=2*pi*s1;
	z=r*cos(t);
	x=u+z*N;
	return x;
}

int main()
{	
	srand((int)time(NULL));
	stu stulist[90],swap;
	int i,j,badnum,tmp;
	for(i=0;i<90;i++){
		stulist[i] = random_info();	
		//printf("%s %s\n",stulist[i].sname,stulist[i].sex?"Ů":"��");
	}
	//��̬�ֲ�����
	for(i=0;i<90;i++){
		stulist[i].grade = gaussian(2.8);
		while(stulist[i].grade < 1.6 || stulist[i].grade > 4.0){
			stulist[i].grade = gaussian(2.8);
		}
	} 
	//��ѡ5-8����ȱ�ڵĻ�ѧ��
	badnum = rand()%4+5;
	for(i=0;i<badnum;i++){
		for(j=0;j<16;){
			tmp = rand()%20;
			if(stulist[i].flag[tmp] == 1) continue;
			stulist[i].flag[tmp] = 1;
			j++;
		}
		stulist[i].grade -= 0.5;
		tmp = rand()%(90-badnum) + badnum;
		swap = stulist[i];
		stulist[i] = stulist[tmp];
		stulist[tmp] = swap;
	} 
	//ÿ�ογ���ѡ0-3��ȱ��ѧ��
	for(i=0;i<20;i++){
		for(j = rand()%3;j>0;j--){
			tmp = rand()%(90-badnum)+badnum;
			stulist[tmp].flag[i] = 1;
			stulist[tmp].grade -= 0.05;
		}
	} 
	//�������������У��˲�Ҳ����csv�в���
	//qsort(stulist,90,sizeof(stu),mycmp);
	//����csv�ļ� 
	char course[50];
	printf("������γ���:");
	scanf("%s",course);
	strcat(course,"���ڱ�.csv");
	FILE *fp = fopen(course, "w+");
    if (fp == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "����,�Ա�,����,����1,����2,����3,����4,����5,����6,����7,����8,����9,����10,����11,����12,����13,����14,����15,����16,����17,����18,����19,����20,ȱ�ڸ���\n");
    for(i=0;i<90;i++){
    	for(j=0;j<20;j++){
    		stulist[i].ratio += stulist[i].flag[j];
		}
		stulist[i].ratio /= 20.0;
    	fprintf(fp, "%s,%s,%lf,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f\n",stulist[i].sname,stulist[i].sex?"Ů":"��",stulist[i].grade,stulist[i].flag[0],stulist[i].flag[1],stulist[i].flag[2],stulist[i].flag[3],stulist[i].flag[4],stulist[i].flag[5],stulist[i].flag[6],stulist[i].flag[7],stulist[i].flag[8],stulist[i].flag[9],stulist[i].flag[10],stulist[i].flag[11],stulist[i].flag[12],stulist[i].flag[13],stulist[i].flag[14],stulist[i].flag[15],stulist[i].flag[16],stulist[i].flag[17],stulist[i].flag[18],stulist[i].flag[19],stulist[i].ratio);
	}
	printf("�����ɹ���");
    fclose(fp);
    return 0;
}


