// cl: /MD
// ?Rva0009A3DECleanup@@YAXXZ retail 0x0009A3DE 61 bytes.
// Four guarded releases via rowed callees with null-checked globals.
// Evidence: callers at 0x0006689A in 0x00066808 plus chain from 0x00109DCF.
class W3DVolumetricShadowManager
{
public:
	void ReleaseResources();
};

class Rva0074011F
{
public:
	void rva0074011F();
};

class Rva00109DCF
{
public:
	void rva00109DCF();
};

class Rva0007BAD6
{
public:
	void rva0007BAD6();
};

class R2GlobalReceiver;

extern class W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;
extern class W3DProjectedShadowManager *TheW3DProjectedShadowManager;
extern class Rva00108660ResourceManager *Rva00DEC2D8Manager;
extern class Rva0007DA23ResourceManager *Rva00DE1FF8Manager;

void Rva0009A3DECleanup()
{
	if (TheW3DVolumetricShadowManager != 0)
		TheW3DVolumetricShadowManager->ReleaseResources();
	if ((*(Rva0074011F **)&TheW3DProjectedShadowManager) != 0)
		(*(Rva0074011F **)&TheW3DProjectedShadowManager)->rva0074011F();
	if ((*(R2GlobalReceiver **)&Rva00DEC2D8Manager) != 0)
		((Rva00109DCF *)(*(R2GlobalReceiver **)&Rva00DEC2D8Manager))->rva00109DCF();
	if ((*(Rva0007BAD6 **)&Rva00DE1FF8Manager) != 0)
		(*(Rva0007BAD6 **)&Rva00DE1FF8Manager)->rva0007BAD6();
}
