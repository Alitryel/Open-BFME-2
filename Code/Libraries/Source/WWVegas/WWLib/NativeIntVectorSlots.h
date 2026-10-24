#pragma once
// Copyright 2025 Electronic Arts Inc.
// SPDX-License-Identifier: GPL-3.0-or-later
// Adapted from EA vector.h through BFME1 reference32774ab0. Include after
// vector.h, before this four-byte instantiation's constructors are used.
// Native PendingSurfaceStruct constructor156A10 selects tableBD3C00:
// deleting-dtor156860 / equality22B3 / Resize155460 / Clear16FED0 /
// ID(value)1969C0 / ID(pointer)154BE0. The element's original type is unknown.
// Clear and pointer ID expand the qualified base operation from vector.h;
// the explicit base declarations in callers otherwise hide those bodies.
// Size-built ordinary destructors match the shared11B body23E3, while the
// forced-inline base retains native cleanup in the speed-built parents.
// Evidence: reverse/attempt_support/sentence-native-vector-table-link-20261024/.
// Native four-byte vector lifetime and table operations.
template<> VectorClass<int>::~VectorClass();
template<> DynamicVectorClass<int>::~DynamicVectorClass();
template<> void DynamicVectorClass<int>::Clear();
template<> int DynamicVectorClass<int>::ID(const int *);
#pragma optimize("s",on)
template<> __forceinline VectorClass<int>::~VectorClass() { Clear(); }
template<> inline DynamicVectorClass<int>::~DynamicVectorClass() {}
#pragma optimize("",on)
template<> inline void DynamicVectorClass<int>::Clear() {
 ActiveCount=0;
 if(Vector && IsAllocated) {delete[] Vector;Vector=0;}
 IsAllocated=false;VectorMax=0;
}
template<> inline int DynamicVectorClass<int>::ID(const int *ptr) {
 if(!IsValid)return 0;
 return ((unsigned long)ptr-(unsigned long)&(*this)[0])/sizeof(int);
}
