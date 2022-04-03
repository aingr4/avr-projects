/*
 * common.c
 *
 * Created: 2022-04-01 10:14:15 PM
 *  Author: Andrew Ingram
 */ 

#include "common.h"
#include <stdlib.h>

char* coreStatusToStr(CoreStatus status)
{
	char *statusStr = NULL;
	switch (status)
	{
		case CoreStatus_OK:
			statusStr = "OK";
			break;
		case CoreStatus_ERROR:
			statusStr = "ERROR";
			break;
		default:
			statusStr = "Unknown Status";
			break; 
	}	
	return statusStr;
}