/*
 * log.c
 *
 * Created: 2022-04-01 10:36:30 PM
 *  Author: Andrew Ingram
 */

#include "common.h"
#include "log.h"

#ifdef ENABLE_LOGGING
#include "usart.h"
#endif /* ENABLE_LOGGING */

#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

LogMethod logMethod;
uint32_t  logId;

void logInit(LogMethod method)
{
#ifdef ENABLE_LOGGING
	logMethod = method;
	logId = 0;
	
	if (logMethod == LogMethod_USART)
	{
		usartInit();
	}
#endif /* ENABLE_LOGGING */
}

void logSendStr(char *logStr)
{
#ifdef ENABLE_LOGGING
	switch(logMethod)
	{
		case LogMethod_USART:
			usartSerialWrite(logStr);
			break;
		default:
			break;
	}
#endif /* ENABLE_LOGGING */
}

void logWrite(LogLevel level, char *formatStr)
{
#ifdef ENABLE_LOGGING

	char    logStr[LOG_STR_LEN]            = "";
	char    logIdStr[LOG_ID_STR_LEN]       = "";
	char    logLevelStr[LOG_LEVEL_STR_LEN] = "";
	
	if (level <= LOG_LEVEL)
	{
		snprintf(logIdStr, sizeof(logIdStr), "[%lu] ", logId++);
		snprintf(logLevelStr, sizeof(logLevelStr), "[%s] ", logLevelToStr(level));
		strncat(logStr, logIdStr, sizeof(logIdStr));
		strncat(logStr, logLevelStr, sizeof(logLevelStr));
		strncat(logStr, formatStr, LOG_FORMAT_STR_LEN);
		
		logSendStr(logStr);	
	}
	
#endif /* ENABLE_DEBUGGING */
}

void logWriteFormat(LogLevel level, char *formatStr, ...)
{
#ifdef ENABLE_LOGGING

	va_list ap;
	char    logStr[LOG_STR_LEN]            = "";
	char    logIdStr[LOG_ID_STR_LEN]       = "";
	char    vaStr[LOG_FORMAT_STR_LEN]      = "";
	char    logLevelStr[LOG_LEVEL_STR_LEN] = "";
	
	if (level <= LOG_LEVEL)
	{
		va_start(ap, formatStr);
		vsnprintf(vaStr, sizeof(vaStr), formatStr, ap);
		va_end(ap);
		
		snprintf(logIdStr, sizeof(logIdStr), "[%lu] ", logId++);
		snprintf(logLevelStr, sizeof(logLevelStr), "[%s] ", logLevelToStr(level));
		strncat(logStr, logIdStr, sizeof(logIdStr));
		strncat(logStr, logLevelStr, sizeof(logLevelStr));
		strncat(logStr, vaStr, sizeof(vaStr));
		
		logSendStr(logStr);	
	}
	
#endif /* ENABLE_DEBUGGING */
}

char* logLevelToStr(LogLevel level)
{
	char *levelStr = "";
	
	switch (level)
	{
		case LogLevel_INFO:
			levelStr = "INFO";
			break;
		case LogLevel_DEBUG:
			levelStr = "DEBUG";
			break;
		case LogLevel_ERROR:
			levelStr = "ERROR";
			break;
		default:
			break;
	}
	
	return levelStr;
}
