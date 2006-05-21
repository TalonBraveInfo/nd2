#ifndef UTIL_STARTUPCHECKER_H
#define UTIL_STARTUPCHECKER_H
//------------------------------------------------------------------------------
/**
    @class nStartupChecker
    @ingroup Util

    The nStartupChecker class checks if the host system meets all 
    preconditions to start the application (correct D3D version, 
    working sound, run-once check). There should be exactly one nStartupChecker
    object alive while the application is running.
    
    (C) 2005 Radon Labs GmbH
*/
#if defined(__WIN32__) || defined(DOXYGEN)
#include "kernel/ntypes.h"
#include "util/nstring.h"
#include <windows.h>

//------------------------------------------------------------------------------
class nStartupChecker
{
public:
    /// constructor
    nStartupChecker();
    /// destructor
    ~nStartupChecker();
    /// check if the app is alreading running
    bool CheckAlreadyRunning(const nString& vendorName, const nString& appName, const nString& appWindowTitle, const nString& errorTitle, const nString& errorMsg);
    /// check for correct Direct3D version
    bool CheckDirect3D(const nString& errorTitle, const nString& errorMsg);
    /// check for working sound
    bool CheckDirectSound(const nString& errorTitle, const nString& errorMsg);

private:
    HANDLE globalMutex;         // required for the check whether the app is alreading running
};
//------------------------------------------------------------------------------
#endif
#endif

