// cl: /O1 /MD
// ??_GNetKeepAliveCommandMsg@@MAEPAXI@Z @0x004D5B30 28B
// Deleting dtor slot 0 of vtable 0x00860244; calls rowed apply at 0x004CEE78 as ICF twin of ??1 then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

class NetKeepAliveCommandMsg { public: NetKeepAliveCommandMsg(EmitVtableTag *); protected: virtual ~NetKeepAliveCommandMsg(); };
// ?<NetKeepAliveCommandMsg::NetKeepAliveCommandMsg> absent-from-retail
NetKeepAliveCommandMsg::NetKeepAliveCommandMsg(EmitVtableTag *) {}
