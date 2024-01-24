#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <mmsystem.h>
using namespace std;
ifstream in2("coada.in");
ifstream in("stiva.in");
ifstream in4("lista.in");
ifstream in5("listad.in");

struct nod
{
    int info;
    nod *urm;
};

nod *s_prim,*s_ultim,*c_prim,*c_ultim,*l_prim,*l_ultim, *d_prim, *d_ultim;

int x,k=-1;
int lista1;
int playgame1,stiva1,coada1,n,i,xx,yy,distanta,lungime;
int camera;
int x_s, y_s, x_c, y_c,x_s_i,y_s_i,x_c_i,y_c_i,x_l,y_l,x_l_i,y_l_i, x_d_i, y_d_i;
char s[100];

void inttochar(int x, char s[100])
{
    int i=0;
    strcpy(s,"");
    while(x)
    {
        s[i]=char(x%10+'0');
        i++;
        x/=10;
    }
    s[i]='\0';
    strrev(s);
}

void creare_stiva(nod *&prim, nod *&ultim)
{
    nod *p;
    int x,n;
    prim = ultim = NULL;
    while(in>>x)
    {
        p = new nod;
        p->info = x;
        p->urm = NULL;
        if(prim==NULL)
        {
            prim=p;
            s_prim = p;
        }
        else
            ultim->urm = p;
        ultim = p;
    }
    s_ultim = p;
}

void creare_coada(nod *&prim, nod *&ultim)
{
    nod *p;
    int x,n;
    prim = ultim = NULL;
    while(in2>>x)
    {
        p = new nod;
        p->info = x;
        p->urm = NULL;
        if(prim==NULL)
        {
            prim=p;
            c_prim = p;
        }
        else
            ultim->urm = p;
        ultim = p;
    }
    c_ultim = ultim;
}
void creare_lista(nod *&prim, nod *&ultim)
{
    nod *p;
    int x,n;
    prim = ultim = NULL;
    while(in4>>x)
    {
        p = new nod;
        p->info = x;
        p->urm = NULL;
        if(prim == NULL)
        {
            prim=p;
            l_prim = p;
        }
        else
            ultim->urm = p;
        ultim = p;
    }
    l_ultim = ultim;
}
void creare_lista_d(nod *&prim, nod *&ultim)
{
    nod *p;
    int x,n;
    prim = ultim = NULL;
    while(in5>>x)
    {
        p = new nod;
        p->info = x;
        p->urm = NULL;
        if(prim == NULL)
        {
            prim=p;
            d_prim = p;
        }
        else
            ultim->urm = p;
        ultim = p;
    }
    d_ultim = ultim;
}

void insereaza_k(nod *&prim, nod *&ultim, int k, int x)
{

    nod *b=l_prim;
    int nr=0;

    if (k<0 || (k !=0 && prim == NULL))
    {
        settextstyle(BOLD_FONT,HORIZ_DIR,2);
        outtextxy(750,540,"ERROR: INCORRECT POSITION!");
        return;
    }
    if(l_prim!=NULL)
    {
        while(b->urm!=NULL)
        {
            nr++;
            b=b->urm; ///nr o sa fie numarul de elem -1
        }

        if(k>nr+1)
        {
            settextstyle(BOLD_FONT,HORIZ_DIR,2);
            outtextxy(750,540,"ERROR: INCORRECT POSITION!");
            //return;
        }
        else
        {


            nod *a=new nod;
            nod *q=new nod;
            q->info=x;
            q->urm=NULL;

            if (k == 0 || prim==NULL) ///atasam ca prim element
            {
                q->urm = l_prim;
                prim = q;
                l_prim=q;
            }

            if (ultim==NULL)  ///setam nodul q ca fiind si prim si ultim
            {
                ultim = q;
                l_ultim=q;
            }
            if(k>0)
            {
                a=prim;
                int j=0;
                while(j<k-1) ///mergem pana la predecesorul pozitiei k
                {
                    a=a->urm;
                    j++;
                }

                q->urm= a->urm;
                a->urm = q;
                if (q ==ultim)
                {
                    ultim =q;
                    l_ultim=q;
                }
            }
        }
    }
}

void elimina_k(nod *&prim, int k)
{
    nod *b=l_prim;
    int nr=0;
    if (k<0 || (k !=0 && prim == NULL))
    {
        settextstyle(BOLD_FONT,HORIZ_DIR,2);
        outtextxy(750,540,"ERROR: INCORRECT POSITION!");
        return;
    }

    else if(l_prim!=NULL)
    {
        while(b->urm!=NULL)
        {
            nr++;
            b=b->urm; ///nr o sa fie numarul de elem -1
        }
        if(k>nr+1)
        {
            settextstyle(BOLD_FONT,HORIZ_DIR,2);
            outtextxy(750,540,"ERROR: INCORRECT POSITION!");
            return;
        }
        else
        {
            int j=0;
            nod *p=new nod;
            if (k ==0 &&l_prim!=NULL)  ///daca vrem sa eliminam primul
            {
                p = l_prim;
                l_prim = l_prim->urm;
                delete p;
                return;
            }
            else
            {
                p = l_prim;
                j=0;
                while(j<k-1 && p->urm!=NULL)   ///ajungem la j=predecesorul pozitiei k
                {
                    p=p->urm;
                    j++;
                }
               if(p->urm->urm==NULL)  ///daca eliminam ultimul elem
                {
                    nod* temp = p;
                    p = p->urm->urm;
                    temp->urm = NULL;
                    l_ultim=p;
                }
                else
                {
                    nod* temp = p;
                    p = p->urm->urm;
                    temp->urm = p;
                }
            }
        }
    }
}
void insereaza_k_d(nod *&prim, nod *&ultim, int k, int x)
{

    nod *b=d_prim;
    int nr=0;

    if (k<0 || (k !=0 && prim == NULL))
    {
        settextstyle(BOLD_FONT,HORIZ_DIR,2);
        outtextxy(750,540,"ERROR: INCORRECT POSITION!");
        return;
    }  ///DACA PUN UN NR < 0 IMI AFISEAZA CA E EROARE


    if(d_prim!=NULL)
    {
        while(b->urm!=NULL)
        {
            nr++;
            b=b->urm; ///nr o sa fie numarul de elem -1
        }

        if(k>nr+1)
        {
            settextstyle(BOLD_FONT,HORIZ_DIR,2);
            outtextxy(750,540,"ERROR: INCORRECT POSITION!");
            //return;  ///NU AFISEAZA
        }
        else
        {


            nod *a=new nod;
            nod *q=new nod;
            q->info=x;
            q->urm=NULL;

            if (k == 0 || prim==NULL) ///atasam ca prim element
            {
                q->urm = l_prim;
                prim = q;
                d_prim=q;
            }

            if (ultim==NULL)  ///setam nodul q ca fiind si prim si ultim
            {
                ultim = q;
                d_ultim=q;
            }
            if(k>0)
            {
                a=prim;
                int j=0;
                while(j<k-1) ///mergem pana la predecesorul pozitiei k
                {
                    a=a->urm;
                    j++;
                }

                q->urm= a->urm;
                a->urm = q;
                if (q ==ultim)
                {
                    ultim =q;
                    d_ultim=q;
                }
            }
        }
    }
}

void elimina_k_d(nod *&prim, int k)
{
    nod *b=d_prim;
    int nr=0;
    if (k<0 || (k !=0 && prim == NULL))
    {
        settextstyle(BOLD_FONT,HORIZ_DIR,2);
        outtextxy(750,540,"ERROR: INCORRECT POSITION!");
        return;
    }
    else if(d_prim!=NULL)
    {
        while(b->urm!=NULL)
        {
            nr++;
            b=b->urm; ///nr o sa fie numarul de elem -1
        }
        if(k>nr+1)
        {
            settextstyle(BOLD_FONT,HORIZ_DIR,2);
            outtextxy(750,540,"ERROR: INCORRECT POSITION!");
            return;
        }
        else
        {
            int j=0;
            nod *p=new nod;
            if (k ==0 && d_prim!=NULL)  ///daca vrem sa eliminam primul
            {
                p = d_prim;
                d_prim = d_prim->urm;
                delete p;
                return;
            }
            else
            {
                p = d_prim;
                j=0;
                while(j<k-1 && p->urm!=NULL)   ///ajungem la predecesorul pozitiei k
                {
                    p=p->urm;
                    j++;
                }
                if(p->urm->urm==NULL)  ///daca eliminam ultimul elem
                {
                    nod* temp = p;
                    p = p->urm->urm;
                    temp->urm = p;
                    d_ultim=p;
                }
                else
                {
                    nod* temp = p;
                    p = p->urm->urm;
                    temp->urm = p;
                }
            }
        }
    }
}
void push_stiva(nod*&prim, int x)
{
    nod* p = new nod;
    p->info = x;
    if(prim != NULL)
    {
        p->urm = prim;
        prim = p;
        ///s_prim = p;
    }
    else
    {
        p->urm = prim;
        prim = p;
        ///s_prim = p;
    }
    s_prim = p;
    y_s += 100;
}

