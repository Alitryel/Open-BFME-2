// Address-derived reconstruction of the 14-byte status and flag setter at 0x00552C40.

class Rva00552C40Status
{
public:
	void setStatus( char status );

private:
	char m_pad[ 0x50 ];
	char m_status;
	char m_flag;
};

void Rva00552C40Status::setStatus( char status )
{
	m_status = status;
	m_flag = 1;
}
