#include<iostream>

#include<string>
using namespace std;
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"boss.h"
#include"manager.h"


int main()
{
	//测试代码
	/*Worker* worker = NULL;
	worker = new Employee(1, "张三", 1);
	worker->showInfo();
	delete worker;

	worker = new Manager(2, "张三", 1);
	worker->showInfo();
	delete worker;

	worker = new Boss(3, "张三", 1);
	worker->showInfo();
	delete worker;*/


	//实例化管理者对象
	WorkerManager wm;

	char choice = 0;
	while (true)
	{

		//显示菜单
		wm.Show_Menu();

		cout << "请做出你的选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case '0'://退出系统
			wm.ExitSystem();
			break;
		case '1'://增加职工
			wm.Add_Emp();
			break;
		case '2'://显示职工
			wm.Show_Emp();
			break;
		case '3'://删除职工
			wm.Del_Emp();
			break;
		case '4'://修改职工
			wm.Mod_Emp();
			break;
		case '5'://查找职工
			wm.Find_Emp();
			break;
		case '6'://排序职工
			wm.Sort_Emp();
			break;
		case '7'://清空文档
			wm.Clean_File();
			break;
		default:
			cout << "输入错误,请重新输入" << endl;
			system("pause");
			system("cls");
			break;
		}

	}
	system("pausse");
	return 0;

}