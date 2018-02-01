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

static IOPMPowerState powerStates[2] = {
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, kIOPMPowerOn, kIOPMPowerOn, kIOPMPowerOn, 0, 0, 0, 0, 0, 0, 0, 0}
};

IOReturn hu_interferenc_TSCAdjustReset::setPowerState(unsigned long powerStateOrdinal, IOService *whatDevice ) {
    if (powerStateOrdinal)
        this->doTSCReset();
    return IOPMAckImplied;
}


void hu_interferenc_TSCAdjustReset::stop(IOService *provider)
{
	PMstop();
    super::stop(provider);
}


bool hu_interferenc_TSCAdjustReset::start(IOService *provider)
{	
	
	if (!super::start(provider)){ return false; }
    PMinit();
    registerPowerDriver(this, powerStates, 2);
    provider->joinPMtree(this);	
	return true;
}

void hu_interferenc_TSCAdjustReset::doTSCReset(){
	
	IOLog("Resetting MSR_IA32_TSC_ADJUST to 0");
	mp_rendezvous_no_intrs(reset_tsc_adjust, NULL);

}