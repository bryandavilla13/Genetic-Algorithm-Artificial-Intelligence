#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

void scrambleArray(int arr[], int size) {
    random_device rd;
    mt19937 gen(rd());
    
    for (int i = size - 1; i > 0; i--) {
        uniform_int_distribution<int> dist(0, i);
        int j = dist(gen);
        swap(arr[i], arr[j]);
    }
}

void scrambleIdPerawat(int idPerawat[]) {
    // bangsal ketiga
    int dummy3[47];
    for (int i = 0; i < 47; i++) {
        dummy3[i] = idPerawat[i+116];
    }
    scrambleArray(dummy3, 47);
    for (int i = 0; i < 47; i++) {
        idPerawat[i+116] = dummy3[i];
    }

    // bangsal kelima
    int dummy5[33];
    for (int i = 0; i < 33; i++) {
        dummy5[i] = idPerawat[i+179];
    }
    scrambleArray(dummy5, 33);
    for (int i = 0; i < 33; i++) {
        idPerawat[i+179] = dummy5[i];
    }

    // bangsal ketujuh
    int dummy7[5];
    for (int i = 0; i < 5; i++) {
        dummy7[i] = idPerawat[i+222];
    }
    scrambleArray(dummy7, 5);
    for (int i = 0; i < 5; i++) {
        idPerawat[i+222] = dummy7[i];
    }

    // bangsal 1,2,4,6,8
    int dummy[175];
    int index = 0;
    for (int i = 0; i < 260; i++) {
        if (i < 116) {
            dummy[index] = idPerawat[i];
            index++;
        }
        else if (i >= 163 && i < 179) {
            dummy[index] = idPerawat[i];
            index++;
        }
        else if (i >= 212 && i < 222) {
            dummy[index] = idPerawat[i];
            index++;
        }
        else if (i >= 227) {
            dummy[index] = idPerawat[i];
            index++;
        }
    }
    index = 0;
    scrambleArray(dummy, 175);
    for (int i = 0; i < 260; i++) {
        if (i < 116) {
            idPerawat[i] = dummy[index];
            index++;
        }
        else if ( i < 179 && i >= 163) {
            idPerawat[i] = dummy[index];
            index++;
        }
        else if ( i < 222 && i >= 212) {
            idPerawat[i] = dummy[index];
            index++;
        }
        else if ( i < 260 && i >= 227) {
            idPerawat[i] = dummy[index];
            index++;
        }
    }
}

class Hari {
    public:
    int idBangsal[260];
    int idPerawat[260];
    int shift[260];
    int bangsal[260];
    void generate(){
        for(int i = 0; i < 260; i++){
            if (i < 94){
                idBangsal[i] = 1;
                idPerawat[i] = i;
                shift[i] = (i+1)%3+1;
                if (i < 72) {
                    bangsal[i] = i%6+1;
                }
                else {
                    bangsal[i] = -1;
                }
            }
            else if (i < 116) {
                idBangsal[i] = 2;
                idPerawat[i] = i;
                shift[i] = (i-93)%3+1;   
                if (i < 112) {
                    bangsal[i] = i%3+1;
                }
                else {
                    bangsal[i] = -1;
                }
            }
            else if (i < 163) {
                idBangsal[i] = 3;
                idPerawat[i] = i - 116;
                shift[i] = (i-115)%3+1;
                if (i < 152) {
                    bangsal[i] = i%3+1;
                }
                else {
                    bangsal[i] = -1;
                }
            }
            else if (i < 179) {
                idBangsal[i] = 4;
                idPerawat[i] = i - 47;
                shift[i] = (i-162)%3+1;
                if (i < 175) {
                    bangsal[i] = 1;
                }
                else {
                    bangsal[i] = -1;
                }
            }
            else if (i < 212) {
                idBangsal[i] = 5;
                idPerawat[i] = i - 179;
                shift[i] = (i-178)%3+1;
                if (i < 203) {
                    bangsal[i] = 1;
                }
                else {
                    bangsal[i] = -1;
                }
            }
            else if (i < 222) {
                idBangsal[i] = 6;
                idPerawat[i] = i - 80;
                shift[i] = (i-211)%2+1;
                if (i < 220) {
                    bangsal[i] = 1;
                }
                else {
                    bangsal[i] = -1;
                }
            }
            else if (i < 227) {
                idBangsal[i] = 7;
                idPerawat[i] = i - 222;
                shift[i] = (i-216)%2+1;
                if (i < 226) {
                    bangsal[i] = 1;
                }
                else {
                    bangsal[i] = -1;
                }
            }
            else if (i < 260) {
                idBangsal[i] = 8;
                idPerawat[i] = i - 85;
                shift[i] = (i-226)%3+1;
                bangsal[i] = 1;
                if (i < 251) {
                    bangsal[i] = 1;
                }
                else {
                    bangsal[i] = -1;
                }
            }
        }
        scrambleIdPerawat(idPerawat);
    }
};

