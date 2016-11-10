#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

class solution {
  public:
    std::vector<size_t> jump(const std::vector<int> & nums) {
        std::vector<std::vector<size_t>> cands = jumpFunc(nums, std::vector<size_t>{0});
        std::cout << "All possible paths:\n";
        for (size_t i = 0; i < cands.size(); i++) {
            std::copy(cands[i].begin(), cands[i].end(), std::ostream_iterator<size_t>(std::cout, " "));
            std::cout << std::endl;
        }
        auto it = std::min_element(cands.begin(), cands.end(),
                                   [](const std::vector<size_t> & p1,const std::vector<size_t> & p2){
                                       return p1.size() < p2.size();
                                   });
        std::cout << "Shortest path:\n";
        std::copy(it->begin(), it->end(), std::ostream_iterator<size_t>(std::cout, " "));
        std::cout << std::endl;
        return *it;
    }

  private:
    std::vector<std::vector<size_t>> jumpFunc(const std::vector<int> & nums, const std::vector<size_t> & curr) {
        std::vector<std::vector<size_t>> result;
        if (curr.back() == nums.size()-1)
            result.push_back(curr);
        else {
            std::vector<size_t> next;
            for (size_t i = 1; i <= nums[curr.back()]; i++)
                next.push_back(curr.back()+i);
           
            for (auto nx : next) {
                auto cpy = curr;
                cpy.push_back(nx);
                auto temp = jumpFunc(nums, cpy);
                for (auto tmp : temp)
                    result.push_back(tmp);
            }
        }
        return result;
    }
};

int main() {
    std::vector<int> nums{2,3,1,1,4};

    solution soln;
    auto minJumps = soln.jump(nums);
    std::cout << "The minimum number of jumps taken to jump to the last is:\n"
              << minJumps.size()-1 << std::endl;
}
