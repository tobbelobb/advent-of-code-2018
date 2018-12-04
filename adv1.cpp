#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric> // std::accumulate has been moved to <numeric> in later c++...
#include <set>

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

    std::set<int> found_freqs = {0};
    int current_freq = 0;
    bool found = false;

    while(!found)
    {
        for(int i = 0; i < numbers.size(); ++i)
        {
            current_freq += numbers[i];
            if(found_freqs.find(current_freq) != found_freqs.end())
            {
                std::cout << "The first frequency occuring twice is: " << current_freq << std::endl;
                found = true;
                break;
            }
            found_freqs.insert(current_freq);
        }
    }

  return 0;
}
