#include "TSCAdjustReset.h"

// Define my superclass

#define super IOService

OSDefineMetaClassAndStructors(hu_interferenc_TSCAdjustReset, IOService)


extern "C"  void reset_tsc_adjust(void *dummy) 
{
	wrmsr64(MSR_IA32_TSC_ADJUST, 0);
}


bool hu_interferenc_TSCAdjustReset::init(OSDictionary *dictionary)
{
	if (!super::init(dictionary)){ return false; }
	return true;
}


void hu_interferenc_TSCAdjustReset::stop(IOService *provider)
{
    super::stop(provider);
}


bool hu_interferenc_TSCAdjustReset::start(IOService *provider)
{	
	IOLog("Resetting MSR_IA32_TSC_ADJUST to 0");
	mp_rendezvous_no_intrs(reset_tsc_adjust, NULL);
	if (!super::start(provider)){ return false; }
	return true;
}

