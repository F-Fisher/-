#include"workerManager.h"

//
WorkerManager::WorkerManager()
{
//�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		//��ʼ��
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
        ifs.close();
		return;

	}
	
//�ļ����ڵ�����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//�ļ�Ϊ��
		cout << "�ļ�Ϊ��" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	///�ļ��������м�¼
	int num = this->get_EmpNum();
	cout<<"ְ������Ϊ��"<<num<<endl;
	this->m_EmpNum = num;
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "ְ����� " << this->m_EmpArray[i]->m_Id
			<< " ����   " << this->m_EmpArray[i]->m_Name
			<< " ���ű��" << this->m_EmpArray[i]->m_DeptId << endl;
	}



}

//��ʾ�˵�
void WorkerManager::Show_Menu()
{
	cout << "*****************************" << endl;
	cout << "*** ��ӭʹ��ְ������ϵͳ ****" << endl;
	cout << "****** 0.�˳�����ϵͳ *******" << endl;
	cout << "****** 1.����ְ����Ϣ *******" << endl;
	cout << "****** 2.��ʾְ����Ϣ *******" << endl;
	cout << "****** 3.ɾ����ְְ�� *******" << endl;
	cout << "****** 4.�޸�ְ����Ϣ *******" << endl;
	cout << "****** 5.����ְ����Ϣ *******" << endl;
	cout << "****** 6.���ձ������ *******" << endl;
	cout << "****** 7.��������ĵ� *******" << endl;
	cout << "*****************************" << endl;
	cout << endl;
}

//�˳�ϵͳ
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//�����Ա
void WorkerManager::Add_Emp()
{
	cout << "���������ְ������" << endl;
	int addNum = 0;//�������
	cin >> addNum;
	if (addNum > 0)
	{
		//���

		//�����¿ռ��С
		int newSize = this->m_EmpNum + addNum;
		//�����¿ռ�
		Worker** newSpace =new Worker* [newSize+4];
		//��ԭ�������ݿ������¿ռ�
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}

		}
		//�������
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "�������" << i + 1 << "����Ա�����" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "����Ա����" << endl;
			cin >> name;
			cout << "��ѡ���" << i + 1 << "����Ա��ְλ" << endl;
			cout << "1 ��ְͨ��" << endl;
			cout << "2 ����" << endl;
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
			//��������ְ�����α��浽������
			newSpace[this->m_EmpNum + i] = worker;

		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;
		//�ı�ռ�ָ��
		m_EmpArray = newSpace;
		//����ְ����
		this->m_EmpNum = newSize;

		//����ְ����Ϊ��
		this->m_FileIsEmpty = false;

		//��ʾ��ӳɹ�
		cout << "�ɹ���ӵ�" << addNum << "����ְ��" << endl;
		this->save();//��������
		system("pause");
		system("cls");
	}
	else
	{
		cout << "�������" << endl;
	}


}

//�����ĵ�
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//�������ʽ���ļ�
	//��ÿһ������Ϣд���ļ�
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();


}

//ͳ������
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ� ��
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

//��ʼ��Ա��
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
		if (dId == 1)//��ְͨ��
		{
			worker = new Employee(id, name, dId);
		}
		if (dId == 2)//����
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

//��ʾְ��
void  WorkerManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڣ���Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
			this->m_EmpArray[i]->showInfo();
	}
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ����
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

//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	int index;
	int id;
	cout << "��������Ҫɾ��Ա�����" << endl;
	cin >> id;
	index = IsExist(id);
	if (index == -1)
	{
		cout << "δ�ҵ�Ա��" << endl;
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
					cout << "ɾ���ɹ�" << endl;
				}
				else
				{
					for(i;i<m_EmpNum-1;i++)
					this->m_EmpArray[i] = this->m_EmpArray[i + 1];
					m_EmpNum--;
					cout << "ɾ���ɹ�" << endl;
				}
	
			}
		}
	}
	this->save();
	system("pause");
	system("cls");


}

//�޸�ְ��
void WorkerManager::Mod_Emp() 
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�������" << endl;
    }
	else
	{
		cout << "��������Ҫ�޸�Ա�����" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			cout << "���ҵ�����" << endl;
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int newdId;
			cout << "��������Id" << endl;
			cin >> newId;
			cout << "������������" << endl;
			cin >> newName;
			cout << "��������ְλ" << endl;
			cout << "1 ��ְͨ��" << endl;
			cout << "2 ����" << endl;
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
			cout << "�޸ĳɹ�" << endl;
			save();
		}
		else
		{
			cout << "���޴���" << endl;
		}

	}
	system("pause");
	system("cls");
}

//����Ա��
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�������" << endl;
	}
	else
	{
		cout << "��������ҷ�ʽ" << endl;
		cout << "1 ���ձ��" << endl;
		cout << "2 ��������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//���ձ��
			int id;
			cout << "��������" << endl;
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "���޴���" << endl;
			}

		}
		else if (select == 2)
		{
			//��������
			cout << "�������������" << endl;
			string name;
			cin >> name;
			bool  flag= false;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ�" << endl;
					m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "���޴���" << endl;
			}
		}
		else 
		{
			cout << "��������" << endl;
		}

	}
	system("pause");
	system("cls");
}

//����Ա��
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�������" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ" << endl;
		cout << " 1 ����ְ��������" << endl;
		cout << " 2 ����ְ���Ž���" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//����
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
			//�ж�һ��ʼ�϶�����Сֵ�����ֵ�ǲ��Ǽ������Сֵ���ֵ��������ǣ���������
			if (i != minOrMax)
			{
				Worker* tmp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = tmp;
			}
			
			
		}
			cout << "����ɹ�" << endl;
			cout << "������Ϊ" << endl;
			this->save();
			this->Show_Emp();
	}



}

//�������
void WorkerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1 ȷ��" << endl;
	cout << "2 ����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ������´���
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
		cout << "��ճɹ�" << endl;
		system("pause");
		system("cls");
	}
	if (select == 2)
	{
		return;
	}
}

//����
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
