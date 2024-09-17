#include "PmergeMe.hpp"

std::vector<int> stepFiveVec(std::vector<std::pair<int, int> >& pairs)
{
    std::vector<int> S;
    for (unsigned long i = 0; i < pairs.size(); i++)
    {
        int target = pairs[i].second;
        std::vector<int>::iterator it = std::lower_bound(S.begin(), S.end(), target);
        S.insert(it, target);
    }
    for (unsigned long i = 0; i < pairs.size(); i++)
    {
        int target = pairs[i].first;
        std::vector<int>::iterator it = std::upper_bound(S.begin(), S.end(), target);
        S.insert(it, target);
    }
    return S;
}



bool compareSecond(const std::pair<int, int>& x, const std::pair<int, int>& y) 
{
    return x.second < y.second;
}

std::vector<std::pair<int, int> > stepFourVec(std::vector<std::pair<int, int> > a)
{
    std::sort(a.begin(), a.end(), compareSecond);
    return (a);
}

bool pairCompare(const std::pair<int, int>& a, const std::pair<int, int>& b) 
{
    return a.first < b.first;
}

std::vector<std::pair<int, int> > mergeVector(std::vector<std::pair<int, int> > a, std::vector<std::pair<int, int> > b) 
{
    std::vector<std::pair<int, int> > c;
    while (!a.empty() && !b.empty()) 
	{
        if (pairCompare(a[0], b[0])) 
		{
            c.push_back(a[0]);
            a.erase(a.begin());
        } 
		else 
		{
            c.push_back(b[0]);
            b.erase(b.begin());
        }
    }
    while (!a.empty()) 
	{
        c.push_back(a[0]);
        a.erase(a.begin());
    }
    while (!b.empty()) 
	{
        c.push_back(b[0]);
        b.erase(b.begin());
    }
    return c;
}

std::vector<std::pair<int, int> > stepThreeVec(std::vector<std::pair<int, int> > a) 
{
    if (a.size() == 1)
        return a;
    
    std::vector<std::pair<int, int> > array1(a.begin(), a.begin() + a.size() / 2);
    std::vector<std::pair<int, int> > array2(a.begin() + a.size() / 2, a.end());
    
    array1 = stepThreeVec(array1);
    array2 = stepThreeVec(array2);
    
    return mergeVector(array1, array2);
}


void   stepTwoVec(std::vector<std::pair<int, int> > &pairs)
{
    int temp;

	for (size_t i = 0; i < pairs.size(); i++)
	{
		if (pairs[i].second < pairs[i].first)
		{
			temp = pairs[i].second;
			pairs[i].second = pairs[i].first;
			pairs[i].first = temp;
		}
	}
}


std::vector<std::pair<int, int> >stepOneVec(std::vector<int> &vec)
{
    std::vector<std::pair<int, int> > pair;
	
	for (size_t i = 0; i < vec.size(); i += 2)
    {
		if (i + 1 < vec.size())
			pair.push_back(std::pair<int, int>(vec[i], vec[i + 1]));
		else
			pair.push_back(std::pair<int, int>(vec[i], -1));
	}
	return (pair);
}


void    groupVec(std::vector<int> &vec)
{
    bool flag = true;

    std::vector<std::pair<int, int> > pairs;
	if (vec.size() == 1)
		return ;
    if (vec.size() % 2 != 0)
        flag = false;
	pairs = stepOneVec(vec);
    stepTwoVec(pairs);
	pairs = stepThreeVec(pairs);
    pairs = stepFourVec(pairs);
    vec = stepFiveVec(pairs);
    if (flag == false)
        vec.erase(vec.begin());
}

/////Vector Implementaciones abajo | Deque Implementaciones debajo////

std::deque<int> stepFiveDeq(std::deque<std::pair<int, int> >& pairs)
{
    std::deque<int> S;
    for (unsigned long i = 0; i < pairs.size(); i++)
    {
        int target = pairs[i].second;
        std::deque<int>::iterator it = std::lower_bound(S.begin(), S.end(), target);
        S.insert(it, target);
    }
    for (unsigned long i = 0; i < pairs.size(); i++)
    {
        int target = pairs[i].first;
        std::deque<int>::iterator it = std::upper_bound(S.begin(), S.end(), target);
        S.insert(it, target);
    }
    return S;
}


std::deque<std::pair<int, int> > stepFourDeq(std::deque<std::pair<int, int> > a)
{
    std::sort(a.begin(), a.end(), compareSecond);
    return (a);
}

std::deque<std::pair<int, int> > mergeDeq(std::deque<std::pair<int, int> > a, std::deque<std::pair<int, int> > b) 
{
    std::deque<std::pair<int, int> > c;
    while (!a.empty() && !b.empty()) 
	{
        if (pairCompare(a[0], b[0])) 
		{
            c.push_back(a[0]);
            a.erase(a.begin());
        } 
		else 
		{
            c.push_back(b[0]);
            b.erase(b.begin());
        }
    }
    while (!a.empty()) 
	{
        c.push_back(a[0]);
        a.erase(a.begin());
    }
    while (!b.empty()) 
	{
        c.push_back(b[0]);
        b.erase(b.begin());
    }
    return c;
}

std::deque<std::pair<int, int> > stepThreeDeq(std::deque<std::pair<int, int> > a) 
{
    if (a.size() == 1)
        return a;
    
    std::deque<std::pair<int, int> > array1(a.begin(), a.begin() + a.size() / 2);
    std::deque<std::pair<int, int> > array2(a.begin() + a.size() / 2, a.end());
    
    array1 = stepThreeDeq(array1);
    array2 = stepThreeDeq(array2);
    
    return mergeDeq(array1, array2);
}


void   stepTwoDeq(std::deque<std::pair<int, int> > &pairs)
{
    int temp;

	for (size_t i = 0; i < pairs.size(); i++)
	{
		if (pairs[i].second < pairs[i].first)
		{
			temp = pairs[i].second;
			pairs[i].second = pairs[i].first;
			pairs[i].first = temp;
		}
	}
}


std::deque<std::pair<int, int> >stepOneDeq(std::deque<int> &deq)
{
    std::deque<std::pair<int, int> > pair;
	
	for (size_t i = 0; i < deq.size(); i += 2)
    {
		if (i + 1 < deq.size())
			pair.push_back(std::pair<int, int>(deq[i], deq[i + 1]));
		else
			pair.push_back(std::pair<int, int>(deq[i], -1));
	}
	return (pair);
}


void    groupDeq(std::deque<int> &deq)
{
    bool flag = true;
    std::deque<std::pair<int, int> > pairs;

	if (deq.size() == 1)
		return ;
    if (deq.size() % 2 != 0)
        flag = false;
	pairs = stepOneDeq(deq);
    stepTwoDeq(pairs);
	pairs = stepThreeDeq(pairs);
    pairs = stepFourDeq(pairs);
    deq = stepFiveDeq(pairs);
    if (flag == false)
        deq.erase(deq.begin());
}