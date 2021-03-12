#include <cmath>
#include <iostream>

const int N = 100;

class Complex
{
    double m_real;
    double m_imaginary;

public:
    Complex() : m_real(0), m_imaginary(0) {}
    Complex(double real) : m_real(real), m_imaginary(0) {}
    Complex(double real, double imaginary)
            : m_real(real), m_imaginary(imaginary) {}
    Complex(Complex &complex)
            : m_real(complex.m_real), m_imaginary(complex.m_imaginary) {}
    ~Complex() {}

    double GetReal() { return m_real; }
    double GetImaginary() { return m_imaginary; }

    void SetReal(double real) { m_real = real; }
    void SetImaginary(double imaginary) { m_imaginary = imaginary; }

    double Abs() { return sqrt(m_real * m_real + m_imaginary * m_imaginary); }

    Complex& operator = (const Complex& complex)
    {
        m_real = complex.m_real;
        m_imaginary = complex.m_imaginary;
        return *this;
    }

    Complex operator +(Complex complex)
    {
        Complex result(m_real + complex.m_real, m_imaginary + complex.m_imaginary);
        return result;
    }

    friend Complex operator *(Complex c1, Complex c2)
    {
        // (a + bi)(c + di) = ac - bd + i(ad + bc)
        Complex result;
        result.m_real = c1.m_real * c2.m_real - c1.m_imaginary * c2.m_imaginary;
        result.m_imaginary = c1.m_real * c2.m_imaginary + c1.m_imaginary * c2.m_real;
        return result;
    }

    friend std::istream &operator>>(std::istream &in, Complex &complex)
    {
        in >> complex.m_real >> complex.m_imaginary;
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, Complex &complex)
    {
        if (complex.m_real != 0 && complex.m_imaginary != 0)
        {
            //afisare a+i*b sau a-i*b
            if (complex.m_imaginary < 0)
            {
                //afisare a-i*b
                out << complex.m_real << "-i*" << -complex.m_imaginary;
            }
            else
            {
                //afisare a+i*b
                out << complex.m_real << "+i*" << complex.m_imaginary;
            }
        }
        else if (complex.m_imaginary == 0)
        {
            out << complex.m_real;
        }
        else
        {
            // complex.m_real == 0
            if (complex.m_imaginary < 0)
                out << "-i*" << -complex.m_imaginary;
            else
                out << "i*" << complex.m_imaginary;
        }
        return out;
    }
    friend class Matrice_Complexa;
};

class Matrice_Complexa
{
    Complex **matrice;
    int m_nrlinii;
    int m_nrcoloane;

public:
    Matrice_Complexa(Complex c, int n, int m)
    {
        m_nrlinii = n;
        m_nrcoloane = m;
        matrice = new Complex *[m_nrlinii];

        for (int i = 0; i < m_nrlinii; i++)
            matrice[i] = new Complex[m_nrcoloane];

        for (int i = 0; i < m_nrlinii; i++)
            for (int j = 0; j < m_nrcoloane; j++)
                matrice[i][j] = c;
    }

    Matrice_Complexa(int n, int m)
    {
        m_nrlinii = n;
        m_nrcoloane = m;
        matrice = new Complex *[m_nrlinii];

        for (int i = 0; i < m_nrlinii; i++)
            matrice[i] = new Complex[m_nrcoloane];

        Complex c(0, 0);
        for (int i = 0; i < m_nrlinii; i++)
            for (int j = 0; j < m_nrcoloane; j++)
                matrice[i][j] = c;
    }

    Matrice_Complexa()
    {
        m_nrlinii = N;
        m_nrcoloane = N;
        matrice = new Complex *[m_nrlinii];

        for (int i = 0; i < m_nrlinii; i++)
            matrice[i] = new Complex[m_nrcoloane];

        Complex c(0, 0);
        for (int i = 0; i < m_nrlinii; i++)
            for (int j = 0; j < m_nrcoloane; j++)
                matrice[i][j] = c;
    }

    ~Matrice_Complexa()
    {
        for (int i = 0; i < m_nrlinii; i++)
            delete[]matrice[i];
        delete[]matrice;
    }

    Matrice_Complexa(Matrice_Complexa &matrice2)
    {
        m_nrlinii = matrice2.m_nrlinii;
        m_nrcoloane = matrice2.m_nrcoloane;
        matrice = new Complex *[m_nrlinii];

        for (int i = 0; i < m_nrlinii; i++)
            matrice[i] = new Complex[m_nrcoloane];

        for (int i = 0; i < m_nrlinii; i++)
            for (int j = 0; j < m_nrcoloane; j++)
                matrice[i][j] = matrice2.matrice[i][j];
    }

