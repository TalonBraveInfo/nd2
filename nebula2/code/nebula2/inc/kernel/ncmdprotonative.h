#ifndef N_CMDPROTONATIVE_H
#define N_CMDPROTONATIVE_H
//------------------------------------------------------------------------------
/**
  @class nCmdProtoNative
  @ingroup ScriptServices
  @brief A factory for nCmd objects that correspond to natively implemented
         script commands.

  (c) 2003 Vadim Macagon
  
  nCmdProtoNative is licensed under the terms of the Nebula License
*/

#ifndef N_CMDPROTO_H
#include "kernel/ncmdproto.h"
#endif

#undef N_DEFINES
#define N_DEFINES nCmdProtoNative
#include "kernel/ndefdllclass.h"

//--------------------------------------------------------------------
class N_PUBLIC nCmdProtoNative : public nCmdProto 
{
public:
    /// constructor
    nCmdProtoNative(const char *_proto_def, ulong _id, void (*)(void *, nCmd *));
    /// copy constructor
    nCmdProtoNative(const nCmdProtoNative& rhs);
    
    bool Dispatch(void *, nCmd *);
    
private:
    /// pointer to C style command handler
    void (*cmd_proc)(void *, nCmd *);
};
//--------------------------------------------------------------------
#endif    

