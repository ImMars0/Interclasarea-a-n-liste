//interclasarea a n liste ordonate


//biblioteci
#include <iostream> //biblioteca pentru citire si afisare
#include <math.h> //biblioteca pentru functii matematice
#include <conio.h> //biblioteca pentru functii de consola

using namespace std;

// Structura pentru lista simplu inlantuita
struct numar {
    int v;       // Valoarea din lista
    numar *urm;  // Legătura către următorul element din lista
};

// Funcție pentru crearea listei
numar* creare_lista() {
    numar *cap, *u, *c; // cap: capătul listei, u: ultimul element, c: elementul curent
    int x, n; // x: valoarea elementului curent, n: numărul de elemente din lista
    
    cout << "Creare lista!" << endl;
    
    // Creare capatul listei
    cout << "Valoare cap lista x = "; cin >> x;
    cap = new numar; // Alocare memorie pentru cap
    cap->v = x;      // Atribuire valoare pentru cap
    cap->urm = nullptr; // Inițializare legatura ca nullptr
    u = cap; // Ultimul element este capătul la inceput
    
    // Citire număr de elemente din listă
    cout << "Numarul de elemente care se adauga in lista (n) = "; cin >> n;
    
    // Adăugare elemente în listă
    for (int i = 1; i <= n; i++) {
        cout << "Valoare de adaugat in lista x = "; cin >> x;// Citire valoare element curent
        c = new numar; // Alocare memorie pentru noul element
        c->v = x;      // Atribuire valoare
        c->urm = NULL; // Inirializare legatura ca NULL
        u->urm = c; // Legăm ultimul element cu noul element
        u = c; // Noul element devine ultimul element
    }
    return cap; // Returnează capătul listei
}

// Functie pentru parcurgerea si afisarea listei
void parcurgere_lista(numar* cap) {
    numar *p = cap; // Initializare cu capatul listei
    cout << "Elementele listei sunt: ";
    while (p != nullptr) { // Cât timp mai exista elemente
        cout << p->v << " "; // Afisam valoarea elementului curent
        p = p->urm; // Trecem la urmatorul element
    }
    cout << endl;
}

// Functie pentru ordonarea listei in ordine crescatoare
void ordonare_lista(numar* cap) {
    if (cap == nullptr || cap->urm == nullptr)//verificam daca lista este goala sau contine un singur element
     {
        return; // Lista goala sau cu un singur element - deja ordonata
    }
    
    bool swapped;//variabila pentru a verifica daca s-a facut o interschimbare in bucla
    do {
        swapped = false;//initializare variabila cu fals
        numar* p = cap;//initializare variabila cu capatul listei
        while (p->urm != nullptr)//parcurgem lista
         {
            if (p->v > p->urm->v) //verificam daca elementul curent este mai mare decat urmatorul
            {//interschimbare valori
                int temp = p->v;// variabila temporara pentru a pastra valoarea elementului curent
                p->v = p->urm->v;//elementul curent ia valoarea urmatorului
                p->urm->v = temp;//urmatorului element ia valoarea elementului curent
                swapped = true;//deoarece s-a facut o interschimbare, variabila swapped devine true
            }
            p = p->urm;//trecem la urmatorul element
        }
    } while (swapped);//repetam bucla cat timp s-a facut o interschimbare
}

// Functie pentru interclasarea a doua liste ordonate
numar* interclasare_doua_liste(numar* lista1, numar* lista2) {
    numar* rezultat = nullptr; // Capul noii liste interclasate
    numar** p = &rezultat; // Pointer catre ultimul element al listei interclasate

    // Parcurgem ambele liste pana cand cel putin una dintre ele devine goala
    while (lista1 != nullptr && lista2 != nullptr) {
        if (lista1->v <= lista2->v) { // Alegem elementul mai mic
            *p = lista1; // Adaugam elementul din prima lista
            lista1 = lista1->urm; // Avansam in prima lista
        } else {
            *p = lista2; // Adaugam elementul din a doua lista
            lista2 = lista2->urm; // Avansam in a doua lista
        }
        p = &((*p)->urm); // Actualizam pointerul pentru urmatorul element
    }

    // Adaugam restul elementelor ramase (daca exista)
    if (lista1 != nullptr) {
        *p = lista1;// Adaugam restul elementelor din prima lista
    } else {
        *p = lista2;// Adaugam restul elementelor din a doua lista
    }

    return rezultat; // Returnam capul listei interclasate
}


// Functie pentru interclasarea a n liste ordonate
numar* interclasare_n_liste(numar* liste[], int n) {
    if (n == 0) {
        return nullptr; // Daca nu exista liste, returnam nullptr
    }
    // Interclasam listele doua cate doua
    while (n > 1) {
        int i = 0, j = n - 1; // Indicii pentru prima si ultima lista
        while (i < j) // Iteram pana cand ajungem la mijlocul listelor
        {
            liste[i] = interclasare_doua_liste(liste[i], liste[j]); // Interclasam doua liste
            i++; // Avansam la urmatoarea pereche
            j--; // Reducem numarul de liste ramase
        }
        n = (n + 1) / 2; // Reducem dimensiunea problemei
    }
    return liste[0]; // Returnam lista finala interclasata
}

// Program principal
int main() {
    int n; // Numarul de liste
    cout << "Numarul de liste: ";
    cin >> n;

    numar* liste[n]; // Array pentru stocarea capetelor listelor

    // Cream fiecare lista
    for (int i = 0; i < n; i++) {
        cout << "Lista " << i + 1 << ":" << endl;
        liste[i] = creare_lista(); // Cream o lista
        ordonare_lista(liste[i]); // Ordonam lista
        cout << "Lista ordonata: ";
        parcurgere_lista(liste[i]); // Afisam lista ordonata
    }

    // Interclasam toate listele
    numar* lista_finala = interclasare_n_liste(liste, n);
    cout << "Lista finala interclasata: ";
    parcurgere_lista(lista_finala); // Afisam lista finala interclasata

    return 0;
}