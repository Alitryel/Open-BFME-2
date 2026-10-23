// cl: /DNDEBUG /MD
// The lobby color-combo wrapper stores one non-owning GameWindow pointer.
// Its assignment folds with the one-pointer store at retail 0x0007B719.
class GameWindow;
class MpGameSetupComboRef
{
public:
    MpGameSetupComboRef &operator=(GameWindow *window);
private:
    GameWindow *m_window;
};

MpGameSetupComboRef &MpGameSetupComboRef::operator=(GameWindow *window)
{
    m_window = window;
    return *this;
}