class kromosom {
    public:
    Hari jadwalHari[7];
    double fitness;
    void generate(){
        for (int i = 0; i < 7; i++) {
            jadwalHari[i].generate();
        };
        fitness = calcFitness();
    }

    void print() {
            cout << "  senin             "
                 << "  selasa            " 
                 << "  rabu              " 
                 << "  kamis             " 
                 << "  jumat             "     
                 << "  sabtu             "       
                 << "  minggu            " << endl;
        for (int i = 0; i < 260; i++) {
            cout << setw(3) << jadwalHari[0].idBangsal[i] << "-" 
                 << setw(3) << jadwalHari[0].idPerawat[i] << "-" 
                 << setw(3) << jadwalHari[0].shift[i] << "-" 
                 << setw(3) << jadwalHari[0].bangsal[i] << "     ";
            cout << setw(3) << jadwalHari[1].idBangsal[i] << "-" 
                 << setw(3) << jadwalHari[1].idPerawat[i] << "-" 
                 << setw(3) << jadwalHari[1].shift[i] << "-" 
                 << setw(3) << jadwalHari[1].bangsal[i] << "     ";
            cout << setw(3) << jadwalHari[2].idBangsal[i] << "-" 
                 << setw(3) << jadwalHari[2].idPerawat[i] << "-" 
                 << setw(3) << jadwalHari[2].shift[i] << "-" 
                 << setw(3) << jadwalHari[2].bangsal[i] << "     ";
            cout << setw(3) << jadwalHari[3].idBangsal[i] << "-" 
                 << setw(3) << jadwalHari[3].idPerawat[i] << "-" 
                 << setw(3) << jadwalHari[3].shift[i] << "-" 
                 << setw(3) << jadwalHari[3].bangsal[i] << "     ";
            cout << setw(3) << jadwalHari[4].idBangsal[i] << "-" 
                 << setw(3) << jadwalHari[4].idPerawat[i] << "-" 
                 << setw(3) << jadwalHari[4].shift[i] << "-" 
                 << setw(3) << jadwalHari[4].bangsal[i] << "     ";
            cout << setw(3) << jadwalHari[5].idBangsal[i] << "-" 
                 << setw(3) << jadwalHari[5].idPerawat[i] << "-" 
                 << setw(3) << jadwalHari[5].shift[i] << "-" 
                 << setw(3) << jadwalHari[5].bangsal[i] << "     ";
            cout << setw(3) << jadwalHari[6].idBangsal[i] << "-" 
                 << setw(3) << jadwalHari[6].idPerawat[i] << "-" 
                 << setw(3) << jadwalHari[6].shift[i] << "-" 
                 << setw(3) << jadwalHari[6].bangsal[i] << endl;
        }
        cout << "  fitness: " << fitness << endl;
    }

