#include<bits/stdc++.h>
#include<Windows.h> //���̱߳��
#include<process.h>
using namespace std;

#define READER 'R'                   //����
#define WRITER 'W'                   //д��
#define INTE_PER_SEC 1000            //ÿ��ʱ���жϵ���Ŀ
#define MAX_THREAD_NUM 64            //����߳���Ŀ

//����������ʼ��
int readercount = 0;//��¼�ȴ��Ķ�����Ŀ
int writercount = 0;//��¼�ȴ���д����Ŀ

HANDLE rc_mutex;//��Ϊ������������ӵĻ����ź��������ڶ�������

HANDLE rc2_mutex;//��Ϊ������������ӵĻ����ź���������д������
HANDLE wc_mutex;//��Ϊд����������ӵĻ����ź���
HANDLE book;//��������ź���
HANDLE wrt;//��֤ÿ��ֻ��һ��д�߽���д��������д�ߵ�����writercount����0��ʱ����֤����ʱû��û�ж�����,�ͷ��ź���book
HANDLE mutex;//����д��ͬʱ�������߽��о������������ź���RWMutex��mutex3���ͷţ���һ����д�ߣ�д�߿����ϻ����Դ

class thread_info {
public:
	int id;		      //�߳����
	char entity;      //�߳����(�ж��Ƕ����̻߳���д���߳�)
	double delay;		 //�߳��ӳ�ʱ��
	double lastTime;	 //�̶߳�д����ʱ��
	void show_all_things() {
		cout << "thread id ->" << id << " entity -> " << entity << " delay ->" << delay <<" lastTime -> " << lastTime << endl;
	}
	thread_info(ifstream & inFile) {
		inFile >> id;
		inFile >> entity;
		inFile >> delay;
		inFile >> lastTime;
		show_all_things();
	}
};
/*****************/
//��������
//���̹���-�����߳�
void rp_threadReader(void *p) {
	DWORD m_delay;                   //�ӳ�ʱ��
	DWORD m_persist;                 //���ļ�����ʱ��
	int m_serial;                    //�߳����
									 //�Ӳ����л����Ϣ
	m_serial = ((thread_info*)(p))->id;
	m_delay = (DWORD)(((thread_info*)(p))->delay *INTE_PER_SEC);
	m_persist = (DWORD)(((thread_info*)(p))->lastTime *INTE_PER_SEC);
	Sleep(m_delay);                  //�ӳٵȴ�

	printf("���߽���%d������ļ�.\n", m_serial);
	//cout << "���߽���"<< m_serial<<"������ļ�." << endl;
	// ��readercount ���л������
	WaitForSingleObject(rc_mutex, -1);
	if (readercount == 0) {
		WaitForSingleObject(book, -1);//��һλ����������
	}
	readercount++;

	//�ͷŵ������ź���rc_mutex
	ReleaseSemaphore(rc_mutex, 1, NULL);

	printf("���߽���%d��ʼ���ļ�.\n", m_serial);
	Sleep(m_persist);
	printf("���߽���%d��ɶ��ļ�.\n", m_serial);

	WaitForSingleObject(rc_mutex, -1);//�޸�readercount
	readercount--;//���߶���
	if (readercount == 0)  {
		ReleaseSemaphore(book, 1, NULL);//�ͷ��鼮��д�߿�д
	}
	ReleaseSemaphore(rc_mutex, 1, NULL);//�ͷŻ����ź���rc_mutex
}
/*****************/
//��������
//���̹���-д���߳�
void rp_threadWriter(void *p)
{
	DWORD m_delay;                   //�ӳ�ʱ��
	DWORD m_persist;                 //���ļ�����ʱ��
	int m_serial;                    //�߳����
									 //�Ӳ����л����Ϣ
	m_serial = ((thread_info*)(p))->id;
	m_delay = (DWORD)(((thread_info*)(p))->delay *INTE_PER_SEC);
	m_persist = (DWORD)(((thread_info*)(p))->lastTime *INTE_PER_SEC);
	Sleep(m_delay);                  //�ӳٵȴ�
	printf("д�߽���%d����д�ļ�.\n", m_serial);
	WaitForSingleObject(book, INFINITE);//������Դ
	/*write is performed*/
	printf("д�߽���%d��ʼ���ļ�.\n", m_serial);
	Sleep(m_persist);
	printf("д�߽���%d��ɶ��ļ�.\n", m_serial);
	ReleaseSemaphore(book, 1, NULL);//�ͷ���Դ
}
//��������

