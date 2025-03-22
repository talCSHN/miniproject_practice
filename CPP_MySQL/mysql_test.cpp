#include <iostream>
#include <mysql.h>

int main()
{
	MYSQL Conn;				// MySQL 정보 담을 구조체
	MYSQL* ConnPtr = NULL;	// MYSQL 핸들
	MYSQL_RES* Result;		// 쿼리 성공 시 결과 담는 구조체포인터
	MYSQL_ROW Row;			// 쿼리 성공 시 결과로 나온 행의 정보를 담는 구조체
	int Stat;				// 쿼리 요청 후 결과(성공 / 실패)

	mysql_init(&Conn);		// MySQL 정보 초기화

	// DB 연결
	ConnPtr = mysql_real_connect(&Conn, "127.0.0.1", "root", "1234", "chatapptest", 3306, (char*)NULL, 0);

	// 연결 결과 확인. NULL인 경우 연결 실패
	if (ConnPtr == NULL) {
		printf("MySQL Connection error : %s\n", mysql_error(&Conn));
		return 1;
	}
	else {
		printf("MySQL Connection Success\n");
	}

	// DB에 쿼리 보내기
	const char* Query = "SELECT * FROM chat";
	Stat = mysql_query(ConnPtr, Query);		// 쿼리 요청 및 성공여부 받아오기
	if (Stat != 0) {						// 쿼리 요청 실패 시 예외처리
		printf("MySQL Query error: %s\n", mysql_error(&Conn));
		return 1;
	}

	// 결과 출력
	Result = mysql_store_result(ConnPtr);				// 결과 확인
	while ((Row = mysql_fetch_row(Result)) != NULL) {	// 결과 출력. 받아온 결과를 mysql_fetch_row 함수로 넘겨주면 Row를 받아  NULL이 아닐때까지 결과 읽어와 출력
		printf("%d %s %s %s\n", atoi(Row[0]), Row[1], Row[2], Row[3]);	// mysql_fetch_row()는 char타입만 반환함. int형 데이터는 atoi()로 int 형변환 해야함
	}
	mysql_free_result(Result);							// 결과 비우기

	// db 연결 해제
	mysql_close(ConnPtr);

	/*std::cout << "ClientInfo : " << mysql_get_client_info() << std::endl;*/
	return 0;
}