void pop_stiva(nod *&prim)
{
    if(prim==NULL)
    {
        settextstyle(BOLD_FONT,HORIZ_DIR,2);
        outtextxy(750,540,"ERROR: THE STACK IS EMPTY!");
    }
    else
    {
        nod* temp = new nod;
        temp = prim;
        prim = prim-> urm;
        ///s_prim = prim;

        delete temp;
    }
    y_s -= 100;
}

void push_coada(nod *&ultim, int x)
{
    nod *q = new nod;
    q->info = x;
    q->urm = NULL;

    if (c_ultim == NULL)
    {
        nod *prim = q;
        ultim = q;
        ///c_ultim = q;
    }
    else
    {
        ultim->urm = q;
        ///c_ultim->urm = q;
        ultim = q;
        ///c_ultim = q;
    }
}

void pop_coada(nod *&prim)
{
    if(prim == NULL)
    {
        settextstyle(BOLD_FONT,HORIZ_DIR,2);
        outtextxy(750,540,"ERROR: THE QUEUE IS EMPTY!");
    }
    else
    {
        nod* temp = new nod;
        temp = prim;
        prim = prim->urm;
        ///c_prim = prim;
        delete temp;
    }
    ///x_c -= 100;
}

void patrat(int x, int y, int l)
{
    line(x-2*l,y+l,x+2*l,y+l);
    delay(50);
    line(x-2*l,y-l,x-2*l,y+l);
    delay(50);
    line(x+2*l,y-l,x-2*l,y-l);
    delay(50);
    line(x+2*l,y+l,x+2*l,y-l);
    delay(50);
    ///PlaySound(TEXT("linie.wav"),NULL,SND_ASYNC);
}
void sageata(int x, int y, int l)
{
    line(x,y,x+l,y);
    delay(50);
    line(x+l,y,x+l/2,y+l/2);
    delay(50);
    line(x+l,y,x+l/2,y-l/2);
    delay(50);
    ///PlaySound(TEXT("linie.wav"),NULL,SND_ALIAS);
}
void sageata_jos(int x, int y, int l)
{
    line(x,y,x,y+l);
    delay(50);
    line(x,y+l,x+l/2,y+l/2);
    delay(50);
    line(x,y+l,x-l/2,y+l/2);
    delay(50);
    ///PlaySound(TEXT("linie.wav"),NULL,SND_ASYNC);
}
void sageata_mica(int x, int y, int l)
{
    line(x,y,x+l,y);
    delay(50);
    line(x+l,y,x+l/1.5,y+l/4);
    delay(50);
    line(x+l,y,x+l/1.5,y-l/4);
    delay(50);
    ///PlaySound(TEXT("linie.wav"),NULL,SND_ASYNC);
}
void afisare_stiva(nod *prim, nod *ultim)
{
    nod *p = s_prim;
    xx=50;
    yy=50;
    x_s_i = xx;
    y_s_i = yy;
    distanta=100;
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(BOLD_FONT,HORIZ_DIR,2);
    outtextxy(xx+80,yy,"head");
    while(p->urm)
    {
        inttochar(p->info,s);
        ultim=p;
        outtextxy(xx,yy,s);
        delay(50);
        int cif=0;
        int aux = p->info;
        int centrare = 0;
        int lungime = 25;
        while(aux)
        {
            cif++;
            aux/=10;
        }

        patrat(xx,yy,lungime);
        if(p->urm != NULL)
            sageata_jos(xx,yy+lungime,distanta/2);
        if((yy+100)>650 &&(p->urm!=NULL)||p==NULL)
        {
            yy=75;
            xx=xx+2*distanta;
            sageata_jos(xx,0,50);
        }
        else
            yy+=distanta;
        p=p->urm;
        if(p->urm==NULL)
        {
            delay(50);
            outtextxy(xx+80,yy,"tail");
            break;
        }
    }
    inttochar(p->info,s);
    ultim=p;
    outtextxy(xx,yy,s);
    delay(50);
    int cif=0;
    int aux = p->info;
    int centrare = 0;
    int lungime = 25;
    while(aux)
    {
        cif++;
        aux/=10;
    }

    patrat(xx,yy,lungime);
    x_s = xx;
    y_s = yy;
}

