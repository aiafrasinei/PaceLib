class Focusable
{

public:
    bool IsFocused()
    {
        return focus;
    }

    void Focus()
    {
        focus = true;
    }

    void Unfocus()
    {
        focus = false;
    }

private:

protected:
    bool focus;
    
};