#include <iostream>
#include <stdlib.h>
using namespace std;
class Piesa
{
    int owner;
    virtual bool destinatie_valida(int rnd_Srs, int col_Srs, int rnd_Dst, int col_Dst, Piesa* Tabla[8][8]) = 0;
public:
    Piesa(int o)
    {
        owner = o;
    }
    virtual int get_piece() = 0;
    int get_owner()
    {
        return owner;
    }
    bool mutare_corecta(int rnd_Srs, int col_Srs, int rnd_Dst, int col_Dst, Piesa* Tabla[8][8])
    {
        Piesa* pDst = Tabla[rnd_Dst][col_Dst];
        if (pDst == 0 || owner != pDst->get_owner())
        {
            return destinatie_valida(rnd_Srs,col_Srs,rnd_Dst,col_Dst,Tabla);
        }
        return false;
    }
};
class Pion : public Piesa
{
    virtual int get_piece()
    {
        return 1;
    }
    bool destinatie_valida(int rnd_Srs, int col_Srs, int rnd_Dst, int col_Dst, Piesa* Tabla[8][8])
    {
        Piesa* pDst = Tabla[rnd_Dst][col_Dst];
        if (pDst == 0)
        {
            //Patratul unde se muta e gol
            if (col_Srs == col_Dst)
            {
                //Se muta pe verticala
                if (get_owner() == 0)
                {
                    //Daca e alb se muta 1 in sus
                    if (rnd_Srs == rnd_Dst + 1)
                        return true;
                }
                else
                {
                    //Daca e negru se muta 1 in jos
                    if (rnd_Dst == rnd_Srs - 1)
                        return true;
                }
            }
        }
        else
        {
            //Patratul unde se muta are piesa de alta culoare
            if ((col_Srs == col_Dst + 1 - 2 * get_owner()) && (rnd_Dst == rnd_Srs + 1 - 2 * get_owner()))
                return true;
        }
        return false;
    }
public:
    Pion(int owner) :Piesa(owner) {};
};