    double calcFitness() {
        int temp = 0;
        int temp2 = 0;
        int liburCount = 0;
        int duaKaliShift = 0;
        int lebihDuaLibur = 0;
        int berpengalaman = 0;
        int bentrokanShift = 0;
        float bobotDuaKaliShift = 0.001;
        float bobotLebihDuaLibur = 0.003;
        float bobotBerpengalaman = 0.005;
        float bobotBentrokanShift = 0.001;
        for (int i = 0; i <6 ; i++) {
            for (int j = 0; j < 260; j++) {
                if (jadwalHari[i].shift[j] == 3) {
                    temp = jadwalHari[i].idPerawat[j];
                    for (int k = 0; k < 260; k++) {
                        if (jadwalHari[i+1].idPerawat[k] == temp && jadwalHari[i+1].shift[k] == 1) {
                            duaKaliShift++;
                        }
                    }
                }
                if (jadwalHari[i].shift[j] == -1) {
                    temp2 = jadwalHari[i].idPerawat[j];
                    liburCount = 0;
                    for (int k = 0; k < 260; k++) {
                        if (jadwalHari[0].idPerawat[k] == temp2 && jadwalHari[0].shift[k] == -1) {
                            liburCount++;
                        }
                        if (jadwalHari[1].idPerawat[k] == temp2 && jadwalHari[1].shift[k] == -1) {
                            liburCount++;
                        }
                        if (jadwalHari[2].idPerawat[k] == temp2 && jadwalHari[2].shift[k] == -1) {
                            liburCount++;
                        }
                        if (jadwalHari[3].idPerawat[k] == temp2 && jadwalHari[3].shift[k] == -1) {
                            liburCount++;
                        }
                        if (jadwalHari[4].idPerawat[k] == temp2 && jadwalHari[4].shift[k] == -1) {
                            liburCount++;
                        }
                        if (jadwalHari[5].idPerawat[k] == temp2 && jadwalHari[5].shift[k] == -1) {
                            liburCount++;
                        }
                        if (jadwalHari[6].idPerawat[k] == temp2 && jadwalHari[6].shift[k] == -1) {
                            liburCount++;
                        }
                    }
                    if (liburCount >= 3)
                    {
                        lebihDuaLibur++;
                    }
                }
            }
            int a111, a112, a113, a114, a115, a116 = 0;
            int a121, a122, a123, a124, a125, a126 = 0;
            int a131, a132, a133, a134, a135, a136 = 0;

            int a211, a212, a213 = 0;
            int a221, a222, a223 = 0;
            int a231, a232, a233 = 0;

            int a311, a312, a313 = 0;
            int a321, a322, a323 = 0;
            int a331, a332, a333 = 0;

            int a411 = 0;
            int a421 = 0;
            int a431 = 0;

            int a511 = 0;
            int a521 = 0;
            int a531 = 0;

            int a611, a612 = 0;
            int a621, a622 = 0;

            int a711 = 0;
            int a721 = 0;

            int a811 = 0;
            int a821 = 0;
            int a831 = 0;

            for (int j = 0; j < 260; j++) {
                if (jadwalHari[i].idPerawat[j] % 4 == 0) {
                    if (jadwalHari[i].idBangsal[j] == 1)
                    {
                        if (jadwalHari[i].shift[j] == 1)
                        {
                            if (jadwalHari[i].bangsal[j] == 1)
                            {
                                a111++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 2)
                            {
                                a112++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 3)
                            {
                                a113++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 4)
                            {
                                a114++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 5)
                            {
                                a115++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 6)
                            {
                                a116++;
                            }
                        }
                        else if (jadwalHari[i].shift[j] == 2)
                        {
                            if (jadwalHari[i].bangsal[j] == 1)
                            {
                                a121++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 2)
                            {
                                a122++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 3)
                            {
                                a123++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 4)
                            {
                                a124++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 5)
                            {
                                a125++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 6)
                            {
                                a126++;
                            }
                        }
                        else if (jadwalHari[i].shift[j] == 3)
                        {
                            if (jadwalHari[i].bangsal[j] == 1)
                            {
                                a131++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 2)
                            {
                                a132++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 3)
                            {
                                a133++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 4)
                            {
                                a134++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 5)
                            {
                                a135++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 6)
                            {
                                a136++;
                            }
                        }
                    }
                    else if (jadwalHari[i].idBangsal[j] == 2)
                    {
                        if (jadwalHari[i].shift[j] == 1)
                        {
                            if (jadwalHari[i].bangsal[j] == 1)
                            {
                                a211++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 2)
                            {
                                a212++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 3)
                            {
                                a213++;
                            }
                        }
                        else if (jadwalHari[i].shift[j] == 2)
                        {
                            if (jadwalHari[i].bangsal[j] == 1)
                            {
                                a221++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 2)
                            {
                                a222++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 3)
                            {
                                a223++;
                            }
                        }
                        else if (jadwalHari[i].shift[j] == 3)
                        {
                            if (jadwalHari[i].bangsal[j] == 1)
                            {
                                a231++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 2)
                            {
                                a232++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 3)
                            {
                                a233++;
                            }
                        }
                        
                    }
                    else if (jadwalHari[i].idBangsal[j] == 3)
                    {
                        if (jadwalHari[i].shift[j] == 1)
                        {
                            if (jadwalHari[i].bangsal[j] == 1)
                            {
                                a311++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 2)
                            {
                                a312++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 3)
                            {
                                a313++;
                            }
                        }
                        else if (jadwalHari[i].shift[j] == 2)
                        {
                            if (jadwalHari[i].bangsal[j] == 1)
                            {
                                a321++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 2)
                            {
                                a322++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 3)
                            {
                                a323++;
                            }
                        }
                        else if (jadwalHari[i].shift[j] == 3)
                        {
                            if (jadwalHari[i].bangsal[j] == 1)
                            {
                                a331++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 2)
                            {
                                a332++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 3)
                            {
                                a333++;
                            }
                        }
                    }
                    else if (jadwalHari[i].idBangsal[j] == 4)
                    {
                        if (jadwalHari[i].shift[j] == 1)
                        {
                            a411++;
                        }
                        else if (jadwalHari[i].shift[j] == 2)
                        {
                            a421++;
                        }
                        else if (jadwalHari[i].shift[j] == 3)
                        {
                            a431++;
                        }
                    }
                    else if (jadwalHari[i].idBangsal[j] == 5)
                    {
                        if (jadwalHari[i].shift[j] == 1)
                        {
                            a511++;
                        }
                        else if (jadwalHari[i].shift[j] == 2)
                        {
                            a521++;
                        }
                        else if (jadwalHari[i].shift[j] == 3)
                        {
                            a531++;
                        }
                    }
                    else if (jadwalHari[i].idBangsal[j] == 6)
                    {
                        if (jadwalHari[i].shift[j] == 1)
                        {
                            if (jadwalHari[i].bangsal[j] == 1)
                            {
                                a611++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 2)
                            {
                                a612++;
                            }
                        }
                        else if (jadwalHari[i].shift[j] == 2)
                        {
                            if (jadwalHari[i].bangsal[j] == 1)
                            {
                                a621++;
                            }
                            else if (jadwalHari[i].bangsal[j] == 2)
                            {
                                a622++;
                            }
                        }
                    }
                    else if (jadwalHari[i].idBangsal[j] == 7)
                    {
                        if (jadwalHari[i].shift[j] == 1)
                        {
                            a711++;
                        }
                        else if (jadwalHari[i].shift[j] == 2)
                        {
                            a721++;
                        }
                    }
                    else if (jadwalHari[i].idBangsal[j] == 8)
                    {
                        if (jadwalHari[i].shift[j] == 1)
                        {
                            a811++;
                        }
                        else if (jadwalHari[i].shift[j] == 2)
                        {
                            a821++;
                        }
                        else if (jadwalHari[i].shift[j] == 3)
                        {
                            a831++;
                        }
                    }
                }
                if (a111 != 0)
                {
                    berpengalaman++;
                }
                if (a112 != 0)
                {
                    berpengalaman++;
                }
                if (a113 != 0)
                {
                    berpengalaman++;
                }
                if (a114 != 0)
                {
                    berpengalaman++;
                }
                if (a115 != 0)
                {
                    berpengalaman++;
                }
                if (a116 != 0)
                {
                    berpengalaman++;
                }
                if (a121 != 0)
                {
                    berpengalaman++;
                }
                if (a122 != 0)
                {
                    berpengalaman++;
                }
                if (a123 != 0)
                {
                    berpengalaman++;
                }
                if (a124 != 0)
                {
                    berpengalaman++;
                }
                if (a125 != 0)
                {
                    berpengalaman++;
                }
                if (a126 != 0)
                {
                    berpengalaman++;
                }
                if (a131 != 0)
                {
                    berpengalaman++;
                }
                if (a132 != 0)
                {
                    berpengalaman++;
                }
                if (a133 != 0)
                {
                    berpengalaman++;
                }
                if (a134 != 0)
                {
                    berpengalaman++;
                }
                if (a135 != 0)
                {
                    berpengalaman++;
                }
                if (a136 != 0)
                {
                    berpengalaman++;
                }
                if (a211 != 0)
                {
                    berpengalaman++;
                }
                if (a212 != 0)
                {
                    berpengalaman++;
                }
                if (a213 != 0)
                {
                    berpengalaman++;
                }
                if (a221 != 0)
                {
                    berpengalaman++;
                }
                if (a222 != 0)
                {
                    berpengalaman++;
                }
                if (a223 != 0)
                {
                    berpengalaman++;
                }
                if (a231 != 0)
                {
                    berpengalaman++;
                }
                if (a232 != 0)
                {
                    berpengalaman++;
                }
                if (a233 != 0)
                {
                    berpengalaman++;
                }
                if (a311 != 0)
                {
                    berpengalaman++;
                }
                if (a312 != 0)
                {
                    berpengalaman++;
                }
                if (a313 != 0)
                {
                    berpengalaman++;
                }
                if (a321 != 0)
                {
                    berpengalaman++;
                }
                if (a322 != 0)
                {
                    berpengalaman++;
                }
                if (a323 != 0)
                {
                    berpengalaman++;
                }
                if (a331 != 0)
                {
                    berpengalaman++;
                }
                if (a332 != 0)
                {
                    berpengalaman++;
                }
                if (a333 != 0)
                {
                    berpengalaman++;
                }
                if (a411 != 0)
                {
                    berpengalaman++;
                }
                if (a421 != 0)
                {
                    berpengalaman++;
                }
                if (a431 != 0)
                {
                    berpengalaman++;
                }
                if (a511 != 0)
                {
                    berpengalaman++;
                }
                if (a521 != 0)
                {
                    berpengalaman++;
                }
                if (a531 != 0)
                {
                    berpengalaman++;
                }
                if (a611 != 0)
                {
                    berpengalaman++;
                }
                if (a612 != 0)
                {
                    berpengalaman++;
                }
                if (a621 != 0)
                {
                    berpengalaman++;
                }
                if (a622 != 0)
                {
                    berpengalaman++;
                }
                if (a711 != 0)
                {
                    berpengalaman++;
                }
                if (a721 != 0)
                {
                    berpengalaman++;
                }
                if (a811 != 0)
                {
                    berpengalaman++;
                }
                if (a821 != 0)
                {
                    berpengalaman++;
                }
                if (a831 != 0)
                {
                    berpengalaman++;
                }
            }
        }

        return (1.f/(1+((duaKaliShift*bobotDuaKaliShift)+(lebihDuaLibur*bobotLebihDuaLibur)+(berpengalaman*bobotBerpengalaman)+(bentrokanShift*bobotBentrokanShift))));
    }
};

