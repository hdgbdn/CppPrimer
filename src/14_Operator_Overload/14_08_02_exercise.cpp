#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

int main()
{
    vector<int> vi{1000, 2000, 3000, 4000, 5000};
    cout << count_if(vi.begin(), vi.end(),
                               std::bind(greater<int>(), placeholders::_1, 1024))
              << std::endl;

    vector<string> vs{"pooh", "pooh", "abc", "pooh"};
    cout << *find_if(vs.begin(), vs.end(),
                               bind(not_equal_to<string>(), placeholders::_1, "pooh"))
              << std::endl;

    transform(vi.begin(), vi.end(), vi.begin(),
                   bind(std::multiplies<int>(), placeholders::_1, 2));
    for (const auto &i : vi)
        cout << i << ' ';
    cout << endl;
    return 0;
}