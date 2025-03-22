#include <iostream>
#include <mysql.h>

int main()
{
	MYSQL Conn;				// MySQL ���� ���� ����ü
	MYSQL* ConnPtr = NULL;	// MYSQL �ڵ�
	MYSQL_RES* Result;		// ���� ���� �� ��� ��� ����ü������
	MYSQL_ROW Row;			// ���� ���� �� ����� ���� ���� ������ ��� ����ü
	int Stat;				// ���� ��û �� ���(���� / ����)

	mysql_init(&Conn);		// MySQL ���� �ʱ�ȭ

	// DB ����
	ConnPtr = mysql_real_connect(&Conn, "127.0.0.1", "root", "1234", "chatapptest", 3306, (char*)NULL, 0);

	// ���� ��� Ȯ��. NULL�� ��� ���� ����
	if (ConnPtr == NULL) {
		printf("MySQL Connection error : %s\n", mysql_error(&Conn));
		return 1;
	}
	else {
		printf("MySQL Connection Success\n");
	}

	// DB�� ���� ������
	const char* Query = "SELECT * FROM chat";
	Stat = mysql_query(ConnPtr, Query);		// ���� ��û �� �������� �޾ƿ���
	if (Stat != 0) {						// ���� ��û ���� �� ����ó��
		printf("MySQL Query error: %s\n", mysql_error(&Conn));
		return 1;
	}

	// ��� ���
	Result = mysql_store_result(ConnPtr);				// ��� Ȯ��
	while ((Row = mysql_fetch_row(Result)) != NULL) {	// ��� ���. �޾ƿ� ����� mysql_fetch_row �Լ��� �Ѱ��ָ� Row�� �޾�  NULL�� �ƴҶ����� ��� �о�� ���
		printf("%d %s %s %s\n", atoi(Row[0]), Row[1], Row[2], Row[3]);	// mysql_fetch_row()�� charŸ�Ը� ��ȯ��. int�� �����ʹ� atoi()�� int ����ȯ �ؾ���
	}
	mysql_free_result(Result);							// ��� ����

	// db ���� ����
	mysql_close(ConnPtr);

	/*std::cout << "ClientInfo : " << mysql_get_client_info() << std::endl;*/
	return 0;
}