void afisare_coada(nod *prim, nod *ultim)
{
    nod *p = c_prim;
    xx=100;
    yy=100;
    x_c_i = xx;
    y_c_i = yy;
    distanta=100;
    lungime=25;
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(BOLD_FONT,HORIZ_DIR,2);
    outtextxy(xx,yy+60,"head");
    while(p->urm)
    {
        inttochar(p->info,s);
        outtextxy(xx,yy,s);
        delay(50);
        int cif=0;
        int aux = p->info;
        int centrare = 0;
        int lungime = 25;
        while(aux)
        {
            cif++;
            aux/=10;
        }

        patrat(xx,yy,lungime);
        if(p->urm != NULL)
            sageata(xx+2*lungime,yy,distanta/2);
        if((xx+100)>750&&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy+=2*distanta;
            sageata(0,yy,50);
        }
        else
            xx+=1.5*distanta;

        p=p->urm;

        if(p->urm==NULL)
        {
            delay(50);
            outtextxy(xx,yy+60,"tail");
            break;
        }
    }
    inttochar(p->info,s);
    ultim=p;
    outtextxy(xx,yy,s);
    delay(100);
    int cif=0;
    int aux = p->info;
    int centrare = 0;
    int lungime = 25;
    while(aux)
    {
        cif++;
        aux/=10;
    }

    patrat(xx,yy,lungime);
    x_c = xx;
    y_c = yy;
}
void afisare_lista(nod *prim, nod *ultim)
{
    nod *p = l_prim;
    xx=50;
    yy=100;
    x_l_i = xx;
    y_l_i = yy;
    distanta=100;
    lungime=25;
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(BOLD_FONT,HORIZ_DIR,2);
    while(p->urm)
    {
        inttochar(p->info,s);
        outtextxy(xx,yy,s);
        delay(50);
        int cif=0;
        int aux = p->info;
        int centrare = 0;
        int lungime = 25;
        while(aux)
        {
            cif++;
            aux/=10;
        }

        patrat(xx,yy,lungime);
        if(p->urm != NULL)
            sageata(xx+2*lungime,yy,distanta/2);
        if((xx+100)>750&&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy+=2*distanta;
            sageata(0,yy,50);
        }
        else
            xx+=1.5*distanta;

        p=p->urm;
    }
    inttochar(p->info,s);
    ultim = p;
    outtextxy(xx,yy,s);
    delay(100);
    int cif=0;
    int aux = p->info;
    int centrare = 0;
    int lungime = 25;
    while(aux)
    {
        cif++;
        aux/=10;
    }

    patrat(xx,yy,lungime);
    x_l = xx;
    y_l = yy;
}
void afisare_lista_d(nod *prim, nod *ultim)
{
    nod *p = d_prim;
    xx=50;
    yy=100;
    x_d_i = xx;
    y_d_i = yy;
    distanta=100;
    lungime=25;
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(BOLD_FONT,HORIZ_DIR,2);
    while(p->urm)
    {
        inttochar(p->info,s);
        outtextxy(xx,yy,s);
        delay(50);
        int cif=0;
        int aux = p->info;
        int centrare = 0;
        int lungime = 25;
        while(aux)
        {
            cif++;
            aux/=10;
        }

        patrat(xx,yy,lungime);
        if(p->urm != NULL)
        {
            sageata_mica(xx+2*lungime,yy,distanta/2);
            sageata_mica(xx+4*lungime,yy,-distanta/2);
        }
        if((xx+100)>750&&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy+=2*distanta;
            sageata_mica(0,yy,distanta/2);
            sageata_mica(distanta/2,yy,-distanta/2);
        }
        else
            xx+=1.5*distanta;

        p=p->urm;
    }
    inttochar(p->info,s);
    ultim = p;
    outtextxy(xx,yy,s);
    delay(100);
    int cif=0;
    int aux = p->info;
    int centrare = 0;
    int lungime = 25;
    while(aux)
    {
        cif++;
        aux/=10;
    }

    patrat(xx,yy,lungime);
}
void animatie_push_stiva()
{
    int x = atoi(s);
    push_stiva(s_prim,x);
    int distanta = 100;
    int lungime = 25;
    int xx = x_s_i;
    int yy = y_s_i;
    int x2= -1;
    int y2= -1;
    nod *p = s_prim;
    while(p->urm != NULL)
    {
        delay(100);
        setcolor(0);
        inttochar(p->urm->info,s);
        outtextxy(xx,yy,s);
        delay(100);
        setcolor(15);
        inttochar(p->info,s);
        outtextxy(xx,yy,s);
        if((yy+distanta)>650 &&(p->urm!=NULL)||p==NULL)
        {
            if(p->urm->urm == NULL)
            {
                sageata_jos(xx,yy+lungime,distanta/2);
                setcolor(0);
                outtextxy(xx+80,yy,"tail");
            }
            x2 = xx;
            y2 = yy;
            yy=75;
            xx=xx+2*distanta;
            setcolor(15);
            sageata_jos(xx,0,50);
        }
        else
            yy+=distanta;
        p = p->urm;
    }
    if((yy-distanta)<0 &&(p->urm!=NULL)||p==NULL)
    {
        setcolor(0);
        outtextxy(x2+80,y2,"tail");
        yy=75;
        xx=xx-2*distanta;
        ///setcolor(15);
        ///sageata_jos(xx,0,50);
    }
    else
        yy -= distanta;
    delay(50);
    setcolor(0);
    outtextxy(xx+80,yy,"tail");
    delay(50);
    setcolor(15);
    sageata_jos(xx,yy+lungime,distanta/2);
    delay(50);
    if((yy+100)>750&&(p->urm!=NULL)||p==NULL)
    {
        yy=75;
        xx+=2*distanta;
        sageata_jos(xx,0,50);
    }
    else
        yy+=distanta;
    inttochar(p->info,s);
    outtextxy(xx,yy,s);
    delay(50);
    patrat(xx,yy,lungime);
    delay(50);
    outtextxy(xx+80,yy,"tail");
    p = s_prim;
}
void animatie_pop_stiva()
{
    delay(50);
    int x;
    int distanta = 100;
    int lungime = 25;
    int xx = x_s_i;
    int yy = y_s_i;
    int x2= -1;
    int y2= -1;
    nod *p = s_prim;
    while(p->urm != NULL)
    {
        delay(100);
        setcolor(0);
        inttochar(p->info,s);
        outtextxy(xx,yy,s);
        delay(100);
        setcolor(15);
        inttochar(p->urm->info,s);
        outtextxy(xx,yy,s);
        if((yy+distanta)>650 &&(p->urm!=NULL)||p==NULL)
        {
            if(p->urm->urm == NULL)
            {
                x2 = xx;
                y2 = yy;
            }
            yy=75;
            xx+=2*distanta;
            ///setcolor(0);
            ///sageata(xx,0,50);
        }
        else
            yy+=distanta;
        p = p->urm;
    }
    delay(50);
    setcolor(0);
    inttochar(p->info,s);
    outtextxy(xx,yy,s);
    patrat(xx,yy,lungime);
    outtextxy(xx+80,yy,"tail");
    if((yy-distanta)<0 &&(p->urm!=NULL)||p==NULL)
    {
        setcolor(0);
        sageata_jos(xx,yy,distanta/2);
        xx = x2 - 2*distanta;
        yy = y2;
        x2 = xx;
        y2 = yy;
        ///setcolor(0);
        ///sageata(0,yy,distanta/2);
    }
    else
        yy-=distanta;
    sageata_jos(xx,yy+lungime,distanta/2);
    if(x2 != -1)
    {
        delay(100);
        setcolor(0);
        sageata_jos(x2,y2+lungime,distanta/2);

        setcolor(15);
        outtextxy(x2+80,y2,"tail");
        x2 = -1;
        y2 = -1;
    }
    delay(50);
    setcolor(15);
    outtextxy(xx+80,yy,"tail");
    if(yy + distanta > 650)
    {
        x_s = xx + 2*distanta;
        y_s = 75;
    }
    else
    {
        x_s = xx;
        y_s = yy + distanta;
    }
    pop_stiva(s_prim);
}
void animatie_push_coada()
{
    int xx = x_c_i;
    int yy = y_c_i;
    int x;
    x = atoi(s);
    push_coada(c_ultim, x);
    int distanta = 100;
    int lungime = 25;
    nod *p = c_prim;
    while(p->urm)
    {
        cout<<p->info<<" ";
        if(p->urm->urm == NULL)
        {
            delay(50);
            setcolor(0);
            outtextxy(xx,yy+60,"tail");
            break;
        }
        if(xx + distanta > 750 && p!= NULL)
        {
            xx = 100;
            yy += 2*distanta;
        }
        else
            xx += 1.5*distanta;
        p = p->urm;
    }
    setcolor(15);
    sageata(xx+2*lungime,yy,distanta/2);
    if(xx + distanta > 750)
    {
        xx = 100;
        yy += 2*distanta;
        sageata(0,yy,distanta/2);
    }
    else
        xx += 1.5*distanta;
    delay(50);
    outtextxy(xx,yy,s);
    delay(50);
    patrat(xx,yy,lungime);
    delay(50);
    outtextxy(xx,yy+60,"tail");
    x_c = xx;
    y_c = yy;
}
void animatie_pop_coada()
{
    delay(50);
    int x;
    int distanta = 100;
    int lungime = 25;
    int xx = x_c_i;
    int yy = y_c_i;
    int x2= -1;
    int y2= -1;
    nod *p = c_prim;
    while(p->urm != NULL)
    {
        delay(100);
        setcolor(0);
        inttochar(p->info,s);
        outtextxy(xx,yy,s);
        delay(100);
        setcolor(15);
        inttochar(p->urm->info,s);
        outtextxy(xx,yy,s);
        if((xx+1.5*distanta)>750 &&(p->urm!=NULL)||p==NULL)
        {
            if(p->urm->urm == NULL)
            {
                x2 = xx;
                y2 = yy;
            }
            xx=100;
            yy=yy+2*distanta;
            setcolor(0);
            ///sageata(xx,0,50);
        }
        else
            xx+=1.5*distanta;
        p = p->urm;
    }
    delay(50);
    setcolor(0);
    inttochar(p->info,s);
    outtextxy(xx,yy,s);
    patrat(xx,yy,lungime);
    outtextxy(xx,yy+60,"tail");
    if((xx-1.5*distanta)<0 &&(p->urm!=NULL)||p==NULL)
    {
        setcolor(0);
        sageata(xx,yy,distanta/2);
        xx=x2;
        yy=yy-2*distanta;
        x2 = xx;
        y2 = yy;
        ///setcolor(0);
        ///sageata(0,yy,distanta/2);
    }
    else
        xx-=1.5*distanta;
    sageata(xx+2*lungime,yy,distanta/2);
    if(x2 != -1)
    {
        delay(100);
        setcolor(0);
        sageata(x2+2*lungime,y2,distanta/2);

        setcolor(15);
        outtextxy(x2,y2+60,"tail");
        x2 = -1;
        y2 = -1;
    }
    delay(50);
    setcolor(15);
    outtextxy(xx,yy+60,"tail");
    if(xx - 1.5*distanta < 0)
    {

        x_c = 100;
        y_c = yy - 2*distanta;
    }
    else
    {
        x_c = xx - 1.5*distanta;
        y_c = yy;
    }
    pop_coada(c_prim);
}
void animatie_insereaza_k()
{
    int xx = x_l_i;
    int yy = y_l_i;
    int aux = 0,x=0;
    nod *p = l_prim;
    char s2[100];
    strcpy(s2,s);
    while(aux < k-1)
    {
        p = p->urm;
        aux++;
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx += 1.5*distanta;
    }
    if((xx+1.5*distanta)>750 &&(p->urm!=NULL)||p==NULL)
    {
        xx=100;
        yy=yy+2*distanta;
    }
    else
        xx += 1.5*distanta;
    x = 0;
    if(k == 0)
    {
        xx = x_l_i;
        yy = y_l_i;
        p = l_prim;
        delay(50);
        setcolor(0);
        inttochar(p->urm->info,s);
        outtextxy(xx,yy,"00000");
        xx += 1.5*distanta;
        delay(50);
        setcolor(15);
        inttochar(p->info,s);
        outtextxy(xx,yy,s);
        x = p->info;
    }
    while(p->urm)
    {
        delay(100);
        inttochar(p->urm->info,s);
        setcolor(0);
        outtextxy(xx,yy,s);
        delay(100);
        setcolor(15);
        inttochar(x,s);
        outtextxy(xx,yy,s);
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx+=1.5*distanta;
        x = p->urm->info;
        p = p->urm;
    }
    delay(100);
    sageata(xx-4*lungime,yy,distanta/2);
    delay(100);
    inttochar(p->info,s);
    outtextxy(xx,yy,s);
    delay(100);
    patrat(xx,yy,lungime);

    xx = 50;
    yy = 100;
    aux = 0;
    x = atoi(s2);
    p = l_prim;
    insereaza_k(l_prim,l_ultim,k,x); ///apeleaza functia sa insereze noul elem
    ///cout<<k<<" "<<s2<<endl;

    xx = 50;
    yy = 100;
    aux = 0;
    p = l_prim;
    while(aux <= k-1)
    {
        p = p->urm;
        aux++;
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx += 1.5*distanta;
    }
    setcolor(15);
    inttochar(x,s);
    outtextxy(xx,yy,s);
    p = l_prim;
    while(p)
    {
        cout<<p->info<<" ";
        p = p->urm;
    }
}
void animatie_elimina_k()
{
    delay(50);
    int x;
    int distanta = 100;
    int lungime = 25;
    int xx = x_l_i;
    int yy = y_l_i;
    int x2= -1;
    int y2= -1;
    int aux = 0;
    inttochar(l_prim->info,s);
    elimina_k(l_prim,k);
    nod *p = l_prim;
    while(aux < k-1)
    {
        p = p->urm;
        aux++;
        if((xx+1.5*distanta)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx += 1.5*distanta;
    }
    if((xx+1.5*distanta)>750 &&(p->urm!=NULL)||p==NULL)
    {
        xx=100;
        yy=yy+2*distanta;
    }
    else if(k > 0)
        xx += 1.5*distanta;
    if(k >= 0)
    {
        if(k == 0)
        {
            delay(50);
            xx = x_l_i;
            yy = y_l_i;
            p = l_prim;
            setcolor(0);
            outtextxy(xx,yy,s);
            delay(50);
            setcolor(15);
            inttochar(p->info,s);
            outtextxy(xx,yy,s);
            xx += 1.5*distanta;
        }
        while(p->urm != NULL)
        {
            delay(100);
            setcolor(0);
            outtextxy(xx,yy,s);
            inttochar(p->info,s);
            outtextxy(xx,yy,s);
            delay(100);
            setcolor(15);
            inttochar(p->urm->info,s);
            outtextxy(xx,yy,s);
            if((xx+100)>750)
            {
                x2 = xx;
                y2 = yy;
            }
            if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
            {
                xx=100;
                yy=yy+2*distanta;
                ///setcolor(0);
                ///sageata(xx,0,50);
            }
            else
                xx+=1.5*distanta;

            p = p->urm;
        }
        delay(50);
        setcolor(0);
        inttochar(p->info,s);
        outtextxy(xx,yy,s);
        patrat(xx,yy,lungime);
        sageata(xx-4*lungime,yy,distanta/2);
        delay(50);
        if(xx == 100)
        {
            xx = x2;
            yy=yy-2*distanta;
            setcolor(0);
            sageata(x2+2*lungime,y2,distanta/2);
        }

        setcolor(15);
        p = l_prim;
        while(p)
        {
            cout<<p->info<<" ";
            p = p->urm;
        }
    }
    else if(k == 0)
    {
        delay(100);
        p = l_prim;

    }

}
void animatie_insereaza_primul()
{
    int xx = x_l_i;
    int yy = y_l_i;
    int aux = 0,x=0;
    nod *p = l_prim;
    char s2[100];
    strcpy(s2,s);
    k = 0;
    while(aux < k-1)
    {
        p = p->urm;
        aux++;
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx += 1.5*distanta;
    }
    if((xx+1.5*distanta)>750 &&(p->urm!=NULL)||p==NULL)
    {
        xx=100;
        yy=yy+2*distanta;
    }
    else
        xx += 1.5*distanta;
    x = 0;
    if(k == 0)
    {
        xx = x_l_i;
        yy = y_l_i;
        p = l_prim;
        delay(50);
        setcolor(0);
        inttochar(p->urm->info,s);
        outtextxy(xx,yy,"00000");
        xx += 1.5*distanta;
        delay(50);
        setcolor(15);
        inttochar(p->info,s);
        outtextxy(xx,yy,s);
        x = p->info;
    }
    while(p->urm)
    {
        delay(100);
        inttochar(p->urm->info,s);
        setcolor(0);
        outtextxy(xx,yy,s);
        delay(100);
        setcolor(15);
        inttochar(x,s);
        outtextxy(xx,yy,s);
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx+=1.5*distanta;
        x = p->urm->info;
        p = p->urm;
    }
    delay(100);
    sageata(xx-4*lungime,yy,distanta/2);
    delay(100);
    inttochar(p->info,s);
    outtextxy(xx,yy,s);
    delay(100);
    patrat(xx,yy,lungime);

    xx = 50;
    yy = 100;
    aux = 0;
    x = atoi(s2);
    p = l_prim;
    insereaza_k(l_prim,l_ultim,k,x); ///apeleaza functia sa insereze noul elem
    ///cout<<k<<" "<<s2<<endl;

    xx = 50;
    yy = 100;
    aux = 0;
    p = l_prim;
    while(aux <= k-1)
    {
        p = p->urm;
        aux++;
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx += 1.5*distanta;
    }
    setcolor(15);
    inttochar(x,s);
    outtextxy(xx,yy,s);
    p = l_prim;
    while(p)
    {
        cout<<p->info<<" ";
        p = p->urm;
    }

}
void animatie_insereaza_ultimul()
{
    k = 0;
    nod *p = l_prim;
    while(p)
    {
        k++;
        p = p->urm;
    }
    ///k devine numarul de elemente din lista
    int xx = x_l_i;
    int yy = y_l_i;
    int aux = 0,x=0;
    p = l_prim;
    char s2[100];
    strcpy(s2,s);
    while(aux < k-1)
    {
        p = p->urm;
        aux++;
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx += 1.5*distanta;
    }
    if((xx+1.5*distanta)>750 &&(p->urm!=NULL)||p==NULL)
    {
        xx=100;
        yy=yy+2*distanta;
    }
    else
        xx += 1.5*distanta;
    x = 0;
    if(k == 0)
    {
        xx = x_l_i;
        yy = y_l_i;
        p = l_prim;
        delay(50);
        setcolor(0);
        inttochar(p->urm->info,s);
        outtextxy(xx,yy,"00000");
        xx += 1.5*distanta;
        delay(50);
        setcolor(15);
        inttochar(p->info,s);
        outtextxy(xx,yy,s);
        x = p->info;
    }
    else
    {
        setcolor(0);
        outtextxy(xx,yy,"00000");
    }
    while(p->urm)
    {
        delay(100);
        inttochar(p->urm->info,s);
        setcolor(0);
        outtextxy(xx,yy,s);
        delay(100);
        setcolor(15);
        inttochar(x,s);
        outtextxy(xx,yy,s);
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx+=1.5*distanta;
        x = p->urm->info;
        p = p->urm;
    }
    delay(100);
    sageata(xx-4*lungime,yy,distanta/2);
    delay(100);
    inttochar(p->info,s);
    outtextxy(xx,yy,s);
    delay(100);
    patrat(xx,yy,lungime);

    xx = 50;
    yy = 100;
    aux = 0;
    x = atoi(s2);
    p = l_prim;
    insereaza_k(l_prim,l_ultim,k,x); ///apeleaza functia sa insereze noul elem
    ///cout<<k<<" "<<s2<<endl;

    xx = 50;
    yy = 100;
    aux = 0;
    p = l_prim;
    while(aux <= k-1)
    {
        p = p->urm;
        aux++;
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx += 1.5*distanta;
    }
    setcolor(15);
    sageata(xx-4*lungime,yy,distanta/2);
    inttochar(x,s);
    delay(50);
    outtextxy(xx,yy,s);
    delay(50);
    patrat(xx,yy,lungime);
}
void animatie_elimina_primul()
{
    delay(50);
    int x;
    k = 0;
    int distanta = 100;
    int lungime = 25;
    int xx = x_l_i;
    int yy = y_l_i;
    int x2= -1;
    int y2= -1;
    int aux = 0;
    inttochar(l_prim->info,s);
    elimina_k(l_prim,k);
    nod *p = l_prim;
    while(aux < k-1)
    {
        p = p->urm;
        aux++;
        if((xx+1.5*distanta)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx += 1.5*distanta;
    }
    if((xx+1.5*distanta)>750 &&(p->urm!=NULL)||p==NULL)
    {
        xx=100;
        yy=yy+2*distanta;
    }
    else if(k > 0)
        xx += 1.5*distanta;
    if(k >= 0)
    {
        if(k == 0)
        {
            delay(50);
            xx = x_l_i;
            yy = y_l_i;
            p = l_prim;
            setcolor(0);
            outtextxy(xx,yy,s);
            delay(50);
            setcolor(15);
            inttochar(p->info,s);
            outtextxy(xx,yy,s);
            xx += 1.5*distanta;
        }
        while(p->urm != NULL)
        {
            delay(100);
            setcolor(0);
            outtextxy(xx,yy,s);
            inttochar(p->info,s);
            outtextxy(xx,yy,s);
            delay(100);
            setcolor(15);
            inttochar(p->urm->info,s);
            outtextxy(xx,yy,s);
            if((xx+100)>750)
            {
                x2 = xx;
                y2 = yy;
            }
            if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
            {
                xx=100;
                yy=yy+2*distanta;
                ///setcolor(0);
                ///sageata(xx,0,50);
            }
            else
                xx+=1.5*distanta;

            p = p->urm;
        }
        delay(50);
        setcolor(0);
        inttochar(p->info,s);
        outtextxy(xx,yy,s);
        patrat(xx,yy,lungime);
        sageata(xx-4*lungime,yy,distanta/2);
        delay(50);
        if(xx == 100)
        {
            xx = x2;
            yy=yy-2*distanta;
            setcolor(0);
            sageata(x2+2*lungime,y2,distanta/2);
        }

        setcolor(15);
        p = l_prim;
        while(p)
        {
            cout<<p->info<<" ";
            p = p->urm;
        }
    }
    else if(k == 0)
    {
        delay(100);
        p = l_prim;

    }
}
void animatie_elimina_ultimul()
{
    int xx = x_l_i;
    int yy = y_l_i;
    k = 0;
    nod *p = l_prim;
    while(p)
    {
        k++;
        p = p->urm;
    }
    ///k devine numarul de elemente din lista

    p = l_prim;
    while(p->urm)
    {
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx += 1.5*distanta;

        p = p->urm;
        if(p->urm->urm == NULL)
        {
            p->urm = NULL;
            setcolor(0);
            sageata(xx+2*lungime,yy,distanta/2);
            if((xx+100)>750)
            {
                xx=100;
                yy=yy+2*distanta;
                setcolor(0);
                sageata(0,yy,distanta/2);
            }
            else
                xx += 1.5*distanta;
            break;
        }
    }
    delay(100);
    inttochar(p->info,s);
    outtextxy(xx,yy,"00000");
    outtextxy(xx,yy,s);
    patrat(xx,yy,lungime);
}
void animatie_insereaza_k_d()
{
    int xx = x_d_i;
    int yy = y_d_i;
    int aux = 0,x=0;
    nod *p = d_prim;
    char s2[100];
    strcpy(s2,s);
    while(aux < k-1)
    {
        p = p->urm;
        aux++;
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx += 1.5*distanta;
    }
    if((xx+1.5*distanta)>750 &&(p->urm!=NULL)||p==NULL)
    {
        xx=100;
        yy=yy+2*distanta;
    }
    else
        xx += 1.5*distanta;
    x = 0;
    if(k == 0)
    {
        xx = x_l_i;
        yy = y_l_i;
        p = l_prim;
        delay(50);
        setcolor(0);
        inttochar(p->urm->info,s);
        outtextxy(xx,yy,"00000");
        xx += 1.5*distanta;
        delay(50);
        setcolor(15);
        inttochar(p->info,s);
        outtextxy(xx,yy,s);
        x = p->info;
    }
    while(p->urm)
    {
        delay(100);
        inttochar(p->urm->info,s);
        setcolor(0);
        outtextxy(xx,yy,s);
        delay(100);
        setcolor(15);
        inttochar(x,s);
        outtextxy(xx,yy,s);
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx+=1.5*distanta;
        x = p->urm->info;
        p = p->urm;
    }
    delay(100);
    sageata_mica(xx-4*lungime,yy,distanta/2);
    sageata_mica(xx-2*lungime,yy,-distanta/2);
    delay(100);
    inttochar(p->info,s);
    outtextxy(xx,yy,s);
    delay(100);
    patrat(xx,yy,lungime);

    xx = 50;
    yy = 100;
    aux = 0;
    x = atoi(s2);
    p = d_prim;
    insereaza_k(d_prim,d_ultim,k,x); ///apeleaza functia sa insereze noul elem
    ///cout<<k<<" "<<s2<<endl;

    xx = 50;
    yy = 100;
    aux = 0;
    p = d_prim;
    while(aux <= k-1)
    {
        p = p->urm;
        aux++;
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx += 1.5*distanta;
    }
    setcolor(15);
    inttochar(x,s);
    outtextxy(xx,yy,s);
    p = d_prim;
    while(p)
    {
        cout<<p->info<<" ";
        p = p->urm;
    }
}
void animatie_elimina_k_d()
{
    delay(50);
    int x;
    int distanta = 100;
    int lungime = 25;
    int xx = x_d_i;
    int yy = y_d_i;
    int x2= -1;
    int y2= -1;
    int aux = 0;
    inttochar(d_prim->info,s);
    elimina_k(d_prim,k);
    nod *p = d_prim;
    while(aux < k-1)
    {
        p = p->urm;
        aux++;
        if((xx+1.5*distanta)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx += 1.5*distanta;
    }
    if((xx+1.5*distanta)>750 &&(p->urm!=NULL)||p==NULL)
    {
        xx=100;
        yy=yy+2*distanta;
    }
    else if(k > 0)
        xx += 1.5*distanta;
    if(k >= 0)
    {
        if(k == 0)
        {
            delay(50);
            xx = x_d_i;
            yy = y_d_i;
            p = d_prim;
            setcolor(0);
            outtextxy(xx,yy,s);
            delay(50);
            setcolor(15);
            inttochar(p->info,s);
            outtextxy(xx,yy,s);
            xx += 1.5*distanta;
        }
        while(p->urm != NULL)
        {
            delay(100);
            setcolor(0);
            outtextxy(xx,yy,s);
            inttochar(p->info,s);
            outtextxy(xx,yy,s);
            delay(100);
            setcolor(15);
            inttochar(p->urm->info,s);
            outtextxy(xx,yy,s);
            if((xx+100)>750)
            {
                x2 = xx;
                y2 = yy;
            }
            if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
            {
                xx=100;
                yy=yy+2*distanta;
                ///setcolor(0);
                ///sageata(xx,0,50);
            }
            else
                xx+=1.5*distanta;

            p = p->urm;
        }
        delay(50);
        setcolor(0);
        inttochar(p->info,s);
        outtextxy(xx,yy,s);
        patrat(xx,yy,lungime);
        sageata_mica(xx-4*lungime,yy,distanta/2);
        sageata_mica(xx-2*lungime,yy,-distanta/2);
        delay(50);
        if(xx == 100)
        {
            xx = x2;
            yy=yy-2*distanta;
            setcolor(0);
            sageata_mica(x2+2*lungime,y2,distanta/2);
            sageata_mica(x2+4*lungime,y2,-distanta/2);
        }

        setcolor(15);
        p = d_prim;
        while(p)
        {
            cout<<p->info<<" ";
            p = p->urm;
        }
    }
    else if(k == 0)
    {
        delay(100);
        p = d_prim;
    }
}
void animatie_insereaza_primul_d()
{
    int xx = x_d_i;
    int yy = y_d_i;
    int aux = 0,x=0;
    nod *p = d_prim;
    char s2[100];
    strcpy(s2,s);
    k = 0;
    while(aux < k-1)
    {
        p = p->urm;
        aux++;
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx += 1.5*distanta;
    }
    if((xx+1.5*distanta)>750 &&(p->urm!=NULL)||p==NULL)
    {
        xx=100;
        yy=yy+2*distanta;
    }
    else
        xx += 1.5*distanta;
    x = 0;
    if(k == 0)
    {
        xx = x_d_i;
        yy = y_d_i;
        p = l_prim;
        delay(50);
        setcolor(0);
        inttochar(p->urm->info,s);
        outtextxy(xx,yy,"00000");
        xx += 1.5*distanta;
        delay(50);
        setcolor(15);
        inttochar(p->info,s);
        outtextxy(xx,yy,s);
        x = p->info;
    }
    while(p->urm)
    {
        delay(100);
        inttochar(p->urm->info,s);
        setcolor(0);
        outtextxy(xx,yy,s);
        delay(100);
        setcolor(15);
        inttochar(x,s);
        outtextxy(xx,yy,s);
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx+=1.5*distanta;
        x = p->urm->info;
        p = p->urm;
    }
    delay(100);
    sageata_mica(xx-4*lungime,yy,distanta/2);
    sageata_mica(xx-2*lungime,yy,-distanta/2);
    delay(100);
    inttochar(p->info,s);
    outtextxy(xx,yy,s);
    delay(100);
    patrat(xx,yy,lungime);

    xx = 50;
    yy = 100;
    aux = 0;
    x = atoi(s2);
    p = d_prim;
    insereaza_k(d_prim,d_ultim,k,x); ///apeleaza functia sa insereze noul elem
    ///cout<<k<<" "<<s2<<endl;

    xx = 50;
    yy = 100;
    aux = 0;
    p = d_prim;
    while(aux <= k-1)
    {
        p = p->urm;
        aux++;
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx += 1.5*distanta;
    }
    setcolor(15);
    sageata_mica(xx+2*lungime,yy,distanta/2);
    sageata_mica(xx+4*lungime,yy,-distanta/2);
    delay(50);
    inttochar(x,s);
    outtextxy(xx,yy,s);
    delay(50);
    patrat(xx,yy,lungime);
    p = d_prim;
    while(p)
    {
        cout<<p->info<<" ";
        p = p->urm;
    }

}
void animatie_insereaza_ultimul_d()
{
    k = 0;
    nod *p = d_prim;
    while(p)
    {
        k++;
        p = p->urm;
    }
    ///k devine numarul de elemente din lista

    int xx = x_d_i;
    int yy = y_d_i;
    int aux = 0,x=0;
    p = d_prim;
    char s2[100];
    strcpy(s2,s);
    while(aux < k-1)
    {
        cout<<p->info<<" ";
        p = p->urm;
        aux++;
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx += 1.5*distanta;
    }
    if((xx+1.5*distanta)>750 &&(p->urm!=NULL)||p==NULL)
    {
        xx=100;
        yy=yy+2*distanta;
    }
    else
        xx += 1.5*distanta;
    x = 0;
    if(k == 0)
    {
        xx = x_d_i;
        yy = y_d_i;
        p = d_prim;
        delay(50);
        setcolor(0);
        inttochar(p->urm->info,s);
        outtextxy(xx,yy,"00000");
        xx += 1.5*distanta;
        delay(50);
        setcolor(15);
        inttochar(p->info,s);
        outtextxy(xx,yy,s);
        x = p->info;
    }
    else
    {
        setcolor(0);
        outtextxy(xx,yy,"00000");
    }
    while(p->urm)
    {
        delay(100);
        inttochar(p->urm->info,s);
        setcolor(0);
        outtextxy(xx,yy,s);
        delay(100);
        setcolor(15);
        inttochar(x,s);
        outtextxy(xx,yy,s);
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx+=1.5*distanta;
        x = p->urm->info;
        p = p->urm;
    }
    delay(50);
    sageata_mica(xx-4*lungime,yy,distanta/2);
    sageata_mica(xx-2*lungime,yy,-distanta/2);
    delay(50);
    inttochar(p->info,s);
    outtextxy(xx,yy,s);
    delay(100);
    patrat(xx,yy,lungime);

    xx = 50;
    yy = 100;
    aux = 0;
    x = atoi(s2);
    p = d_prim;
    insereaza_k_d(d_prim,d_ultim,k,x); ///apeleaza functia sa insereze noul elem
    ///cout<<k<<" "<<s2<<endl;

    xx = x_d_i;
    yy = y_d_i;
    aux = 0;
    p = d_prim;
    while(aux <= k-1)
    {
        p = p->urm;
        aux++;
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx += 1.5*distanta;
    }
    setcolor(15);
    sageata_mica(xx-4*lungime,yy,distanta/2);
    sageata_mica(xx-2*lungime,yy,-distanta/2);
    delay(50);
    inttochar(x,s);
    outtextxy(xx,yy,s);
    delay(50);
    patrat(xx,yy,lungime);
    p = d_prim;
    while(p)
    {
        cout<<p->info<<" ";
        p = p->urm;
    }

}
void animatie_elimina_primul_d()
{
    delay(50);
    int x;
    k = 0;
    int distanta = 100;
    int lungime = 25;
    int xx = x_d_i;
    int yy = y_d_i;
    int x2= -1;
    int y2= -1;
    int aux = 0;
    inttochar(d_prim->info,s);
    elimina_k(d_prim,k);
    nod *p = d_prim;
    while(aux < k-1)
    {
        p = p->urm;
        aux++;
        if((xx+1.5*distanta)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx += 1.5*distanta;
    }
    if((xx+1.5*distanta)>750 &&(p->urm!=NULL)||p==NULL)
    {
        xx=100;
        yy=yy+2*distanta;
    }
    else if(k > 0)
        xx += 1.5*distanta;
    if(k >= 0)
    {
        if(k == 0)
        {
            delay(50);
            xx = x_d_i;
            yy = y_d_i;
            p = d_prim;
            setcolor(0);
            outtextxy(xx,yy,s);
            delay(50);
            setcolor(15);
            inttochar(p->info,s);
            outtextxy(xx,yy,s);
            xx += 1.5*distanta;
        }
        while(p->urm != NULL)
        {
            delay(100);
            setcolor(0);
            outtextxy(xx,yy,s);
            inttochar(p->info,s);
            outtextxy(xx,yy,s);
            delay(100);
            setcolor(15);
            inttochar(p->urm->info,s);
            outtextxy(xx,yy,s);
            if((xx+100)>750)
            {
                x2 = xx;
                y2 = yy;
            }
            if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
            {
                xx=100;
                yy=yy+2*distanta;
                ///setcolor(0);
                ///sageata(xx,0,50);
            }
            else
                xx+=1.5*distanta;

            p = p->urm;
        }
        delay(50);
        setcolor(0);
        inttochar(p->info,s);
        outtextxy(xx,yy,s);
        patrat(xx,yy,lungime);
        sageata(xx-4*lungime,yy,distanta/2);
        delay(50);
        if(xx == 100)
        {
            xx = x2;
            yy=yy-2*distanta;
            setcolor(0);
            sageata_mica(x2+2*lungime,y2,distanta/2);
            sageata_mica(x2+4*lungime,y2,-distanta/2);
        }
        setcolor(15);
        p = d_prim;
        while(p)
        {
            cout<<p->info<<" ";
            p = p->urm;
        }
    }
    else if(k == 0)
    {
        delay(100);
        p = d_prim;
    }
}
void animatie_elimina_ultimul_d()
{
    int xx = x_d_i;
    int yy = y_d_i;
    k = 0;
    nod *p = d_prim;
    while(p)
    {
        k++;
        p = p->urm;
    }
    ///k devine numarul de elemente din lista

    p = d_prim;
    while(p->urm)
    {
        if((xx+100)>750 &&(p->urm!=NULL)||p==NULL)
        {
            xx=100;
            yy=yy+2*distanta;
        }
        else
            xx += 1.5*distanta;
        p = p->urm;
        if(p->urm->urm == NULL)
        {
            p->urm = NULL;
            setcolor(0);
            sageata_mica(xx+2*lungime,yy,distanta/2);
            sageata_mica(xx+4*lungime,yy,-distanta/2);
            if((xx+100)>750)
            {
                xx=100;
                yy=yy+2*distanta;
                setcolor(0);
                sageata_mica(0,yy,distanta/2);
                sageata_mica(distanta/2,yy,-distanta/2);
            }
            else
                xx += 1.5*distanta;
            break;
        }
    }
    delay(100);
    inttochar(p->info,s);
    outtextxy(xx,yy,s);
    patrat(xx,yy,lungime);
}
void menu()
{
    delay(100);

    readimagefile("proiect.jpg",0,0,1100,700);
    setcolor(15);

    settextstyle(BOLD_FONT,HORIZ_DIR,2);
    rectangle(450,320,700,250);
    outtextxy(550,280,"START");

    rectangle(450,420,700,350);
    outtextxy(550,380,"EXIT");
}
void stiva()
{

    ///stiva1=initwindow(1100,700, "STACK");
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    rectangle(800,220,1050,300);
    outtextxy(900,250,"PUSH");

    rectangle(800,320,1050,400);
    outtextxy(900,350,"POP");

    rectangle(800,420,1050,500);
    outtextxy(900,450,"BACK");
}
void coada()
{   settextstyle(BOLD_FONT,HORIZ_DIR,3);
    rectangle(800,220,1050,300);
    outtextxy(900,250,"PUSH");

    rectangle(800,320,1050,400);
    outtextxy(900,350,"POP");

    rectangle(800,420,1050,500);
    outtextxy(900,450,"BACK");
}
void lista()
{
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    rectangle(800,220,1050,300);
    outtextxy(860,250,"INSEREAZA K");

    rectangle(800,320,1050,400);
    outtextxy(870,350,"ELIMINA K");

    rectangle(500,420,790,500);
    outtextxy(530,450,"INSEREAZA PRIMUL");

    rectangle(800,420,1050,500);
    outtextxy(830,450,"ELIMINA PRIMUL");

    rectangle(500,520, 790, 600);
    outtextxy(530,550,"INSEREAZA ULTIMUL");

    rectangle(800,520, 1050, 600);
    outtextxy(830,550,"ELIMINA ULTIMUL");

    rectangle(800, 620, 1050, 700);
    outtextxy(900, 650,"BACK");
}
void listad()
{
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    rectangle(800,220,1050,300);
    outtextxy(860,250,"INSEREAZA K");

    rectangle(800,320,1050,400);
    outtextxy(870,350,"ELIMINA K");

    rectangle(500,420,790,500);
    outtextxy(530,450,"INSEREAZA PRIMUL");

    rectangle(800,420,1050,500);
    outtextxy(830,450,"ELIMINA PRIMUL");

    rectangle(500,520, 790, 600);
    outtextxy(530,550,"INSEREAZA ULTIMUL");

    rectangle(800,520, 1050, 600);
    outtextxy(830,550,"ELIMINA ULTIMUL");

    rectangle(800, 620, 1050, 700);
    outtextxy(900, 650,"BACK");
}
void inputbox()
{
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setcolor(15);
    rectangle(800,520,1050,600);
    outtextxy(700,550,"INPUT:");

}
void inputboxk()
{
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setcolor(15);
    rectangle(100,500,250,550);
    outtextxy(25,520,"INPUT:");
    rectangle(100,600,250,650);
    outtextxy(35,620,"K:");
}

void playgame()
{
    delay(200);
    readimagefile("proiect.jpg",0,0,1100,700);

    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    outtextxy(520,200,"CHOOSE:");

    settextstyle(BOLD_FONT,HORIZ_DIR,2);
    rectangle(450,320,700,250);
    outtextxy(550,280,"STACK");

    rectangle(450,420,700,350);
    outtextxy(550,380,"QUEUE");

    rectangle(450, 520,700,450);
    outtextxy(550,480, "LIST");

    rectangle(710, 520, 740, 450);
    outtextxy(720,480,"D");

    rectangle(450, 620,700,550);
    outtextxy(510,580, "BACK TO MENU");
}

void update(int camera)
{
    cleardevice();
    closegraph();
    delay(200);
    switch(camera)
    {
    case 1:
    {
        int menu_ = initwindow(1100,700,"menu");
        menu();
        while(1)
        {
            POINT mouse;
            GetCursorPos(&mouse);
            int mx=mouse.x;
            int my=mouse.y;

            if(GetAsyncKeyState(VK_LBUTTON))
                if((mx<700 && mx>450)&&(my<420 && my>350))
                {
                    //PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    closegraph();///click EXIT
                }

                else if((mx<700 && mx>450)&&(my<320 && my>250))  ///click START
                {
                    camera = 2;///playgame
                    update(camera);
                }
        }
        break;
    }
    case 2:
    {
       // PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
        int playgame_ = initwindow(1100,700,"playgame");
        playgame();
        while(1)
        {
            POINT mouse;
            GetCursorPos(&mouse);
            int mx=mouse.x;
            int my=mouse.y;
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if((mx<700 && mx>450)&&(my<320 && my>250)) ///click stiva
                {
                    camera = 3;///stiva
                    update(camera);
                }
                if((mx<700 && mx>450)&&(my<420 && my>350)) ///click coada
                {
                    camera = 4;///coada
                    update(camera);
                }
                if((mx<700 && mx>450)&&(my<520 && my>450))///click lista
                {
                    camera = 5;
                    update(camera);
                }
                if((mx<700 && mx>450)&&(my<620 && my>550))///click back
                {
                    camera = 1;
                    update(camera);
                }
                if((mx<800 && mx>710)&&(my<520 && my>450))///click lista dubla
                {
                    camera = 6;
                    update(camera);
                }

            }
        }
        break;
    }
    case 3:
    {
       // PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
        int stiva_ = initwindow(1100,700,"STIVA");
        char input[100];
        int i=0;
        stiva();
        inputbox();
        if(s_ultim == NULL)
            creare_stiva(s_prim,s_ultim);
        afisare_stiva(s_prim,s_ultim);
        while(1)
        {
            POINT mouse;
            GetCursorPos(&mouse);
            int mx=mouse.x;
            int my=mouse.y;
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if((mx<1050 && mx>800)&&(my<500 && my>420))///back
                {
                    camera = 2;
                    update(camera);
                }
                if((mx<1050 && mx>800)&&(my<300 && my>220))///push
                {
                 //   PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    animatie_push_stiva();
                }
                if((mx<1050 && mx>800)&&(my<400 && my>320))///pop
                {
                  //  PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    animatie_pop_stiva();
                }
            }
            if(kbhit())
            {
                char c = getch();
                if(c == 13)///enter
                    break;
                if(c == 8 && i > 0)///backspace
                {
                    setcolor(0);
                    outtextxy(925,550,input);
                    setcolor(15);
                    i--;
                    input[i]='\0';
                    outtextxy(925,550,input);
                }
                else if(c >='0' && c <='9' && i<=5)///cifra
                {
                    input[i] = c;
                    i++;
                    input[i] = '\0';
                    outtextxy(925,550,input);
                }
            }
            strcpy(s,input);
        }
        break;
    }
    case 4:
    {
      //  PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
        int coada_ = initwindow(1100,700,"COADA");
        char input[100];
        int i=0;
        coada();
        inputbox();
        if(c_ultim == NULL)
            creare_coada(c_prim,c_ultim);
        afisare_coada(c_prim,c_ultim);
        while(1)
        {
            POINT mouse;
            GetCursorPos(&mouse);
            int mx=mouse.x;
            int my=mouse.y;
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if((mx<1050 && mx>800)&&(my<500 && my>420))///back
                {
                    camera = 2;
                    update(camera);
                }
                if((mx<1050 && mx>800)&&(my<300 && my>220))///push
                {
                  //  PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    animatie_push_coada();
                }
                if((mx<1050 && mx>800)&&(my<400 && my>320))///pop
                {
                  //  PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    animatie_pop_coada();
                }
            }
            if(kbhit())
            {
                char c = getch();
                if(c == 13)///enter
                    break;
                if(c == 8 && i > 0)///backspace
                {
                    setcolor(0);
                    outtextxy(925,550,input);
                    setcolor(15);
                    i--;
                    input[i]='\0';
                    outtextxy(925,550,input);
                }
                else if(c >='0' && c <='9' && i<=5)///cifra
                {
                    input[i] = c;
                    i++;
                    input[i] = '\0';
                    outtextxy(925,550,input);
                }
            }
            strcpy(s,input);
        }
        break;
    }
    case 5:
    {
      //  PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
        int lista_ = initwindow(1100,700,"LISTA");
        char input[100];
        char inputk[100];
        int i=0;
        int i2=0;
        int selected = 0;
        lista();
        inputboxk();
        if(l_ultim == NULL)
            creare_lista(l_prim,l_ultim);
        afisare_lista(l_prim,l_ultim);
        while(1)
        {
            POINT mouse;
            GetCursorPos(&mouse);
            int mx=mouse.x;
            int my=mouse.y;
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if((mx < 250 && mx > 100) && (my<550 && my>500))///select input
                {
                 //   PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    selected = 1;
                }
                if((mx < 250 && mx > 100) && (my<650 && my>600))///select k
                {
                  //  PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    selected = 2;
                }
                strcpy(s,input);
                k = atoi(inputk);
                delay(10);
                if((mx<1050 && mx>800)&&(my<700 && my>620))///back
                {
                    camera = 2;
                    update(camera);
                }

                if((mx<1050 && mx>800)&&(my<300 && my>220))///insereaza k
                {
                 //   PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    animatie_insereaza_k();
                }
                if((mx<1050 && mx>800)&&(my<400 && my>320))///elimina k
                {
                 //   PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    animatie_elimina_k();
                }
                if((mx<790 && mx>500)&&(my<500 && my>420))///insereaza primul
                {
                //    PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    animatie_insereaza_primul();
                }
                if((mx<1050 && mx>800)&&(my<500 && my>420))///elimina primul
                {
                //    PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    animatie_elimina_primul();
                }
                if((mx<790 && mx>500)&&(my<600 && my>520))///insereaza ultimul
                {
                  //  PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    animatie_insereaza_ultimul();
                }
                if((mx<1050 && mx>800)&&(my<600 && my>520))///elimina ultimul
                {
                    //PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    animatie_elimina_ultimul();
                    selected = 0;
                    /*
                    fflush(stdin);
                    while(kbhit())
                        getch();
                    strcpy(input,"");
                    strcpy(inputk,"");
                    i=0;
                    i2=0;*/
                }

            }
            if(kbhit())
            {
                if(selected == 1)
                {
                    char c = getch();
                    if(c == 13)///enter
                        break;
                    if(c == 8 && i > 0)///backspace
                    {
                        setcolor(0);
                        outtextxy(175,525,input);
                        setcolor(15);
                        i--;
                        input[i]='\0';
                        outtextxy(175,525,input);
                    }
                    else if(c >='0' && c <='9' && i<=5)///cifra
                    {
                        input[i] = c;
                        i++;
                        input[i] = '\0';
                        outtextxy(175,525,input);
                    }
                }
                else if(selected == 2)
                {
                    char c = getch();
                    if(c == 13)///enter
                        break;
                    if(c == 8 && i2 > 0)///backspace
                    {
                        setcolor(0);
                        outtextxy(175,625,inputk);
                        setcolor(15);
                        i2--;
                        inputk[i2]='\0';
                        outtextxy(175,625,inputk);
                    }
                    else if(c >='0' && c <='9' && i2<=1)///cifra
                    {
                        inputk[i2] = c;
                        i2++;
                        inputk[i2] = '\0';
                        outtextxy(175,625,inputk);
                    }
                }
            }
        }
        break;
    }
    case 6:
    {
       // PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
        int listad_ = initwindow(1100,700,"LISTA DUBLA");
        char input[100];
        char inputk[100];
        int i=0;
        int i2=0;
        int selected = 0;
        listad();
        inputboxk();
        if(d_ultim == NULL)
            creare_lista_d(d_prim,d_ultim);
        afisare_lista_d(d_prim,d_ultim);
        while(1)
        {
            POINT mouse;
            GetCursorPos(&mouse);
            int mx=mouse.x;
            int my=mouse.y;
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if((mx < 250 && mx > 100) && (my<550 && my>500))///select input
                {
                  //  PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    selected = 1;
                }
                if((mx < 250 && mx > 100) && (my<650 && my>600))///select k
                {
                   // PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    selected = 2;
                }
                strcpy(s,input);
                k = atoi(inputk);
                delay(10);
                if((mx<1050 && mx>800)&&(my<700 && my>620))///back
                {
                    camera = 2;
                    update(camera);
                }

                if((mx<1050 && mx>800)&&(my<300 && my>220))///insereaza k
                {
                  //  PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    animatie_insereaza_k_d();
                }
                if((mx<1050 && mx>800)&&(my<400 && my>320))///elimina k
                {
                   // PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    animatie_elimina_k_d();
                }
                if((mx<790 && mx>500)&&(my<500 && my>420))///insereaza primul
                {
                   // PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    animatie_insereaza_primul_d();
                }
                if((mx<1050 && mx>800)&&(my<500 && my>420))///elimina primul
                {
                   // PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    animatie_elimina_primul_d();
                }
                if((mx<790 && mx>500)&&(my<600 && my>520))///insereaza ultimul
                {
                  //  PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    animatie_insereaza_ultimul_d();
                }
                if((mx<1050 && mx>800)&&(my<600 && my>520))///elimina ultimul
                {
                   // PlaySound(TEXT("button.wav"),NULL,SND_ASYNC);
                    animatie_elimina_ultimul_d();
                    selected = 0;
                    /*
                    fflush(stdin);
                    while(kbhit())
                        getch();
                    strcpy(input,"");
                    strcpy(inputk,"");
                    i=0;
                    i2=0;*/
                }

            }
            if(kbhit())
            {
                if(selected == 1)
                {
                    char c = getch();
                    if(c == 13)///enter
                        break;
                    if(c == 8 && i > 0)///backspace
                    {
                        setcolor(0);
                        outtextxy(175,525,input);
                        setcolor(15);
                        i--;
                        input[i]='\0';
                        outtextxy(175,525,input);
                    }
                    else if(c >='0' && c <='9' && i<=5)///cifra
                    {
                        input[i] = c;
                        i++;
                        input[i] = '\0';
                        outtextxy(175,525,input);
                    }
                }
                else if(selected == 2)
                {
                    char c = getch();
                    if(c == 13)///enter
                        break;
                    if(c == 8 && i2 > 0)///backspace
                    {
                        setcolor(0);
                        outtextxy(175,625,inputk);
                        setcolor(15);
                        i2--;
                        inputk[i2]='\0';
                        outtextxy(175,625,inputk);
                    }
                    else if(c >='0' && c <='9' && i2<=1)///cifra
                    {
                        inputk[i2] = c;
                        i2++;
                        inputk[i2] = '\0';
                        outtextxy(175,625,inputk);
                    }
                }
            }
        }
        break;
    }
    }
}
int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    camera = 1;
    update(camera);

    getch();
    closegraph();
    return 0;
}
