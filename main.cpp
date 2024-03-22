#include <iostream>
#include <ctime>
#include <cmath>
#include<vector>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<fstream>

using namespace std;

void rand_tab(int *tab, int n)
{
    //int tab[n];
    srand( time( NULL ) );

    for (int i=0; i<n; i++)
    {
        tab[i] = rand()%101;
    }
}

void show(int *tab, int n)
{
    for (int i=0; i<n; i++)
    {
        cout<<tab[i]<<endl;
    }
}

void insertion_sort(std::vector<int>& tab)
{
    int i = 1;
    while(i<tab.size())
    {
        int j=i;
        while(j>0 && tab[j-1] > tab[j])
        {
            swap(tab[j-1], tab[j]);
            j--;
        }
        i++;
    }
}

//Sedgewick: 1, 8, 23, 77, 281, 1073, …, 4^(k+1) + 3*2^(k) + 1
void shell_sort(std::vector<int>& tab) //  shellSort_z_przyrostami_Sedgewicka
{
    int n; 
    cin>>n;
    int k_tab[n];
    k_tab[0]=1;
    //cout<<k_tab[0]<<endl;
    int i=0;
    
    k_tab[1]=1;
    while(k_tab[i+1] < n)
    {
        if ((pow(4, i+1) + 3 * pow(2,i) + 1) >= n)
        {
            break;
        }
        
            k_tab[i+1] = pow(4, i+1) + 3 * pow(2,i) + 1;
            //cout<<k_tab[i+1]<<endl;

        i++;
    }


    int indeks = i;
   

    while (indeks >= 0)
    {
     int k = k_tab[indeks];
    //cout<<"indeks: "<<indeks<<endl;

    int i = 1;

    while(i<n)
    {
        int p=k;
        // int p=k[i];
        while(p<n)
        {
            int j=i;
            //cout<<tab[j+p-1]<<"test"<<endl;
            while(j>0 && tab[j-1] > tab[j+p-1])
            {
                if(j+p-1 <n)
                {
                    swap(tab[j-1], tab[j+p-1]);
                }
            j--;
            }

            p+=k;
            // p+=k[i];
        }
        i+=1;
    }
        indeks--;
    }
    
}

void selection_sort(std::vector<int>& tab)
{
    int n; 
    cin>>n;
    int mini=0;
    for(int i=0; i<n-1; i++)
    {
        mini=i;
        for(int j=i+1; j<n; j++)
        {
            if(tab[j] < tab[mini])
            {
                mini=j;
            }
            
        }
        swap(tab[mini], tab[i]);
    }
}

void Zbuduj_kopiec(std::vector<int>& tab, int n)
{
    for(int i = 1; i < n; i++)
    {
        int j = i; 
        int k = j / 2;
        int x = tab[i];
    
    while((k > 0) && (tab[k] < x))
    {
      tab[j] = tab[k];
      j = k; 
      k = j / 2;
    }
    tab[j] = x;
  }
}

void heap_sort(std::vector<int>& tab)
{
    int n;
    cin>>n;
    Zbuduj_kopiec(tab, n);

    for(int i = n; i > 0; i--)
  {
    if(i==n)
    {
        swap(tab[0], tab[i-1]);
    }
    else
    {
        swap(tab[0], tab[i]);
    }
    
    int j = 0; 
    int k = 1;
    int m;
    while(k < i)
    {
      if((k + 1 < i) && (tab[k + 1] > tab[k]))
        m = k + 1;
      else
        m = k;
      if(tab[m] <= tab[j]) break;
        swap(tab[j], tab[m]);
        j = m;
        k = j + j;
    }
  }


}

// Ip - indeks poczatkowy
// Ik - indeks koncowy
int QuickSort_podziel_skrajnie_lewy(std::vector<int>& tab, int ip, int ik)
{
    int pivot = tab[ip];

    int i=ip;
    int j=ik+1;

    while (i<j)
    {
        while(tab[++i] < pivot){continue;}
        while(pivot < tab[--j]){continue;}
            if(i < j)
		    {
                swap(tab[i],tab[j]);
            }
    }

    tab[ip] = tab[j]; tab[j] = pivot;
    return j;
}


void quick_sort_left_pivot(std::vector<int>& tab, int ip, int ik)
{   

    if(ip < ik)
    {
        int poprzedni_pivot = QuickSort_podziel_skrajnie_lewy(tab, ip, ik);
        quick_sort_left_pivot(tab, ip, poprzedni_pivot - 1);
        quick_sort_left_pivot(tab, poprzedni_pivot + 1, ik);
    }
}


