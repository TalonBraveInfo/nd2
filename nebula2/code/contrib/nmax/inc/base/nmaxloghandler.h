//-----------------------------------------------------------------------------
//  nmaxloghandler.h
//
//  (C)2004 Johannes Kellner
//-----------------------------------------------------------------------------
#ifndef N_MAXLOGHANDLER_H
#define N_MAXLOGHANDLER_H

//-----------------------------------------------------------------------------
/**
    @class nMaxLogHandler
    @ingroup NebulaMaxExport2Contrib

    @brief A class which redirects log messages to MAX log system from Nebula's.
    
    MAX maintains a log file that contains the text of error/warning/information/debug 
    messages generated by the system and plug-ins in @b Network directory.

    This class is used to work the Nebula2 log handler with Max log system.

    @note
    See @b LogSys class for more information on log system of 3DS Max in the 3dsmax SDK.

    The following code shows an example:
    @code
    // 
    nMaxLogHandler* logHandler = n_new(nLogHandler);
    nKernelServer::Instance()->SetLogHandler(logHanlder);
    ...

    // an instance of the LogSys max class should be specified before put any log 
    // messages to the created log handler.
    Interface* interf;
    ...
    logHandler->SetLogSys(interf);
    @endcode

    - 26-Mar-05 kims added the doc.
*/
#include <Max.h>

#include "kernel/nloghandler.h"

//-----------------------------------------------------------------------------
class nMaxLogHandler : public nLogHandler
{
public:
	nMaxLogHandler();
	~nMaxLogHandler();
	 
	/// print a message to the max.log dump
	virtual void Print(const char* msg, va_list argList);
	/// show an important message (may block the program until the user acks)
	virtual void Message(const char* msg, va_list argList);
	/// show an error message (may block the program until the user acks)
	virtual void Error(const char* msg, va_list argList);
	
	///Setup the reference to Max Interface Log
	void SetLogSys(LogSys* log);

private:
	enum logType
	{
		LOG_PRINT = 1,
		LOG_MESSAGE,
		LOG_ERROR	
	};

    enum
    {
        // size of a log message.
        LOG_SIZE = 2048
    };

	int numMsgDismissed;
	
	void doLog(logType type, const char* msg, va_list argList);
	LogSys* log;

};
//-----------------------------------------------------------------------------
#endif