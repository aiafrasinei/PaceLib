#pragma once


namespace PaceLib
{

    inline int OnePercent(int input)
    {
        return (int)input/100;
    }

    inline int FivePercent(int input)
    {
        return (int)(input * 0.5);
    }

    inline int TenPercent(int input)
    {
        return (int)(input * 0.10);
    }

    inline int Percent(int input, int nr)
    {
        return (int)(OnePercent(input) * nr);
    }

    inline int Percent(int input, float nr)
    {
        return (int)(input * nr);
    }

    inline int Half(int input)
    {
        return (int)(input/2);
    }

    inline int Third(int input)
    {
        return (int)(input/3);
    }

    inline int Quarter(int input)
    {
        return (int)(input/4);
    }

}
