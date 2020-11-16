#include <iostream>
#include <vector>
using namespace std;
class Piesa
{
protected:
    int owner;
    int id;
public:
    Piesa(int o, int i)
    {
        owner = o;
        id = i;
    }
    int get_owner()
    {
        return owner;
    }
    int get_id()
    {
        return id;
    }
};
class Pion : public Piesa
{
protected:
    Pion(int owner, int id) :Piesa(owner, id) {};
};
class Tabla
{
    int latime, lungime;
    int tura;
    vector<Piesa> piese;
public:
    Tabla()
    {
        latime = lungime = 8;
        for(int i=0;i<16;i++)
            piese.push_back(Piesa(0, i));
        for(int i=0;i<16;i++)
            piese.push_back(Piesa(1, i));
        tura = 0;
    }
    ~Tabla()
    {
        latime = lungime = 0;
        for (int i = 0; i < piese.size(); i++)
        {
            piese.pop_back();
        }
    }
};
int main()
{
    
}
