// dla gcc należy dodać do opcji kompilacji: -mrdrnd
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#ifdef _MSC_VER
    #include <immintrin.h>
#else
    #include <x86intrin.h>
    #include <cpuid.h>
#endif

void PokerTest(uint32_t* tab,uint32_t n,uint32_t bits,uint32_t shift);

// tablice rozkładu (chi^2)^(-1) dla alfa=0.00005 i ilości bitów od 1 do 16 (potrzebne do testu pokerowego)
double chi2d[16]={0.0000, 0.0033, 0.2446, 2.1649, 9.2011, 28.3720, 74.1655, 176.3910, 395.9294,
		856.3608, 1807.4305, 3752.2915, 7702.4312, 15688.1539, 31780.4343, 64135.8807};
double chi2u[16]={16.4481, 22.5547, 31.5124, 46.1678, 71.3986, 116.3546, 198.6229, 352.4279, 644.9045,
		1208.4807, 2305.4147, 4456.5556, 8698.4169, 17096.6945, 33772.4144, 66952.9681};

// funkcja odczytuje i zwraca licznik wykonanych cykli procesora
static inline unsigned long long rdtsc() {
    unsigned dummy;
    return __rdtscp(&dummy);
}

// Inicjuje MT[] dla generatora Mersenne Twister
uint32_t MT[624];
uint32_t mti = 0;
void InicjujMT(uint32_t x0){
	uint64_t x;
	uint32_t i=0;
	MT[0] = x0;
	do{
		x = MT[i];
		x = (23023 * x) & 0xffffffffull;
		i++;
		x = (    3 * x) & 0xffffffffull;
		MT[i] = x;
	}while(i < 623);
}
// Generator liczb losowych Mersenne Twister
uint32_t MTrand(){
  const uint32_t MA[] = {0,0x9908b0df};
  uint32_t y,i1,i397;
  i1      = mti +   1; if(  i1 > 623) i1 = 0;
  i397    = mti + 397; if(i397 > 623) i397 -= 624;
  y       = (MT[mti] & 0x80000000) | (MT[i1] & 0x7fffffff);
  MT[mti] = MT[i397] ^ (y >> 1) ^ MA[y & 1];
  y       = MT[mti];
  y       ^=  y >> 11;
  y       ^= (y <<  7) & 0x9d2c5680;
  y       ^= (y << 15) & 0xefc60000;
  y       ^=  y >> 18;
  mti     = i1;
  return y;
}