kromosom crossover(kromosom p1, kromosom p2) {
    kromosom hasil;
    int random;
    double random_number;

    for (int i = 0; i < 7; i++)
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<double> dis(0.0, 1.0);
        random_number = dis(gen);
        random = random_number < 0.5 ? 0 : 1;

        if (random == 0)
        {
            for (int j = 0; j < 260; j++)
            {
                hasil.jadwalHari[i].idBangsal[j] = p1.jadwalHari[i].idBangsal[j];
                hasil.jadwalHari[i].idPerawat[j] = p1.jadwalHari[i].idPerawat[j];
                hasil.jadwalHari[i].shift[j] = p1.jadwalHari[i].shift[j];
                hasil.jadwalHari[i].bangsal[j] = p1.jadwalHari[i].bangsal[j];
            }
        }
        else
        {
            for (int j = 0; j < 260; j++)
            {
                hasil.jadwalHari[i].idBangsal[j] = p2.jadwalHari[i].idBangsal[j];
                hasil.jadwalHari[i].idPerawat[j] = p2.jadwalHari[i].idPerawat[j];
                hasil.jadwalHari[i].shift[j] = p2.jadwalHari[i].shift[j];
                hasil.jadwalHari[i].bangsal[j] = p2.jadwalHari[i].bangsal[j];
            }
        }
    }
    hasil.fitness = hasil.calcFitness();
    return hasil;
};

