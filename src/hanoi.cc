// AUTHOR: Javier Garcia Santana
// DATE: 10/2/2023
// EMAIL: javier.santana@tprs.stud.vu.lt
// VERSION: 2.0
// SUBJECT: Artificial Intelligence
// EXCERCISE Nº: 1
// COMMENTS:
// 1. Calculate the total number of moves required i.e. "pow(2, n)
//    - 1" here n is number of disks.
// 2. If number of disks (i.e. n) is even then interchange destination 
//    pole and auxiliary pole.
// 3. for i = 1 to total number of moves:
//      if i%3 == 1:
//     legal movement of top disk between source pole and 
//         destination pole
//      if i%3 == 2:
//     legal movement top disk between source pole and 
//         auxiliary pole    
//      if i%3 == 0:
//         legal movement top disk between auxiliary pole 
//         and destination pole
//
// COMPILATION: make

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>

using namespace std::chrono;


void printRods(const std::vector<std::vector<char> > rods, const char rod_names[], const int kNdisks) {
  for (int i = 0; i < rods.size(); ++i) {
    std::cout << rod_names[i] << "=(";
    for (int j = 0; j < rods[i].size(); ++j) {
      std::cout << rods[i][j] - '0';
      if (j != rods[i].size() - 1){
        std::cout << " ";
      }
    }
    std::cout << ")";
    if (!rods[i].empty()) {
      for (int k = 0; k < ((kNdisks + (kNdisks - 1)) + 1) - (rods[i].size() + (rods[i].size() - 1)); ++k) {
        std::cout << " ";
      }
    } else {
      for (int k = 0; k < (kNdisks + (kNdisks - 1) + 1); ++k) {
        std::cout << " ";
      }
    }
  }
  std::cout << std::endl;
}

void moveDisk(std::vector<std::vector<char> >& rods, int a, int b, const char rod_names[]) {
  if (rods[b].empty() || (!rods[a].empty() && rods[a][rods[a].size() - 1] < rods[b][rods[b].size() - 1])) {

    rods[b].push_back(rods[a][rods[a].size() - 1]);
    std::cout << "Move disk " << rods[a][rods[a].size() - 1] - '0' << " from " << rod_names[a] << " to " 
    << rod_names[b] << ".      ";

    rods[a].erase(rods[a].end() - 1);
    return;
  } else {
    moveDisk(rods, b, a, rod_names);
  }
}

int main(int argc, char* argv[]) {

  auto start = high_resolution_clock::now();

  int n_of_disks = std::stoi(argv[1]);
  if (n_of_disks > 0 && n_of_disks < 11) {
    char rod_names[] = {'A', 'B', 'C'};
    std::vector<std::vector<char> > rods(3);
    for (int i = n_of_disks; i > 0; --i) {
      rods[0].push_back(i + '0');
    }
    int n_moves = (pow(2, n_of_disks)) - 1;

    if (n_of_disks % 2 == 0) {
      swap(rods[1], rods[2]);
      std::swap(rod_names[1], rod_names[2]);
    }

    std::cout << "   Initial State:                  ";
    printRods(rods, rod_names, n_of_disks);
    std::cout << std::endl;

    for (int i = 1; i <= n_moves; ++i) {
      if (i < 10) {
        std::cout << "   ";
      } else if (i < 100) {
        std::cout << "  ";
      } else if (i < 1000) {
        std::cout << " ";
      }
      std::cout << i << ".";

      switch (i % 3) {
        case 1:
          moveDisk(rods, 0, 2, rod_names);
          printRods(rods, rod_names, n_of_disks);
          break;

        case 2:
          moveDisk(rods, 0, 1, rod_names);
          printRods(rods, rod_names, n_of_disks);
          break;

        case 0:
          moveDisk(rods, 1, 2, rod_names);
          printRods(rods, rod_names, n_of_disks);
          break;
      
        default:
          break;
      }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time elapsed: " << duration.count() << " microseconds" << std::endl;
  } else {
    std::cerr << "ERROR: OUT OF RANGE" << std::endl;
  }
  return 0;
}