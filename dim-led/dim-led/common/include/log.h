/*
 * log.h
 *
 * Created: 2022-04-01 10:34:36 PM
 *  Author: Andrew Ingram
 */ 
#ifndef LOG_H
#define LOG_H

// DEFINES
#define ENABLE_LOGGING // If this is defined, we show logs
#define LOG_LEVEL LogLevel_DEBUG // Determines the level of logs we show

#define LOG_STR_LEN        128
#define LOG_ID_STR_LEN     13
#define LOG_LEVEL_STR_LEN  9
#define LOG_FORMAT_STR_LEN (LOG_STR_LEN - LOG_ID_STR_LEN - LOG_LEVEL_STR_LEN)


// MACROS
#define LOG_INIT(method) (logInit(method))
#define LOG(logLevel, formatStr) logWrite(logLevel, formatStr)
#define LOGF(logLevel, formatStr, ...) logWriteFormat(logLevel, formatStr, __VA_ARGS__)


// ENUMS
typedef enum {
	LogLevel_ERROR = 0,
	LogLevel_INFO  = 1,
	LogLevel_DEBUG = 2,
} LogLevel;

typedef enum {
	LogMethod_USART
} LogMethod;


// FUNCTIONS
void  logSendStr(char *logStr);
void  logWrite(LogLevel level, char *formatStr);
void  logWriteFormat(LogLevel level, char *formatStr, ...);
void  logInit(LogMethod method);
char* logLevelToStr(LogLevel level);

#endif /* LOG_H */