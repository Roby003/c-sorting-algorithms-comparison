#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <cmath>
using namespace std;
ifstream in("date.in");
ofstream out("timpi.out");
void rand_generator2(int v[], long long nr_max, long long nr)
{
    srand(time(NULL));
    for (int i = 0; i < nr; i++)
        v[i] = rand() % nr_max;
}
int aux_v[100000000];
void radix_sort(int v[], int base, long long n)
{
    int init_base = base;
    int count[base];
    for (int i = 0; i < base; i++)
        count[i] = 0;
    int max_size = 0;
    for (int i = 0; i < n; i++)
    {
        int aux = v[i], maxi = 0;
        while (aux)
        {
            maxi++;
            aux /= base;
        }
        max_size = max(max_size, maxi);
    }
    for (int k = 0; k < max_size; k++)
    {
        for (int i = 0; i < init_base; i++)
            count[i] = 0;
        for (int i = 0; i < n; i++)
            count[(v[i] % base) / (base / init_base)]++;

        for (int i = 1; i < init_base; i++)
        {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--)
        {
            int aux = --(count[(v[i] % base) / (base / init_base)]);

            aux_v[aux] = v[i];
        }
        for (int i = 0; i < n; i++)
            v[i] = aux_v[i];

        base *= init_base;
    }
}
void merge(int v[], int low, int mid, int high, long long n)
{
    int aux = high - low + 1, i = low, k = low, j = mid + 1;

    while (i <= mid && j <= high)
    {
        if (v[i] < v[j])
        {
            aux_v[k] = v[i];
            k++;
            i++;
        }
        else
        {
            aux_v[k] = v[j];
            j++;
            k++;
        }
    }

    while (i <= mid)
    {
        aux_v[k++] = v[i++];
    }
    while (j <= high)
        aux_v[k++] = v[j++];

    for (int i = low; i <= high; i++)
        v[i] = aux_v[i];
}

void merge_sort(int v[], int low, int high, int n)
{
    int mid;
    if (low < high)
    {
        mid = (low + high) / 2;
        merge_sort(v, low, mid, n);
        merge_sort(v, mid + 1, high, n);

        merge(v, low, mid, high, n);
    }
}
bool test_sort(int v[], long long n)
{
    for (int i = 1; i < n; i++)
    {
        if (v[i] < v[i - 1])
            return 0;
    }
    return 1;
}
int count[100000000];
void count_sort(int v[], long long n)
{
    int maxi = 0;

    for (int i = 0; i < n; i++)
        maxi = max(maxi, v[i]);
    for (int i = 0; i < maxi + 1; i++)
        count[i] = 0;

    for (int i = 0; i < n; i++)
    {

        count[v[i]]++;
    }
    for (int i = 1; i <= maxi; i++)
        count[i] += count[i - 1];

    for (int i = 0; i < n; i++)
    {
        aux_v[--count[v[i]]] = v[i];
    }
    for (int i = 0; i < n; i++)
        v[i] = aux_v[i];
}

void shell_sort(int v[], long long n)
{
    for (int gap = n / 2; gap > 0; gap = gap / 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = v[i];
            int j;
            for (j = i; j >= gap && v[j - gap] > temp; j -= gap)
                v[j] = v[j - gap];
            v[j] = temp;
        }
    }
}
void bubble_sort(int v[], long long n)
{
    int ok;
    do
    {
        ok = 0;
        for (int i = 1; i < n; i++)
            if (v[i] < v[i - 1])
            {
                swap(v[i], v[i - 1]);
                ok = 1;
            }
    } while (ok == 1);
}

void quicksort(int v[], long long low, long long high)
{
    long long i = low, j = high;
    long long pivot = v[(low + high) / 2];
    while (i <= j)
    {
        while (v[i] < pivot)
            i++;
        while (v[j] > pivot)
            j--;
        if (i <= j)
        {
            swap(v[i], v[j]);
            i++;
            j--;
        }
    }
    if (low < j)
        quicksort(v, low, j);
    if (i < high)
        quicksort(v, i, high);
}
long long nr_max = 10000000, n = 100000000;
int v[100000000];
int nrTeste;
int main()
{
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;

    int base=2<<16;
    in>>nrTeste;
    const int b=nrTeste;
    
    for(int i=1;i<=b;i++)
    {  
        out<<i<<"::\n";
        in>>nr_max>>n;
        out<<nr_max<<" "<<n<<endl;
    /// **********radix****************
    rand_generator2(v,nr_max,n);
    auto t1 = high_resolution_clock::now();
    radix_sort(v, base, n);
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    out<<"radix:"<<test_sort(v,n)<<"_"<< ms_double.count() << "ms\n";
    
    
    ///**************count*****************
     rand_generator2(v,nr_max,n);
    t1 = high_resolution_clock::now();
    count_sort(v,n);
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
    out<<"count: "<<test_sort(v,n)<<"_"<< ms_double.count() << "ms\n";

    ///*************merge**********
    rand_generator2(v,nr_max,n);
    t1 = high_resolution_clock::now();
    merge_sort(v,0,n,n);
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
    out<<"merge: "<<test_sort(v,n)<<"_"<< ms_double.count() << "ms\n";

    ///*********shell*************
    rand_generator2(v,nr_max,n);
    t1 = high_resolution_clock::now();
    shell_sort(v,n);
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
    out<<"shell: "<<test_sort(v,n)<<"_"<< ms_double.count() << "ms\n";

    ///********quick***********
    rand_generator2(v,nr_max,n);
    t1 = high_resolution_clock::now();
    quicksort(v,0,n-1);
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
    out<<"quick: "<<test_sort(v,n)<<"_"<< ms_double.count() << "ms\n";

    }
    return 0;
}