class Cal : public Piesa
{
    virtual int get_piece()
    {
        return 2;
    }
    bool destinatie_valida(int rnd_Srs, int col_Srs, int rnd_Dst, int col_Dst, Piesa* Tabla[8][8])
    {
        //Patratul unde se muta e neocupat sau ocupat de alta culoare
        if ((col_Srs == col_Dst + 1 - 2 * get_owner()) && (rnd_Srs = rnd_Dst + 2 - 4 * get_owner()))
        {
            return true;
        }
        if ((col_Srs == col_Dst + 2 - 4 * get_owner()) && (rnd_Srs = rnd_Dst + 1 - 2 * get_owner()))
        {
            return true;
        }
        return false;
    }
public:
    Cal(int owner) : Piesa(owner) {}
};
class Nebun : public Piesa
{
    virtual int get_piece()
    {
        return 3;
    }
    bool destinatie_valida(int rnd_Srs, int col_Srs, int rnd_Dst, int col_Dst, Piesa* Tabla[8][8])
    {
        if (abs(col_Dst - col_Srs) == abs(rnd_Dst - col_Srs))
        {
            //Verifica ca nu sunt alte piese pe drumul nebunului
            int rnd_Directie;
            int col_Directie;
            int rnd_Curent;
            int col_Curent;
            if (rnd_Dst - rnd_Srs > 0)
                rnd_Directie = 1;
            else
                rnd_Directie = -1;
            if (col_Dst - col_Srs > 0)
                col_Directie = 1;
            else
                col_Directie = -1;
            for (rnd_Curent = rnd_Srs + rnd_Directie, col_Curent = col_Srs + col_Directie; col_Curent != col_Dst; rnd_Curent += rnd_Directie, col_Curent += col_Directie)
            {
                if (Tabla[rnd_Curent][col_Curent] != 0)
                    return false;
            }
            return true;
        }
        return false;
    }
public:
    Nebun(int owner) :Piesa(owner) {};
};
class Turn : public Piesa
{
    virtual int get_piece()
    {
        return 4;
    }
    bool destinatie_valida(int rnd_Srs, int col_Srs, int rnd_Dst, int col_Dst, Piesa* Tabla[8][8])
    {
        //Verifica ca nu sunt alte piese pe drumul turnului 
        if (rnd_Srs == rnd_Dst)
        {
            //Verifica pe orizontala
            int col_Directie;
            if (col_Dst - col_Srs > 0)
                col_Directie = 1;
            else
                col_Directie = -1;
            for (int col_Curent = col_Srs + col_Directie; col_Curent != col_Dst; col_Curent += col_Directie)
            {
                if (Tabla[rnd_Srs][col_Curent] != 0)
                    return false;
            }
            return true;
        }
        else if (col_Dst == col_Srs)
        {
            //Verifica pe verticala
            int rnd_Directie;
            if (rnd_Dst - rnd_Srs > 0)
                rnd_Directie = 1;
            else
                rnd_Directie = -1;
            for (int rnd_Curent = rnd_Srs + rnd_Directie; rnd_Curent != rnd_Dst; rnd_Curent += rnd_Directie)
            {
                if (Tabla[rnd_Curent][col_Srs] != 0)
                    return false;
            }
            return true;
        }
        return false;
    }
public:
    Turn(int owner) :Piesa(owner) {};
};
class Regina : public Piesa
{
    virtual int get_piece()
    {
        return 5;
    }
    bool destinatie_valida(int rnd_Srs, int col_Srs, int rnd_Dst, int col_Dst, Piesa* Tabla[8][8])
    {
        //Verifica ca nu sunt alte piese pe drumul reginei 
        if (abs(col_Dst - col_Srs) == abs(rnd_Dst - col_Srs))
        {
            //Verifica pe diagonala
            int rnd_Directie;
            int col_Directie;
            int rnd_Curent;
            int col_Curent;
            if (rnd_Dst - rnd_Srs > 0)
                rnd_Directie = 1;
            else
                rnd_Directie = -1;
            if (col_Dst - col_Srs > 0)
                col_Directie = 1;
            else
                col_Directie = -1;
            for (rnd_Curent = rnd_Srs + rnd_Directie, col_Curent = col_Srs + col_Directie; col_Curent != col_Dst; rnd_Curent += rnd_Directie, col_Curent += col_Directie)
            {
                if (Tabla[rnd_Curent][col_Curent] != 0)
                    return false;
            }
            return true;
        }
        else if (rnd_Srs == rnd_Dst)
        {
            //Verifica pe orizontala
            int col_Directie;
            if (col_Dst - col_Srs > 0)
                col_Directie = 1;
            else
                col_Directie = -1;
            for (int col_Curent = col_Srs + col_Directie; col_Curent != col_Dst; col_Curent += col_Directie)
            {
                if (Tabla[rnd_Srs][col_Curent] != 0)
                    return false;
            }
            return true;
        }
        else if (col_Dst == col_Srs)
        {
            //Verifica pe verticala
            int rnd_Directie;
            if (rnd_Dst - rnd_Srs > 0)
                rnd_Directie = 1;
            else
                rnd_Directie = -1;
            for (int rnd_Curent = rnd_Srs + rnd_Directie; rnd_Curent != rnd_Dst; rnd_Curent += rnd_Directie)
            {
                if (Tabla[rnd_Curent][col_Srs] != 0)
                    return false;
            }
            return true;
        }
        return false;
    }
public:
    Regina(int owner) :Piesa(owner) {};
};
class Rege :public Piesa
{
    virtual int get_piece()
    {
        return 6;
    }
    bool destinatie_valida(int rnd_Srs, int col_Srs, int rnd_Dst, int col_Dst, Piesa* Tabla[8][8])
    {
        if (abs(col_Srs - col_Dst) == 1 && abs(rnd_Srs - rnd_Dst) == 1)
            return true;
        return false;
    }
public:
    Rege(int owner) :Piesa(owner) {};
};
class TablaJoc
{
    Piesa* Tabla[8][8];
public:
    TablaJoc()
    {
        for(int rnd=0;rnd<8;rnd++)
            for (int col = 0; col < 8; col++)
            {
                Tabla[rnd][col] = 0;

            }
        //Aseaza piesele negre si aloca memorie
        for (int col = 0; col < 8; col++)
            Tabla[6][col] = new Pion(1);
        Tabla[7][0] = new Turn(1);
        Tabla[7][1] = new Cal(1);
        Tabla[7][2] = new Nebun(1);
        Tabla[7][3] = new Rege(1);
        Tabla[7][4] = new Regina(1);
        Tabla[7][5] = new Nebun(1);
        Tabla[7][6] = new Cal(1);
        Tabla[7][7] = new Turn(1);
        //Aseaza piesele albe si aloca memorie
        for (int col = 0; col < 8; col++)
            Tabla[1][col] = new Pion(0);
        Tabla[0][0] = new Turn(0);
        Tabla[0][1] = new Cal(0);
        Tabla[0][2] = new Nebun(0);
        Tabla[0][3] = new Rege(0);
        Tabla[0][4] = new Regina(0);
        Tabla[0][5] = new Nebun(0);
        Tabla[0][6] = new Cal(0);
        Tabla[0][7] = new Turn(0);
    }
    ~TablaJoc()
    {
        for (int rnd = 0; rnd < 8; rnd++)
            for (int col = 0; col < 8; col++)
            {
                delete Tabla[rnd][col];
                Tabla[rnd][col] = 0;
            }
    }
    Piesa* (*get_tabla(void))[8]
    {
        return Tabla;
    }
    Piesa* get_piesa(int i, int j)
    {
        return Tabla[i][j];
    }
    void set_piesa(int i, int j, Piesa* p)
    {
        Tabla[i][j] = p;
    }
    void set_tabla(Piesa* t[8][8])
    {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                Tabla[i][j] = t[i][j];
    }
    bool verifica_sah(int owner)
    {
        //Gaseste regele pe Tabla
        int col_Rege, rnd_Rege;
        for(int rnd=0;rnd<8;rnd++)
            for (int col = 0; col < 8; col++)
                if (Tabla[rnd][col] != 0 && (*Tabla)[rnd][col].get_owner() == owner && (*Tabla)[rnd][col].get_piece() == 6)
                {
                    col_Rege = col;
                    rnd_Rege = rnd;
                }
        //Verifica daca vreuna din piesele oponentului poate sa ia regele
        for (int rnd = 0; rnd < 8; rnd++)
            for (int col = 0; col < 8; col++)
                if (Tabla[rnd][col] != 0 && (*Tabla)[rnd][col].get_owner() == owner && (*Tabla)[rnd][col].mutare_corecta(rnd, col, rnd_Rege, col_Rege, Tabla))
                    return true;
        return false;
    }
    bool exista_mutari(int owner)
    {
        //Parcurge toate piesele si verifica daca vreuna are mutari corecte dispnibile
        for (int rnd = 0; rnd < 8; rnd++)
            for (int col = 0; col < 8; col++)
                if (Tabla[rnd][col] != 0 && (*Tabla)[rnd][col].get_owner() == owner)
                {
                    for (int rnd_Mutare = 0; rnd_Mutare < 8; rnd_Mutare++)
                        for (int col_Mutare = 0; col_Mutare < 8; col_Mutare++)
                            if (Tabla[rnd][col]->mutare_corecta(rnd, col, rnd_Mutare, col_Mutare, Tabla))
                            {
                                //Executa mutarea
                                Piesa* p = Tabla[rnd_Mutare][col_Mutare];
                                Tabla[rnd_Mutare][col_Mutare] = Tabla[rnd][col];
                                Tabla[rnd][col] = 0;
                                //Verifica daca dupa mutare regele jucatorului care a mutat nu este in sah
                                bool sah = verifica_sah(owner);
                                //Anuleaza mutarea precedenta
                                Tabla[rnd][col]= Tabla[rnd_Mutare][col_Mutare];
                                Tabla[rnd_Mutare][col_Mutare] = p;
                                if (!sah)
                                    return true;
                            }
                }
        return false;
    }
    
