#ifndef PERCEPTRONS_HPP
#define PERCEPTRONS_HPP



class Perceptrons
{
public:
    Perceptrons() = default;
    
    template <typename T>
    static bool And(T x1, T x2)
    {
        double w1, w2, theta;

        w1 = 0.5;
        w2 = 0.5;
        theta = 0.7;

        return (double)(w1 * x1) + double(w2 * x2) > theta ? true : false;
    }

    template <typename T>
    static bool Nand(T x1, T x2)
    {
        double w1, w2, theta;
        w1 = -0.5;
        w2 = -0.5;
        theta = -0.6;

        return (double)(w1 * x1) + double(w2 * x2) > theta ? true : false;
    }

    template <typename T>
    static bool Or(T x1, T x2)
    {
        double w1, w2, theta;

        w1 = 0.5;
        w2 = 0.5;
        theta = 0.4;

        return (double)(w1 * x1) + double (w2 * x2) > theta ? true : false;
    }

    template <typename T>
    static bool Xor(T x1, T x2)
    {
        return Perceptrons::And<T>(
            Perceptrons::Or<T>(x1, x2),
            Perceptrons::Nand<T>(
                x1, x2
            )
        );
    }
};

#endif