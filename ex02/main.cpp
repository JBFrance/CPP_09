#include "PmergeMe.hpp"

void    print_deq(std::deque<int> deq, int n)
{
    int len = deq.size();
    switch(n)
    {
        case 0:
        std::cout << "Before ";
        break ;
        case 1:
        std::cout << "After ";
    }
    for (int i = 0; i < len; i++)
        std::cout << deq[i] << " ";
    std::cout << "\n";
}

void    print_vec(std::vector<int> vec, int n)
{
    int len = vec.size();
    switch(n)
    {
        case 0:
        std::cout << "Before ";
        break ;
        case 1:
        std::cout << "After ";
    }
    for (int i = 0; i < len; i++)
        std::cout << vec[i] << " ";
    std::cout << "\n";
}

bool    check_duplicates(std::vector<int> vec)
{
    int len = vec.size();
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (vec[i] == vec[j])
                return false;
        }
    }
    return true;
}

void    store_data(std::vector<int> &vec, std::deque<int> &deq, int argc, char **argv)
{
    int num_elem;
    for (int i = 1; i < argc; i++) 
    {
        for (int j = 0; argv[i][j] != '\0'; j++) 
        {
            if (!(isdigit(argv[i][j]) || (j == 0 && (argv[i][j] == '-' || argv[i][j] == '+')))) 
            {
                std::cout << "Error: non-numeric character" << std::endl;
                exit(1);
            }
        }
        if (std::atoi(argv[i]) < 0) 
        {
            std::cout << "Error: not a positive number" << std::endl;
            exit(1);
        }
        vec.push_back(std::atoi(argv[i]));
        deq.push_back(std::atoi(argv[i]));
        num_elem = i;
    }
    if (check_duplicates(vec) == false)
    {
        std::cout << "Error: duplicates detected" << std::endl;
        exit(1);
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Invalid number of arguments" << std::endl;
        return (1);
    }
    std::vector<int> vec;
    std::deque<int> deq;
    store_data(vec, deq, argc, argv);

    clock_t vstart = clock();
    clock_t vend = clock();
    double vec_time = static_cast<double>(vend - vstart) * 1000000 / CLOCKS_PER_SEC;
    std::cout << "__________" << std::endl;
    print_vec(vec, 0);
    groupVec(vec);
    print_vec(vec, 1);
    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector<int> : " << vec_time << "us" << std::endl;

    clock_t dstart = clock();
    clock_t dend = clock();
    double dec_time = static_cast<double>(dend - dstart) * 1000000 / CLOCKS_PER_SEC;
    std::cout << "__________" << std::endl;
    print_deq(deq, 0);
    groupDeq(deq);
    print_deq(deq, 1);
    std::cout << "Time to process a range of " << deq.size() << " elements with std::deque<int> : " << dec_time << "us" << std::endl;
    return (0);
}