void rand_pivot(std::vector<int>& tab, int ip, int ik)
{
    srand(time(0));
    int rand_pivot = ip + (rand() % (ik - ip+1));
    swap(tab[ip], tab[rand_pivot]);
}

int QuickSort_podziel_losowy(std::vector<int>& tab, int ip, int ik)
{
    rand_pivot(tab, ip, ik);

    int pivot = tab[ip];
    int i=ip;
    int j=ik+1;

    while (i<j)
    {
        while(tab[++i] < pivot){continue;}
        while(pivot < tab[--j]){continue;}
            if(i < j)
		    {
                swap(tab[i],tab[j]);
            }
    }

    tab[ip] = tab[j]; tab[j] = pivot;
    return j;
}


void quick_sort_random_pivot(std::vector<int>& tab, int ip, int ik)
{
    if(ip<ik)
    {
        int poprzedni_pivot = QuickSort_podziel_skrajnie_lewy(tab, ip, ik);
            quick_sort_random_pivot(tab, ip, poprzedni_pivot - 1);
            quick_sort_random_pivot(tab, poprzedni_pivot + 1, ik);
    }
        
}



void sort_using_algorithm(std::vector<int>& data, int algorithm) {
    std::cout << "\n\n\n---Sorting Algorithm: ";
    switch (algorithm)
    {
    case 1:
        std::cout << "Insertion sort---\n";
        insertion_sort(data);
        break;
    case 2:
        std::cout << "Shell sort---\n";
        shell_sort(data);
        break;
    case 3:
        std::cout << "Selection sort---\n";
        selection_sort(data);
        break;
    case 4:
        std::cout << "Heap sort---\n";
        heap_sort(data);
        break;
    case 5:
        std::cout << "Quick sort with left pivot---\n";
        quick_sort_left_pivot(data,0, data.size() - 1);
        break;
    case 6:
        std::cout << "Quick sort with random pivot---\n";
        quick_sort_random_pivot(data,0, data.size() - 1);
        break;
    default:
        std::cout << "There's no such thing, mate 0_0" << std::endl;
        break;
    }
}


int main(int argc, char *argv[]) {


//     if(argc != 3 || string(argv[1] != "--algorithm"))
//     {
//         return -1;
//     }

//     int algo = atoi(argv[1]);
//     int n;
//     std::cin >> n;

// int * tab;
//     tab = new int[n+1];

    // for(int i=0; i<n; i++)
    // {
    //     cin>>tab[i];
    // }

    // InsertionSort(tab, n);

    /*
    InsertSort - done
    SelectionSort - done
    HeapSort - done; ogarnąć
    ShelSort - done

    QuickSortv1 - done
    QuickSortv2 - done
    
    */
   // int n=10;
    //int * tab;
    //tab = new int[n+1];
//     rand_tab(tab, n);
//    show(tab, n);
//     cout<<"######"<<endl;
//     //InsertionSort(tab, n);
//     //SelectionSort(tab, n);
//     //QuickSort_skrajnie_lewy(tab, 0, n);
//     //QuickSort_losowy(tab, 0, n);
//     //HeapSort(tab, n);
    
//     shellSort_z_przyrostami_Sedgewicka(tab, n);

//    show(tab, n);


//     delete []tab;    
//     return 0;

if (argc != 2) {
        std::cerr << "Usage: make run INPUT = <file_name>\n";
        return 1;
    }

    // Open the file
    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Unable to open file " << argv[1] << "\n";
        return 1;
    }

    // Read the data from the file
    std::vector<int> data;
    int x,n; 
    while (file >> x) {
        data.push_back(x);
    }

    // Close the file
    file.close();
    
    std::cout << "\n\n---SELECT THE SORTING ALGORITHM---\n\n1. Insertion sort\n2. Shell sort\n3. Selection sort\n4. Heap sort\n5. Quick sort with left pivot\n6. Quick sort with random pivot\n\n";
    std::cin >> n;
    // Array before sorting
    std::cout << "\n\n----Array before----\n\n";
    for (const auto &elem : data) {
        std::cout << elem << " ";
    }

    // Sorting algorithm
    sort_using_algorithm(data, n);

    // Print the sorted data
    std::cout << "\n\n----Sorted data----\n\n";
    for (const auto &value : data) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    return 0;

}
