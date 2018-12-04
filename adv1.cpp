#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric> // std::accumulate has been moved to <numeric> in later c++...
#include <unordered_set>

int main (int argc, char** argv) {
    if(argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 0;
    }

    std::ifstream is(argv[1]);
    std::istream_iterator<int> start(is), end; // Default-constructed istream_iterator is end-of-stream iterator
    std::vector<int> numbers(start, end); // Reads file line by line until
    const long int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "Sum: " << sum << std::endl;

    std::unordered_set<int> found_freqs = {0};
    int current_freq = 0;
    bool found = false;

    while(!found)
    {
        for(int i = 0; i < numbers.size(); ++i)
        {
            current_freq += numbers[i];
            // Insert also does a find and returns a useful value
            // Started looking for this by doing
            // perf record -g
            // followed by
            // perf report --sort=dso,comm
            // ... and realizing that comparison was called a lot from two functions: insert and find
            auto res = found_freqs.insert(current_freq);
            if (res.second == false)
            {
                std::cout << "The first frequency occuring twice is: " << current_freq << std::endl;
                found = true;
                break;
            }
        }
    }

  return 0;
}
