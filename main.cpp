#include "Main.h"

int main()
{
	int  curtime[6];
	char date[20];

  //Call function Connect Database
	ConDatabase();
  
	while(1)
	{
		get_current_num_time(curtime);
		sprintf_s(date, "%04d-%02d-%02d %02d:%02d:%02d", curtime[0], curtime[1], curtime[2], curtime[3], curtime[4], curtime[5]);

		if((curtime[5] == 0) || (curtime[5] == 1) || (curtime[5] == 2) || (curtime[5] == 3) || (curtime[5] == 4) || 
		   (curtime[5] == 5) || (curtime[5] == 6) || (curtime[5] == 7) || (curtime[5] == 8) || (curtime[5] == 9) || (curtime[5] == 10) )
		{
			printf("%04d-%02d-%02d %02d:%02d:%02d \n", curtime[0], curtime[1], curtime[2], curtime[3], curtime[4], curtime[5]);
		
     	}
	
		Sleep(1000); //10 Sec
	}

	return 0;
}

void ConDatabase()
{
	
	//----------------------------- DB initialize --------------------------------------------
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLHandle);
 
	SQLSetEnvAttr(SQLHandle,SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
 
	SQLAllocHandle(SQL_HANDLE_DBC, SQLHandle, &SQLHandle);

	//----------------------------------Setting connection------------------------------------
	
	SQLCHAR rc[1024];
	

	switch(SQLDriverConnect (SQLHandle, NULL,(SQLCHAR*)"DRIVER={SQL Server};SERVER=localhost;DATABASE=YOURDATABASENAME;UID=YOURID;PWD=YOURPASSWORD;" ,
				SQL_NTS, rc, 1024, NULL,SQL_DRIVER_NOPROMPT))
	{
		case SQL_SUCCESS_WITH_INFO:
			//show_error(SQL_HANDLE_DBC, SQLHandle);
			printf ("\n Connection Database Success ! \n");
			break;

		case SQL_INVALID_HANDLE:

		case SQL_ERROR:
			show_error(SQL_HANDLE_DBC, SQLHandle);
			printf ("\n Connection Database Failed ! \n ");
			SQLReturn = -1;
			break;

		default:
			break;
	}

	if(SQLReturn == -1)
		return;

}

void CloseDatabase()
{
	//--------------------------------------- close db connection -----------------------------
	SQLFreeHandle(SQL_HANDLE_STMT, SQLHandle );
	SQLDisconnect(SQLHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLHandle);
}
void show_error(unsigned int handletype, const SQLHANDLE &handle)
{
	SQLCHAR sqlstate[1024];
	SQLCHAR message[1024];
	if(SQL_SUCCESS == SQLGetDiagRec(handletype, handle, 1, sqlstate, NULL, message, 1024, NULL))
	printf("Message: %s \n",message);
	printf("SQLSTATE: %d\n",sqlstate);
}

void get_current_num_time(int int_time[6])
{   
	time_t timer;
	struct tm newtime;
	
	timer = time(NULL);

	localtime_s(&newtime, &timer);
	int_time[0] = newtime.tm_year + 1900;
	int_time[1] = newtime.tm_mon + 1;
	int_time[2] = newtime.tm_mday;
	int_time[3] = newtime.tm_hour;
	int_time[4] = newtime.tm_min;
	int_time[5] = newtime.tm_sec;
}
