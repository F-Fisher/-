#include"workerManager.h"

//
WorkerManager::WorkerManager()
{
//文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		//初始化
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
        ifs.close();
		return;

	}
	
//文件存在但数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件为空
		cout << "文件为空" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	///文件存在且有记录
	int num = this->get_EmpNum();
	cout<<"职工人数为："<<num<<endl;
	this->m_EmpNum = num;
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "职工编号 " << this->m_EmpArray[i]->m_Id
			<< " 姓名   " << this->m_EmpArray[i]->m_Name
			<< " 部门编号" << this->m_EmpArray[i]->m_DeptId << endl;
	}



}

//显示菜单
void WorkerManager::Show_Menu()
{
	cout << "*****************************" << endl;
	cout << "*** 欢迎使用职工管理系统 ****" << endl;
	cout << "****** 0.退出管理系统 *******" << endl;
	cout << "****** 1.增加职工信息 *******" << endl;
	cout << "****** 2.显示职工信息 *******" << endl;
	cout << "****** 3.删除离职职工 *******" << endl;
	cout << "****** 4.修改职工信息 *******" << endl;
	cout << "****** 5.查找职工信息 *******" << endl;
	cout << "****** 6.按照编号排序 *******" << endl;
	cout << "****** 7.清空所有文档 *******" << endl;
	cout << "*****************************" << endl;
	cout << endl;
}

//退出系统
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//添加人员
void WorkerManager::Add_Emp()
{
	cout << "请输入添加职工人数" << endl;
	int addNum = 0;//添加人数
	cin >> addNum;
	if (addNum > 0)
	{
		//添加

		//计算新空间大小
		int newSize = this->m_EmpNum + addNum;
		//开辟新空间
		Worker** newSpace =new Worker* [newSize+4];
		//将原来的数据拷贝到新空间
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}

		}
		//批量添加
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "请输入第" << i + 1 << "个新员工编号" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新员姓名" << endl;
			cin >> name;
			cout << "请选择第" << i + 1 << "个新员工职位" << endl;
			cout << "1 普通职工" << endl;
			cout << "2 经理" << endl;
			cout << "3 boss" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 1);
				break;
			case 3:
				worker = new Boss(id, name, 1);
				break;

			}
			//将创建的职工责任保存到数组中
			newSpace[this->m_EmpNum + i] = worker;

		}
		//释放原有空间
		delete[] this->m_EmpArray;
		//改变空间指针
		m_EmpArray = newSpace;
		//更新职工数
		this->m_EmpNum = newSize;

		//更新职工不为空
		this->m_FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加第" << addNum << "名新职工" << endl;
		this->save();//保存数据
		system("pause");
		system("cls");
	}
	else
	{
		cout << "输入错误" << endl;
	}


}

//保存文档
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//用输出方式打开文件
	//将每一个人信息写入文件
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();


}

//统计人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//打开文件 读
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs>>id&&ifs>>name&&ifs>>dId)

	{
		num++;

	}
	return num;
}

//初始化员工
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)//普通职工
		{
			worker = new Employee(id, name, dId);
		}
		if (dId == 2)//经理
		{
			worker = new Manager(id, name, dId);
		}
		if (dId == 3)//boss
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();


}

//显示职工
void  WorkerManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在，或为空" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
			this->m_EmpArray[i]->showInfo();
	}
	system("pause");
	system("cls");
}

//判断职工是否存在
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (m_EmpArray[i]->m_Id == id)
		{
			index = 1;
			break;
		}
	}
	return index;

}

//删除职工
void WorkerManager::Del_Emp()
{
	int index;
	int id;
	cout << "请输入想要删除员工编号" << endl;
	cin >> id;
	index = IsExist(id);
	if (index == -1)
	{
		cout << "未找到员工" << endl;
		return;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (m_EmpArray[i]->m_Id == id)
			{
				if (i == m_EmpNum - 1)
				{
					m_EmpArray[i] = NULL;
					m_EmpNum--;
					cout << "删除成功" << endl;
				}
				else
				{
					for(i;i<m_EmpNum-1;i++)
					this->m_EmpArray[i] = this->m_EmpArray[i + 1];
					m_EmpNum--;
					cout << "删除成功" << endl;
				}
	
			}
		}
	}
	this->save();
	system("pause");
	system("cls");


}

//修改职工
void WorkerManager::Mod_Emp() 
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << endl;
    }
	else
	{
		cout << "请输入想要修改员工编号" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			cout << "查找到此人" << endl;
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int newdId;
			cout << "请输入新Id" << endl;
			cin >> newId;
			cout << "请输入新姓名" << endl;
			cin >> newName;
			cout << "请输入新职位" << endl;
			cout << "1 普通职工" << endl;
			cout << "2 经理" << endl;
			cout << "3 boss" << endl;
			cin >> newdId;
			Worker* worker = NULL;
			switch (newdId)
			{
			case 1:
				worker = new Employee(newId, newName, newdId);
				break;
			case 2:
				worker = new Manager(newId, newName, newdId);
				break;
			case 3:
				worker = new Boss(newId, newName, newdId);
				break;
			default:
				break;
			}
			this->m_EmpArray[ret] = worker;
			cout << "修改成功" << endl;
			save();
		}
		else
		{
			cout << "查无此人" << endl;
		}

	}
	system("pause");
	system("cls");
}

//查找员工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << endl;
	}
	else
	{
		cout << "请输入查找方式" << endl;
		cout << "1 按照编号" << endl;
		cout << "2 按照姓名" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//按照编号
			int id;
			cout << "请输入编号" << endl;
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "查找成功" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查无此人" << endl;
			}

		}
		else if (select == 2)
		{
			//按照姓名
			cout << "请输入查找姓名" << endl;
			string name;
			cin >> name;
			bool  flag= false;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功" << endl;
					m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "查无此人" << endl;
			}
		}
		else 
		{
			cout << "输入有误" << endl;
		}

	}
	system("pause");
	system("cls");
}

//排序员工
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式" << endl;
		cout << " 1 按照职工号升序" << endl;
		cout << " 2 按照职工号降序" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//升序
				{
					if (this->m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else
				{
					if (this->m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}
			//判断一开始认定的最小值或最大值是不是计算的最小值最大值，如果不是，交换数据
			if (i != minOrMax)
			{
				Worker* tmp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = tmp;
			}
			
			
		}
			cout << "排序成功" << endl;
			cout << "排序结果为" << endl;
			this->save();
			this->Show_Emp();
	}



}

//清空数据
void WorkerManager::Clean_File()
{
	cout << "确定清空？" << endl;
	cout << "1 确定" << endl;
	cout << "2 返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);//删除文件后重新创建
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				m_EmpArray[i] = NULL;
			}
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;

		}
		cout << "清空成功" << endl;
		system("pause");
		system("cls");
	}
	if (select == 2)
	{
		return;
	}
}

//析构
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			delete this->m_EmpArray[i];
			m_EmpArray[i] = NULL;
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}

}
