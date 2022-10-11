#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include<string>
#define N 0.3	//标准差 
#define pi 3.1415926
#define e 2.71828
//code:gzrosefinch
using namespace std;
//单姓 
string firstName = "赵钱孙李周吴郑王冯陈褚卫蒋沈韩杨朱秦尤许何吕施张孔曹严华金魏陶姜戚邹喻柏水窦章云苏潘葛奚范彭郎鲁韦昌马苗凤花方俞任袁柳鲍史唐费廉岑薛雷贺倪汤封";
//复姓 
string firstName_2 = "万俟司马上官欧阳夏侯诸葛闻人东方赫连皇甫尉迟公羊澹台公冶宗政濮阳淳于单于太叔申屠公孙仲孙轩辕令狐钟离宇文长孙慕容鲜于闾丘司徒司空";
//名 
string name = "震壮思豪乐功善庆民友河江浩谦奇之翰伯宏言鸣斌栋克翔鹏晨士建致炎行盛琛冠腾榕风航瑛憧雪筠竹凝欢枫芸菲伊宜姬荔丽娟";

//学生结构体
struct stu
{
	char sname[20]={'\0'};		//名字 
	int sex;	//性别：男为0，女为1 
	int flag[20]={0};	//出勤状况：到勤为0，缺席为1 
	float ratio = 0;
	double grade;
}; 

//绩点排序算法
int mycmp(const void * p1, const void * p2){
	const stu *a = (const stu *)p1;
	const stu *b = (const stu *)p2;
	int res = a->grade > b->grade?1:-1;
	return res;
} 

//随机生成学生名字性别 
stu random_info()
{
	stu s;
	
	int tmp = rand()%5;	//复姓学生约占总学生数的%5 
	char t[3] = {'\0'};
	if(tmp > 0){	//单姓 
		tmp = rand()%firstName.length();
		if(tmp%2) tmp--;
		t[0] = firstName[tmp];
		t[1] = firstName[tmp+1];
		strcat(s.sname,(const char*)t);
	}
	else{	//复姓 
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
	//名 
	tmp = rand()%111;
	if(tmp%2) tmp--;
	t[0] = firstName[tmp];
	t[1] = firstName[++tmp];
	strcat(s.sname,(const char*)t);
	//性别 
	s.sex = rand()%2;
	return s;
}

//用Box_Muller算法产生高斯分布的随机数，u为均值 
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
		//printf("%s %s\n",stulist[i].sname,stulist[i].sex?"女":"男");
	}
	//正态分布绩点
	for(i=0;i<90;i++){
		stulist[i].grade = gaussian(2.8);
		while(stulist[i].grade < 1.6 || stulist[i].grade > 4.0){
			stulist[i].grade = gaussian(2.8);
		}
	} 
	//挑选5-8名爱缺勤的坏学生
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
	//每次课程挑选0-3名缺勤学生
	for(i=0;i<20;i++){
		for(j = rand()%3;j>0;j--){
			tmp = rand()%(90-badnum)+badnum;
			stulist[tmp].flag[i] = 1;
			stulist[tmp].grade -= 0.05;
		}
	} 
	//按绩点升序排列，此步也可在csv中操作
	//qsort(stulist,90,sizeof(stu),mycmp);
	//生成csv文件 
	char course[50];
	printf("请输入课程名:");
	scanf("%s",course);
	strcat(course,"出勤表.csv");
	FILE *fp = fopen(course, "w+");
    if (fp == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "姓名,性别,绩点,出勤1,出勤2,出勤3,出勤4,出勤5,出勤6,出勤7,出勤8,出勤9,出勤10,出勤11,出勤12,出勤13,出勤14,出勤15,出勤16,出勤17,出勤18,出勤19,出勤20,缺勤概率\n");
    for(i=0;i<90;i++){
    	for(j=0;j<20;j++){
    		stulist[i].ratio += stulist[i].flag[j];
		}
		stulist[i].ratio /= 20.0;
    	fprintf(fp, "%s,%s,%lf,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f\n",stulist[i].sname,stulist[i].sex?"女":"男",stulist[i].grade,stulist[i].flag[0],stulist[i].flag[1],stulist[i].flag[2],stulist[i].flag[3],stulist[i].flag[4],stulist[i].flag[5],stulist[i].flag[6],stulist[i].flag[7],stulist[i].flag[8],stulist[i].flag[9],stulist[i].flag[10],stulist[i].flag[11],stulist[i].flag[12],stulist[i].flag[13],stulist[i].flag[14],stulist[i].flag[15],stulist[i].flag[16],stulist[i].flag[17],stulist[i].flag[18],stulist[i].flag[19],stulist[i].ratio);
	}
	printf("创建成功！");
    fclose(fp);
    return 0;
}