int main()
{
    int populasi_awal = 50;
    float total_fitness = 0.f;
    float mutation_rate = 2/100;
    int jumlah_iterasi = 500;
    int best_index = -1;
    int change_index = -1;

    kromosom populasi[populasi_awal];
    for (int j = 0; j < populasi_awal; j++)
    {
        populasi[j] = kromosom();
        populasi[j].generate();
    }

    for (int i = 1; i <= jumlah_iterasi ; i++)
    {
        // Roulette wheel selection
        double random_number1 = (double)rand() / RAND_MAX;
        double random_number2 = (double)rand() / RAND_MAX;
        double sum_fitness = 0;
        int selected_index1 = -1;
        int selected_index2 = -1;
        total_fitness = 0;

        for (int j = 0; j < populasi_awal; j++) {
            total_fitness += populasi[j].fitness;
        }

        for (int j = 0; j < populasi_awal; j++) {
            sum_fitness += populasi[j].fitness / total_fitness;
            if (selected_index1 == -1 && sum_fitness >= random_number1) {
                selected_index1 = j;
            }
            if (selected_index2 == -1 && sum_fitness >= random_number2) {
                selected_index2 = j;
            }
        }

        kromosom selected_kromosom1 = populasi[selected_index1];
        kromosom selected_kromosom2 = populasi[selected_index2];

        kromosom offspring = crossover(selected_kromosom1, selected_kromosom2);

        double random_number3 = (double)rand() / RAND_MAX;

        if (random_number3 < mutation_rate) {
            if (i % 3 == 0)
            {
                offspring.jadwalHari[0].generate();
                offspring.jadwalHari[3].generate();
                offspring.jadwalHari[6].generate();
            }
            else if (i % 3 == 1)
            {
                offspring.jadwalHari[1].generate();
                offspring.jadwalHari[4].generate();
            }
            else if (i % 3 == 2)
            {
                offspring.jadwalHari[2].generate();
                offspring.jadwalHari[5].generate();
            }
        }

        float min_fitness = 999999.f;
        change_index = -1;
        float max_fitness = -1.f;
        
        for (int j = 0; j < populasi_awal; j++) {
            if (populasi[j].fitness < min_fitness) {
                min_fitness = populasi[j].fitness;
                change_index = j;
            }
            if (populasi[j].fitness > max_fitness)
            {
                max_fitness = populasi[j].fitness;
                best_index = j;
            }
        }

        populasi[change_index] = offspring;

        total_fitness = 0.f;

        for (int j = 0; j < populasi_awal; j++) {
            total_fitness += populasi[j].fitness;
        }

        float rata_rata_fitness = total_fitness / populasi_awal;
        float accuracy = (rata_rata_fitness + max_fitness)/2;

        cout << "Iterasi ke-" << setw(3) << i << " Akurasi: " << accuracy << " Max: " << max_fitness << " Rata-Rata: " << rata_rata_fitness << endl;
    }
    cout << "kromosom terbaik adalah " << endl;
    populasi[best_index].print();
}