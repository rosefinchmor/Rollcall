#include<bits/stdc++.h>
//code:gzrosefinch
using namespace std;
int ab[8][25]={0};	//读入的出勤情况，0为到勤，1为缺勤
int rd[8]={0};	//抽点概率 
int mark[8]={0};	//记录到勤次数 
void read_csv(string filename) //读入数据集 
{
    ifstream inFile(filename);
    string lineStr;
    getline(inFile,lineStr);
    int i=0,j;
    while(getline(inFile,lineStr)) //这里的循环是每次读取一整行的数据,把结果保存在lineStr中，lineStr是用逗号分割开的
    {
        stringstream ss(lineStr); //这里stringstream是一个字符串流类型，用lineStr来初始化变量 ss
        string str;
        //按照逗号进行分割，剩余绩点及到勤 
        for(j=0;j<3;j++) 
        {
        	getline(ss,str,',');	
        }
        for(j=0;j<20;j++){
        	getline(ss,str,',');
        	ab[i][j] = atoi(&str[0]);
		}
		i++;
		if(i>7) break;
    }
    //打印一下看看
//    for(i=0;i<7;i++){
//    	for(j=0;j<20;j++){
//    		cout<<ab[i][j]<<" ";
//		}
//		cout<<endl;
//	}
}
 
double algorithm(char *fn)
{
	srand((unsigned)time(NULL));
	int i,j;
	int x=0,y=0;	//x为有效点名次数，y为总点名次数 
	for(i=0;i<7;i++){
		rd[i] += 4;
	}
    //读取整个文件
    char filename[50]={'\0'};
    strcat(filename,fn);
    strcat(filename,"出勤表.csv");
    read_csv(filename);
    //第一轮
	for(i=0;i<7;i++){
		ab[i][0]--;
		if(ab[i][0] < 0) rd[i] += 20;	//概率为3 
		else x++;
		y++;
	}
	//第二轮至第四轮 
	int total = 25;
	for(j=1;j<4;j++){
		for(i=0;i<7;i++){
			if(rand()%total<rd[i]){
				ab[i][j]--;
				if(ab[i][j] > 0) rd[i] += 20;
				else{
					 x++;
					 mark[i]++;
				}
				y++;
			}
		}
		total += 10;
	}  
	//第五轮至第二十轮
	int target = -1,surplus = 0;
	for(j=5;j<20;j++){
		for(i=0;i<7;i++){
			if(rand()%total<rd[i]){
				ab[i][j]--;
				if(ab[i][j] > 0) rd[i] += 10;
				else{
					x++;
					mark[i]++;
					if(mark[i] == 4){
						surplus = 19 - j;
						j = 20;
						break;
					}
				}
				y++;
			}
		}
	}
	x += surplus;
	y += surplus;
    return x*0.1/y*10;
}

int main()
{
	char fn[50];
	double sum_E = 0,rs;
	for(int i=0;i<5;i++){
		printf("请输入您要点名的课程："); 
		scanf("%s",fn);
		rs = algorithm(fn);
		sum_E += rs;
		cout<<rs<<endl;
	}
	sum_E /= 5;
	cout<<"----------------------------------------"<<endl; 
	cout<<"抽点方案："<<endl;
	cout<<"1. 第一次点绩点最低的7个人，提高缺勤学生的抽点概率"<<endl;
	cout<<"第二次及之后在此7人中抽点，不断提高缺勤学生的抽点概率，抽点概率增速为S1，直到第4次"<<endl;
	cout<<"第五次及之后，降低抽点概率增速为S2，并记录学生到勤次数，若有到勤次数先满4次的学生，则今后只点该学生"<<endl;
	cout<<"五门课程E值均值为："<<sum_E;
}
