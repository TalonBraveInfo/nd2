#ifndef N_FILETIMEPOSIX_H
#define N_FILETIMEPOSIX_H
//------------------------------------------------------------------------------
/**
    @class nFileTimePosix

    Implement POSIX nFileTime class.
    
    (C) 2003 RadonLabs GmbH
*/
#include "kernel/ntypes.h"

#ifndef __LINUX__
#error "_nFileTimePosix: trying to compile POSIX class on hostile platform"
#endif

//------------------------------------------------------------------------------
class _nFileTimePosix
{
public:
    /// constructor
    _nFileTimePosix();
    /// operator ==
    friend bool operator ==(const _nFileTimePosix& a, const _nFileTimePosix& b);
    /// operator >=
    friend bool operator >(const _nFileTimePosix& a, const _nFileTimePosix& b);
    /// operator <=
    friend bool operator <(const _nFileTimePosix& a, const _nFileTimePosix& b);

private:
    friend class nFile;
    time_t time;
};

//------------------------------------------------------------------------------
/**
*/
inline
_nFileTimePosix::_nFileTimePosix()
{
    time = 0;
}

//------------------------------------------------------------------------------
/**
*/
inline
bool 
operator ==(const _nFileTimePosix& a, const _nFileTimePosix& b)
{
    return (a.time == b.time);
}

//------------------------------------------------------------------------------
/**
*/
inline
bool
operator >(const _nFileTimePosix& a, const _nFileTimePosix& b)
{
    return (a.time > b.time);
}

//------------------------------------------------------------------------------
/**
*/
inline
bool
operator <(const _nFileTimePosix& a, const _nFileTimePosix& b)
{
    return (a.time < b.time);
}

//------------------------------------------------------------------------------
#endif

