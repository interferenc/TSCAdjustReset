/*  Do what you want with this. 
 This work originates from the ideas of Turbo and the 
 frustrations of cosmo1t the dell owner.
 *
 */


#include <IOKit/IOService.h>
#include <IOKit/IOLib.h>
#include <i386/proc_reg.h>



//reg define
#define MSR_IA32_TSC_ADJUST             0x0000003b



//extern fucntion defined in mp.c from xnu
extern "C" void  mp_rendezvous_no_intrs(
										void (*action_func)(void *),
										void *arg);




class hu_interferenc_TSCAdjustReset : public IOService
{
	OSDeclareDefaultStructors(hu_interferenc_TSCAdjustReset)

public:
    virtual bool init(OSDictionary *dictionary = 0);
    virtual bool start(IOService *provider);
    virtual void stop(IOService *provider);

};