void ReaderPriority(char *file)
{
	DWORD n_thread = 0;           //�߳���Ŀ
	DWORD thread_ID;            //�߳�ID
	DWORD wait_for_all;         //�ȴ������߳̽���

								//�����ź���
	rc_mutex = CreateSemaphore(NULL, 1, 1, "mutex_for_readcount");//���߶�count�޸Ļ����ź�������ֵΪ1,���Ϊ1
	book = CreateSemaphore(NULL, 1, 1, NULL);//�鼮��������ź�������ֵΪ1,���ֵΪ1

	HANDLE h_Thread[MAX_THREAD_NUM];//�߳̾��,�̶߳��������
	thread_info *_thread_info = (thread_info *)malloc(sizeof(thread_info) * MAX_THREAD_NUM );

	int id = 0;
	readercount = 0;               //��ʼ��readcount
	ifstream inFile;
	inFile.open(file);
	cout << "��������:" << endl;
	while (inFile)
	{
		//����ÿһ������,д�ߵ���Ϣ
		_thread_info[n_thread] = *(new  thread_info(inFile));
		
		n_thread++;
		inFile.get();
	}
	for (int i = 0; i<(int)(n_thread); i++)
	{
		if (_thread_info[i].entity == READER || _thread_info[i].entity == 'r')
		{
			//�������߽���
			h_Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(rp_threadReader), &_thread_info[i], 0, &thread_ID);
		}
		else
		{
			//����д�߳�
			h_Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(rp_threadWriter), &_thread_info[i], 0, &thread_ID);
		}
	}
	//�ȴ����߳̽���

	//�رվ��
	wait_for_all = WaitForMultipleObjects(n_thread, h_Thread, TRUE, -1);
	cout << endl;
	cout << "���ж���д���Ѿ���ɲ�������" << endl;
	for(int i = 0; i<(int)(n_thread); i++)
		CloseHandle(h_Thread[i]);
	CloseHandle(rc_mutex);
	CloseHandle(book);
}
/*****************/
//д������
//���̹���-�����߳�
void wp_threadReader(void *p) {
	DWORD m_delay;                   //�ӳ�ʱ��
	DWORD m_persist;                 //���ļ�����ʱ��
	int m_serial;                    //�߳����
									 //�Ӳ����л����Ϣ
	m_serial = ((thread_info*)(p))->id;
	m_delay = (DWORD)(((thread_info*)(p))->delay *INTE_PER_SEC);
	m_persist = (DWORD)(((thread_info*)(p))->lastTime *INTE_PER_SEC);
	Sleep(m_delay);                  //�ӳٵȴ�

	printf("���߽���%d������ļ�.\n", m_serial);
	WaitForSingleObject(mutex, -1);
	WaitForSingleObject(book, -1);
	WaitForSingleObject(rc2_mutex, -1);//��readercount�������
	if (readercount == 0)WaitForSingleObject(wrt, -1);//��һλ����������,ͬʱ��ֹд�߽���д����
	readercount++;

	ReleaseSemaphore(rc2_mutex, 1, NULL);//�ͷŻ����ź���rc_mutex
	ReleaseSemaphore(book, 1, NULL);//�ͷŻ����ź���book
	ReleaseSemaphore(mutex, 1, NULL);//�ͷŻ����ź���mutex
									 /* reading is performed */
	cout <<"���߽���" << m_serial << "��ʼ���ļ�"<<endl;

	Sleep(m_persist);
	cout <<"���߽���" << m_serial << "��ɶ��ļ�"<<endl;

	WaitForSingleObject(rc2_mutex, -1);//�޸�readercount
	readercount--;//���߶���
	if (readercount == 0)ReleaseSemaphore(wrt, 1, NULL);//�ͷ���Դ��д�߿�д
	ReleaseSemaphore(rc2_mutex, 1, NULL);//�ͷŻ����ź���rc_mutex
}
/*****************/
//д������
//���̹���-д���߳�
void wp_threadWriter(void *p) {
	DWORD m_delay;                   //�ӳ�ʱ��
	DWORD m_persist;                 //���ļ�����ʱ��
	int m_serial;                    //�߳����
									 //�Ӳ����л����Ϣ
	m_serial = ((thread_info*)(p))->id;
	m_delay = (DWORD)(((thread_info*)(p))->delay *INTE_PER_SEC);
	m_persist = (DWORD)(((thread_info*)(p))->lastTime *INTE_PER_SEC);
	Sleep(m_delay);                  //�ӳٵȴ�

	printf("д�߽���%d����д�ļ�.\n", m_serial);
	WaitForSingleObject(wc_mutex, -1);//��writercount�������
	if (writercount == 0)WaitForSingleObject(book, -1);//��һλд��������Դ
	writercount++;
	ReleaseSemaphore(wc_mutex, 1, NULL);//�ͷ���Դ

	WaitForSingleObject(wrt, -1);
	/*write is performed*/
	cout <<"д�߽���" << m_serial << "��ʼд�ļ�"<<endl;
	Sleep(m_persist);
	cout <<"д�߽���" << m_serial << "���д�ļ�"<<endl;
	ReleaseSemaphore(wrt, 1, NULL);//�ͷ���Դ

	WaitForSingleObject(wc_mutex, -1);//��writercount�������
	writercount--;
	if (writercount == 0)ReleaseSemaphore(book, 1, NULL);//�ͷ���Դ
	ReleaseSemaphore(wc_mutex, 1, NULL);//�ͷ���Դ
}
//д������
void WriterPriority(char *file) {
	DWORD n_thread = 0;           //�߳���Ŀ
	DWORD thread_ID;            //�߳�ID
	DWORD wait_for_all;         //�ȴ������߳̽���

								//�����ź���
	rc2_mutex = CreateSemaphore(NULL, 1, 1, "mutex_for_readercount");//���߶�count�޸Ļ����ź�������ֵΪ1,���Ϊ1
	wc_mutex = CreateSemaphore(NULL, 1, 1, "mutex_for_writercount");//д�߶�count�޸Ļ����ź�������ֵΪ1,���Ϊ1
	wrt = CreateSemaphore(NULL, 1, 1, NULL);//
	mutex = CreateSemaphore(NULL, 1, 1, NULL);//
	book = CreateSemaphore(NULL, 1, 1, NULL);//�鼮��������ź�������ֵΪ1,���ֵΪ1

	HANDLE h_Thread[MAX_THREAD_NUM];//�߳̾��,�̶߳��������
	thread_info *_thread_info = (thread_info *)malloc(sizeof(thread_info) * MAX_THREAD_NUM );

	int id = 0;
	readercount = 0;               //��ʼ��readcount
	writercount = 0;
	ifstream inFile;
	inFile.open(file);
	cout << "д������:" << endl;
		while (inFile)
	{
		//����ÿһ������,д�ߵ���Ϣ
		_thread_info[n_thread] = *(new  thread_info(inFile));
		
		n_thread++;
		inFile.get();
	}
	for (int i = 0; i<(int)(n_thread); i++)
	{
		if (_thread_info[i].entity == READER || _thread_info[i].entity == 'r')
		{
			//�������߽���
			h_Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(wp_threadReader), &_thread_info[i], 0, &thread_ID);
		}
		else
		{
			//����д�߳�
			h_Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(wp_threadWriter), &_thread_info[i], 0, &thread_ID);
		}
	}
	//�ȴ����߳̽���

	//�رվ��
	wait_for_all = WaitForMultipleObjects(n_thread, h_Thread, TRUE, -1);
	cout << endl;
	cout << "���ж���д���Ѿ���ɲ�������" << endl;
	for (int i = 0; i<(int)(n_thread); i++)
		CloseHandle(h_Thread[i]);
	CloseHandle(wc_mutex);
	CloseHandle(rc2_mutex);
	CloseHandle(book);
}
//������
int main()
{
	char choice;
	while (true)
	{
		//��ӡ��ʾ��Ϣ
		cout << "     ����������̵߳����㷨ѡ��       " << endl;
		cout << "     1����������" << endl;
		cout << "     2��д������" << endl;
		cout << "     3���˳�����" << endl;
		cout << endl;
		//���������Ϣ����ȷ����������
		int enter_wrong = 0;
		do {
			choice = (char)getchar();
			if(choice != '1'&&choice != '2'&&choice != '3') {
				enter_wrong = 1;
				cout << "enter wrong , please enter 1 2 or 3"<<endl;
			}else{
				enter_wrong = 0;
			}

		} while (enter_wrong == 1);

		system("cls");
		//ѡ��1����������
		if (choice == '1')
			//ReaderPriority("thread.txt");
			ReaderPriority(const_cast<char *>("thread.txt"));
		//ѡ��2��д������
		else if (choice == '2')
			WriterPriority(const_cast<char *>("thread.txt"));
		//ѡ��3���˳�
		else
			return 0;
		//����
		printf("\nPress Any Key to Coutinue");
		getchar();
		// system("cls");
	}
	return 0;
}