    Matrice_Complexa operator+(Matrice_Complexa &matrice2)
    {
        if (m_nrlinii != matrice2.m_nrlinii || m_nrcoloane != matrice2.m_nrcoloane)
        {
            std::cout << "Matricele nu se pot aduna." << std::endl;
        }

        Complex c;
        Matrice_Complexa result(c, m_nrlinii, m_nrcoloane);

        for (int i = 0; i < m_nrlinii; i++)
            for (int j = 0; j <= m_nrcoloane; j++)
                result.matrice[i][j] = matrice2.matrice[i][j] + matrice[i][j];
        return result;
    }

    Matrice_Complexa operator*(Matrice_Complexa &matrice2)
    {
        if (m_nrcoloane != matrice2.m_nrcoloane)
        {
            std::cout << "Matricele nu se pot inmulti." << std::endl;
        }

        Complex c;
        Matrice_Complexa result(c, m_nrlinii, matrice2.m_nrcoloane);

        for (int i = 0; i < m_nrlinii; i++)
            for (int j = 0; j < matrice2.m_nrcoloane; j++)
                for (int l = 0; l < m_nrcoloane; l++)
                    {
                        Complex x;
                        x = matrice[i][l] * matrice2.matrice[l][j];
                        result.matrice[i][j] = result.matrice[i][j] + x;
                    }
        return result;
    }

    Matrice_Complexa operator=(const Matrice_Complexa &matrice2)
    {
        if (this == &matrice2)
            return *this;

        for (int i = 0; i < m_nrlinii; i++)
            delete[]matrice[i];
        delete[]matrice;

        m_nrlinii = matrice2.m_nrlinii;
        m_nrcoloane = matrice2.m_nrcoloane;
        matrice = new Complex *[m_nrlinii];

        for (int i = 0; i < m_nrlinii; i++)
            matrice[i] = new Complex[m_nrcoloane];

        for (int i = 0; i < m_nrlinii; i++)
            for (int j = 0; j < m_nrcoloane; j++)
                matrice[i][j] = matrice2.matrice[i][j];
    }

    friend std::istream&operator>>(std::istream& in, Matrice_Complexa& matrice2)
    {
        for(int i=0; i<matrice2.m_nrlinii; i++)
            delete []matrice2.matrice[i];
        delete []matrice2.matrice;

        in >> matrice2.m_nrlinii >> matrice2.m_nrcoloane;
        matrice2.matrice = new Complex*[matrice2.m_nrcoloane];
        for(int i=0; i<matrice2.m_nrlinii; i++)
            matrice2.matrice[i] = new Complex[matrice2.m_nrcoloane];

        for(int i=0; i<matrice2.m_nrlinii; i++)
            for(int j=0; j<matrice2.m_nrcoloane; j++)
                in >> matrice2.matrice[i][j];
        return in;
    }

    friend std::ostream&operator<<(std::ostream& out, Matrice_Complexa& matrice2)
    {
        for(int i=0; i<matrice2.m_nrlinii; i++)
        {
            for(int j=0; j<matrice2.m_nrcoloane; j++)
                out << matrice2.matrice[i][j] << " ";
            out << '\n';
        }
        return out;
    }
};

void printMenuOptions()
{
    std::cout << "1. Cititi, memorati si afisati n matrice complexe." << std::endl;
    std::cout << "2. Calculati suma matricelor." << std::endl;
    std::cout << "3. Calcualti produsul matricelor." << std::endl;
    std::cout << "4. Oprire." << std::endl;
    std::cout << std::endl;
}

void InteractiveMenu()
{
    std::cout << "Alegeti dintre urmatoarele optiuni: " << std::endl;
    printMenuOptions();
    int option = 0;
    int exit_option = 4;
    int nr = 0;

    std:: cin >> option;
    while(option != exit_option)
    {
        if(option == 1)
        {
            // citire, afisare, memorare matrice
            break;
        }
        else if(option == 2)
        {
            // suma matrice
            break;
        }
        else if(option == 3)
        {
            // produs matrice
            break;
        }
        //reafisam meniul
        std::cout << std::endl;
        printMenuOptions();
        //citim noua optiune
        std::cin >> option;
    }
}

int main()
{
    InteractiveMenu();
    return 0;
}