    friend ostream& operator<<(ostream& out, const TablaJoc& Tabla_Joc)
    {
        const int lat_patrat = 9;
        const int inl_patrat = 5;
        for (int rnd = 0; rnd < 8 * inl_patrat; rnd++)
        {
            int rnd_patrat = rnd / inl_patrat;
            if (rnd % inl_patrat == (inl_patrat / 2 + 1))
            {
                out << "----" << 8 - rnd_patrat << "----";
            }
            else
            {
                out << "---------";
            }
            for (int col = 0; col < 8 * lat_patrat; col++)
            {
                int col_patrat = col / lat_patrat;
                if (rnd % inl_patrat == (inl_patrat / 2) && (col % 9 == 3 || col % 9 == 4 || col % 9 == 5) && Tabla_Joc.Tabla[7 - rnd_patrat][col_patrat] != 0)
                {
                    if (col % 9 == 5)
                    {
                        out << ((Tabla_Joc.Tabla[7 - rnd_patrat][col_patrat]->get_owner()==0) ? 'A' : 'N');
                    }
                    else if (col % 9 == 4)
                    {
                        out << '-';
                    }
                    else if (col % 9 == 3)
                    {
                        switch (Tabla_Joc.Tabla[7 - rnd_patrat][col_patrat]->get_piece())
                        {
                        case 1:
                            out << 'P';
                            break;
                        case 2:
                            out << 'T';
                            break;
                        case 3:
                            out << 'C';
                            break;
                        case 4:
                            out << 'N';
                            break;
                        case 5:
                            out << 'r';
                            break;
                        case 6:
                            out << 'R';
                            break;
                        }

                    }
                }
                else
                {
                    if ((rnd_patrat + col_patrat) % 2 == 1)
                        out << '-';
                    else
                        out << ' ';
                }
            }out << '\n';
        }
        //for (int rnd = 0; rnd < lat_patrat; rnd++)
        //{
        //    if()
        //}
        return out;
    }
};
class Pozitie
{
    int rnd, col;
public:
    Pozitie(int x = 0, int y = 0)
    {
        rnd = x;
        col = y;
    }
    int get_rnd()
    {
        return rnd;
    }
    int get_col()
    {
        return col;
    }
    int set_rnd(int i)
    {
        rnd = i;
    }
    int set_col(int i)
    {
        col = i;
    }
    bool pozitie_pe_tabla()
    {
        return rnd >= 0 && col >= 0 && rnd <= 7 && col <= 7;
    }
    friend istream& operator>>(istream& in, Pozitie& poz)
    {
        int x, y;
        in >> x;
        in >> y;
        poz.rnd = x-1;
        poz.col = y-1;
        return in;
    }
    void operator = (const Pozitie& poz)
    {
        rnd = poz.rnd;
        col = poz.col;
    }

};
class Joc
{
    TablaJoc Tabla_Joc;
    int jucator;
public:
    Joc()
    {
        jucator = 0;
    }
    void Start()
    {
        do
        {
            executa_tura(Tabla_Joc.get_tabla());
            schimba_jucatorul();
        } while (!sfarsit_joc());
        cout << Tabla_Joc;
    }
    void executa_tura (Piesa* Tabla[8][8])
    {
        bool mutare_valida = false;
        do 
        {
            cout << Tabla_Joc;
            cout << "Tura jucatorului " << ((jucator == 0) ? "Alb" : "Negru") << "\nPiesa: ";
            Pozitie srs, dst;
            cin >> srs;
            cout << "La: ";
            cin >> dst;
            if (srs.pozitie_pe_tabla() && dst.pozitie_pe_tabla())
            {
                Piesa* p_Curenta = Tabla[srs.get_rnd()][srs.get_col()];
                if (p_Curenta != 0 && p_Curenta->get_owner() == jucator)
                {
                    if (p_Curenta->mutare_corecta(srs.get_rnd(), srs.get_col(), dst.get_rnd(), dst.get_col(), Tabla))
                    {
                        Piesa* p_Temp = Tabla[dst.get_rnd()][dst.get_col()];
                        Tabla_Joc.set_piesa(dst.get_rnd(), dst.get_col(), Tabla_Joc.get_piesa(srs.get_rnd(), srs.get_col()));
                        Tabla_Joc.set_piesa(srs.get_rnd(), srs.get_col(), 0);
                        if (!Tabla_Joc.verifica_sah(jucator))
                        {
                            delete p_Temp;
                            mutare_valida = true;
                        }
                        else
                        {
                            Tabla_Joc.set_piesa(srs.get_rnd(), srs.get_col(), Tabla_Joc.get_piesa(dst.get_rnd(), dst.get_col()));
                            Tabla_Joc.set_piesa(dst.get_rnd(), dst.get_col(), 0);
                        }
                    }
                }
            }
            if (!mutare_valida)
            {
                cout << "Mutare incorecta!\n";
            }
        } while (!mutare_valida);
    }
    void schimba_jucatorul()
    {
        jucator = (jucator == 1) ? 1 : 0;
    }
    bool sfarsit_joc()
    {
        bool mutare_posibila = Tabla_Joc.exista_mutari(jucator);
        if (!mutare_posibila)
        {
            if (Tabla_Joc.verifica_sah(jucator))
            {
                schimba_jucatorul();
                cout << "Sah mat, jucatorul " << ((jucator == 0) ? "Alb" : "Negru") << " a castigat";
            }
            else
                cout << "Remiza!";
        }
        return !mutare_posibila;
    }
};
int main()
{
    Joc Sah;
    Sah.Start();
    return 0;
}
