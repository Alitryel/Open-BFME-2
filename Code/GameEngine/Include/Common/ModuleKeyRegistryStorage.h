// One aligned storage object for the LargeGroupAudio module-pointer registry.
// Native E03CE0..E03CF3 is initially zero; the next datum starts at E03CF4.
// The original global spelling is unknown. This behavior-derived name owns
// the storage used by the independently verified initializer and shutdown.
#ifndef BFME_MODULE_KEY_REGISTRY_STORAGE_H
#define BFME_MODULE_KEY_REGISTRY_STORAGE_H
union BfmeModuleKeyRegistryStorage
{
    unsigned int words[5];
};
extern BfmeModuleKeyRegistryStorage BfmeLargeGroupAudioRegistry;
#endif