int main(){
    // liczby do przechowywania cykli procesora
    unsigned long long sr1,sr2;
    // liczby do przechowywania wartości minimalnej i maksymalnej z tablicy
	unsigned cmin=0xFFFFFFFF,cmax=0;
	// inicjowanie generatorów losowych
	srand(time(0));
	InicjujMT(time(0));
	// rozmiar tablicy i tworzenie tablicy
	unsigned n=64*1024*1024;
	unsigned *tabl;
	long index;
	tabl=(unsigned*)malloc(n*sizeof(unsigned));

	if(tabl==0)
		printf("Brak pamieci\n");
	else{
		printf("TABLICA ZAJMUJE %lu MB pamieci\n",(n*sizeof(unsigned))/(1024*1024));
        // sprawdzamy zwykły generator liczb losowych
        unsigned coileb,maxbit=0;
        for(unsigned temp=RAND_MAX;temp!=0;temp>>=1) maxbit++;
        printf("\nRand_max: %u, bity %u",RAND_MAX,maxbit);
        cmin=0xFFFFFFFF;cmax=0;
        // losujemy tablicê
		sr1=rdtsc();
        for(int i=0;i<n;i++)
		    tabl[i]=rand();
		sr2=rdtsc();
        // znajdujemy maksimum i minimum tablicy
        for(int i=0;i<n;i++){
            if(tabl[i]<cmin)
                cmin=tabl[i];
            else if(tabl[i]>cmax)
                cmax=tabl[i];
        }
        printf("\nTESTOWANIE RAND: min=%u, max=%u\n",cmin,cmax);
        printf("Czas wykonania 1 rand %llu cykli\n",(sr2-sr1)/n);
        // wykonanujemy testu pokerowy
        coileb=3;
		for(int i=0;i<=maxbit-coileb;i+=coileb)
			PokerTest(tabl,n,coileb,i);

		// sprawdzamy generator Mersenne Twister
		cmin=0xFFFFFFFF;cmax=0;
        // losujemy tablicê
		sr1=rdtsc();
		for(int i=0;i<n;i++)
			tabl[i]=MTrand();
		sr2=rdtsc();
		// znajdujemy maksimum i minimum tablicy
		for(int i=0;i<n;i++){
			if(tabl[i]<cmin)
				cmin=tabl[i];
			else if(tabl[i]>cmax)
				cmax=tabl[i];
		}
		printf("\nTESTOWANIE MTRAND: min=%u, max=%u\n",cmin,cmax);
		printf("Czas wykonania 1 mtrand %llu cykli\n",(sr2-sr1)/n);
		coileb=4;
		#ifdef _MSC_VER
        _BitScanReverse(&index, cmax);
        #else
        index = __bsrd(cmax);
        #endif
		maxbit=index+1;
		for(int i=0;i<=maxbit-coileb;i+=coileb)
			PokerTest(tabl,n,coileb,i);
// sprawdzamy teraz czy dostępna jest funkcja rdrand
        printf("\nSprawdzanie dostepnosci rdrand: ");
        int cpui[4];
        #ifdef _MSC_VER
        __cpuidex(cpui, 1, 0);
        #else
        __cpuid(1,cpui[0],cpui[1],cpui[2],cpui[3]);
        #endif
        index=cpui[2];
        if(index & 0x4000000){
            printf("dostepne");
            cmin=0xFFFFFFFF;cmax=0;
            // losujemy tablicę
            sr1=rdtsc();
            //for(int i=0;i<n;i++)
                //_rdrand32_step(&(tabl[i]));
            sr2=rdtsc();
            // znajdujemy maksimum i minimum tablicy
            for(int i=0;i<n;i++){
                if(tabl[i]<cmin)
                    cmin=tabl[i];
                else if(tabl[i]>cmax)
                    cmax=tabl[i];
            }
            printf("\nTESTOWANIE RDRAND: min=%u, max=%u\n",cmin,cmax);
            printf("Czas wykonania 1 rdrand %llu cykli\n",(sr2-sr1)/n);
            coileb=4;
            #ifdef _MSC_VER
            _BitScanReverse(&index, cmax);
            #else
            index = __bsrd(cmax);
            #endif
            maxbit=index+1;
            for(int i=0;i<=maxbit-coileb;i+=coileb)
                PokerTest(tabl,n,coileb,i);
        } else {
            printf("niedostepne\n");
        }
        // usuwamy tablicę
        free(tabl);
	}
	printf("\nKoniec");
    char znak;
    znak = getchar();
    return 0;
}

// funkcja wykonuje test pokerowy i wyœwietla jego wynik
// tab - tablica liczb losowych, n - rozmiar tablicy, bits - ilość bitów sprawdzanych, shift - przesunięcie bitów
// sprawdzane będą bity od shift do shift+bits-1 z każdego elementu tablicy tab
void PokerTest(unsigned* tab,unsigned n,unsigned bits,unsigned shift){
    unsigned powerOfTwo = 1 << bits;

	unsigned mask = powerOfTwo - 1;

	unsigned long long numbers[powerOfTwo];

	// unsigned long long* numbers = (unsigned long long*)malloc(powerOfTwo);

	memset(&numbers, 0, powerOfTwo * sizeof(unsigned long long));

	for (unsigned i = 0; i < n; i++)
	{
		numbers[(tab[i] >> shift) & mask]++;
	}

	double sum = 0;
	double y = ((double)n) / powerOfTwo;

	double x;

	for (unsigned i = 0; i < powerOfTwo; i++)
	{
		x = numbers[i] - y;
		sum += x * x;
	}

	sum /= y;

	printf(sum < chi2u[bits - 1] && sum > chi2d[bits - 1] ? "Zaliczone" : "Nie zaliczone");
	printf("bity = %2u - %2u\n", shift, shift + bits);
}
